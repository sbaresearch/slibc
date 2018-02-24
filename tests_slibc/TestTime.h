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
#ifndef TEST_TIME_H
#define TEST_TIME_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestTime : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (TestTime);
	
	
	CPPUNIT_TEST (test_asctime_s);
	CPPUNIT_TEST (test_ctime_s);
	CPPUNIT_TEST (test_gmtime_s);
	CPPUNIT_TEST (test_localtime_s);
	
	CPPUNIT_TEST_SUITE_END ();
	
public:
	void setUp (void);
	void tearDown (void);
	
protected:
	void test_asctime_s (void);
	void test_ctime_s (void);
	void test_gmtime_s (void);
	void test_localtime_s (void);
};

#endif
