#pragma once

#include <iostream>
#include <vector>

#include "LargeBitboard.h"
#include "OuterTotalisticCA.h"
#include "IViewableBitboard.h"


namespace BitboardCA
{
	/** Cellular Automata class */
	class GenerationOuterTotalisticCA
		: public IViewableBitboard
	{
		private:
			std::size_t m_States;
			OuterTotalisticCA * m_pInnerCA;
			std::vector<LargeBitboard *> m_pWeakList;

		public:
			/** constructor */
			GenerationOuterTotalisticCA(std::size_t size_x, std::size_t size_y, std::size_t states);

			/** destructor */
			virtual ~GenerationOuterTotalisticCA();

			/** step one */
			void Step();

			void Randomize();

			/** instance of inner OuterTotalisticCA setter */
			void SetInnerCAInstance(OuterTotalisticCA * inner_ca);

			std::size_t GetSizeX()
			{
				return m_pWeakList[0]->GetSizeX();
			}

			std::size_t GetSizeY()
			{
				return m_pWeakList[0]->GetSizeY();
			}

			std::size_t GetCellState(std::size_t x, std::size_t y)
			{
				for ( std::size_t i = m_States ; i > 1 ; i -- )
				{
					std::size_t state = i - (std::size_t)1;
					if ( m_pWeakList[state]->GetCellState(x, y) == 1 )
						return state;
				}
				return 0;
			}

			void SetCellState(std::size_t x, std::size_t y, std::size_t state)
			{
				for ( std::size_t i = 0 ; i < m_States ; i ++ )
					m_pWeakList[i]->SetCellState((i == state), x, y);
			}

		protected:

	};

}

