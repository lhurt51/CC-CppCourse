#ifndef DATA_CONVERTER_CLASS_HPP
    #define DATA_CONVERTER_CLASS_HPP

    #include <iostream>
    #include <chrono>
    #include <stdexcept>

    class DateConverter
    {

        enum                    Month
        {
                                JANUARY,
                                FEBRUARY,
                                MARCH,
                                APRIL,
                                MAY,
                                JUNE,
                                JULY,
                                AUGUST,
                                SEPTEMBER,
                                OCTOBER,
                                NOVEMBER,
                                DECEMBER,
                                NUM_OF_MONTHS
        };

        Month                   m_month;
        unsigned int            m_day;
        unsigned int            m_year;

    public:

        DateConverter(void);
        DateConverter(unsigned int day, unsigned int month, unsigned int year);

        void                    printDate(void) const;

        class                   MonthOutOfRangeException : public std::exception
        {
        public:
            virtual const char *what() const throw();
        };

        class                   DayOutOfRangeException : public std::exception
        {
        public:
            virtual const char *what() const throw();
        };

    private:

        std::string             convertMonthToString(void) const;

        friend std::ostream&    operator<<(std::ostream &os, const DateConverter& dc);

    };

#endif
