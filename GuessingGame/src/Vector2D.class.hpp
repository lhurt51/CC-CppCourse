#ifndef VECTOR2D_CLASS_HPP
  #define VECTOR2D_CLASS_HPP

  #include <includes.hpp>
  #include <tuple>
  #include <set>
  #include <cfloat>
  #include <climits>

  template<typename T>
  class Vector2D {
  public:

    T x;
    T y;

    // Default constructor
    Vector2D(void);
    // Single int Constructor
    Vector2D(const T& vxy);
    // Main constructor
    Vector2D(const T& vx, const T& vy);
    // Copy constructor
    Vector2D(const Vector2D& src);

    // Overload operators --
    Vector2D&               operator=(const Vector2D& v);
    Vector2D&               operator+=(const Vector2D& v);
    Vector2D&               operator-=(const Vector2D& v);
    Vector2D&               operator*=(const Vector2D& v);
    Vector2D&               operator/=(const Vector2D& v);
    Vector2D&               operator*=(const T& s);
    Vector2D&               operator/=(const T& s);
    Vector2D                operator-(void) const;

    friend bool             operator>(const Vector2D& l, const Vector2D& r) { return std::tie(l.x, l.y) < std::tie(r.x, r.y); };
    friend bool             operator<(const Vector2D& l, const Vector2D& r) { return r < l; };
    friend bool             operator>=(const Vector2D& l, const Vector2D& r) { return !(l < r); };
    friend bool             operator<=(const Vector2D& l, const Vector2D& r) { return !(r < l); };
    friend bool             operator==(const Vector2D& l, const Vector2D& r) { return std::tie(l.x, l.y) == std::tie(r.x, r.y); };
    friend bool             operator!=(const Vector2D& l, const Vector2D& r) { return !(l == r); };

    friend std::ostream&    operator<<(std::ostream& o, const Vector2D& i) { return o << "Vector2D (" << i.x << "," << i.y << ")"; };
  };

  // Regular math operator overloads --
  template<typename T>
  Vector2D<T>               operator+(const Vector2D<T>& l, const Vector2D<T>& r);
  template<typename T>
  Vector2D<T>               operator-(const Vector2D<T>& l, const Vector2D<T>& r);
  template<typename T>
  Vector2D<T>               operator*(const Vector2D<T>& l, const Vector2D<T>& r);
  template<typename T>
  Vector2D<T>               operator/(const Vector2D<T>& l, const Vector2D<T>& r);
  // Scalar operator overloads --
  template<typename T>
  Vector2D<T>               operator*(const T& s, const Vector2D<T>& v);
  template<typename T>
  Vector2D<T>               operator*(const Vector2D<T>& v, const T& s);
  template<typename T>
  Vector2D<T>               operator/(const T& s, const Vector2D<T>& v);
  template<typename T>
  Vector2D<T>               operator/(const Vector2D<T>& v, const T& s);

#endif
