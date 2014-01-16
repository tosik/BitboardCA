#pragma once

#include "LargeBitboard.h"


namespace BitboardCA
{
	/** Cellular Automata class */
	class OuterTotalisticCA
		: public LargeBitboard
	{

		public:
			/** constructor */
			OuterTotalisticCA(std::size_t size_x, std::size_t size_y);

			/** destructor */
			virtual ~OuterTotalisticCA();

			/** step one */
			void Step();

			/** Update Bitboard by Outer Totalistic */
			Bitboard StepByOuterTotalistic(Bitboard board,
					Bitboard board_a, Bitboard board_b, Bitboard board_c,
					Bitboard board_d,                   Bitboard board_e,
					Bitboard board_f, Bitboard board_g, Bitboard board_h);

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

	};

}

