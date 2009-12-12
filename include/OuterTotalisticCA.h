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


#pragma once

#include <iostream>
#include <vector>

#include "LargeBitboard.h"


namespace BitboardCA
{
	/** Cellular Automata class */
	class OuterTotalisticCA
		: public LargeBitboard
	{

		public:
			/** constructor */
			OuterTotalisticCA(std::size_t size_x, std::size_t size_y);

			/** destructor */
			virtual ~OuterTotalisticCA();

			/** step one */
			void Step();

			/** Update Bitboard by Outer Totalistic */
			Bitboard StepByOuterTotalistic(Bitboard board,
					Bitboard board_a, Bitboard board_b, Bitboard board_c,
					Bitboard board_d,                   Bitboard board_e,
					Bitboard board_f, Bitboard board_g, Bitboard board_h);

		protected:
			// you should code automata rule you like.
			// like this:
			//
			//   Bitboard Rule(Bitboard board, Bitboard s0, Bitboard s1, Bitboard s2, Bitboard s3,
			//                 Bitboard s4, Bitboard s5, Bitboard s6, Bitboard s7, Bitboard s8 )
			//   {
			//     // Conway's game of life
			//     return ( ~board & s3 ) | ( board & ( s2 | s3 ) );
			//   }
			//
			virtual Bitboard Rule(	Bitboard board, Bitboard s0, Bitboard s1, Bitboard s2, Bitboard s3,
									Bitboard s4, Bitboard s5, Bitboard s6, Bitboard s7, Bitboard s8 ) = 0;

	};

}

