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



#include "GenerationOuterTotalisticCA.h"

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include "BitboardViewer.h"

using namespace BitboardCA;


//#define VIEW_DEBUG_1
#define VIEW_DEBUG_2
//#define VIEW_DEBUG_3


GenerationOuterTotalisticCA::GenerationOuterTotalisticCA(std::size_t size_x, std::size_t size_y)
	: m_TopCA(size_x, size_y)
{
	for ( int i = 0 ; i < 4 ; i ++ )
		m_pWeakList[i] = new LargeBitboard(size_x, size_y, false);
}

GenerationOuterTotalisticCA::~GenerationOuterTotalisticCA()
{
	for ( int i = 0 ; i < 4 ; i ++ )
		delete m_pWeakList[i];
}

void GenerationOuterTotalisticCA::Step()
{
	std::size_t size_x = m_TopCA.GetSizeX();
	std::size_t size_y = m_TopCA.GetSizeY();

	BitboardViewer viewer;

	// step(3) => A
	LargeBitboard A(size_x, size_y);
	m_TopCA.Copy(m_pWeakList[3]);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(m_TopCA);
#endif
	m_TopCA.Step();
	A.Copy(&m_TopCA);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(A);
#endif

	// 2 or 1 or 0 => B
	LargeBitboard B(size_x, size_y);
	B.Copy(m_pWeakList[2]);
	B.Or(m_pWeakList[1]);
	B.Or(m_pWeakList[0]);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(B);
#endif

	// A - B => C
	LargeBitboard C(size_x, size_y);
	C.Copy(&A);
	C.Or(&B);
	C.Xor(&B);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(C);
#endif

	// 3 - C => D
	LargeBitboard D(size_x, size_y);
	D.Copy(m_pWeakList[3]);
	D.Or(&C);
	D.Xor(&C);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(D);
#endif

	// copy back
	m_pWeakList[0]->Copy(m_pWeakList[1]);
	m_pWeakList[1]->Copy(m_pWeakList[2]);
	m_pWeakList[2]->Copy(&D);
	m_pWeakList[3]->Copy(&C);

#ifdef VIEW_DEBUG_2
	viewer.ViewLargeBitboardForDebug(m_TopCA);
#endif
#ifdef VIEW_DEBUG_3
	for ( int i = 3 ; i >= 0 ; i -- )
	{
		printf("i = %d\n", i);
		viewer.ViewLargeBitboardForDebug(*m_pWeakList[i]);
	}
#endif
}

void GenerationOuterTotalisticCA::Randomize()
{
	m_pWeakList[3]->Randomize();
	//m_pWeakList[3]->SetCellState(true, 4, 4);
	//m_pWeakList[3]->SetCellState(true, 5, 4);
	//m_pWeakList[3]->SetCellState(true, 4, 5);
	//m_pWeakList[3]->SetCellState(true, 3, 4);
	//m_pWeakList[3]->SetCellState(true, 4, 3);
}

