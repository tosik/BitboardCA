/*
 * BitboardCA. Cellular Automata using bitboard algorithms.
 * Copyright (C) Toshiyuki Hirooka <toshi.hirooka@gmail.com> http://wasabi.in/
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>

#include <bbca.h>

namespace BCA = BitboardCA;

class ConwaysLifeOfGameCA
	: public BCA::CA
{
	public:
		ConwaysLifeOfGameCA(int size_x, int size_y)
			: CA(size_x, size_y)
		{
		};

	protected:
		BCA::Bitboard rule(
				BCA::Bitboard board,
				BCA::Bitboard s0, BCA::Bitboard s1, BCA::Bitboard s2,
				BCA::Bitboard s3, BCA::Bitboard s4, BCA::Bitboard s5,
				BCA::Bitboard s6, BCA::Bitboard s7, BCA::Bitboard s8 )
		{
			return ( ~board & s3 ) | ( board & ( s2 | s3 ) );
		};
};

class TestBitboardCA
	: public CppUnit::TestCase
{
	public:

		ConwaysLifeOfGameCA m_small_ca;

		explicit TestBitboardCA()
			: CppUnit::TestCase()
			, m_small_ca(8,8)
		{
		}


		virtual void setUp()
		{
		}
		virtual void tearDown()
		{
		}

		void testClear()
		{
			int size_x = 25;
			int size_y = 29;
			ConwaysLifeOfGameCA ca(size_x, size_y);
			ca.clear();
			for ( int i = 0 ; i < size_x ; i ++ )
				for ( int j = 0 ; j < size_y ; j ++ )
					CPPUNIT_ASSERT_EQUAL(ca.getCellState(i, j), false);
		}

		void testChangeCell()
		{
			ConwaysLifeOfGameCA ca(17, 15);
			ca.clear();
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 1), false);

			ca.setCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 0), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 1), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 1), false);

			ca.clear();
			ca.setCellState(true, 1, 2);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 2), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(2, 1), false);

			ca.clear();
			ca.setCellState(true, -1, 0);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(-1, 0), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 0), false);

			ca.clear();
			ca.setCellState(true, 3, 2);
			ca.setCellState(true, 4, 2);
			ca.setCellState(false, 3, 2);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(3, 2), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(4, 2), true);
		}

		void testSmallSizeCA()
		{
			int size_x = 8;
			int size_y = 8;
			ConwaysLifeOfGameCA ca(size_x, size_y);

			ca.clear();
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 1), false);
		}

		void testSmallSizeMemberCA()
		{
			m_small_ca.clear();
			CPPUNIT_ASSERT_EQUAL(m_small_ca.getCellState(0, 0), false);
		}

		void testBlock()
		{
			ConwaysLifeOfGameCA ca(5, 5);

			// blinker
			ca.clear();
			ca.setCellState(true, 1, 1);
			ca.setCellState(true, 1, 2);
			ca.setCellState(true, 2, 1);
			ca.setCellState(true, 2, 2);
			ca.view();
			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.step();

				CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 2), true);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(2, 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(2, 2), true);

				CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 0), false);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 2), false);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 1), false);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 2), false);
			}
			ca.view();
		}

		void testBlinker()
		{
			ConwaysLifeOfGameCA ca(5, 5);

			// blinker
			ca.clear();
			ca.setCellState(true, 1, 0);
			ca.setCellState(true, 1, 1);
			ca.setCellState(true, 1, 2);
			ca.view();
			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.step();
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 0), (count % 2) == 1);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(1, 2), (count % 2) == 1);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(2, 1), (count % 2) != 1);
				CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 1), (count % 2) != 1);
			}
			ca.view();
		}

		void testGetSize()
		{
			{
				ConwaysLifeOfGameCA ca(1, 2);
				CPPUNIT_ASSERT_EQUAL(ca.getSizeX(), 1);
				CPPUNIT_ASSERT_EQUAL(ca.getSizeY(), 2);
			}
			{
				ConwaysLifeOfGameCA ca(4, 7);
				CPPUNIT_ASSERT_EQUAL(ca.getSizeX(), 4);
				CPPUNIT_ASSERT_EQUAL(ca.getSizeY(), 7);
			}
			{
				ConwaysLifeOfGameCA ca(143, 102);
				CPPUNIT_ASSERT_EQUAL(ca.getSizeX(), 143);
				CPPUNIT_ASSERT_EQUAL(ca.getSizeY(), 102);
			}
		}

		void testCanCreateSmallestCA()
		{
			ConwaysLifeOfGameCA ca(0, 0);
			CPPUNIT_ASSERT_EQUAL(ca.getSizeX(), 0);
			CPPUNIT_ASSERT_EQUAL(ca.getSizeY(), 0);
			ca.setCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(0, 0), true);
		}

		void testGlider()
		{
			testGlider(14, 14);
		}

		void testCanCreateTooBigCA()
		{
			testGlider(1024, 1024);
		}

		void testGlider(int X, int Y)
		{
			ConwaysLifeOfGameCA ca(X, Y);
			CPPUNIT_ASSERT_EQUAL(ca.getSizeX(), X);
			CPPUNIT_ASSERT_EQUAL(ca.getSizeY(), Y);

			ca.setCellState(true, X-1, Y-1);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X-1, Y-1), true);

			// Glider
			ca.clear();
			ca.setCellState(true, X/2 + 1, Y/2 + 0);
			ca.setCellState(true, X/2 + 0, Y/2 + 1);
			ca.setCellState(true, X/2 + 0, Y/2 + 2);
			ca.setCellState(true, X/2 + 1, Y/2 + 2);
			ca.setCellState(true, X/2 + 2, Y/2 + 2);
			ca.view();
			ca.step();
			ca.step();
			ca.step();
			ca.step();
			ca.view();
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 1, Y/2 + 1 + 0), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 0, Y/2 + 1 + 1), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 0, Y/2 + 1 + 2), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 1, Y/2 + 1 + 2), true);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 2, Y/2 + 1 + 2), true);

			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 0, Y/2 + 1 + 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 2, Y/2 + 1 + 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 1, Y/2 + 1 + 1), false);
			CPPUNIT_ASSERT_EQUAL(ca.getCellState(X/2 - 1 + 2, Y/2 + 1 + 1), false);
		}

		static CppUnit::Test * suite()
		{
			CppUnit::TestSuite * suite = new CppUnit::TestSuite("TestBitboardCA");
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testClear", &TestBitboardCA::testClear));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testChangeCell", &TestBitboardCA::testChangeCell));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testSmallSizeCA", &TestBitboardCA::testSmallSizeCA));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testSmallSizeMemberCA", &TestBitboardCA::testSmallSizeMemberCA));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testBlock", &TestBitboardCA::testBlock));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testBlinker", &TestBitboardCA::testBlinker));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testGlider", &TestBitboardCA::testGlider));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testGetSize", &TestBitboardCA::testGetSize));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testCanCreateSmallestCA", &TestBitboardCA::testCanCreateSmallestCA));
			suite->addTest(new CppUnit::TestCaller<TestBitboardCA>("testCanCreateTooBigCA", &TestBitboardCA::testCanCreateTooBigCA));
			return suite;
		}
};



int main(int argc, char * argv[])
{
	CppUnit::TestResult controller;

	CppUnit::TestResultCollector result;
	controller.addListener(&result);

	CppUnit::BriefTestProgressListener progress;
	controller.addListener(&progress);

	CppUnit::TestRunner runner;
	runner.addTest(TestBitboardCA::suite());
	runner.run(controller);


	// output
	{
		CppUnit::CompilerOutputter outputter(&result, std::cout);
		outputter.write();
	}
	{
		std::ofstream xmlstream("results/TestBitboardCA.xml");
		CppUnit::XmlOutputter outputter(&result, xmlstream);
		outputter.write();
	}

	return result.wasSuccessful() ? 0 : -1;
}

