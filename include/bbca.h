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


namespace BitboardCA
{
	/** Bitboard type */
	typedef unsigned long long int Bitboard;

	/** Cellular Automata class */
	class CA
	{
		public:
			/** constructor */
			CA(int size_x, int size_y);

			/** destructor */
			virtual ~CA();

			/** step one */
			void step();

			/** Update Bitboard by Outer Totalistic */
			Bitboard stepByOuterTotalistic(Bitboard&, Bitboard&, Bitboard&, Bitboard&, Bitboard&, Bitboard&, Bitboard&, Bitboard&, Bitboard&);

			/** view simply board to console */
			void view();

			/** get board size of x */
			int getSizeX();

			/** get board size of y */
			int getSizeY();

			/** randomize board */
			void randomize();

			/** all cells die */
			void clear();

			/** get a state of cell */
			bool getCellState(int x, int y);
			void setCellState(bool cell, int x, int y);

		protected:
			// you should code automata rule you like.
			// like this:
			//
			//   Bitboard rule(Bitboard board, Bitboard s0, Bitboard s1, Bitboard s2, Bitboard s3,
			//                 Bitboard s4, Bitboard s5, Bitboard s6, Bitboard s7, Bitboard s8 )
			//   {
			//     // Conway's game of life
			//     return ( ~board & s3 ) | ( board & ( s2 | s3 ) ); 
			//   }
			//
			virtual Bitboard rule(Bitboard board, Bitboard s0, Bitboard s1, Bitboard s2, Bitboard s3,
					Bitboard s4, Bitboard s5, Bitboard s6, Bitboard s7, Bitboard s8 ) = 0;

		private:
			/** size of board */
			int size_x, size_y;

			/** number of bitboard */
			int board_size_x, board_size_y;

			/** bitboard array */
			std::vector<Bitboard> boards;

			/** get bitboard from board array */
			Bitboard getBoard(int x, int y);

			/** view bitboard */
			void viewBitboard(Bitboard b);

	};

}

