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
	const int count = 500;

	BCA::GenerationOuterTotalisticCA ca(2000, 1500, 4);
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


