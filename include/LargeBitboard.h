#pragma once

#include "bbcommon.h"
#include "IViewableBitboard.h"

#include <cstddef>


namespace BitboardCA
{
	/** Large Bitboard class */
	class LargeBitboard
		: public IViewableBitboard
	{
		protected:
			/** size of board */
			std::size_t m_SizeX, m_SizeY;

			/** number of bitboard */
			std::size_t m_BitboardSizeX, m_BitboardSizeY;

			/** bitboard array */
			Bitboard * m_BitboardList;


		public:
			/** constructor */
			LargeBitboard(std::size_t size_x, std::size_t size_y, bool direct_size_mode=false);

			/** destructor */
			virtual ~LargeBitboard();

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
			std::size_t GetCellState(std::size_t x, std::size_t y);

			/** set a state of cell */
			void SetCellState(bool cell, std::size_t x, std::size_t y);

			/** get a bitboard */
			Bitboard GetBitboard(std::size_t x, std::size_t y);
			Bitboard GetBitboard(std::size_t i);

			/** set a bitboard */
			void SetBitboard(Bitboard bitboard, std::size_t x, std::size_t y);
			void SetBitboard(Bitboard bitboard, std::size_t i);

			/** get size of bitboard list */
			std::size_t GetBitboardListSize();

			/** get size x of bitboard list */
			std::size_t GetBitboardListSizeX();

			/** get size y of bitboard list */
			std::size_t GetBitboardListSizeY();

			/** get biboard list*/
			Bitboard * GetBitboardList();

			void Copy(LargeBitboard * large);
			void Or(LargeBitboard * large);
			void And(LargeBitboard * large);
			void Xor(LargeBitboard * large);

		protected:
			/** get bitboard from board array */
			Bitboard GetBoard(std::size_t x, std::size_t y);

			/** get shift size used when set/get cells */
			inline std::size_t GetBitboardShiftSize(std::size_t x, std::size_t y);

			/** get biboard index used when set/get cells */
			inline std::size_t GetBitboardIndex(std::size_t x, std::size_t y);

	};

}


