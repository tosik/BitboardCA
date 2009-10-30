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

#include "bbcommon.h"


namespace BitboardCA
{
	/** Cellular Automata class */
	class CA
	{
		private:
			/** size of board */
			std::size_t m_SizeX, m_SizeY;

			/** number of bitboard */
			std::size_t m_BitboardSizeX, m_BitboardSizeY;

			/** bitboard array */
			Bitboard * m_BitboardList;


		public:
			/** constructor */
			CA(std::size_t size_x, std::size_t size_y);

			/** destructor */
			virtual ~CA();

			/** step one */
			void Step();

			/** Update Bitboard by Outer Totalistic */
			Bitboard StepByOuterTotalistic(Bitboard board,
					Bitboard board_a, Bitboard board_b, Bitboard board_c,
					Bitboard board_d,                   Bitboard board_e,
					Bitboard board_f, Bitboard board_g, Bitboard board_h);

			/** view simply board to console */
			void View();

			/** get board size of x */
			std::size_t GetSizeX();

			/** get board size of y */
			std::size_t GetSizeY();

			/** randomize board */
			void Randomize();

			/** all cells die */
			void Clear();
			void Clear(Bitboard * bitboards, std::size_t size);

			/** get a state of cell */
			bool GetCellState(std::size_t x, std::size_t y);
			void SetCellState(bool cell, std::size_t x, std::size_t y);

			/** get size of bitboard list */
			std::size_t GetBitboardListSize();

			/** get size x of bitboard list */
			std::size_t GetBitboardListSizeX();

			/** get size y of bitboard list */
			std::size_t GetBitboardListSizeY();

			/** get biboard list*/
			Bitboard * GetBitboardList();


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

		private:
			/** get bitboard from board array */
			Bitboard GetBoard(std::size_t x, std::size_t y);

			/** get shift size used when set/get cells */
			inline std::size_t GetBitboardShiftSize(std::size_t x, std::size_t y);

			/** get biboard index used when set/get cells */
			inline std::size_t GetBitboardIndex(std::size_t x, std::size_t y);

	};

}

