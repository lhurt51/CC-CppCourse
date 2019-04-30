/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 4/27/2019																		*
*																				*
* Assignment Requirement:                                                       *
*                       														*
* (Printing Dates in Various Formats) Dates are commonly printed in several     *
* different formats in business correspondence. Two of the more common          *
* formats are                                                                   *
*   07/21/1955                                                                  *
*   July 21, 1955                                                               *
* Write a program that reads a date in the first format and prints that date    *
* in the second format.                                                         *
*                                                                               *
* I used strtok and it took 8 line of executable code                           *
*                                                                               *
* I also used union and struct (assume month is two digits) and it took 5 lines *
* of executable code.			                     			                *
*																				*
\*******************************************************************************/
(Printing Dates in Various Formats) Dates are commonly printed in several different formats
in business correspondence. Two of the more common formats are
07/21/1955
July 21, 1955
Write a program that reads a date in the first format and prints that date in the second format.

I used strtok and it took 8 line of executable code

I also used union and struct (assume month is two digits) and it took 5 lines of executable code.

#include "DateConverter.class.hpp"

DateConverter::DateConverter(void)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    setUnion((unsigned int)local_tm.tm_mday, (unsigned int)(local_tm.tm_mon + 1), (unsigned int)(local_tm.tm_year + 1900));
}

DateConverter::DateConverter(unsigned int day, unsigned int month, unsigned int year)
{
    if (month > 12 || month == 0)
        throw DateConverter::MonthOutOfRangeException();
    else if (day > 31 || day == 0)
        throw DateConverter::DayOutOfRangeException();
    else
    {
        setUnion(day, month, year);
    }
}

DateConverter::DateConverter(const std::string& date)
{
    if (date.length() != 10)
        throw DateConverter::WrongeFormatException();
    else
    {
        strncpy(dateUnion.dateData, date.c_str(), 10);
        changeDelim('\0');
    }
}

void                    DateConverter::setUnion(unsigned int day, unsigned int month, unsigned int year)
{
    std::string newDate = ((month < 10) ? "0" : "") + std::to_string(month - 1) + "/"
                        + ((day < 10) ? "0" : "") + std::to_string(day) + "/"
                        + std::to_string(year);

    setUnion(newDate);
}

void                    DateConverter::setUnion(const std::string& date)
{
    strncpy(dateUnion.dateData, date.c_str(), 10);
    changeDelim('\0');
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
    return "Date Converter requires a day between the range 1 - 31";
}

const char *DateConverter::WrongeFormatException::what() const throw()
{
    return "Date Converter requires a string MM/DD/YYYY";
}

void   DateConverter::changeDelim(char delim)
{
    dateUnion.dateParse.delimiter1 = delim;
    dateUnion.dateParse.delimiter2 = delim;
}

std::string DateConverter::convertMonthToString(void) const
{
    switch (std::stoi(dateUnion.dateParse.month)) {
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
    return os << dc.convertMonthToString() << " " << dc.dateUnion.dateParse.day << ", " << dc.dateUnion.dateParse.year;
}
