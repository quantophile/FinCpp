#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace FinCpp::Basics {
	enum class HolidayCalendarId {
		Target = 1,
		LON = 2,
		US = 3
	};

	class HolidayCalendar {
	public:
		HolidayCalendar();
		HolidayCalendar(HolidayCalendarId id);
		HolidayCalendar(HolidayCalendarId id, boost::date_time::weekdays firstWeekendDay, boost::date_time::weekdays secondWeekendDay);
		HolidayCalendar(const HolidayCalendar& h);
		bool isHoliday(boost::gregorian::date d) const; 
		bool isBusDay(boost::gregorian::date d) const;
	private:
		std::vector<boost::gregorian::date> m_holidayDates;
		boost::date_time::weekdays m_firstWeekendDay;
		boost::date_time::weekdays m_secondWeekendDay;
		HolidayCalendarId m_holidayCalendarId;
		void generateSchedule(HolidayCalendarId id);
		void removeSatSun();
	};
}
