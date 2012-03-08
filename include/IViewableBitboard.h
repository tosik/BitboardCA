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



