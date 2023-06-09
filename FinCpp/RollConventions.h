#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;

namespace FinCpp::Basics
{
	enum class RollConventions
	{
		DAY_1 = 1,
		DAY_2 = 2,
		DAY_3 = 3,
		DAY_4 = 4,
		DAY_5 = 5,
		DAY_6 = 6,
		DAY_7 = 7,
		DAY_8 = 8,
		DAY_9 = 9,
		DAY10 = 10,
		DAY11 = 11,
		DAY12 = 12,
		DAY_13 = 13,
		DAY_14 = 14,
		DAY_15 = 15,
		DAY_16 = 16,
		DAY_17 = 17,
		DAY_18 = 18,
		DAY_19 = 19,
		DAY_20 = 20,
		DAY_21 = 21,
		DAY_22 = 22,
		DAY_23 = 23,
		DAY_24 = 24,
		DAY_25 = 25,
		DAY_26 = 26,
		DAY_27 = 27,
		DAY_28 = 28,
		DAY_29 = 29,
		DAY_30 = 30,
		EOM = 31,
		NONE = 0,
		IMM = 100,
		DAY_SUN = 101,
		DAY_MON = 102,
		DAY_TUE = 103,
		DAY_WED = 104,
		DAY_THU = 105,
		DAY_FRI = 106,
		DAY_SAT = 107
	};
}

