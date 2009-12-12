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
//#define VIEW_DEBUG_2
//#define VIEW_DEBUG_3


GenerationOuterTotalisticCA::GenerationOuterTotalisticCA(std::size_t size_x, std::size_t size_y, std::size_t states)
	: m_TopCA(size_x, size_y)
	, m_States(states)
{
	if ( states < 2 )
		throw; // TODO : exception

	for ( std::size_t i = 0 ; i < states ; i ++ )
		m_pWeakList.push_back(new LargeBitboard(size_x, size_y, false));
}

GenerationOuterTotalisticCA::~GenerationOuterTotalisticCA()
{
	for ( std::vector<LargeBitboard*>::iterator it = m_pWeakList.begin() ;
	   it != m_pWeakList.end() ; it ++ )
		delete (*it);
}

void GenerationOuterTotalisticCA::Step()
{
	std::size_t size_x = m_TopCA.GetSizeX();
	std::size_t size_y = m_TopCA.GetSizeY();

	BitboardViewer viewer;

	// step(m_States - 1) => A
	LargeBitboard A(size_x, size_y);
	m_TopCA.Copy(m_pWeakList[m_States - 1]);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(m_TopCA);
#endif
	m_TopCA.Step();
	A.Copy(&m_TopCA);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(A);
#endif

	// or(m_States - 1 .. 0) => B
	LargeBitboard B(size_x, size_y);
	B.Copy(m_pWeakList[m_States - 2]);
	for ( std::size_t i = 0 ; i <= m_States - 3 ; i ++ )
	{
		B.Or(m_pWeakList[i]);
	}
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

	// m_States - 1 - C => D
	LargeBitboard D(size_x, size_y);
	D.Copy(m_pWeakList[m_States - 1]);
	D.Or(&C);
	D.Xor(&C);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug(D);
#endif

	// copy back
	for ( std::size_t i = 0 ; i <= m_States - 3 ; i ++ )
		m_pWeakList[i]->Copy(m_pWeakList[i+1]);
	m_pWeakList[m_States - 2]->Copy(&D);
	m_pWeakList[m_States - 1]->Copy(&C);

#ifdef VIEW_DEBUG_2
	viewer.ViewLargeBitboardForDebug(m_TopCA);
#endif
#ifdef VIEW_DEBUG_3
	for ( int i = m_States - 1 ; i >= 0 ; i -- )
	{
		printf("i = %d\n", i);
		viewer.ViewLargeBitboardForDebug(*m_pWeakList[i]);
	}
#endif
}

void GenerationOuterTotalisticCA::Randomize()
{
	m_pWeakList[m_States - 1]->Randomize();
}

