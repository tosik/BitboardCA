#pragma once

#include "bbcommon.h"
#include "IViewableBitboard.h"


namespace BitboardCA
{
	/** Large Bitboard class */
	class LargeBitboard
		: public IViewableBitboard
	{
		protected:
			/** size of board */
			unsigned int m_SizeX, m_SizeY;

			/** number of bitboard */
			unsigned int m_BitboardSizeX, m_BitboardSizeY;

			/** bitboard array */
			Bitboard * m_BitboardList;


		public:
			/** constructor */
			LargeBitboard(unsigned int size_x, unsigned int size_y, bool direct_size_mode=false);

			/** destructor */
			virtual ~LargeBitboard();

			/** get board size of x */
			unsigned int GetSizeX();

			/** get board size of y */
			unsigned int GetSizeY();

			/** randomize board */
			void Randomize();

			/** all cells die */
			void Clear();
			void Clear(Bitboard * bitboards, unsigned int size);

			/** get a state of cell */
			unsigned int GetCellState(unsigned int x, unsigned int y);

			/** set a state of cell */
			void SetCellState(bool cell, unsigned int x, unsigned int y);

			/** get a bitboard */
			Bitboard GetBitboard(unsigned int x, unsigned int y);
			Bitboard GetBitboard(unsigned int i);

			/** set a bitboard */
			void SetBitboard(Bitboard bitboard, unsigned int x, unsigned int y);
			void SetBitboard(Bitboard bitboard, unsigned int i);

			/** get size of bitboard list */
			unsigned int GetBitboardListSize();

			/** get size x of bitboard list */
			unsigned int GetBitboardListSizeX();

			/** get size y of bitboard list */
			unsigned int GetBitboardListSizeY();

			/** get biboard list*/
			Bitboard * GetBitboardList();

			void Copy(LargeBitboard * large);
			void Or(LargeBitboard * large);
			void And(LargeBitboard * large);
			void Xor(LargeBitboard * large);

		protected:
			/** get bitboard from board array */
			Bitboard GetBoard(unsigned int x, unsigned int y);

			/** get shift size used when set/get cells */
			inline unsigned int GetBitboardShiftSize(unsigned int x, unsigned int y);

			/** get biboard index used when set/get cells */
			inline unsigned int GetBitboardIndex(unsigned int x, unsigned int y);

	};

}


