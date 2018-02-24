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
#include "slibc/time.h"

#include <iostream>
#include <sstream>
#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "TestTime.h"
#include "RuntimeConstraintViolation.h"



using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION (TestTime);

void TestTime :: setUp (void)
{
	// SetUp your objects
	set_constraint_handler_s(cpp_constraint_handler_s);
}

void TestTime :: tearDown (void) 
{
	// Delete your objects
	
}

void TestTime :: test_asctime_s (void)
{
	struct tm t;
	struct tm *time = &t;
	time->tm_sec = 1;
	time->tm_min = 1;
	time->tm_hour = 1;
	time->tm_mday = 1;
	time->tm_mon = 1;
	time->tm_year = 20;
	time->tm_wday = 1;
	time->tm_yday = 1;
	time->tm_isdst = 0;

	char date[26];
	rsize_t maxsize = 26;
	char datecompare[] = "Mon Feb  1 01:01:01 1920\n\0";
	
	CPPUNIT_ASSERT_THROW(asctime_s(NULL, maxsize, time), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(asctime_s(date, maxsize, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(asctime_s(date, RSIZE_MAX+1, time), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(asctime_s(date, 25, time), RuntimeConstraintViolation);
		
	asctime_s(date, maxsize, time);
	CPPUNIT_ASSERT_EQUAL(strcmp(date,datecompare),0);
}

void TestTime :: test_ctime_s (void)
{
	struct tm t;
	struct tm *time = &t;
	time->tm_sec = 1;
	time->tm_min = 1;
	time->tm_hour = 1;
	time->tm_mday = 1;
	time->tm_mon = 1;
	time->tm_year = 20;
	time->tm_wday = 1;
	time->tm_yday = 1;
	time->tm_isdst = 0;
	
	time_t curtimer = mktime(time);
	time_t *timer = &curtimer;
	char date[26];
	rsize_t maxsize = 26;
	char datecompare[] = "Sun Feb  1 01:01:01 1920\n";

	CPPUNIT_ASSERT_THROW(ctime_s(NULL, maxsize, timer), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(ctime_s(date, maxsize, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(ctime_s(date, RSIZE_MAX+1, timer), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(ctime_s(date, 25, timer), RuntimeConstraintViolation);

	ctime_s(date, maxsize, timer);
	CPPUNIT_ASSERT_EQUAL(strcmp(date,datecompare),0);
}

void TestTime :: test_gmtime_s (void)
{
	struct tm a_time_bd;
	a_time_bd.tm_sec = 1;
	a_time_bd.tm_min = 1;
	a_time_bd.tm_hour = 1;
	a_time_bd.tm_mday = 1;
	a_time_bd.tm_mon = 1;
	a_time_bd.tm_year = 20;
	a_time_bd.tm_wday = 1;
	a_time_bd.tm_yday = 1;
	a_time_bd.tm_isdst = 0;
	
	time_t a_time = mktime(&a_time_bd);
	
	struct tm convtime;

	CPPUNIT_ASSERT_THROW(gmtime_s(NULL, &convtime), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(gmtime_s(&a_time, NULL), RuntimeConstraintViolation);
	gmtime_s(&a_time, &convtime);
	
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_sec, convtime.tm_sec);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_min, convtime.tm_min);
	//Because of Conversion to UTC, must be corrected depending on offset to UTC
	//CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_hour+2, convtime.tm_hour);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_mday, convtime.tm_mday);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_mon, convtime.tm_mon);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_year, convtime.tm_year);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_wday, convtime.tm_wday);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_yday, convtime.tm_yday);
	CPPUNIT_ASSERT_EQUAL(a_time_bd.tm_isdst, convtime.tm_isdst);
}

void TestTime :: test_localtime_s (void)
{
	struct tm t;
	struct tm *time = &t;
	time->tm_sec = 1;
	time->tm_min = 1;
	time->tm_hour = 1;
	time->tm_mday = 1;
	time->tm_mon = 1;
	time->tm_year = 20;
	time->tm_wday = 1;
	time->tm_yday = 1;
	time->tm_isdst = 0;
	
	time_t curtimer = mktime(time);
	time_t *timer = &curtimer;
	struct tm convtime;

	CPPUNIT_ASSERT_THROW(localtime_s(NULL, &convtime), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(localtime_s(timer, NULL), RuntimeConstraintViolation);
	localtime_s(timer, &convtime);
	
	CPPUNIT_ASSERT_EQUAL(time->tm_sec, convtime.tm_sec);
	CPPUNIT_ASSERT_EQUAL(time->tm_min, convtime.tm_min);
	CPPUNIT_ASSERT_EQUAL(time->tm_hour, convtime.tm_hour);
	CPPUNIT_ASSERT_EQUAL(time->tm_mday, convtime.tm_mday);
	CPPUNIT_ASSERT_EQUAL(time->tm_mon, convtime.tm_mon);
	CPPUNIT_ASSERT_EQUAL(time->tm_year, convtime.tm_year);
	CPPUNIT_ASSERT_EQUAL(time->tm_wday, convtime.tm_wday);
	CPPUNIT_ASSERT_EQUAL(time->tm_yday, convtime.tm_yday);
	CPPUNIT_ASSERT_EQUAL(time->tm_isdst, convtime.tm_isdst);
}
