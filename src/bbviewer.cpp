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

#include "bbviewer.h"


namespace BitboardCA
{
	BitboardViewer::BitboardViewer(std::ostream * ostream)
	{
		m_pOstream = ostream;
	}

	void BitboardViewer::ViewBitboardLine(Bitboard b, std::size_t y)
	{
		b >>= y * 8;
		for ( std::size_t i = 0 ; i < 8 ; i++ )
		{
			if ( b % 2 == 1 )
				(*m_pOstream) << "* ";
			else
				(*m_pOstream) << "  ";
			b >>= 1;
		}
	}

	void BitboardViewer::ViewBitboard(Bitboard b)
	{
		for ( std::size_t i = 0 ; i < 8 ; i++ )
		{
			ViewBitboardLine(b, i);
			(*m_pOstream) << std::endl;
		}
	}

	void BitboardViewer::ViewBitboardInfo(Bitboard * bitboards, std::size_t size_x, std::size_t size_y)
	{
		(*m_pOstream) << "---- Bitboard List Info ----" << std::endl;
		(*m_pOstream) << "Size = (" << size_x << ", " << size_y << ")" << std::endl;

		for ( std::size_t y = 0 ; y < size_y ; y++ )
		{
			for ( std::size_t yy = 0 ; yy < 8 ; yy++ )
			{
				for ( std::size_t x = 0 ; x < size_x ; x++ )
				{
					ViewBitboardLine(bitboards[size_x - x - 1 + (size_y - y - 1) * size_x], yy);
					(*m_pOstream) << "|";
				}
				(*m_pOstream) << std::endl;
			}
			for ( std::size_t x = 0 ; x < size_x ; x++ )
				(*m_pOstream) << "---------------- ";
			(*m_pOstream) << std::endl;
		}
	}

}
