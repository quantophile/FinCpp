#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

namespace FinCpp::Basics{
	class SchedulePeriod
	{
	public:
		boost::gregorian::date getUnadjustedStartDate();
		boost::gregorian::date getUnadjustedEndDate();
		boost::gregorian::date getStartDate();
		boost::gregorian::date getEndDate();
	private:
		boost::gregorian::date m_unadjustedStartDate;
		boost::gregorian::date m_unadjustedEndDate;
		boost::gregorian::date m_startDate;
		boost::gregorian::date m_endDate;
	};
}
