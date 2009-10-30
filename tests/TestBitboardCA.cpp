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
#include <bbviewer.h>

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
		CPPUNIT_TEST(testBlank);
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
					CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(i, j));
		}

		void testBlank()
		{
			const std::size_t SIZE_X = 5;
			const std::size_t SIZE_Y = 5;
			ConwaysLifeOfGameCA ca(SIZE_X, SIZE_Y);

			ca.Clear();

			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.Step();

				for ( std::size_t x = 0 ; x < SIZE_X ; x ++ )
				{
					for ( std::size_t y = 0 ; y < SIZE_Y ; y ++ )
					{
						CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(x, y));
					}
				}
			}
		}

		void testChangeCell()
		{
			ConwaysLifeOfGameCA ca(17, 15);
			ca.Clear();
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 0));
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 1));

			ca.SetCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(0, 0));
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 1));
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(1, 0));
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(1, 1));

			ca.Clear();
			ca.SetCellState(true, 1, 2);
			CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(1, 2));
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(2, 1));

			ca.Clear();
			ca.SetCellState(true, 1, 0);
			CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(1, 0));
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 0));

			ca.Clear();
			ca.SetCellState(true, 3, 2);
			ca.SetCellState(true, 4, 2);
			ca.SetCellState(false, 3, 2);
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(3, 2));
			CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(4, 2));
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

				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(1, 1));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(1, 2));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(2, 1));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(2, 2));

				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 0));
				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 2));
				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 1));
				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 2));
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
				CPPUNIT_ASSERT_EQUAL((count % 2) == 1, ca.GetCellState(1, 0));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(1, 1));
				CPPUNIT_ASSERT_EQUAL((count % 2) == 1, ca.GetCellState(1, 2));
				CPPUNIT_ASSERT_EQUAL((count % 2) != 1, ca.GetCellState(2, 1));
				CPPUNIT_ASSERT_EQUAL((count % 2) != 1, ca.GetCellState(0, 1));
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
			CPPUNIT_ASSERT_EQUAL(X, ca.GetSizeX());
			CPPUNIT_ASSERT_EQUAL(Y, ca.GetSizeY());

			ca.SetCellState(true, X-1, Y-1);
			CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(X-1, Y-1));

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

				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(X/2 - i + 1, Y/2 + i + 0));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(X/2 - i + 0, Y/2 + i + 1));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(X/2 - i + 0, Y/2 + i + 2));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(X/2 - i + 1, Y/2 + i + 2));
				CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(X/2 - i + 2, Y/2 + i + 2));

				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(X/2 - i + 0, Y/2 + i + 0));
				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(X/2 - i + 2, Y/2 + i + 0));
				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(X/2 - i + 1, Y/2 + i + 1));
				CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(X/2 - i + 2, Y/2 + i + 1));
			}
		}

		void testGetSize()
		{
			{
				ConwaysLifeOfGameCA ca(1, 2);
				CPPUNIT_ASSERT_EQUAL((size_t)1, ca.GetSizeX());
				CPPUNIT_ASSERT_EQUAL((size_t)2, ca.GetSizeY());
			}
			{
				ConwaysLifeOfGameCA ca(4, 7);
				CPPUNIT_ASSERT_EQUAL((size_t)4, ca.GetSizeX());
				CPPUNIT_ASSERT_EQUAL((size_t)7, ca.GetSizeY());
			}
			{
				ConwaysLifeOfGameCA ca(143, 102);
				CPPUNIT_ASSERT_EQUAL((size_t)143, ca.GetSizeX());
				CPPUNIT_ASSERT_EQUAL((size_t)102, ca.GetSizeY());
			}
		}

		void testCanCreateSmallestCA()
		{
			ConwaysLifeOfGameCA ca(1, 1);
			CPPUNIT_ASSERT_EQUAL((size_t)1, ca.GetSizeX());
			CPPUNIT_ASSERT_EQUAL((size_t)1, ca.GetSizeY());
			CPPUNIT_ASSERT_EQUAL(false, ca.GetCellState(0, 0));
			ca.SetCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL(true, ca.GetCellState(0, 0));
		}

};


class TestBitboardViewer
	: public CppUnit::TestFixture
{
	public:
		explicit TestBitboardViewer()
			: CppUnit::TestFixture()
		{
		}

	private:
		CPPUNIT_TEST_SUITE(TestBitboardViewer);
		CPPUNIT_TEST(testViewBitboard);
		CPPUNIT_TEST_SUITE_END();


	public:
		virtual void setUp()
		{
		}
		virtual void tearDown()
		{
		}


	protected:

		void testViewBitboard()
		{
			std::ostringstream stream;
			BCA::BitboardViewer viewer(&stream);

			// view blank
			{
				{
					stream.str("");
					viewer.ViewBitboard(0ULL);

					// size = bit_chars(2bytes) * bitboard_size_x * bitboard_size_y + new_line_num
					CPPUNIT_ASSERT_EQUAL((std::size_t)(2 * 8 * 8 + 8), stream.str().length());
				}

				{
					stream.str("");
					viewer.ViewBitboard(0ULL);

					std::string right_string =
						"                \n" \
						"                \n" \
						"                \n" \
						"                \n" \
						"                \n" \
						"                \n" \
						"                \n" \
						"                \n";

					CPPUNIT_ASSERT_EQUAL(right_string, stream.str());
				}

				{
					stream.str("");
					viewer.ViewBitboard(0xFFFFFFFFFFFFFFFFULL);

					std::string right_string =
						"* * * * * * * * \n" \
						"* * * * * * * * \n" \
						"* * * * * * * * \n" \
						"* * * * * * * * \n" \
						"* * * * * * * * \n" \
						"* * * * * * * * \n" \
						"* * * * * * * * \n" \
						"* * * * * * * * \n";

					CPPUNIT_ASSERT_EQUAL(right_string, stream.str());
				}

				{
					stream.str("");
					viewer.ViewBitboard(0x0F0F0F0F0F0F0F0F0ULL);

					std::string right_string =
						"        * * * * \n" \
						"        * * * * \n" \
						"        * * * * \n" \
						"        * * * * \n" \
						"        * * * * \n" \
						"        * * * * \n" \
						"        * * * * \n" \
						"        * * * * \n";

					CPPUNIT_ASSERT_EQUAL(right_string, stream.str());
				}

				{
					stream.str("");
					viewer.ViewBitboard(0x80C0E0F0F8FCFEFFULL);

					std::string right_string =
						"* * * * * * * * \n" \
						"  * * * * * * * \n" \
						"    * * * * * * \n" \
						"      * * * * * \n" \
						"        * * * * \n" \
						"          * * * \n" \
						"            * * \n" \
						"              * \n";

					CPPUNIT_ASSERT_EQUAL(right_string, stream.str());
				}

				{
					stream.str("");
					viewer.ViewBitboard(0x80C0E0F0F8070301ULL);

					std::string right_string =
						"*               \n" \
						"* *             \n" \
						"* * *           \n" \
						"      * * * * * \n" \
						"        * * * * \n" \
						"          * * * \n" \
						"            * * \n" \
						"              * \n";

					CPPUNIT_ASSERT_EQUAL(right_string, stream.str());
				}
			}
		}

};



CPPUNIT_TEST_SUITE_REGISTRATION(TestBitboardCA);
CPPUNIT_TEST_SUITE_REGISTRATION(TestBitboardViewer);


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

