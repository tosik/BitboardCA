#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "GenerationOuterTotalisticCA.h"
#include "BitboardViewer.h"

namespace BCA = BitboardCA;

class InnerCAForStarwars
	: public BCA::OuterTotalisticCA
{
	public:
		InnerCAForStarwars(std::size_t size_x, std::size_t size_y)
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

int main()
{
	const int count = 50;

	BCA::GenerationOuterTotalisticCA ca(10000, 10000, 4);
	InnerCAForStarwars starwars(ca.GetSizeX(), ca.GetSizeY());
	ca.SetInnerCAInstance(&starwars);

	std::cout << ca.GetSizeX() << " x " << ca.GetSizeY()
		<< " size Cellular Automata counts " << count << " loops." << std::endl;
	std::cout << "start benchmarking..." << std::endl;

	ca.Randomize();

	clock_t start, end;
	start = clock();
	for ( int steps = 0 ; steps < count ; steps ++ )
		ca.Step();
	end = clock();

	std::cout << "count = " << count << std::endl;
	std::cout << "size = " << "(" << ca.GetSizeX() << ", " << ca.GetSizeY() << ")" << std::endl;
	std::cout << "time = " << (double)(end - start)/CLOCKS_PER_SEC << " sec" << std::endl;
	std::cout << (double)(end - start)/count/CLOCKS_PER_SEC << " sec per count " << std::endl;

	return 0;
}


