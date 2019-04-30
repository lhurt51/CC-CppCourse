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

        union
        {
            struct
            {
                char month[2];
                char delimiter1;
                char day[2];
                char delimiter2;
                char year[4];
            } dateParse;
            char dateData[10];
        } dateUnion;

    public:

        DateConverter(void);
        DateConverter(unsigned int day, unsigned int month, unsigned int year);
        DateConverter(const std::string& date);

        void                    setUnion(unsigned int day, unsigned int month, unsigned int year);
        void                    setUnion(const std::string& date);

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

        class                   WrongeFormatException : public std::exception
        {
        public:
            virtual const char *what() const throw();
        };

    private:

        void                    changeDelim(char delim);

        std::string             convertMonthToString(void) const;

        friend std::ostream&    operator<<(std::ostream &os, const DateConverter& dc);

    };

#endif
