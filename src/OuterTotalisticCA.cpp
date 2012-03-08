#include "OuterTotalisticCA.h"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include "BitboardViewer.h"

using namespace BitboardCA;

OuterTotalisticCA::OuterTotalisticCA(std::size_t size_x, std::size_t size_y)
	: LargeBitboard(size_x, size_y)
{
}

OuterTotalisticCA::~OuterTotalisticCA()
{
}

void OuterTotalisticCA::Step()
{
	BitboardViewer viewer;
	LargeBitboard new_large_bitboard(m_BitboardSizeX, m_BitboardSizeY, true);
	new_large_bitboard.Clear();

	// calc outer totalistic each bitboards
	for ( std::size_t y = 1 ; y < m_BitboardSizeY - 1 ; y++ )
	{
		for ( std::size_t x = 1 ; x < m_BitboardSizeX - 1 ; x++ )
		{
			new_large_bitboard.SetBitboard(StepByOuterTotalistic(
					m_BitboardList[(x  ) + (y  ) * m_BitboardSizeX],
					m_BitboardList[(x-1) + (y-1) * m_BitboardSizeX],
					m_BitboardList[(x  ) + (y-1) * m_BitboardSizeX],
					m_BitboardList[(x+1) + (y-1) * m_BitboardSizeX],
					m_BitboardList[(x-1) + (y  ) * m_BitboardSizeX],
					m_BitboardList[(x+1) + (y  ) * m_BitboardSizeX],
					m_BitboardList[(x-1) + (y+1) * m_BitboardSizeX],
					m_BitboardList[(x  ) + (y+1) * m_BitboardSizeX],
					m_BitboardList[(x+1) + (y+1) * m_BitboardSizeX]
			), x, y);
		}
	}

	// mask for usable a expect multiple of 8
	// mask X
	const static Bitboard MASK_X[8] = {
		0xffffffffffffffffULL,
		0x8080808080808080ULL,
		0xc0c0c0c0c0c0c0c0ULL,
		0xe0e0e0e0e0e0e0e0ULL,
		0xf0f0f0f0f0f0f0f0ULL,
		0xf8f8f8f8f8f8f8f8ULL,
		0xfcfcfcfcfcfcfcfcULL,
		0xfefefefefefefefeULL
	};
	for ( std::size_t i = 1 ; i < m_BitboardSizeY ; i ++)
		new_large_bitboard.SetBitboard(
				new_large_bitboard.GetBitboard(i * m_BitboardSizeX - 2) & MASK_X[m_SizeX % 8],
				i * m_BitboardSizeX - 2);

	// mask Y
	const static Bitboard MASK_Y[8] = {
		0xffffffffffffffffULL,
		0xff00000000000000ULL,
		0xffff000000000000ULL,
		0xffffff0000000000ULL,
		0xffffffff00000000ULL,
		0xffffffffff000000ULL,
		0xffffffffffff0000ULL,
		0xffffffffffffff00ULL
	};
	for ( std::size_t i = 1 ; i < m_BitboardSizeX ; i ++)
		new_large_bitboard.SetBitboard(
				new_large_bitboard.GetBitboard(i + m_BitboardSizeX * (m_BitboardSizeY - 2)) & MASK_Y[m_SizeY % 8],
				i + m_BitboardSizeX * (m_BitboardSizeY - 2));

	// copy back
	for ( std::size_t i = 0 ; i < GetBitboardListSize() ; i ++ )
		m_BitboardList[i] = new_large_bitboard.GetBitboard(i);
}

// explanation in japanese http://d.hatena.ne.jp/tosik/20071115/1195120024
Bitboard OuterTotalisticCA::StepByOuterTotalistic(Bitboard board,
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
	return Rule(board, s0, s1, s2, s3, s4, s5, s6, s7, s8);
}
