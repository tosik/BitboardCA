#pragma once

#include "bbcommon.h"
#include "LargeBitboard.h"
#include "IViewableBitboard.h"


namespace BitboardCA
{
	class BitboardViewer
	{
		// output target
		std::ostream * m_pOstream;

		public:
			BitboardViewer(std::ostream * ostream = &std::cout);

			/** view bitboard */
			void ViewBitboard(IViewableBitboard & viewable);

			/** view bitboard */
			void ViewBitboard(Bitboard b);

			/** view LargeBitboard */
			void ViewLargeBitboard(Bitboard * bitboards, unsigned int size_x, unsigned int siz_y);

			/** view LargeBitboard */
			void ViewLargeBitboard(LargeBitboard & large_bitboard);
			void ViewLargeBitboardForDebug(LargeBitboard & large_bitboard);

			/** view one line Bitboard at position y */
			void ViewBitboardLine(Bitboard b, unsigned int y);
	};
}

