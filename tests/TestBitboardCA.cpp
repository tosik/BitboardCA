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
		ConwaysLifeOfGameCA(std::size_t size_x, std::size_t size_y)
			: CA(size_x, size_y)
		{
		};

	protected:
		BCA::Bitboard Rule(
			BCA::Bitboard board,
			BCA::Bitboard s0, BCA::Bitboard s1, BCA::Bitboard s2,
			BCA::Bitboard s3, BCA::Bitboard s4, BCA::Bitboard s5,
			BCA::Bitboard s6, BCA::Bitboard s7, BCA::Bitboard s8 )
		{
			return ( ~board & s3 ) | ( board & ( s2 | s3 ) );
		};
};

class TestBitboardCA
	: public CppUnit::TestFixture
{
		ConwaysLifeOfGameCA m_small_ca;

	public:
		explicit TestBitboardCA()
			: CppUnit::TestFixture()
			, m_small_ca(8,8)
		{
		}

	private:
		CPPUNIT_TEST_SUITE(TestBitboardCA);
		CPPUNIT_TEST(testClear);
		CPPUNIT_TEST(testChangeCell);
		CPPUNIT_TEST(testSmallSizeCA);
		CPPUNIT_TEST(testSmallSizeMemberCA);
		CPPUNIT_TEST(testBlock);
		CPPUNIT_TEST(testBlinker);
		CPPUNIT_TEST(testGlider);
		CPPUNIT_TEST(testGetSize);
		CPPUNIT_TEST(testCanCreateSmallestCA);
		CPPUNIT_TEST(testCanCreateTooBigCA);
		CPPUNIT_TEST_SUITE_END();


	public:
		virtual void setUp()
		{
		}
		virtual void tearDown()
		{
		}


	protected:

		void testClear()
		{
			int size_x = 25;
			int size_y = 29;
			ConwaysLifeOfGameCA ca(size_x, size_y);
			ca.Clear();
			for ( int i = 0 ; i < size_x ; i ++ )
				for ( int j = 0 ; j < size_y ; j ++ )
					CPPUNIT_ASSERT_EQUAL(ca.GetCellState(i, j), false);
		}

		void testChangeCell()
		{
			ConwaysLifeOfGameCA ca(17, 15);
			ca.Clear();
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 1), false);

			ca.SetCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), true);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 1), false);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 1), false);

			ca.Clear();
			ca.SetCellState(true, 1, 2);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 2), true);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(2, 1), false);

			ca.Clear();
			ca.SetCellState(true, -1, 0);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(-1, 0), true);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), false);

			ca.Clear();
			ca.SetCellState(true, 3, 2);
			ca.SetCellState(true, 4, 2);
			ca.SetCellState(false, 3, 2);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(3, 2), false);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(4, 2), true);
		}

		void testSmallSizeCA()
		{
			int size_x = 8;
			int size_y = 8;
			ConwaysLifeOfGameCA ca(size_x, size_y);

			ca.Clear();
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), false);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 1), false);
		}

		void testSmallSizeMemberCA()
		{
			m_small_ca.Clear();
			CPPUNIT_ASSERT_EQUAL(m_small_ca.GetCellState(0, 0), false);
		}

		void testBlock()
		{
			ConwaysLifeOfGameCA ca(5, 5);

			// blinker
			ca.Clear();
			ca.SetCellState(true, 1, 1);
			ca.SetCellState(true, 1, 2);
			ca.SetCellState(true, 2, 1);
			ca.SetCellState(true, 2, 2);
			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.Step();

				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 2), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(2, 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(2, 2), true);

				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), false);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 2), false);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 1), false);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 2), false);
			}
		}

		void testBlinker()
		{
			ConwaysLifeOfGameCA ca(5, 5);

			// blinker
			ca.Clear();
			ca.SetCellState(true, 1, 0);
			ca.SetCellState(true, 1, 1);
			ca.SetCellState(true, 1, 2);
			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.Step();
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 0), (count % 2) == 1);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(1, 2), (count % 2) == 1);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(2, 1), (count % 2) != 1);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 1), (count % 2) != 1);
			}
		}

		void testGlider()
		{
			testGlider(14, 14);
		}

		void testCanCreateTooBigCA()
		{
			//testGlider(1024, 1024);
			testGlider(102, 102);
		}

		void testGlider(std::size_t X, std::size_t Y)
		{
			ConwaysLifeOfGameCA ca(X, Y);
			CPPUNIT_ASSERT_EQUAL(ca.GetSizeX(), X);
			CPPUNIT_ASSERT_EQUAL(ca.GetSizeY(), Y);

			ca.SetCellState(true, X-1, Y-1);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X-1, Y-1), true);

			// Glider
			ca.Clear();
			ca.SetCellState(true, X/2 + 1, Y/2 + 0);
			ca.SetCellState(true, X/2 + 0, Y/2 + 1);
			ca.SetCellState(true, X/2 + 0, Y/2 + 2);
			ca.SetCellState(true, X/2 + 1, Y/2 + 2);
			ca.SetCellState(true, X/2 + 2, Y/2 + 2);

			for ( std::size_t i = 1 ; i < X/2-2 ; i ++ )
			{
				ca.Step();
				ca.Step();
				ca.Step();
				ca.Step();

				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 1, Y/2 + i + 0), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 0, Y/2 + i + 1), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 0, Y/2 + i + 2), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 1, Y/2 + i + 2), true);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 2, Y/2 + i + 2), true);

				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 0, Y/2 + i + 0), false);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 2, Y/2 + i + 0), false);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 1, Y/2 + i + 1), false);
				CPPUNIT_ASSERT_EQUAL(ca.GetCellState(X/2 - i + 2, Y/2 + i + 1), false);
			}
		}

		void testGetSize()
		{
			{
				ConwaysLifeOfGameCA ca(1, 2);
				CPPUNIT_ASSERT_EQUAL(ca.GetSizeX(), (size_t)1);
				CPPUNIT_ASSERT_EQUAL(ca.GetSizeY(), (size_t)2);
			}
			{
				ConwaysLifeOfGameCA ca(4, 7);
				CPPUNIT_ASSERT_EQUAL(ca.GetSizeX(), (size_t)4);
				CPPUNIT_ASSERT_EQUAL(ca.GetSizeY(), (size_t)7);
			}
			{
				ConwaysLifeOfGameCA ca(143, 102);
				CPPUNIT_ASSERT_EQUAL(ca.GetSizeX(), (size_t)143);
				CPPUNIT_ASSERT_EQUAL(ca.GetSizeY(), (size_t)102);
			}
		}

		void testCanCreateSmallestCA()
		{
			ConwaysLifeOfGameCA ca(1, 1);
			CPPUNIT_ASSERT_EQUAL(ca.GetSizeX(), (size_t)1);
			CPPUNIT_ASSERT_EQUAL(ca.GetSizeY(), (size_t)1);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), false);
			ca.SetCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), true);
		}

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestBitboardCA);


int main(int argc, char * argv[])
{
	CppUnit::TestResult controller;

	CppUnit::TestResultCollector result;
	controller.addListener(&result);

	CppUnit::BriefTestProgressListener progress;
	controller.addListener(&progress);

	CppUnit::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
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

