#include <gtest/gtest.h>
#include "../include/money.h"

TEST(MoneyTest, DefaultConstructor) {
    Money m;
    EXPECT_EQ(m.toString(), "0");
}

TEST(MoneyTest, StringConstructor) {
    Money m("12345");
    EXPECT_EQ(m.toString(), "12345");

    Money m2("0");
    EXPECT_EQ(m2.toString(), "0");

    Money m3("999999");
    EXPECT_EQ(m3.toString(), "999999");
}

TEST(MoneyTest, CopyAssignmentOperator) {
    Money m1("12345");
    Money m2("67890");

    m2 = m1;

    EXPECT_EQ(m1.toString(), m2.toString());

    m1 += Money("10000");
    EXPECT_NE(m1.toString(), m2.toString());
}

TEST(MoneyTest, MoveConstructor) {
    Money m1("12345");
    Money m2 = std::move(m1);

    EXPECT_EQ(m2.toString(), "12345");

    EXPECT_EQ(m1.toString(), "0");
}

TEST(MoneyTest, MoveAssignmentOperator) {
    Money m1("12345");
    Money m2("67890");

    m2 = std::move(m1);

    EXPECT_EQ(m2.toString(), "12345");

    EXPECT_EQ(m1.toString(), "0");
}

TEST(MoneyTest, SubtractionOperation) {
    Money m1("1000");
    Money m2("999");
    Money result = m1 - m2;
    EXPECT_EQ(result.toString(), "1");

    m1 = Money("10000");
    m2 = Money("1");
    result = m1 - m2;
    EXPECT_EQ(result.toString(), "9999");
}


TEST(MoneyTest, AdditionAssignment) {
    Money m1("100");
    Money m2("200");
    m1 += m2;
    EXPECT_EQ(m1.toString(), "300");
}


TEST(MoneyTest, SubtractionAssignment) {
    Money m1("500");
    Money m2("100");
    m1 -= m2;
    EXPECT_EQ(m1.toString(), "400");

    EXPECT_THROW(m1 -= Money("500"), std::invalid_argument);
}

TEST(MoneyTest, ComparisonOperators) {
    Money m1("500");
    Money m2("1000");

    EXPECT_TRUE(m1 < m2);
    EXPECT_FALSE(m1 > m2);
    EXPECT_TRUE(m1 <= m2);
    EXPECT_FALSE(m1 >= m2);

    Money m3("1000");
    EXPECT_TRUE(m2 == m3);
    EXPECT_FALSE(m1 == m3);
    EXPECT_TRUE(m1 != m3);
}

TEST(MoneyTest, InvalidString) {
    EXPECT_THROW(Money("abc"), std::invalid_argument);
    EXPECT_THROW(Money("12a34"), std::invalid_argument);
}

TEST(MoneyTest, InputOutputOperations) {
    std::stringstream ss;
    Money m("12345");

    ss << m;
    EXPECT_EQ(ss.str(), "12345");

    Money m2;
    ss >> m2;
    EXPECT_EQ(m2.toString(), "12345");
}
