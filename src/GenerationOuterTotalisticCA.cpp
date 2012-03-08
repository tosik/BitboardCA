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
	: m_States(states)
	, m_pInnerCA(NULL)
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
	std::size_t size_x = m_pInnerCA->GetSizeX();
	std::size_t size_y = m_pInnerCA->GetSizeY();

	BitboardViewer viewer;

	// step(m_States - 1) => A
	LargeBitboard A(size_x, size_y);
	m_pInnerCA->Copy(m_pWeakList[m_States - 1]);
#ifdef VIEW_DEBUG_1
	viewer.ViewLargeBitboardForDebug((*m_pInnerCA));
#endif
	m_pInnerCA->Step();
	A.Copy(&(*m_pInnerCA));
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
	viewer.ViewLargeBitboardForDebug((*m_pInnerCA));
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

void GenerationOuterTotalisticCA::SetInnerCAInstance(OuterTotalisticCA * inner_ca)
{
	m_pInnerCA = inner_ca;
}

