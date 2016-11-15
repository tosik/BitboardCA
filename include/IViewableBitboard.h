#pragma once

#include "bbcommon.h"


namespace BitboardCA
{
	/** Viewable Bitboard interface */
	class IViewableBitboard
	{
		public:
			/** get board size of x */
			virtual unsigned int GetSizeX() = 0;

			/** get board size of y */
			virtual unsigned int GetSizeY() = 0;

			/** get a state of cell */
			virtual unsigned int GetCellState(unsigned int x, unsigned int y) = 0;
	};

}



