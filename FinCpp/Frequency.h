#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "PeriodType.h"

namespace FinCpp::Basics {
	class Frequency
	{
	public:
		Frequency() : m_numOfPeriods{ 1 }, m_unit{ PeriodType::YEARS } {}
		Frequency(std::string freq)
		{
			m_numOfPeriods = stoi(freq.substr(0, freq.length() - 2));
			m_unit = static_cast<PeriodType>(freq[freq.length() - 1]);
		}
		Frequency(int numPeriods, PeriodType periodType) : m_numOfPeriods{numPeriods}, m_unit {periodType} {}
	private:
		int m_numOfPeriods;
		PeriodType m_unit;
	};
}
