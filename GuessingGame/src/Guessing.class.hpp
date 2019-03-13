#ifndef GUESSING_CLASS_HPP
    #define GUESSING_CLASS_HPP

    #include <typedefs.hpp>
    #include <vector>

    template<typename T>
    class Guessing {

        std::vector<T>  _guessingList;
        T               _playerInput;

    public:

        Guessing(std::vector<T> guessingList, T playerInput);
        Guessing(Guessing const &src);
        ~Guessing(void);

        Guessing&        operator=(const Guessing& rhs);

        std::vector<T>  getGuessingList(void) const;
        T               getPlayerInput(void) const;

        int             binarySearch(const std::vector<T>& vec, int start, int end, const T& key);

    };

#endif
