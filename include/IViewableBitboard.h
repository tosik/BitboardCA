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

#include <cstddef>


namespace BitboardCA
{
	/** Viewable Bitboard interface */
	class IViewableBitboard
	{
		public:
			/** get board size of x */
			virtual std::size_t GetSizeX() = 0;

			/** get board size of y */
			virtual std::size_t GetSizeY() = 0;

			/** get a state of cell */
			virtual std::size_t GetCellState(std::size_t x, std::size_t y) = 0;
	};

}



