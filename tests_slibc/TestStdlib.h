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
#ifndef TEST_STDLIB_H
#define TEST_STDLIB_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestStdlib : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (TestStdlib);

	CPPUNIT_TEST (test_getenv_s);
	CPPUNIT_TEST (test_qsort_s);
	CPPUNIT_TEST (test_bsearch_s);

	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp (void);
	void tearDown (void);

protected:
	void test_getenv_s (void);
	void test_qsort_s (void);
	void test_bsearch_s (void);
};

#endif
