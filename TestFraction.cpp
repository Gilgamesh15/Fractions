#include <array>
#include <limits>

#include <backend/cpp/Fractions.hpp>
#include <gtest/gtest.h>

namespace Fraction{
// test if no argument constructor throws
TEST(FractionTest, DefaultConstructor) {
    EXPECT_NO_THROW(Fraction<long>());
}

// test if numerator only argument constructor throws
TEST(FractionTest, OneArgumentConstruction) {
    constexpr long max_long = std::numeric_limits<long>::max();
    constexpr long min_long = std::numeric_limits<long>::min();

    EXPECT_NO_THROW(Fraction<long>{max_long});
    EXPECT_NO_THROW(Fraction<long>{3});
    EXPECT_NO_THROW(Fraction<long>{0});
    EXPECT_NO_THROW(Fraction<long>{-3});
    EXPECT_NO_THROW(Fraction<long>{min_long});
}

// test if numerator two argument constructor throws
TEST(FractionTest, TwoArgumentConstruction) {
    // for big positive denominator
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::max(), std::numeric_limits<long>::max()));
    EXPECT_NO_THROW(Fraction<long>(4, std::numeric_limits<long>::max()));
    EXPECT_NO_THROW(Fraction<long>(0, std::numeric_limits<long>::max()));
    EXPECT_NO_THROW(Fraction<long>(4, std::numeric_limits<long>::max()));
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::min(), std::numeric_limits<long>::max()));

    // for positive denominator
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::max(), 3));
    EXPECT_NO_THROW(Fraction<long>(4, 3));
    EXPECT_NO_THROW(Fraction<long>(0, 3));
    EXPECT_NO_THROW(Fraction<long>(-4, 3));
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::min(), 3));

    // for zero denominator
    EXPECT_THROW(Fraction<long>(std::numeric_limits<long>::max(), 0), std::invalid_argument);
    EXPECT_THROW(Fraction<long>(4, 0), std::invalid_argument);
    EXPECT_THROW(Fraction<long>(0, 0), std::invalid_argument);
    EXPECT_THROW(Fraction<long>(-4, 0), std::invalid_argument);
    EXPECT_THROW(Fraction<long>(std::numeric_limits<long>::min(), 0), std::invalid_argument);

    // for negative denominator
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::max(), -3));
    EXPECT_NO_THROW(Fraction<long>(4, -3));
    EXPECT_NO_THROW(Fraction<long>(0, -3));
    EXPECT_NO_THROW(Fraction<long>(-4, -3));
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::min(), -3));

    // for big negative denominator
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::max(), std::numeric_limits<long>::min()));
    EXPECT_NO_THROW(Fraction<long>(4, std::numeric_limits<long>::min()));
    EXPECT_NO_THROW(Fraction<long>(0, std::numeric_limits<long>::min()));
    EXPECT_NO_THROW(Fraction<long>(-4, std::numeric_limits<long>::min()));
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::min(), std::numeric_limits<long>::min()));
}

// test valid templates not throwing
TEST(FractionTest, ProperTemplateConstruction) {
    EXPECT_NO_THROW(Fraction<signed char>(std::numeric_limits<signed char>::max(), 4));
    EXPECT_NO_THROW(Fraction<short>(std::numeric_limits<short>::max(), 4));
    EXPECT_NO_THROW(Fraction<short int>(std::numeric_limits<short int>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed short>(std::numeric_limits<signed short>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed short int>(std::numeric_limits<signed short int>::max(), 4));
    EXPECT_NO_THROW(Fraction<int>(std::numeric_limits<int>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed>(std::numeric_limits<signed>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed int>(std::numeric_limits<signed int>::max(), 4));
    EXPECT_NO_THROW(Fraction<long>(std::numeric_limits<long>::max(), 4));
    EXPECT_NO_THROW(Fraction<long int>(std::numeric_limits<long int>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed long>(std::numeric_limits<signed long>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed long int>(std::numeric_limits<signed long int>::max(), 4));
    EXPECT_NO_THROW(Fraction<long long>(std::numeric_limits<long long>::max(), 4));
    EXPECT_NO_THROW(Fraction<long long int>(std::numeric_limits<long long int>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed long long>(std::numeric_limits<signed long long>::max(), 4));
    EXPECT_NO_THROW(Fraction<signed long long int>(std::numeric_limits<signed long long int>::max(), 4));
}

// test if getMumerator properly returns numerator
TEST(FractionTest, GetNumerator) {
    Fraction<long> f1(std::numeric_limits<long>::max(), 823);
    EXPECT_EQ(f1.getNumerator(), std::numeric_limits<long>::max());

    Fraction<long> f2(3, 823);
    EXPECT_EQ(f2.getNumerator(), 3);

    Fraction<long> f3(0, 823);
    EXPECT_EQ(f3.getNumerator(), 0);

    Fraction<long> f4(-3, 823);
    EXPECT_EQ(f4.getNumerator(), -3);

    Fraction<long> f5(std::numeric_limits<long>::min(), 823);
    EXPECT_EQ(f5.getNumerator(), std::numeric_limits<long>::min());
}

// test if getDenominator properly returns denominator
TEST(FractionTest, GetDenominator) {
    Fraction<long> f1(823, std::numeric_limits<long>::max());
    EXPECT_EQ(f1.getDenominator(), std::numeric_limits<long>::max());

    Fraction<long> f2(823, 3);
    EXPECT_EQ(f2.getDenominator(), 3);

    Fraction<long> f4(823, -3);
    EXPECT_EQ(f4.getDenominator(), 3);

    Fraction<long> f5(823, std::numeric_limits<long>::min());
    EXPECT_EQ(f5.getDenominator(), std::numeric_limits<long>::max() - 1);
}

// test if toDouble properly calculates the approximation
TEST(FractionTest, ToDouble) {
    // for denominator max
    Fraction<long> f1(std::numeric_limits<long>::max(), std::numeric_limits<long>::max());
    Fraction<long> f2(3, std::numeric_limits<long>::max());
    Fraction<long> f3(0, std::numeric_limits<long>::max());
    Fraction<long> f4(-3, std::numeric_limits<long>::max());
    Fraction<long> f5(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());

    EXPECT_DOUBLE_EQ(f1.toDouble(), static_cast<double>(std::numeric_limits<long>::max()) / std::numeric_limits<long>::max());
    EXPECT_DOUBLE_EQ(f2.toDouble(), static_cast<double>(3) / std::numeric_limits<long>::max());
    EXPECT_DOUBLE_EQ(f3.toDouble(), static_cast<double>(0) / std::numeric_limits<long>::max());
    EXPECT_DOUBLE_EQ(f4.toDouble(), static_cast<double>(-3) / std::numeric_limits<long>::max());
    EXPECT_DOUBLE_EQ(f5.toDouble(), static_cast<double>(std::numeric_limits<long>::min()) / std::numeric_limits<long>::max());

    // for denominator positive
    Fraction<long> f6(std::numeric_limits<long>::max(), 3);
    Fraction<long> f7(3, 3);
    Fraction<long> f8(0, 3);
    Fraction<long> f9(-3, 3);
    Fraction<long> f10(std::numeric_limits<long>::min(), 3);

    EXPECT_DOUBLE_EQ(f6.toDouble(), static_cast<double>(std::numeric_limits<long>::max()) / 3);
    EXPECT_DOUBLE_EQ(f7.toDouble(), static_cast<double>(3) / 3);
    EXPECT_DOUBLE_EQ(f8.toDouble(), static_cast<double>(0) / 3);
    EXPECT_DOUBLE_EQ(f9.toDouble(), static_cast<double>(-3) / 3);
    EXPECT_DOUBLE_EQ(f10.toDouble(), static_cast<double>(std::numeric_limits<long>::min()) / 3);

    // for denominator negative
    Fraction<long> f11(std::numeric_limits<long>::max(), -3);
    Fraction<long> f12(3, -3);
    Fraction<long> f13(0, -3);
    Fraction<long> f14(-3, -3);
    Fraction<long> f15(std::numeric_limits<long>::min(), -3);

    EXPECT_DOUBLE_EQ(f11.toDouble(), static_cast<double>(std::numeric_limits<long>::max()) / -3);
    EXPECT_DOUBLE_EQ(f12.toDouble(), static_cast<double>(3) / -3);
    EXPECT_DOUBLE_EQ(f13.toDouble(), static_cast<double>(0) / -3);
    EXPECT_DOUBLE_EQ(f14.toDouble(), static_cast<double>(-3) / -3);
    EXPECT_DOUBLE_EQ(f15.toDouble(), static_cast<double>(std::numeric_limits<long>::min()) / -3);

    // for denominator min
    Fraction<long> f16(std::numeric_limits<long>::max(), std::numeric_limits<long>::min());
    Fraction<long> f17(3, std::numeric_limits<long>::min());
    Fraction<long> f18(0, std::numeric_limits<long>::min());
    Fraction<long> f19(-3, std::numeric_limits<long>::min());
    Fraction<long> f20(std::numeric_limits<long>::min(), std::numeric_limits<long>::min());

    EXPECT_DOUBLE_EQ(f16.toDouble(), static_cast<double>(std::numeric_limits<long>::max()) / std::numeric_limits<long>::min());
    EXPECT_DOUBLE_EQ(f17.toDouble(), static_cast<double>(3) / std::numeric_limits<long>::min());
    EXPECT_DOUBLE_EQ(f18.toDouble(), static_cast<double>(0) / std::numeric_limits<long>::min());
    EXPECT_DOUBLE_EQ(f19.toDouble(), static_cast<double>(-3) / std::numeric_limits<long>::min());
    EXPECT_DOUBLE_EQ(f20.toDouble(), static_cast<double>(std::numeric_limits<long>::min()) / std::numeric_limits<long>::min());
}

// test if to string properly gives back formatted Fraction
TEST(FractionTest, toString) {
    Fraction<long> f(-13, 7);
    EXPECT_EQ(f.toString(), "-13/7");
}

// Test if reducing fractions eliminates minus in denominator and simplifies properly
TEST(FractionTest, reduction) {
    Fraction<long> f1(121, 11);
    EXPECT_EQ(f1.getNumerator(), 11);
    EXPECT_EQ(f1.getDenominator(), 1);
    Fraction<long> f2(11, -121);
    EXPECT_EQ(f2.getNumerator(), -1);
    EXPECT_EQ(f2.getDenominator(), 11);
}
TEST(FractionTest, Addition) {
    Fraction<long int> f1(1, 2);
    Fraction<long int> f2(1, 3);
    Fraction<long int> f3(2, -3);
    Fraction<long int> result = f1 + f2;
    EXPECT_EQ(result.getNumerator(), 5);
    EXPECT_EQ(result.getDenominator(), 6);
    result = f1 + f3;
    EXPECT_EQ(result.getNumerator(), -1);
    EXPECT_EQ(result.getDenominator(), 6);
}
TEST(FractionTest, substraction) {
    Fraction<long int> f1(1, 2);
    Fraction<long int> f2(1, 3);
    Fraction<long int> f3(2, -3);
    Fraction<long int> result = f1 - f2;
    EXPECT_EQ(result.getNumerator(), 1);
    EXPECT_EQ(result.getDenominator(), 6);
    result = f1 - f3;
    EXPECT_EQ(result.getNumerator(), 7);
    EXPECT_EQ(result.getDenominator(), 6);
}
TEST(FractionTest, multiplication) {
    Fraction<long int> f1(1, 2);
    Fraction<long int> f2(1, 3);
    Fraction<long int> f3(2, -3);
    Fraction<long int> result = f1 * f2;
    EXPECT_EQ(result.getNumerator(), 1);
    EXPECT_EQ(result.getDenominator(), 6);
    result = f1 * f3;
    EXPECT_EQ(result.getNumerator(), -1);
    EXPECT_EQ(result.getDenominator(), 3);
}
TEST(FractionTest, division) {
    Fraction<long int> f1(1, 2);
    Fraction<long int> f2(1, 3);
    Fraction<long int> f3(2, -3);
    Fraction<long int> result = f1 / f2;
    EXPECT_EQ(result.getNumerator(), 3);
    EXPECT_EQ(result.getDenominator(), 2);
    result = f1 / f3;
    EXPECT_EQ(result.getNumerator(), -3);
    EXPECT_EQ(result.getDenominator(), 4);
}
TEST(FractionTest, PrefixAddition) {
    Fraction<long int> f1(-3, 4);
    ++f1;
    EXPECT_EQ(f1.getNumerator(), 1);
    EXPECT_EQ(f1.getDenominator(), 4);
}
TEST(FractionTest, PostfixAddition) {
    Fraction<long int> f1(-3, 4);
    f1++;
    EXPECT_EQ(f1.getNumerator(), 1);
    EXPECT_EQ(f1.getDenominator(), 4);
}
TEST(FractionTest, PrefixSubstraction) {
    Fraction<long int> f1(-3, 4);
    --f1;
    EXPECT_EQ(f1.getNumerator(), -7);
    EXPECT_EQ(f1.getDenominator(), 4);
}
TEST(FractionTest, PostfixSubstraction) {
    Fraction<long int> f1(-3, 4);
    f1--;
    EXPECT_EQ(f1.getNumerator(), -7);
    EXPECT_EQ(f1.getDenominator(), 4);
}
TEST(FractionTest, ShortHandAddition) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    f1 += f2;
    EXPECT_EQ(f1.getNumerator(), -1);
    EXPECT_EQ(f1.getDenominator(), 2);
}
TEST(FractionTest, ShortHandSubstraction) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    f1 -= f2;
    EXPECT_EQ(f1.getNumerator(), -1);
    EXPECT_EQ(f1.getDenominator(), 1);
}
TEST(FractionTest, ShortHandMultiplication) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    f1 *= f2;
    EXPECT_EQ(f1.getNumerator(), -3);
    EXPECT_EQ(f1.getDenominator(), 16);
}
TEST(FractionTest, ShortHandDivision) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    f1 /= f2;
    EXPECT_EQ(f1.getNumerator(), -3);
    EXPECT_EQ(f1.getDenominator(), 1);
}
TEST(FractionTest, Equality) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    Fraction<long int> f3(-3, 4);
    EXPECT_EQ(f1 == f2, false);
    EXPECT_EQ(f1 == f3, true);
}
TEST(FractionTest, Inequality) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    Fraction<long int> f3(-3, 4);
    EXPECT_EQ(f1 != f2, true);
    EXPECT_EQ(f1 != f3, false);
}
TEST(FractionTest, GreaterThen) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    Fraction<long int> f3(-5, 4);
    EXPECT_EQ(f1 >= f1, true);
    EXPECT_EQ(f1 >= f2, false);
    EXPECT_EQ(f1 >= f3, true);
}
TEST(FractionTest, GreaterOrEqualThen) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    Fraction<long int> f3(-5, 4);
    EXPECT_EQ(f1 >= f1, true);
    EXPECT_EQ(f1 >= f2, false);
    EXPECT_EQ(f1 >= f3, true);
}
TEST(FractionTest, LesserThen) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    Fraction<long int> f3(-5, 4);
    EXPECT_EQ(f1 < f1, false);
    EXPECT_EQ(f1 < f2, true);
    EXPECT_EQ(f1 < f3, false);
}
TEST(FractionTest, LesserOrEqualThen) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2(1, 4);
    Fraction<long int> f3(-5, 4);
    EXPECT_EQ(f1 <= f1, true);
    EXPECT_EQ(f1 <= f2, true);
    EXPECT_EQ(f1 <= f3, false);
}
TEST(FractionTest, Assignment) {
    Fraction<long int> f1(-3, 4);
    Fraction<long int> f2;
    f2 = f1;
    EXPECT_EQ(f2.getNumerator(), -3);
    EXPECT_EQ(f2.getDenominator(), 4);
}
TEST(FractionTest, FractionAndInts) {
    Fraction<long int> f1(-3, 4);
    f1 += 2;
    EXPECT_EQ(f1.getNumerator(), 5);
    EXPECT_EQ(f1.getDenominator(), 4);
    f1 -= 4;
    EXPECT_EQ(f1.getNumerator(), -11);
    EXPECT_EQ(f1.getDenominator(), 4);
    f1 *= 2;
    EXPECT_EQ(f1.getNumerator(), -11);
    EXPECT_EQ(f1.getDenominator(), 2);
    f1 /= 4;
    EXPECT_EQ(f1.getNumerator(), -11);
    EXPECT_EQ(f1.getDenominator(), 8);

    Fraction<long int> f2(-4, 1);
    EXPECT_EQ((-4) == f2, true);
    EXPECT_EQ((-4) != f2, false);
    EXPECT_EQ((4) == f2, false);
    EXPECT_EQ((4) != f2, true);
    EXPECT_EQ((-4) <= f2, true);
    EXPECT_EQ((-4) >= f2, true);
    EXPECT_EQ((-4) < f2, false);
    EXPECT_EQ((-4) > f2, false);

    EXPECT_EQ(f2 == -4, true);
    EXPECT_EQ(f2 != -4, false);
    EXPECT_EQ(f2 == 4, false);
    EXPECT_EQ(f2 != 4, true);
    EXPECT_EQ(f2 <= -4, true);
    EXPECT_EQ(f2 >= -4, true);
    EXPECT_EQ(f2 < -4, false);
    EXPECT_EQ(f2 > -4, false);

    EXPECT_EQ((-3) == f2, false);
    EXPECT_EQ((-3) != f2, true);
    EXPECT_EQ((3) == f2, false);
    EXPECT_EQ((3) != f2, true);
    EXPECT_EQ((-3) <= f2, false);
    EXPECT_EQ((-3) >= f2, true);
    EXPECT_EQ((-3) < f2, false);
    EXPECT_EQ((-3) > f2, true);

    EXPECT_EQ(f2 == -3, false);
    EXPECT_EQ(f2 != -3, true);
    EXPECT_EQ(f2 == 3, false);
    EXPECT_EQ(f2 != 3, true);
    EXPECT_EQ(f2 <= -3, true);
    EXPECT_EQ(f2 >= -3, false);
    EXPECT_EQ(f2 < -3, true);
    EXPECT_EQ(f2 > -3, false);

    EXPECT_EQ((-5) == f2, false);
    EXPECT_EQ((-5) != f2, true);
    EXPECT_EQ((5) == f2, false);
    EXPECT_EQ((5) != f2, true);
    EXPECT_EQ((-5) <= f2, true);
    EXPECT_EQ((-5) >= f2, false);
    EXPECT_EQ((-5) < f2, true);
    EXPECT_EQ((-5) > f2, false);

    EXPECT_EQ(f2 == -5, false);
    EXPECT_EQ(f2 != -5, true);
    EXPECT_EQ(f2 == 5, false);
    EXPECT_EQ(f2 != 5, true);
    EXPECT_EQ(f2 <= -5, false);
    EXPECT_EQ(f2 >= -5, true);
    EXPECT_EQ(f2 < -5, false);
    EXPECT_EQ(f2 > -5, true);
}

}
