#include "BitboardViewer.h"


namespace BitboardCA
{
	BitboardViewer::BitboardViewer(std::ostream * ostream)
	{
		m_pOstream = ostream;
	}

	std::string GetCellString(std::size_t s)
	{
		switch ((int)s)
		{
			case 0:
				return " ";
			case 1:
				return "*";
			case 2:
				return "o";
			case 3:
				return "@";
			default:
				return "!";
		}
	}

	void BitboardViewer::ViewBitboard(IViewableBitboard & viewable)
	{
		for ( std::size_t y = 0 ; y < viewable.GetSizeY() ; y ++ )
		{
			for ( std::size_t x = 0 ; x < viewable.GetSizeX() ; x ++ )
				(*m_pOstream) << GetCellString(viewable.GetCellState(x, y)).c_str() << " ";
			(*m_pOstream) << std::endl;
		}
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

	void BitboardViewer::ViewLargeBitboard(Bitboard * bitboards, std::size_t size_x, std::size_t size_y)
	{
		LargeBitboard large_bitboard(size_x, size_y, true);
		for ( std::size_t y = 0 ; y < size_y ; y ++ )
			for ( std::size_t x = 0 ; x < size_x ; x ++ )
				large_bitboard.SetBitboard(bitboards[x + y * size_x], x, y);

		ViewLargeBitboard(large_bitboard);
	}

	void BitboardViewer::ViewLargeBitboard(LargeBitboard & large_bitboard)
	{
		std::size_t size_x = large_bitboard.GetBitboardListSizeX();
		std::size_t size_y = large_bitboard.GetBitboardListSizeY();

		for ( std::size_t y = 0 ; y < size_y ; y++ )
		{
			for ( std::size_t yy = 0 ; yy < 8 ; yy++ )
			{
				for ( std::size_t x = 0 ; x < size_x ; x++ )
				{
					ViewBitboardLine(large_bitboard.GetBitboard(size_x - x - 1, (size_y - y - 1)), yy);
					(*m_pOstream) << "|";
				}
				(*m_pOstream) << std::endl;
			}
			for ( std::size_t x = 0 ; x < size_x ; x++ )
				(*m_pOstream) << "---------------- ";
			(*m_pOstream) << std::endl;
		}
	}

	void BitboardViewer::ViewLargeBitboardForDebug(LargeBitboard & large_bitboard)
	{
		std::size_t size_x = large_bitboard.GetBitboardListSizeX();
		std::size_t size_y = large_bitboard.GetBitboardListSizeY();

		for ( std::size_t y = 1 ; y < size_y - 1 ; y++ )
		{
			for ( std::size_t yy = 0 ; yy < 8 ; yy++ )
			{
				for ( std::size_t x = 1 ; x < size_x - 1 ; x++ )
				{
					ViewBitboardLine(large_bitboard.GetBitboard(size_x - x - 1, (size_y - y - 1)), yy);
					(*m_pOstream) << "|";
				}
				(*m_pOstream) << std::endl;
			}
			for ( std::size_t x = 1 ; x < size_x - 1 ; x++ )
				(*m_pOstream) << "---------------- ";
			(*m_pOstream) << std::endl;
		}
	}

}
