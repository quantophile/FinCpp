#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "SchedulePeriod.h"

namespace FinCpp::Basics {
	class Schedule {
	private:
		std::vector<SchedulePeriod> m_schedulePeriods;
	};
}
