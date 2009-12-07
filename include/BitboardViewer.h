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

#include "bbcommon.h"
#include "LargeBitboard.h"

#include <iostream>
#include <vector>


namespace BitboardCA
{
	class BitboardViewer
	{
		// output target
		std::ostream * m_pOstream;

		public:
			BitboardViewer(std::ostream * ostream = &std::cout);

			/** view bitboard */
			void ViewBitboard(Bitboard b);

			/** view LargeBitboard */
			void ViewLargeBitboard(Bitboard * bitboards, std::size_t size_x, std::size_t siz_y);

			/** view LargeBitboard */
			void ViewLargeBitboard(LargeBitboard & large_bitboard);
			void ViewLargeBitboardForDebug(LargeBitboard & large_bitboard);

			/** view one line Bitboard at position y */
			void ViewBitboardLine(Bitboard b, std::size_t y);
	};
}

