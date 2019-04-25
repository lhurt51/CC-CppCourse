#include "DateConverter.class.hpp"

DateConverter::DateConverter(void)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);

    m_year = local_tm.tm_year + 1900;
    m_month = (Month)((unsigned int)local_tm.tm_mon);
    m_day = local_tm.tm_mday;
}

DateConverter::DateConverter(unsigned int day, unsigned int month, unsigned int year) : m_year(year)
{
    if (month > 12 || month == 0)
        throw DateConverter::MonthOutOfRangeException();
    else if (day > 31 || day == 0)
        throw DateConverter::DayOutOfRangeException();
    else
    {
        this->m_month = (Month)((unsigned int)(month - 1));
        this->m_day = day;
    }
}

void   DateConverter::printDate(void) const
{
    std::cout << *this << std::endl;
}

const char *DateConverter::MonthOutOfRangeException::what() const throw()
{
    return "Date Converter requires a month between the range 1 - 12";
}

const char *DateConverter::DayOutOfRangeException::what() const throw()
{
    return "Date Converter requires a month between the range 1 - 31";
}

std::string DateConverter::convertMonthToString(void) const
{
    switch (m_month) {
        case JANUARY:
            return "January";
        case FEBRUARY:
            return "February";
        case MARCH:
            return "March";
        case APRIL:
            return "April";
        case MAY:
            return "May";
        case JUNE:
            return "June";
        case JULY:
            return "July";
        case AUGUST:
            return "August";
        case SEPTEMBER:
            return "September";
        case OCTOBER:
            return "October";
        case NOVEMBER:
            return "November";
        case DECEMBER:
            return "December";
        default:
            return "Bad Month Value";
    }
}

std::ostream& operator<<(std::ostream &os, const DateConverter& dc)
{
    return os << dc.convertMonthToString() << " " << dc.m_day << ", " << dc.m_year;
}
