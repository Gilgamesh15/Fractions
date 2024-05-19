
#include <limits>       //for std::numeric_limits<T>::min(), std::numeric_limits<T>::max()
#include <numeric>      //for std::gcd, std::abs
#include <string>       //for std::string
#include <type_traits>  //for std::is_integral<T>::value, std::is_same<T, bool>::value, std::is_unsigned<T>::value

namespace Fraction{
/**
 * FRACTION CLASS
 *
 * Type must be an unsigned integer and will specify Fraction upper and lower limits
 * The class is supposed to mimic floating point types but without risk of inaccuracies
 */
template <class T>
class Fraction {
private:
    // members
    T numerator_;
    T denominator_;

    // methods
    void reduce();  // reduces the fraction and eliminates minus sign from denominator

public:
    // constructors
    Fraction(const T &numerator = 0, const T &denominator = 1);  // constructs fraction with default args of 0/1

    // getters
    T getNumerator() const;        // returns numerator
    T getDenominator() const;      // returns denominator
    double toDouble() const;       // returns double approximation
    std::string toString() const;  // retuns "{numerator} / {denominator}"

    // basic mathematical operators on fraction x fraction
    Fraction<T> operator+(const Fraction<T> &other) const;  // adds fraction to fractions
    Fraction<T> operator-(const Fraction<T> &other) const;  // substracts fraction from fractions
    Fraction<T> operator*(const Fraction<T> &other) const;  // multiplies fraction by fraction
    Fraction<T> operator/(const Fraction<T> &other) const;  // divides fraction by fraction

    // basic mathematical operators on fraction x value
    Fraction<T> operator+(const T &rhs) const;  // adds integerlike value to fractions
    Fraction<T> operator-(const T &rhs) const;  // substracts integerlike value from fractions
    Fraction<T> operator*(const T &rhs) const;  // multiplies fraction by integerlike value
    Fraction<T> operator/(const T &rhs) const;  // divides fraction by integerlike value

    /**
     * BASIC MATHEMATICAL OPERATORS ON INTEGERLIKE VALUE X FRACTiON
     *
     * return new fraction that is the result of:
     *
     * integerlike value [ + - * / ] fraction
     */
    friend Fraction<T> operator+(const T &lhs, const Fraction<T> &fraction) { return Fraction<T>(lhs) + fraction; }
    friend Fraction<T> operator-(const T &lhs, const Fraction<T> &fraction) { return Fraction<T>(lhs) - fraction; }
    friend Fraction<T> operator*(const T &lhs, const Fraction<T> &fraction) { return Fraction<T>(lhs) * fraction; }
    friend Fraction<T> operator/(const T &lhs, const Fraction<T> &fraction) { return Fraction<T>(lhs) / fraction; }

    // prefix
    Fraction<T> &operator++();
    Fraction<T> &operator--();

    // postfix
    Fraction<T> operator++(int);
    Fraction<T> operator--(int);

    // shorthand basic mathematical operators on Fraction x fraction
    Fraction<T> &operator+=(const Fraction<T> &other);
    Fraction<T> &operator-=(const Fraction<T> &other);
    Fraction<T> &operator*=(const Fraction<T> &other);
    Fraction<T> &operator/=(const Fraction<T> &other);

    // shorthand basic mathematical operators on Fraction x integerlike value
    Fraction<T> &operator+=(const T &rhs);
    Fraction<T> &operator-=(const T &rhs);
    Fraction<T> &operator*=(const T &rhs);
    Fraction<T> &operator/=(const T &rhs);

    // comparison operators on fraction x fraction
    bool operator==(const Fraction &other) const;
    bool operator!=(const Fraction &other) const;
    bool operator>(const Fraction &other) const;
    bool operator>=(const Fraction &other) const;
    bool operator<(const Fraction &other) const;
    bool operator<=(const Fraction &other) const;

    // comparison operators on fraction x value
    bool operator==(const T &value) const;
    bool operator!=(const T &value) const;
    bool operator>(const T &value) const;
    bool operator>=(const T &value) const;
    bool operator<(const T &value) const;
    bool operator<=(const T &value) const;

    /**
     * COMPARISON OPERATORS FOR INTEGERLIKE VALUE X FRACTION
     *
     * return truth value of:
     *
     * integerlike value [ == != > >= < <= ] fraction
     */
    friend bool operator==(const T &lhs, const Fraction<T> &rhs) { return Fraction<T>(lhs) == rhs; }
    friend bool operator!=(const T &lhs, const Fraction<T> &rhs) { return Fraction<T>(lhs) != rhs; }
    friend bool operator>(const T &lhs, const Fraction<T> &rhs) { return Fraction<T>(lhs) > rhs; }
    friend bool operator>=(const T &lhs, const Fraction<T> &rhs) { return Fraction<T>(lhs) >= rhs; }
    friend bool operator<(const T &lhs, const Fraction<T> &rhs) { return Fraction<T>(lhs) < rhs; }
    friend bool operator<=(const T &lhs, const Fraction<T> &rhs) { return Fraction<T>(lhs) <= rhs; }
};

/**
 * REDUCE - REDUCES THE FRACTION AND FIXES THE PLUS/MINUS SIGHNS
 *
 * Using gcd reduces numerator and denominator.
 * Then it checks if denominator is negative.
 * If it is then we want to change sighn of both numerator and denominator.
 * Due to an overflow problem with changing sighn of numeric limit min,
 * we check if numerator or denominator is numeric limit min,
 * if either or both ore then we act accordingly.
 */
template <typename T>
void Fraction<T>::reduce() {
    T common_divisor = std::gcd(numerator_, denominator_);
    numerator_ /= common_divisor;
    denominator_ /= common_divisor;
    if (denominator_ < 0) {
        if (numerator_ == std::numeric_limits<T>::min()) {
            numerator_ = std::numeric_limits<T>::max() - 1;
            if (denominator_ == std::numeric_limits<T>::min()) {
                denominator_ = std::numeric_limits<T>::max() - 1;
            } else {
                denominator_ = -denominator_;
            }
        } else if (denominator_ == std::numeric_limits<T>::min()) {
            denominator_ = std::numeric_limits<T>::max() - 1;
            if (numerator_ == std::numeric_limits<T>::min()) {
                numerator_ = std::numeric_limits<T>::max() - 1;
            } else {
                numerator_ = -numerator_;
            }
        } else {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }
}

/**
 * CONSTRUCTOR
 *
 * Allows only for unsigned integer types
 * Allows only for non zero denominators
 * Reduces the given fraction
 *
 * Following types allowed:
 *
 * signed char
 * short
 * short int
 * signed short
 * signed short int
 * int
 * signed
 * signed int
 * long
 * long int
 * signed long
 * signed long int
 * long long
 * long long int
 * signed long long
 * signed long long int
 */
template <typename T>
Fraction<T>::Fraction(const T &numerator, const T &denominator) : numerator_(numerator), denominator_(denominator) {
    static_assert(std::is_integral<T>::value, "Template parameter must be an integral type.");
    static_assert(!std::is_same<T, bool>::value, "Bool type is not allowed.");
    static_assert(!std::is_unsigned<T>::value, "Unsigned integral types are not allowed.");
    if (denominator == 0)
        throw std::invalid_argument("Denominator cannot be zero.");
    reduce();
}
/**
 * GETTERS
 *
 * getNumerator
 * getDenominator
 * toDouble
 * toString
 *
 * Self explanatory
 */
template <class T>
T Fraction<T>::getNumerator() const {
    return numerator_;
}

template <class T>
T Fraction<T>::getDenominator() const {
    return denominator_;
}

template <class T>
double Fraction<T>::toDouble() const {
    return static_cast<double>(numerator_) / denominator_;
}

template <class T>
std::string Fraction<T>::toString() const {
    return std::to_string(numerator_) + "/" + std::to_string(denominator_);
}

template <class T>
Fraction<T> Fraction<T>::operator+(const Fraction<T> &other) const {
    return Fraction(numerator_ * other.denominator_ + denominator_ * other.numerator_, denominator_ * other.denominator_);
}

template <class T>
Fraction<T> Fraction<T>::operator-(const Fraction<T> &other) const {
    return Fraction(numerator_ * other.denominator_ - denominator_ * other.numerator_, denominator_ * other.denominator_);
}

template <class T>
Fraction<T> Fraction<T>::operator*(const Fraction<T> &other) const {
    return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
}

template <class T>
Fraction<T> Fraction<T>::operator/(const Fraction<T> &other) const {
    if (other.numerator_ == 0)
        throw std::invalid_argument("Cannot divide by a fraction with a numerator of zero.");
    return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
}

template <class T>
Fraction<T> Fraction<T>::operator+(const T &rhs) const {
    return *this + Fraction(rhs);
}

template <class T>
Fraction<T> Fraction<T>::operator-(const T &rhs) const {
    return *this - Fraction(rhs);
}

template <class T>
Fraction<T> Fraction<T>::operator*(const T &rhs) const {
    return *this * Fraction(rhs);
}

template <class T>
Fraction<T> Fraction<T>::operator/(const T &rhs) const {
    return *this / Fraction(rhs);
}

template <class T>
Fraction<T> &Fraction<T>::operator++() {
    *this += 1;
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator--() {
    *this -= 1;
    return *this;
}

template <class T>
Fraction<T> Fraction<T>::operator++(int) {
    Fraction<T> temp = *this;
    ++(*this);
    return temp;
}

template <class T>
Fraction<T> Fraction<T>::operator--(int) {
    Fraction<T> temp = *this;
    --(*this);
    return temp;
}

template <class T>
Fraction<T> &Fraction<T>::operator+=(const Fraction<T> &other) {
    numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    denominator_ = denominator_ * other.denominator_;
    reduce();
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator-=(const Fraction<T> &other) {
    numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
    denominator_ = denominator_ * other.denominator_;
    reduce();
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator*=(const Fraction<T> &other) {
    numerator_ = numerator_ * other.numerator_;
    denominator_ = denominator_ * other.denominator_;
    reduce();
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator/=(const Fraction<T> &other) {
    if (other.numerator_ == 0) {
        throw std::invalid_argument("Cannot divide by a fraction with a numerator of zero.");
    }
    numerator_ = numerator_ * other.denominator_;
    denominator_ = denominator_ * other.numerator_;
    reduce();
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator+=(const T &rhs) {
    *this = *this + Fraction<T>(rhs);
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator-=(const T &rhs) {
    *this = *this - Fraction<T>(rhs);
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator*=(const T &rhs) {
    *this = *this * Fraction<T>(rhs);
    return *this;
}

template <class T>
Fraction<T> &Fraction<T>::operator/=(const T &rhs) {
    *this = *this / Fraction<T>(rhs);
    return *this;
}

template <class T>
bool Fraction<T>::operator==(const Fraction<T> &other) const {
    return numerator_ * other.denominator_ == denominator_ * other.numerator_;
}

template <class T>
bool Fraction<T>::operator!=(const Fraction<T> &other) const {
    return !(*this == other);
}

template <class T>
bool Fraction<T>::operator>(const Fraction<T> &other) const {
    return numerator_ * other.denominator_ > denominator_ * other.numerator_;
}

template <class T>
bool Fraction<T>::operator<(const Fraction<T> &other) const {
    return numerator_ * other.denominator_ < denominator_ * other.numerator_;
}

template <class T>
bool Fraction<T>::operator>=(const Fraction<T> &other) const {
    return !(*this < other);
}

template <class T>
bool Fraction<T>::operator<=(const Fraction<T> &other) const {
    return !(*this > other);
}

template <class T>
bool Fraction<T>::operator==(const T &value) const {
    return *this == Fraction<T>(value);
}

template <class T>
bool Fraction<T>::operator!=(const T &value) const {
    return *this != Fraction<T>(value);
}

template <class T>
bool Fraction<T>::operator>(const T &value) const {
    return *this > Fraction<T>(value);
}

template <class T>
bool Fraction<T>::operator>=(const T &value) const {
    return *this >= Fraction<T>(value);
}

template <class T>
bool Fraction<T>::operator<(const T &value) const {
    return *this < Fraction<T>(value);
}

template <class T>
bool Fraction<T>::operator<=(const T &value) const {
    return *this <= Fraction<T>(value);
}

template <class T>
bool operator==(const T &lhs, const Fraction<T> &rhs) {
    return Fraction<T>(lhs) == rhs;
}

template <class T>
bool operator!=(const T &lhs, const Fraction<T> &rhs) {
    return Fraction<T>(lhs) != rhs;
}

template <class T>
bool operator>(const T &lhs, const Fraction<T> &rhs) {
    return Fraction<T>(lhs) > rhs;
}

template <class T>
bool operator>=(const T &lhs, const Fraction<T> &rhs) {
    return Fraction<T>(lhs) >= rhs;
}

template <class T>
bool operator<(const T &lhs, const Fraction<T> &rhs) {
    return Fraction<T>(lhs) < rhs;
}

template <class T>
bool operator<=(const T &lhs, const Fraction<T> &rhs) {
    return Fraction<T>(lhs) <= rhs;
}

}
