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

int main()
{
	//BCA::GenerationOuterTotalisticCA ca(48, 8);
	BCA::GenerationOuterTotalisticCA ca(48, 40, 4);

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

