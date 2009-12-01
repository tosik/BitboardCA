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

GenerationOuterTotalisticCA::GenerationOuterTotalisticCA(std::size_t size_x, std::size_t size_y)
	: m_TopCA(size_x, size_y)
{
}

GenerationOuterTotalisticCA::~GenerationOuterTotalisticCA()
{
}

void GenerationOuterTotalisticCA::Step()
{
	BitboardViewer viewer;
	m_TopCA.Step();
	viewer.ViewLargeBitboard(m_TopCA);
}

void GenerationOuterTotalisticCA::Randomize()
{
	m_TopCA.Randomize();
}

