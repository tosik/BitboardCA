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

#include <OuterTotalisticCA.h>
#include <GenerationOuterTotalisticCA.h>
#include <BitboardViewer.h>

namespace BCA = BitboardCA;

class ConwaysGameOfLifeCA
	: public BCA::OuterTotalisticCA
{
	public:
		ConwaysGameOfLifeCA(std::size_t size_x, std::size_t size_y)
			: OuterTotalisticCA(size_x, size_y)
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

class TestOuterTotalisticCA
	: public CppUnit::TestFixture
{
		ConwaysGameOfLifeCA m_small_ca;

	public:
		explicit TestOuterTotalisticCA()
			: CppUnit::TestFixture()
			, m_small_ca(8,8)
		{
		}

	private:
		CPPUNIT_TEST_SUITE(TestOuterTotalisticCA);
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
			ConwaysGameOfLifeCA ca(size_x, size_y);
			ca.Clear();
			for ( int i = 0 ; i < size_x ; i ++ )
				for ( int j = 0 ; j < size_y ; j ++ )
					CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(i, j));
		}

		void testBlank()
		{
			const std::size_t SIZE_X = 5;
			const std::size_t SIZE_Y = 5;
			ConwaysGameOfLifeCA ca(SIZE_X, SIZE_Y);

			ca.Clear();

			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.Step();

				for ( std::size_t x = 0 ; x < SIZE_X ; x ++ )
				{
					for ( std::size_t y = 0 ; y < SIZE_Y ; y ++ )
					{
						CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(x, y));
					}
				}
			}
		}

		void testChangeCell()
		{
			ConwaysGameOfLifeCA ca(17, 15);
			ca.Clear();
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 0));
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 1));

			ca.SetCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(0, 0));
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 1));
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(1, 0));
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(1, 1));

			ca.Clear();
			ca.SetCellState(true, 1, 2);
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(1, 2));
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(2, 1));

			ca.Clear();
			ca.SetCellState(true, 1, 0);
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(1, 0));
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 0));

			ca.Clear();
			ca.SetCellState(true, 3, 2);
			ca.SetCellState(true, 4, 2);
			ca.SetCellState(false, 3, 2);
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(3, 2));
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(4, 2));
		}

		void testSmallSizeCA()
		{
			int size_x = 8;
			int size_y = 8;
			ConwaysGameOfLifeCA ca(size_x, size_y);

			ca.Clear();
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 0), (std::size_t)0);
			CPPUNIT_ASSERT_EQUAL(ca.GetCellState(0, 1), (std::size_t)0);
		}

		void testSmallSizeMemberCA()
		{
			m_small_ca.Clear();
			CPPUNIT_ASSERT_EQUAL(m_small_ca.GetCellState(0, 0), (std::size_t)0);
		}

		void testBlock()
		{
			ConwaysGameOfLifeCA ca(5, 5);

			// blinker
			ca.Clear();
			ca.SetCellState(true, 1, 1);
			ca.SetCellState(true, 1, 2);
			ca.SetCellState(true, 2, 1);
			ca.SetCellState(true, 2, 2);
			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.Step();

				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(1, 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(1, 2));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(2, 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(2, 2));

				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 0));
				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 2));
				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 2));
			}
		}

		void testBlinker()
		{
			ConwaysGameOfLifeCA ca(5, 5);

			// blinker
			ca.Clear();
			ca.SetCellState(true, 1, 0);
			ca.SetCellState(true, 1, 1);
			ca.SetCellState(true, 1, 2);
			for ( int count = 0 ; count < 100 ; count ++ )
			{
				ca.Step();
				CPPUNIT_ASSERT_EQUAL((std::size_t)(count % 2), ca.GetCellState(1, 0));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(1, 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)(count % 2), ca.GetCellState(1, 2));
				CPPUNIT_ASSERT_EQUAL((std::size_t)(1 - count % 2), ca.GetCellState(2, 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)(1 - count % 2), ca.GetCellState(0, 1));
			}
		}

		void testGlider()
		{
			testGlider(14, 14);
		}

		void testCanCreateTooBigCA()
		{
			testGlider(500, 600);
		}

		void testGlider(std::size_t X, std::size_t Y)
		{
			ConwaysGameOfLifeCA ca(X, Y);
			CPPUNIT_ASSERT_EQUAL(X, ca.GetSizeX());
			CPPUNIT_ASSERT_EQUAL(Y, ca.GetSizeY());

			ca.SetCellState(true, X-1, Y-1);
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(X-1, Y-1));

			// Glider
			ca.Clear();
			ca.SetCellState(true, X/2 + 1, Y/2 + 0);
			ca.SetCellState(true, X/2 + 0, Y/2 + 1);
			ca.SetCellState(true, X/2 + 0, Y/2 + 2);
			ca.SetCellState(true, X/2 + 1, Y/2 + 2);
			ca.SetCellState(true, X/2 + 2, Y/2 + 2);

			BCA::BitboardViewer viewer(&std::cout);

			for ( std::size_t i = 1 ; i < X/2-2 ; i ++ )
			{
				ca.Step();
				ca.Step();
				ca.Step();
				ca.Step();

				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(X/2 - i + 1, Y/2 + i + 0));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(X/2 - i + 0, Y/2 + i + 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(X/2 - i + 0, Y/2 + i + 2));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(X/2 - i + 1, Y/2 + i + 2));
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(X/2 - i + 2, Y/2 + i + 2));

				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(X/2 - i + 0, Y/2 + i + 0));
				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(X/2 - i + 2, Y/2 + i + 0));
				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(X/2 - i + 1, Y/2 + i + 1));
				CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(X/2 - i + 2, Y/2 + i + 1));
			}
		}

		void testGetSize()
		{
			{
				ConwaysGameOfLifeCA ca(1, 2);
				CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetSizeX());
				CPPUNIT_ASSERT_EQUAL((std::size_t)2, ca.GetSizeY());
			}
			{
				ConwaysGameOfLifeCA ca(4, 7);
				CPPUNIT_ASSERT_EQUAL((std::size_t)4, ca.GetSizeX());
				CPPUNIT_ASSERT_EQUAL((std::size_t)7, ca.GetSizeY());
			}
			{
				ConwaysGameOfLifeCA ca(143, 102);
				CPPUNIT_ASSERT_EQUAL((std::size_t)143, ca.GetSizeX());
				CPPUNIT_ASSERT_EQUAL((std::size_t)102, ca.GetSizeY());
			}
		}

		void testCanCreateSmallestCA()
		{
			ConwaysGameOfLifeCA ca(1, 1);
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetSizeX());
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetSizeY());
			CPPUNIT_ASSERT_EQUAL((std::size_t)0, ca.GetCellState(0, 0));
			ca.SetCellState(true, 0, 0);
			CPPUNIT_ASSERT_EQUAL((std::size_t)1, ca.GetCellState(0, 0));
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
		CPPUNIT_TEST(testViewLargeBitboard);
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

		void testViewLargeBitboard()
		{
			std::ostringstream stream;
			BCA::BitboardViewer viewer(&stream);

			// view blank
			{
				{
					stream.str("");
					BCA::Bitboard bitboards[6] = {
						0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL,
					};
					viewer.ViewLargeBitboard(bitboards, 2, 3);

					CPPUNIT_ASSERT_EQUAL((std::size_t)945, stream.str().length());
				}

				{
					stream.str("");
					BCA::Bitboard bitboards[6] = {
						0x0123456789ABCDEFULL,
						0xFEDCBA9876543210ULL,
						0x0909787856563434ULL,
						0x1029384756473829ULL,
						0x1122334455667788ULL,
						0xFF00AA0033008800ULL,
					};
					viewer.ViewLargeBitboard(bitboards, 2, 3);

					std::string right_string =
						"                |      *       * |\n" \
						"      *       * |* * *   * * *   |\n" \
						"                |  * *     * *   |\n" \
						"* *     * *     |*   *   *   *   |\n" \
						"                |    *       *   |\n" \
						"  *   *   *   * |* *     * *     |\n" \
						"                |  *       *     |\n" \
						"* * * * * * * * |*       *       |\n" \
						"---------------- ---------------- \n" \
						"*     *   *     |    *   * *     |\n" \
						"      * * *     |    *   * *     |\n" \
						"* * *       *   |  * *   *   *   |\n" \
						"  * *   *   *   |  * *   *   *   |\n" \
						"* * *       *   |      * * * *   |\n" \
						"      * * *     |      * * * *   |\n" \
						"*     *   *     |*     *         |\n" \
						"        *       |*     *         |\n" \
						"---------------- ---------------- \n" \
						"        *       |* * * *   * * * |\n" \
						"  *     * *     |*   * *     * * |\n" \
						"    *   *   *   |* *   *   *   * |\n" \
						"  * *   * * *   |*     *       * |\n" \
						"      * *     * |* * *     * *   |\n" \
						"  *   * * *   * |*   *       *   |\n" \
						"    * * *   * * |* *       *     |\n" \
						"  * * * * * * * |*               |\n" \
						"---------------- ---------------- \n";

					CPPUNIT_ASSERT_EQUAL(right_string, stream.str());
				}
			}
		}
};


class InnerCAForGeneration
	: public BCA::OuterTotalisticCA
{
	public:
		InnerCAForGeneration(std::size_t size_x, std::size_t size_y)
			: BCA::OuterTotalisticCA(size_x, size_y)
		{
		}

	protected:
		BCA::Bitboard Rule(
				BCA::Bitboard board,
				BCA::Bitboard s0, BCA::Bitboard s1, BCA::Bitboard s2,
				BCA::Bitboard s3, BCA::Bitboard s4, BCA::Bitboard s5,
				BCA::Bitboard s6, BCA::Bitboard s7, BCA::Bitboard s8 )
		{
			// starwars
			return ( board & ( s3 | s4 | s5 ) ) | ( ~board & s2 );
		}
};

class TestGenerationOuterTotalisticCA
	: public CppUnit::TestFixture
{
		ConwaysGameOfLifeCA m_small_ca;

	public:
		explicit TestGenerationOuterTotalisticCA()
			: CppUnit::TestFixture()
			, m_small_ca(8,8)
		{
		}

	private:
		CPPUNIT_TEST_SUITE(TestGenerationOuterTotalisticCA);
		CPPUNIT_TEST(testStableSmallCase);
		CPPUNIT_TEST(testActivitySmallCase);
		CPPUNIT_TEST_SUITE_END();


	public:
		virtual void setUp()
		{
		}
		virtual void tearDown()
		{
		}


	protected:

		void testStableSmallCase()
		{
			BCA::GenerationOuterTotalisticCA ca(12, 9, 4);
			InnerCAForGeneration inner(ca.GetSizeX(), ca.GetSizeY());
			ca.SetInnerCAInstance(&inner);

			ca.SetCellState(4, 5, 3);
			ca.SetCellState(4, 6, 3);
			ca.SetCellState(5, 5, 3);
			ca.SetCellState(4, 4, 3);
			ca.SetCellState(3, 5, 3);

			for ( int i = 0 ; i < 100 ; i ++ )
			{
				CPPUNIT_ASSERT_EQUAL((std::size_t)3, ca.GetCellState(4, 5));
				CPPUNIT_ASSERT_EQUAL((std::size_t)3, ca.GetCellState(4, 6));
				CPPUNIT_ASSERT_EQUAL((std::size_t)3, ca.GetCellState(5, 5));
				CPPUNIT_ASSERT_EQUAL((std::size_t)3, ca.GetCellState(4, 4));
				CPPUNIT_ASSERT_EQUAL((std::size_t)3, ca.GetCellState(3, 5));
				ca.Step();
			}
		}

		void testActivitySmallCase()
		{
			const std::size_t SIZE_X = 12;
			const std::size_t SIZE_Y = 9;
			BCA::GenerationOuterTotalisticCA ca(SIZE_X, SIZE_Y, 4);
			InnerCAForGeneration inner(SIZE_X, SIZE_Y);
			ca.SetInnerCAInstance(&inner);

			ca.SetCellState(4, 4, 3);
			ca.SetCellState(4, 3, 3);
			ca.SetCellState(4, 2, 3);
			ca.SetCellState(4, 3, 3);
			ca.SetCellState(3, 5, 3);

			BCA::BitboardViewer viewer;

			for ( int i = 0 ; i < 3 ; i ++ )
			{
				ca.Step();
			}

			std::size_t expect[SIZE_Y][SIZE_X] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 0, 1, 3, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			};
			for ( std::size_t y = 0 ; y < ca.GetSizeY() ; y ++ )
				for ( std::size_t x = 0 ; x < ca.GetSizeX() ; x ++ )
					CPPUNIT_ASSERT_EQUAL(expect[y][x], ca.GetCellState(x, y));
		}
};


CPPUNIT_TEST_SUITE_REGISTRATION(TestOuterTotalisticCA);
CPPUNIT_TEST_SUITE_REGISTRATION(TestGenerationOuterTotalisticCA);
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

