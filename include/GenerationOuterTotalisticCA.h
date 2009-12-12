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
#include "OuterTotalisticCA.h"


namespace BitboardCA
{
	class TopCA
		: public OuterTotalisticCA
	{
	public:
		TopCA(std::size_t size_x, std::size_t size_y)
			: OuterTotalisticCA(size_x, size_y)
		{
		}

	protected:
		Bitboard Rule(
			Bitboard board,
			Bitboard s0, Bitboard s1, Bitboard s2,
			Bitboard s3, Bitboard s4, Bitboard s5,
			Bitboard s6, Bitboard s7, Bitboard s8 )
		{
			// starwars
			return ( board & ( s3 | s4 | s5 ) ) | ( ~board & s2 );
		}
	};

	/** Cellular Automata class */
	class GenerationOuterTotalisticCA
	{
		private:
			TopCA m_TopCA;
			std::vector<LargeBitboard *> m_pWeakList;
			std::size_t m_States;

		public:
			/** constructor */
			GenerationOuterTotalisticCA(std::size_t size_x, std::size_t size_y, std::size_t states);

			/** destructor */
			virtual ~GenerationOuterTotalisticCA();

			/** step one */
			void Step();

			void Randomize();

		protected:

	};

}

