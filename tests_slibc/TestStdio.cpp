/* Copyright (C) 2011-2012 SBA Research gGmbh

   This file is part of the Slibc Library.

   The Slibc Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The Slibc library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the Slibc Library; if not, see
   <http://www.gnu.org/licenses/>.  
*/
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define SLIBC_WANT_MKTEMP
#include "slibc/string.h"
#include "slibc/stdio.h"
#include "TestStdio.h"
#include "RuntimeConstraintViolation.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <iostream>
#include <fstream>

using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION (TestStdio);

     
void listFilesInDir(const string &dirname, vector<string> &files)
{
	DIR *dp;
	struct dirent *ep;
     
	dp = opendir (dirname.c_str());
	if (dp != NULL)
	{
		while ((ep = readdir (dp)))
			files.push_back(ep->d_name);
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");
}
	 
void TestStdio::setUp()
{
	set_constraint_handler_s(cpp_constraint_handler_s);
}

void TestStdio::tearDown()
{
}

void TestStdio :: test_slibc_set_get_temp_dir (void)
{
	char tooLong[PATH_MAX];
	memset(tooLong, 't', sizeof(tooLong));
	char tmpName[PATH_MAX];

	CPPUNIT_ASSERT_THROW(slibc_set_tmp_dir(NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(slibc_set_tmp_dir(tooLong), RuntimeConstraintViolation);

	CPPUNIT_ASSERT_THROW(slibc_get_tmp_dir(NULL, PATH_MAX), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(slibc_get_tmp_dir(tmpName, 0), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(slibc_get_tmp_dir(tmpName, RSIZE_MAX+1), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(slibc_get_tmp_dir(tmpName, 1), RuntimeConstraintViolation);


	errno_t ret = slibc_get_tmp_dir(tmpName, sizeof(tmpName));
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_EQUAL(0, strcmp(tmpName, "/tmp/"));


	ret = slibc_set_tmp_dir("/tmp/my");
	CPPUNIT_ASSERT_EQUAL(0, ret);

	ret = slibc_get_tmp_dir(tmpName, sizeof(tmpName));
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_EQUAL(string("/tmp/my/"), string(tmpName)); 
	
	slibc_set_tmp_dir("/tmp/");
}

// void TestStdio :: test_slibc_tmp_functions(void)
// {

// }


void TestStdio :: test_tmpfile_s (void)
{
	CPPUNIT_ASSERT_THROW(tmpfile_s(NULL), RuntimeConstraintViolation);
	
	FILE *tmp = NULL;
	
	vector<string> filesBefore;
	listFilesInDir("/tmp/", filesBefore);

	int res = tmpfile_s(&tmp);
	
	CPPUNIT_ASSERT_EQUAL(0, res);
	CPPUNIT_ASSERT_EQUAL(false, tmp ==	NULL);

	// make sure we can write
	int ret = fprintf(tmp, "%s", "test\n");
	CPPUNIT_ASSERT_EQUAL(5, ret);

	//make sure it gets deleted again
	fclose(tmp);
	vector<string> filesAfter;
	listFilesInDir("/tmp/", filesAfter);
	CPPUNIT_ASSERT_EQUAL(filesAfter.size(), filesBefore.size());
}

#define SLIBC_TMP_DIR "/tmp/slibc_tmp_dir"

void TestStdio :: test_tmpnam_s (void)
{
	char s[L_tmpnam_s + sizeof(SLIBC_TMP_DIR)];
	rsize_t maxsize = sizeof(s);

	CPPUNIT_ASSERT_THROW(tmpnam_s(NULL,maxsize), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(tmpnam_s(s,RSIZE_MAX+1), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(tmpnam_s(s, 0), RuntimeConstraintViolation);
	// we assume that 1 is small than L_tmpnam_s
	CPPUNIT_ASSERT_THROW(tmpnam_s(s, 1), RuntimeConstraintViolation);

	errno_t res = tmpnam_s(s, maxsize);
	CPPUNIT_ASSERT_EQUAL(0, res);
	CPPUNIT_ASSERT(string(s).find("/tmp/") == 0);

	res = tmpnam_s(s, maxsize);
	CPPUNIT_ASSERT_EQUAL(0, res);
	CPPUNIT_ASSERT(string(s).find("/tmp/") == 0);

	(void) mkdir(SLIBC_TMP_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	res = slibc_set_tmp_dir(SLIBC_TMP_DIR);
	CPPUNIT_ASSERT_EQUAL(0, res);

	res = tmpnam_s(s, maxsize);
	CPPUNIT_ASSERT_EQUAL(0, res);
	CPPUNIT_ASSERT(string(s).find(SLIBC_TMP_DIR) == 0);

	// set it back
	res = slibc_set_tmp_dir("/tmp");
	CPPUNIT_ASSERT_EQUAL(0, res);

	remove(SLIBC_TMP_DIR);
}

void TestStdio :: test_mkstemp_s (void)
{
	char temp[] = "/tmp/testXXXXXX";
	int sizeInChars = strlen(temp);
	int fd = 0;


	CPPUNIT_ASSERT_THROW(mkstemp_s(NULL, &fd, sizeInChars), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(mkstemp_s(temp, &fd, sizeInChars-1), RuntimeConstraintViolation);
	strcpy(temp,"/tmp/testXXXXX");
	CPPUNIT_ASSERT_THROW(mkstemp_s(temp, &fd, sizeInChars), RuntimeConstraintViolation);

	strcpy(temp,"/tmp/testXXXXXX");
	int res = mkstemp_s(temp, &fd, sizeInChars);
	CPPUNIT_ASSERT_EQUAL(true, res == 0);
	CPPUNIT_ASSERT_EQUAL(true, fd != -1);
	remove(temp);
}

void TestStdio :: test_mktemp_s (void)
{
	char temp[] = "/tmp/testXXXXXX";
	int sizeInChars = strlen(temp);
	int fd = 0;


	CPPUNIT_ASSERT_THROW(mktemp_s(NULL, sizeInChars), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(mktemp_s(temp, sizeInChars-1), RuntimeConstraintViolation);
	strcpy(temp,"/tmp/testXXXXX");
	CPPUNIT_ASSERT_THROW(mktemp_s(temp, sizeInChars), RuntimeConstraintViolation);

	strcpy(temp,"/tmp/testXXXXXX");
	int res = mktemp_s(temp, sizeInChars);
	CPPUNIT_ASSERT_EQUAL(true, res == 0);
	CPPUNIT_ASSERT_EQUAL(true, fd != -1);
}
