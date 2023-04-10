#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "DateUtils.h"

using boost::gregorian::date;

namespace FinCpp::Basics {
	class DayCountBase {
	protected:
		/**
		 * Returns the number of calendar days in the period [startInclusive,endExclusive).
		 * Refer here: https://en.wikipedia.org/wiki/Day_count_convention.
		 * \param startInclusive
		 * \param endExclusive
		 * \return 
		 */
		inline int daysBetween(date startInclusive, date endExclusive) {
			return (endExclusive - startInclusive).days();
		}
	};
	/**
	 * .
	 */
	class DayCountAct360 : DayCountBase
	{
	public:
		inline double yearFraction(date d1, date d2)
		{
			return daysBetween(d1, d2) / 360;
		}
	};

	/**
	 * ACT/ACT assumes that a year consists of 365 or 366 days (in case of a leap year), and that the days
	 * between dates s and t, s prior to t, are counted as the actual number of calendar days between the two
	 * dates, including the first but not the second.
	 * 
	 * If s and t are dates belonging to the same year and n is the actual number of days in the year, then the 
	 * year fraction equals (t - s)/n. 
	 * 
	 * If s and t are dates belonging to two different years, let J_i be the first of January of the second year,
	 * J_f be the first of January of the final year, n_i be the number of days in the first year, n_f be the number
	 * of days of the final year, and y the number of years between the first and the final year, then the year 
	 * fraction equals (J_i - s)/n_i + y + (t - J_f)/n_f
	 */
	class DayCountActAct : DayCountBase
	{
	public:
		inline double yearFraction(date d1, date d2)
		{
			int y1{ d1.year() };
			int y2{ d2.year() };

			if (y1 == y2)
			{
				return (d2 - d1).days() / DateUtils::lengthOfYear(y1);
			}
			else {
				auto j_i{ date(y1 + 1,1,1) };
				auto j_f{ date(y2,1,1) };
				auto n_i = DateUtils::lengthOfYear(y1);
				auto n_f = DateUtils::lengthOfYear(y2);
				auto y = y2 - y1;
				return (j_i - d1).days() / n_i + y + (d2 - j_f).days() / n_f;
			}
		}
	};

	/**
	 * ACT/365 convention assumes that the year consists of 365 days (there is no distinction
	 * between leap years and non-leap years). 
	 */
	class DayCountAct365 :DayCountBase
	{
	public:
		inline double yearFraction(date d1, date d2)
		{
			return daysBetween(d1, d2) / 365;
		}
	};

	class DayCount30360ISDA : DayCountBase
	{
	public:
		inline double yearFraction(date d1, date d2)
		{
			date startDate{ d1 };
			date endDate{ d2 };

			if (d2.day() == 31 && d1.day() > 29)
			{
				endDate = date(d2.year(), d2.month(), 30);
			}

			if (d1.day() == 31)
			{
				startDate = date(d1.year(), d1.month(), 30);
			}

			return (360 * (endDate.year() - startDate.year()) + 30 * (endDate.month() - startDate.month()) + (endDate.day() - startDate.day())) / 360;
		}
	};
}

