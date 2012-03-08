#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "OuterTotalisticCA.h"
#include "BitboardViewer.h"

namespace BCA = BitboardCA;

class ConwaysGameOfLife
	: public BCA::OuterTotalisticCA
{
	public:
		ConwaysGameOfLife(std::size_t size_x, std::size_t size_y)
			: OuterTotalisticCA(size_x, size_y)
		{
		}

	protected:
		BCA::Bitboard Rule(
			BCA::Bitboard board,
			BCA::Bitboard s0, BCA::Bitboard s1, BCA::Bitboard s2,
			BCA::Bitboard s3, BCA::Bitboard s4, BCA::Bitboard s5,
			BCA::Bitboard s6, BCA::Bitboard s7, BCA::Bitboard s8 )
		{
			// making automata rule
			return ( ~board & s3 ) | ( board & ( s2 | s3 ) ); // Conway's game of life
			//return ( ~board & s3 ) | ( board & ( s2 | s3 | s4 ) ); // maze
			//return ( ~board & ( s3 | s4 | s6 | s7 | s8 ) ) | ( board & ( s3 | s6 | s7 | s8 ) ); // Day & Night
		}
};

int main()
{
	ConwaysGameOfLife ca(48, 40);

	ca.Randomize();
	BCA::BitboardViewer viewer;

	// view detail
	viewer.ViewBitboard(ca);

	for ( int steps = 0 ; steps < 1000 ; steps ++ )
	{
		ca.Step();

		// view detail
		viewer.ViewBitboard(ca);
		std::cout << "-----------------------" << std::endl;
	}

	return 0;
}

