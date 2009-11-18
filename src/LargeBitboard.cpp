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



#include "LargeBitboard.h"

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstdio>

using namespace BitboardCA;

LargeBitboard::LargeBitboard(std::size_t size_x, std::size_t size_y, bool direct_size_mode)
{
	m_SizeX = size_x;
	m_SizeY = size_y;

	if ( direct_size_mode )
	{
		m_BitboardSizeX = size_x;
		m_BitboardSizeY = size_y;
	}
	else
	{
		m_BitboardSizeX = (size_x-1)/8+3;
		m_BitboardSizeY = (size_y-1)/8+3;
	}

	m_BitboardList = new Bitboard[GetBitboardListSize()];
	Clear();
}

LargeBitboard::~LargeBitboard()
{
	delete [] m_BitboardList;
}

Bitboard * LargeBitboard::GetBitboardList()
{
	return m_BitboardList;
}


inline Bitboard LargeBitboard::GetBoard(std::size_t x, std::size_t y)
{
	return m_BitboardList[x + y * 8];
}

std::size_t LargeBitboard::GetSizeX()
{
	return m_SizeX;
}

std::size_t LargeBitboard::GetSizeY()
{
	return m_SizeY;
}

void LargeBitboard::Randomize()
{
	srand((unsigned)time(NULL));
	for ( std::size_t i = 0 ; i < GetBitboardListSize() ; i ++ )
		// generate random number of 64 bit
		m_BitboardList[i] =
			rand() +
			rand() * 0x0000000000010000ULL +
			rand() * 0x0000001000000000ULL +
			rand() * 0x0100000000000000ULL +
			( rand() % 0xf ) * 0x1000000000000000ULL;
}

void LargeBitboard::Clear()
{
	Clear(m_BitboardList, GetBitboardListSize());
}

void LargeBitboard::Clear(Bitboard * bitboards, std::size_t size)
{
	// clear boards array by zero
	for ( std::size_t i = 0 ; i < size ; i ++ )
	{
		bitboards[i] = 0ULL;
	}
}

inline std::size_t LargeBitboard::GetBitboardIndex(std::size_t x, std::size_t y)
{
	return x / 8 + y / 8 * m_BitboardSizeX + 1 + m_BitboardSizeX;
}
inline std::size_t LargeBitboard::GetBitboardShiftSize(std::size_t x, std::size_t y)
{
	return ( 7 - x % 8 ) + ( 7 - y % 8 ) * 8;
}

bool LargeBitboard::GetCellState(std::size_t x, std::size_t y)
{
	std::size_t bitboard_index = GetBitboardIndex(x, y);
	std::size_t shift_size = GetBitboardShiftSize(x, y);

	return ( ( m_BitboardList[bitboard_index] >> ( shift_size ) ) % 2 == 1 );
}

void LargeBitboard::SetCellState(bool cell, std::size_t x, std::size_t y)
{
	std::size_t bitboard_index = GetBitboardIndex(x, y);
	std::size_t shift_size = GetBitboardShiftSize(x, y);

	if ( cell )
		m_BitboardList[bitboard_index] |= ( (Bitboard)1 << shift_size );
	else
		m_BitboardList[bitboard_index] &= (Bitboard)0xffffffffffffffffULL ^ ( (Bitboard)1 << shift_size );
}

Bitboard LargeBitboard::GetBitboard(std::size_t x, std::size_t y)
{
	return m_BitboardList[x + y * m_BitboardSizeX];
}

Bitboard LargeBitboard::GetBitboard(std::size_t i)
{
	return m_BitboardList[i];
}

void LargeBitboard::SetBitboard(Bitboard b, std::size_t x, std::size_t y)
{
	m_BitboardList[x + y * m_BitboardSizeX] = b;
}

void LargeBitboard::SetBitboard(Bitboard b, std::size_t i)
{
	m_BitboardList[i] = b;
}

std::size_t LargeBitboard::GetBitboardListSize()
{
	return m_BitboardSizeX * m_BitboardSizeY;
}

std::size_t LargeBitboard::GetBitboardListSizeX()
{
	return m_BitboardSizeX;
}

std::size_t LargeBitboard::GetBitboardListSizeY()
{
	return m_BitboardSizeY;
}


