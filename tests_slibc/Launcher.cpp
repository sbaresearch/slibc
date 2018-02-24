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
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>

int main (int argc, char* argv[])
{
	CPPUNIT_NS :: TestResult testresult;

	// Listener for collecting individual test results
	CPPUNIT_NS :: TestResultCollector collectedresults;
	testresult.addListener (&collectedresults);

	// Listener for outputting individual test results
	CPPUNIT_NS :: BriefTestProgressListener progress;
	testresult.addListener (&progress);

	// add test suite
	CPPUNIT_NS :: TestRunner testrunner;
	testrunner.addTest (CPPUNIT_NS :: TestFactoryRegistry :: getRegistry ().makeTest ());
	testrunner.run (testresult);

	// Output results in compiler format
	CPPUNIT_NS :: CompilerOutputter compileroutputter (&collectedresults, std::cerr);
	compileroutputter.write ();

	return collectedresults.wasSuccessful () ? 0 : 1;
}
