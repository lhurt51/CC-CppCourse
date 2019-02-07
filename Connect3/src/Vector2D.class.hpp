#ifndef VECTOR2D_CLASS_HPP
  #define VECTOR2D_CLASS_HPP

  #include <includes.hpp>

  // Vector class for computations
  class Vector2D {
    // Declaring private variables
    int   _x;
    int   _y;

  public:

    // Default constructor
    Vector2D(void);
    // Main constructor
    Vector2D(int x, int y);
    // Copy constructor
    Vector2D(Vector2D const &src);
    // The deconstructor
    ~Vector2D(void);

    // The getters
    int     getX(void) const;
    int     getY(void) const;
    // The setters
    void              setX(int x);
    void              setY(int y);

    // Overload operators
    Vector2D          &operator=(Vector2D const &rhs);
    Vector2D          operator+(Vector2D const &rhs) const;
    Vector2D          operator-(Vector2D const &rhs) const;
    Vector2D          operator*(Vector2D const &rhs) const;
    Vector2D          operator/(Vector2D const &rhs) const;
    bool              operator==(Vector2D const &rhs) const;
    bool              operator!=(Vector2D const &rhs) const;

  };

  // To print the vector
  std::ostream	&operator<<(std::ostream &o, Vector2D const &i);

#endif
