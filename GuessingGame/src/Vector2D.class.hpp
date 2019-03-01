#ifndef VECTOR2D_CLASS_HPP
  #define VECTOR2D_CLASS_HPP

  #include <iostream>
  #include <tuple>
  #include <cmath>
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
    Vector2D                operator-(void) const { return Vector2D<T>(-x, -y); };

    friend bool             operator<(const Vector2D& l, const Vector2D& r) { return std::tie(l.x, l.y) < std::tie(r.x, r.y); };
    friend bool             operator<=(const Vector2D& l, const Vector2D& r) { return !(l < r); };
    friend bool             operator>(const Vector2D& l, const Vector2D& r) { return r < l; };
    friend bool             operator>=(const Vector2D& l, const Vector2D& r) { return !(r < l); };
    friend bool             operator==(const Vector2D& l, const Vector2D& r) { return std::tie(l.x, l.y) == std::tie(r.x, r.y); };
    friend bool             operator!=(const Vector2D& l, const Vector2D& r) { return !(l == r); };

    friend std::ostream&    operator<<(std::ostream& o, const Vector2D& i) { return o << "Vector2D (" << i.x << "," << i.y << ")"; };
  };

  // Regular math operator overloads --
  template<typename T>
  Vector2D<T>               operator+(const Vector2D<T>& l, const Vector2D<T>& r) { return Vector2D<T>(l) += r; };
  template<typename T>
  Vector2D<T>               operator-(const Vector2D<T>& l, const Vector2D<T>& r) { return Vector2D<T>(l) -= r; };
  template<typename T>
  Vector2D<T>               operator*(const Vector2D<T>& l, const Vector2D<T>& r) { return Vector2D<T>(l) *= r; };
  template<typename T>
  Vector2D<T>               operator/(const Vector2D<T>& l, const Vector2D<T>& r) { return Vector2D<T>(l) /= r; };
  // Scalar operator overloads --
  template<typename T>
  Vector2D<T>               operator*(const T& s, const Vector2D<T>& v) { return Vector2D<T>(v) *= s; };
  template<typename T>
  Vector2D<T>               operator*(const Vector2D<T>& v, const T& s) { return Vector2D<T>(v) *= s; };
  template<typename T>
  Vector2D<T>               operator/(const T& s, const Vector2D<T>& v) { return Vector2D<T>(v) /= s; };
  template<typename T>
  Vector2D<T>               operator/(const Vector2D<T>& v, const T& s) { return Vector2D<T>(v) /= s; };

  // Utility Functions
  template<typename T>
  extern T                  DotProduct(const Vector2D<T>& a, const Vector2D<T>& b);
  template<typename T>
  extern T                  CrossProduct(const Vector2D<T>& a, const Vector2D<T>& b);
  template<typename T>
  T                         EuclideanNorm(const Vector2D<T>& v);
  template<typename T>
  Vector2D<T>               Normal(const Vector2D<T>& v);
  template<typename T>
  Vector2D<T>               Perpendicular(const Vector2D<T>& v);
  template<typename T>
  bool                      Inersect(const Vector2D<T>& line1A, const Vector2D<T>& line1B, const Vector2D<T>& line2A, const Vector2D<T>& line2B);
  template<typename T>
  Vector2D<T>               GetInersect(const Vector2D<T>& line1A, const Vector2D<T>& line1B, const Vector2D<T>& line2A, const Vector2D<T>& line2B);

#endif
