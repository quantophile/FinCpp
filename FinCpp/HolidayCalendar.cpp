#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "HolidayCalendar.h"
#include "DateUtils.h"

using boost::gregorian::date;
using boost::gregorian::days;

namespace FinCpp::Basics {

	HolidayCalendar::HolidayCalendar():m_holidayCalendarId  {HolidayCalendarId::Target}, 
		m_firstWeekendDay{boost::date_time::weekdays::Saturday}, m_secondWeekendDay{boost::date_time::weekdays::Sunday}
	{
		generateSchedule(m_holidayCalendarId);
	}

	HolidayCalendar::HolidayCalendar(HolidayCalendarId holidayCalendarId) :m_holidayCalendarId{ holidayCalendarId }, 
		m_firstWeekendDay{ boost::date_time::weekdays::Saturday }, m_secondWeekendDay{ boost::date_time::weekdays::Sunday }
	{
		generateSchedule(m_holidayCalendarId);
	}

	HolidayCalendar::HolidayCalendar(HolidayCalendarId id, boost::date_time::weekdays firstWeekendDay, boost::date_time::weekdays secondWeekendDay) :m_holidayCalendarId{ id },
		m_firstWeekendDay{ firstWeekendDay }, m_secondWeekendDay{ secondWeekendDay }
	{
	}

	HolidayCalendar::HolidayCalendar(const HolidayCalendar& h) : m_holidayCalendarId{ h.m_holidayCalendarId },
		m_firstWeekendDay{ h.m_firstWeekendDay }, m_secondWeekendDay{ h.m_secondWeekendDay }, m_holidayDates{ h.m_holidayDates }
	{
	}

	void HolidayCalendar::removeSatSun()
	{
		std::vector<date> holidays;

		for (auto& x : m_holidayDates)
		{
			if (!(x.day_of_week() == boost::date_time::weekdays::Saturday || x.day_of_week() == boost::date_time::weekdays::Sunday))
			{
				holidays.push_back(x);
			}
		}

		m_holidayDates = holidays;
	}

	void HolidayCalendar::generateSchedule(HolidayCalendarId holidayCalendarId) {
		switch (holidayCalendarId)
		{
		case HolidayCalendarId::Target:
			for (auto year{ 1950 }; year <= 2100; ++year)
			{
				if (year >= 2000)
				{
					m_holidayDates.push_back(date(year, 1, 1));
					m_holidayDates.push_back(DateUtils::easter(year) - days(2));
					m_holidayDates.push_back(DateUtils::easter(year) + days(1));
					m_holidayDates.push_back(date(year, 5, 1));
					m_holidayDates.push_back(date(year, 12, 25));
					m_holidayDates.push_back(date(year, 12, 26));
				}
				else
				{
					m_holidayDates.push_back(date(year, 1, 1));
					m_holidayDates.push_back(date(year, 12, 25));
				}

				if (year == 1999 || year == 2001)
				{
					m_holidayDates.push_back(date(year, 12, 31));
				}

				removeSatSun();
			}
			break;
		case HolidayCalendarId::LON:
			break;
		case HolidayCalendarId::US:
			break;
		default:
			break;
		}
	}

	bool HolidayCalendar::isHoliday(date d)
	{
		auto result = std::find_if(m_holidayDates.begin(), m_holidayDates.end(), d);
		if (d.day_of_week() == m_firstWeekendDay || d.day_of_week() == m_secondWeekendDay)
		{
			return true;
		}
		else
		{
			return (result != std::end(m_holidayDates));
		}
	}

	bool HolidayCalendar::isBusDay(date d)
	{
		return !(isHoliday(d));
	}
}
