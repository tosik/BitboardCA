#include "LargeBitboard.h"

using namespace BitboardCA;


void DebugCheckSize(LargeBitboard * left, LargeBitboard * right)
{
#if DEBUG
	assert (( left->GetBitboardListSizeX() == right->GetBitboardListSizeX() ) &&
		( left->GetBitboardListSizeY() == right->GetBitboardListSizeY() ));
#endif
}


LargeBitboard::LargeBitboard(unsigned int size_x, unsigned int size_y, bool direct_size_mode)
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


inline Bitboard LargeBitboard::GetBoard(unsigned int x, unsigned int y)
{
	return m_BitboardList[x + y * 8];
}

unsigned int LargeBitboard::GetSizeX()
{
	return m_SizeX;
}

unsigned int LargeBitboard::GetSizeY()
{
	return m_SizeY;
}

void LargeBitboard::Randomize()
{
	for ( unsigned int i = 0 ; i < GetBitboardListSize() ; i ++ )
		// generate random number of 64 bit
		m_BitboardList[i] =
			GetRandom() +
			GetRandom() * 0x0000000000010000ULL +
			GetRandom() * 0x0000001000000000ULL +
			GetRandom() * 0x0100000000000000ULL +
			( GetRandom() % 0xf ) * 0x1000000000000000ULL;
}

void LargeBitboard::Clear()
{
	Clear(m_BitboardList, GetBitboardListSize());
}

void LargeBitboard::Clear(Bitboard * bitboards, unsigned int size)
{
	// clear boards array by zero
	for ( unsigned int i = 0 ; i < size ; i ++ )
	{
		bitboards[i] = 0ULL;
	}
}

inline unsigned int LargeBitboard::GetBitboardIndex(unsigned int x, unsigned int y)
{
	return x / 8 + y / 8 * m_BitboardSizeX + 1 + m_BitboardSizeX;
}
inline unsigned int LargeBitboard::GetBitboardShiftSize(unsigned int x, unsigned int y)
{
	return ( 7 - x % 8 ) + ( 7 - y % 8 ) * 8;
}

unsigned int LargeBitboard::GetCellState(unsigned int x, unsigned int y)
{
	unsigned int bitboard_index = GetBitboardIndex(x, y);
	unsigned int shift_size = GetBitboardShiftSize(x, y);

	return ( m_BitboardList[bitboard_index] >> ( shift_size ) )% 2;
}

void LargeBitboard::SetCellState(bool cell, unsigned int x, unsigned int y)
{
	unsigned int bitboard_index = GetBitboardIndex(x, y);
	unsigned int shift_size = GetBitboardShiftSize(x, y);

	if ( cell )
		m_BitboardList[bitboard_index] |= ( (Bitboard)1 << shift_size );
	else
		m_BitboardList[bitboard_index] &= (Bitboard)0xffffffffffffffffULL ^ ( (Bitboard)1 << shift_size );
}

Bitboard LargeBitboard::GetBitboard(unsigned int x, unsigned int y)
{
	return m_BitboardList[x + y * m_BitboardSizeX];
}

Bitboard LargeBitboard::GetBitboard(unsigned int i)
{
	return m_BitboardList[i];
}

void LargeBitboard::SetBitboard(Bitboard b, unsigned int x, unsigned int y)
{
	m_BitboardList[x + y * m_BitboardSizeX] = b;
}

void LargeBitboard::SetBitboard(Bitboard b, unsigned int i)
{
	m_BitboardList[i] = b;
}

unsigned int LargeBitboard::GetBitboardListSize()
{
	return m_BitboardSizeX * m_BitboardSizeY;
}

unsigned int LargeBitboard::GetBitboardListSizeX()
{
	return m_BitboardSizeX;
}

unsigned int LargeBitboard::GetBitboardListSizeY()
{
	return m_BitboardSizeY;
}

void LargeBitboard::Copy(LargeBitboard * large)
{
	DebugCheckSize(this, large);
	for ( unsigned int i = 0 ; i < GetBitboardListSize() ; i ++ )
		m_BitboardList[i] = large->GetBitboardList()[i];
}

void LargeBitboard::Or(LargeBitboard * large)
{
	DebugCheckSize(this, large);
	for ( unsigned int i = 0 ; i < GetBitboardListSize() ; i ++ )
		m_BitboardList[i] |= large->GetBitboardList()[i];
}

void LargeBitboard::And(LargeBitboard * large)
{
	DebugCheckSize(this, large);
	for ( unsigned int i = 0 ; i < GetBitboardListSize() ; i ++ )
		m_BitboardList[i] &= large->GetBitboardList()[i];
}

void LargeBitboard::Xor(LargeBitboard * large)
{
	DebugCheckSize(this, large);
	for ( unsigned int i = 0 ; i < GetBitboardListSize() ; i ++ )
		m_BitboardList[i] ^= large->GetBitboardList()[i];
}

