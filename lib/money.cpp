#include <algorithm>
#include <stdexcept>
#include <cstring>
#include "../include/money.h"

Money::Money() : data(nullptr), size(0) {}

Money::Money(const std::string& amount) : data(nullptr), size(0) {
    fromString(amount);
}

Money::Money(const Money& other) : size(other.size) {
    data = new unsigned char[size];
    std::copy(other.data, other.data + size, data);
}

Money::Money(Money&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new unsigned char[size];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

Money& Money::operator=(Money&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

Money::~Money() {
    delete[] data;
}

void Money::fromString(const std::string& amount) {
    size_t len = amount.length();
    resize(len);
    for (size_t i = 0; i < len; ++i) {
        if (isdigit(amount[len - 1 - i])) {
            data[i] = amount[len - 1 - i] - '0';
        } else {
            throw std::invalid_argument("Invalid character in amount string.");
        }
    }
}

std::string Money::toString() const {
    std::string result;

    for (size_t i = 0; i < size; ++i) {
        result += std::to_string(data[size - 1 - i]);
    }

    size_t firstNonZero = result.find_first_not_of('0');
    if (firstNonZero == std::string::npos) {
        return "0";
    }

    return result.substr(firstNonZero);
}


void Money::resize(size_t newSize) {
    unsigned char* newData = new unsigned char[newSize]();
    size_t minSize = (newSize < size) ? newSize : size;
    std::copy(data, data + minSize, newData);
    delete[] data;
    data = newData;
    size = newSize;
}

Money Money::operator+(const Money& other) const {
    Money result;
    size_t maxSize = std::max(size, other.size);
    result.resize(maxSize + 1);

    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char sum = carry;
        if (i < size) sum += data[i];
        if (i < other.size) sum += other.data[i];
        result.data[i] = sum % 10;
        carry = sum / 10;
    }

    return result;
}

Money Money::operator-(const Money& other) const {
    if (*this < other) {
        throw std::invalid_argument("Cannot subtract larger amount from smaller.");
    }

    Money result;
    result.resize(size);

    unsigned char borrow = 0;
    for (size_t i = 0; i < size; ++i) {
        int diff = data[i] - (i < other.size ? other.data[i] : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.data[i] = diff;
    }

    return result;
}

Money& Money::operator+=(const Money& other) {
    *this = *this + other;
    return *this;
}

Money& Money::operator-=(const Money& other) {
    *this = *this - other;
    return *this;
}

bool Money::operator==(const Money& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    if (size != other.size) return size < other.size;
    for (int i = size - 1; i >= 0; --i) {
        if (data[i] != other.data[i]) return data[i] < other.data[i];
    }
    return false;
}

bool Money::operator>(const Money& other) const {
    return other < *this;
}

bool Money::operator<=(const Money& other) const {
    return !(other < *this);
}

bool Money::operator>=(const Money& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << money.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    std::string amount;
    is >> amount;
    money.fromString(amount);
    return is;
}

