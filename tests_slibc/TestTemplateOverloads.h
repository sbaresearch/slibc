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
#ifndef TESTMSCANF_S_H
#define TESTMSCANF_S_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>


class TestTemplateOverloads : public CPPUNIT_NS :: TestFixture
{
public:
	void setUp ();
	void tearDown ();

protected:
	void test_strcpy_s();
	void test_strncpy_s();
	void test_strcat_s();
	void test_strncat_s();
	void test_sprintf_s();
	void test_snprintf_s();

private:
	CPPUNIT_TEST_SUITE (TestTemplateOverloads);

	CPPUNIT_TEST(test_strcpy_s);
	CPPUNIT_TEST(test_strncpy_s);
	CPPUNIT_TEST(test_strcat_s);
	CPPUNIT_TEST(test_strncat_s);
	CPPUNIT_TEST(test_sprintf_s);
	CPPUNIT_TEST(test_snprintf_s);

	CPPUNIT_TEST_SUITE_END ();
};

#endif
