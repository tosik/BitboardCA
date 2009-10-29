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



#include "bbca.h"

#include <cstdlib>
#include <ctime>

using namespace BitboardCA;

CA::CA(int size_x, int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;
	this->board_size_x = (size_x-1)/8+3;
	this->board_size_y = (size_y-1)/8+3;
	boards.resize(board_size_x * board_size_y, 0ULL);
}

CA::~CA()
{
}

void CA::step()
{
	std::vector<Bitboard> boards2(boards.size());

	// calc outer totalistic each bitboards
	for(int y=1; y<board_size_y-1; y++)
		for(int x=1; x<board_size_x-1; x++)
		{
			boards2[x+y*board_size_x] = stepByOuterTotalistic(
					boards[(x  )+(y  )*board_size_x],
					boards[(x-1)+(y-1)*board_size_x], boards[(x  )+(y-1)*board_size_x], boards[(x+1)+(y-1)*board_size_x],
					boards[(x-1)+(y  )*board_size_x],                                   boards[(x+1)+(y  )*board_size_x],
					boards[(x-1)+(y+1)*board_size_x], boards[(x  )+(y+1)*board_size_x], boards[(x+1)+(y+1)*board_size_x]
			);
		}

	// mask for usable a expect multiple of 8
	// mask X
	static Bitboard mask_x[8] = {
		0xffffffffffffffffULL,
		0x8080808080808080ULL,
		0xc0c0c0c0c0c0c0c0ULL,
		0xe0e0e0e0e0e0e0e0ULL,
		0xf0f0f0f0f0f0f0f0ULL,
		0xf8f8f8f8f8f8f8f8ULL,
		0xfcfcfcfcfcfcfcfcULL,
		0xfefefefefefefefeULL
	};
	for(int i=1; i<board_size_y; i++)
		boards2[i * board_size_x - 2] = boards2[i * board_size_x - 2] & mask_x[size_x % 8];

	// mask Y
	static Bitboard mask_y[8] = {
		0xffffffffffffffffULL,
		0xff00000000000000ULL,
		0xffff000000000000ULL,
		0xffffff0000000000ULL,
		0xffffffff00000000ULL,
		0xffffffffff000000ULL,
		0xffffffffffff0000ULL,
		0xffffffffffffff00ULL
	};
	for(int i=1; i<board_size_x; i++)
	{
		boards2[i + board_size_x * (board_size_y - 2)] = boards2[i + board_size_x * (board_size_y - 2)] & mask_y[size_y % 8];
	}

	boards = boards2;
}

// explanation in japanese http://d.hatena.ne.jp/tosik/20071115/1195120024
Bitboard CA::stepByOuterTotalistic(Bitboard board,
		Bitboard board_a, Bitboard board_b, Bitboard board_c,
		Bitboard board_d,                   Bitboard board_e,
		Bitboard board_f, Bitboard board_g, Bitboard board_h)
{

	Bitboard s0, s1, s2, s3, s4, s5, s6, s7, s8;

	// shift 1 bit to center
	Bitboard a, b, c, d, e, f, g, h;
	a = ( ( board   & 0xfefefefefefefe00ULL ) >> 9  ) | ( ( board_a & 0x0000000000000001ULL ) << 63 ) |
		( ( board_b & 0x00000000000000feULL ) << 55 ) | ( ( board_d & 0x0101010101010100ULL ) >> 1  ) ;
	b = ( ( board   & 0xffffffffffffff00ULL ) >> 8  ) | ( ( board_b & 0x00000000000000ffULL ) << 56 ) ;
	c = ( ( board   & 0x7f7f7f7f7f7f7f00ULL ) >> 7  ) | ( ( board_c & 0x0000000000000080ULL ) << 49 ) |
		( ( board_b & 0x000000000000007fULL ) << 57 ) | ( ( board_e & 0x8080808080808000ULL ) >> 15 ) ;
	d = ( ( board   & 0xfefefefefefefefeULL ) >> 1  ) | ( ( board_d & 0x0101010101010101ULL ) << 7  ) ;
	e = ( ( board   & 0x7f7f7f7f7f7f7f7fULL ) << 1  ) | ( ( board_e & 0x8080808080808080ULL ) >> 7  ) ;
	f = ( ( board   & 0x00fefefefefefefeULL ) << 7  ) | ( ( board_f & 0x0100000000000000ULL ) >> 49 ) |
		( ( board_g & 0xfe00000000000000ULL ) >> 57 ) | ( ( board_d & 0x0001010101010101ULL ) << 15 ) ;
	g = ( ( board   & 0x00ffffffffffffffULL ) << 8  ) | ( ( board_g & 0xff00000000000000ULL ) >> 56 ) ;
	h = ( ( board   & 0x007f7f7f7f7f7f7fULL ) << 9  ) | ( ( board_h & 0x8000000000000000ULL ) >> 63 ) |
		( ( board_g & 0x7f00000000000000ULL ) >> 55 ) | ( ( board_e & 0x0080808080808080ULL ) << 1  ) ;


	// count sums
	// s0..8 are sums of living neighborhoods

	s0 = ~( a | b );
	s1 = a ^ b;
	s2 = a & b;

	s3 = c & s2;
	s2 = ( s2 & ~c ) | ( s1 & c );
	s1 = ( s1 & ~c ) | ( s0 & c );
	s0 = s0 & ~c;

	s4 = d & s3;
	s3 = ( s3 & ~d ) | ( s2 & d );
	s2 = ( s2 & ~d ) | ( s1 & d );
	s1 = ( s1 & ~d ) | ( s0 & d );
	s0 = s0 & ~d;

	s5 = e & s4;
	s4 = ( s4 & ~e ) | ( s3 & e );
	s3 = ( s3 & ~e ) | ( s2 & e );
	s2 = ( s2 & ~e ) | ( s1 & e );
	s1 = ( s1 & ~e ) | ( s0 & e );
	s0 = s0 & ~e;

	s6 = f & s5;
	s5 = ( s5 & ~f ) | ( s4 & f );
	s4 = ( s4 & ~f ) | ( s3 & f );
	s3 = ( s3 & ~f ) | ( s2 & f );
	s2 = ( s2 & ~f ) | ( s1 & f );
	s1 = ( s1 & ~f ) | ( s0 & f );
	s0 = s0 & ~f;

	s7 = g & s6;
	s6 = ( s6 & ~g ) | ( s5 & g );
	s5 = ( s5 & ~g ) | ( s4 & g );
	s4 = ( s4 & ~g ) | ( s3 & g );
	s3 = ( s3 & ~g ) | ( s2 & g );
	s2 = ( s2 & ~g ) | ( s1 & g );
	s1 = ( s1 & ~g ) | ( s0 & g );
	s0 = s0 & ~g;

	s8 = h & s7;
	s7 = ( s7 & ~h ) | ( s6 & h );
	s6 = ( s6 & ~h ) | ( s5 & h );
	s5 = ( s5 & ~h ) | ( s4 & h );
	s4 = ( s4 & ~h ) | ( s3 & h );
	s3 = ( s3 & ~h ) | ( s2 & h );
	s2 = ( s2 & ~h ) | ( s1 & h );
	s1 = ( s1 & ~h ) | ( s0 & h );
	s0 = s0 & ~h;

	// calc optional rule using sums
	return rule(board,s0,s1,s2,s3,s4,s5,s6,s7,s8);
}

inline Bitboard CA::rule(Bitboard board, Bitboard s0, Bitboard s1, Bitboard s2,
		Bitboard s3, Bitboard s4, Bitboard s5, Bitboard s6, Bitboard s7, Bitboard s8 )
{
	return ( ~board & s3 ) | ( board & ( s2 | s3 ) );
}

void CA::view()
{
	std::cout << std::endl;
	for(int y=0; y<size_y; y++)
	{
		for(int x=0; x<size_x; x++)
			std::cout << (getCellState(x,y) ? "* " : "  ");
		std::cout << std::endl;
	}
	for (int x=0; x<size_x*2; x++)
		std::cout << "-";
	std::cout << std::endl;
}

void CA::viewBitboard(Bitboard b)
{
	for(int i=0; i<64; i++)
	{
		if ( b % 2 == 1 )
			std::cout << "* ";
		else
			std::cout << "  ";
		if ( i % 8 == 7 )
			std::cout << std::endl;
		b >>= 1;
	}
	std::cout << "----------------" << std::endl;
}

inline Bitboard CA::getBoard(int x, int y)
{
	return boards[x+y*8];
}

int CA::getSizeX()
{
	return size_x;
}

int CA::getSizeY()
{
	return size_y;
}

void CA::randomize()
{
	srand((unsigned)time(NULL));
	for(int y=0; y<size_y+2; y++)
		for(int x=0; x<size_x+2; x++)
			// generate random number of 64 bit
			boards[x+y*board_size_x] =
				rand() +
				rand() * 0x0000000000010000ULL +
				rand() * 0x0000001000000000ULL +
				rand() * 0x0100000000000000ULL +
				( rand() % 0xf ) * 0x1000000000000000ULL;
}

void CA::clear()
{
	// clear boards array by zero
	for ( std::size_t i = 0 ; i < boards.size() ; i ++ )
	{
		boards[i] = 0ULL;
	}
}

bool CA::getCellState(int x, int y)
{
	return (((boards[x/8+y/8*board_size_x+1+board_size_x] >> (7-x%8)+(7-y%8)*8) % 2 == 1) ? true : false );
}

void CA::setCellState(bool cell, int x, int y)
{
	if ( cell )
		boards[x/8+y/8*board_size_x+1+board_size_x] |= ( (Bitboard)1 << (7-x%8)+(7-y%8)*8 );
	else
		boards[x/8+y/8*board_size_x+1+board_size_x] &= 0xffffffffffffffffULL^( (Bitboard)1 << (7-x%8)+(7-y%8)*8 );
}


