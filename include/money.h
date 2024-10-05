#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class Money {
public:
    Money();
    Money(const std::string& amount);
    Money(const Money& other);
    Money(Money&& other) noexcept;
    Money& operator=(const Money& other);
    Money& operator=(Money&& other) noexcept;
    ~Money();

    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);

    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator<=(const Money& other) const;
    bool operator>=(const Money& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Money& money);
    friend std::istream& operator>>(std::istream& is, Money& money);

    std::string toString() const;

private:
    unsigned char* data;
    size_t size;

    void fromString(const std::string& amount);

    void resize(size_t newSize);
};


#endif
