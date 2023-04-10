#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_calendar.hpp>
#include "DayOfWeek.h"

namespace FinCpp::Basics {
	class DateUtils {
	public:
		static inline bool isLeapYear(int year)
		{
			return ((year % 4 == 0) && (!(year % 100 == 0))) || (year % 400 == 0);
		}
		
		static inline boost::gregorian::date ensureLeapDay(boost::gregorian::date input)
		{
			if (isLeapYear(input.year())) {
				return boost::gregorian::date(input.year(), 2, 29);
			}
			else {
				if (isLeapYear(input.year()+1))
					return boost::gregorian::date(input.year() + 1, 2, 29);
				if (isLeapYear(input.year() + 2))
					return boost::gregorian::date(input.year() + 2, 2, 29);
				if (isLeapYear(input.year() + 3))
					return boost::gregorian::date(input.year() + 3, 2, 29);
			}
		}

		static inline boost::gregorian::date nextLeapDay(boost::gregorian::date input)
		{
			int yy = input.year();

			/**  
			* Handle if already a leap day, move forward either 4 or 8 years
			*/
			if (input.month() == 2 && input.day() == 29)
			{
				if (isLeapYear(yy))
				{
					return ensureLeapDay(boost::gregorian::date(yy + 4, 2, 29));
				}
			}

			/**
			 * Handle if before February 29 in a leap year.
			 */
			if (input.month() <= 2 && isLeapYear(input.year()))
			{
				return boost::gregorian::date(input.year(), 2, 29);
			}

			/**
			 * Handle any other date.
			 */
			int yy = static_cast<int>(input.year() / 4) * 4;
			return ensureLeapDay(boost::gregorian::date(yy + 4, 2, 29));
		}

		/**
		 * Get the number of days in the month.
		 * 
		 * \param d
		 * \return 
		 */
		static inline int getLengthOfMonth(boost::gregorian::date d)
		{
			return d.end_of_month().day();
		}

		static inline boost::gregorian::date firstInMonth(int year, int month, boost::date_time::weekdays dow)
		{
			auto firstOfMonth = boost::gregorian::date(year, month, 1);
			auto result{ firstOfMonth };

			while (result.day_of_week() != dow)
			{
				result = result + boost::gregorian::days(1);
			}

			return result;
		}

		static inline boost::gregorian::date lastInMonth(int year, int month, boost::date_time::weekdays dow)
		{
			auto firstOfMonth = boost::gregorian::date(year, month, 1);
			auto numDays = getLengthOfMonth(firstOfMonth);
			auto endOfMonth = boost::gregorian::date(year, month, numDays);

			auto result{ endOfMonth };
			
			while (result.day_of_week() != dow)
			{
				result -= boost::gregorian::days(1);
			}
		}

		/**
		 * Meeus/John/Butcher's algorithm to calculate the Easter day of any given year.
		 * 
		 * \param year
		 * \return Easter date
		 */
		static inline boost::gregorian::date easter(int year)
		{
			int a = year % 19;
			int b = static_cast<int>(year / 100);
			int c = year % 100;
			int d = static_cast<int>(b /4);
			int e = b % 4;
			int f = static_cast<int>((b + 8) / 25);
			int g = (b - f + 1);
			int h = (19 * a + b - d - g + 15) % 30;
			int i = static_cast<int>(c / 4);
			int k = c % 4;
			int l = (32 + 2 * e + 2 * i - h - k) % 7;
			int m = static_cast<int>((a + 11 * h + 22 * l) / 451);
			int month = static_cast<int>((h + l - 7 * m + 114) / 31);
			int dd = ((h + l - 7 * m + 114) % 31) + 1;

			return boost::gregorian::date(year, month, dd);
		}
		
	};
}
