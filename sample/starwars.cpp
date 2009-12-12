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

// your class
// define user rules on like this class.
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
	// create a ca with generation
	BCA::GenerationOuterTotalisticCA ca(48, 40, 4);
	// you need inner ca instance. create and set like below.
	InnerCAForStarwars starwars(ca.GetSizeX(), ca.GetSizeY());
	ca.SetInnerCAInstance(&starwars);

	ca.Randomize();
	BCA::BitboardViewer viewer;

	for ( int steps = 0 ; steps < 1000 ; steps ++ )
	{
		ca.Step();
		viewer.ViewBitboard(ca);
		std::cout << "----" << std::endl;
	}

	return 0;
}

