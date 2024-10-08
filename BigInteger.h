#include <iostream>
#include <string>
#include <vector>

class BigInteger
{
public:

    BigInteger();
    BigInteger(int a);
    BigInteger(const std::string& s);

    bool operator<(const BigInteger& b) const;
    bool operator>(const BigInteger& b) const;
    bool operator<=(const BigInteger& b) const;
    bool operator>=(const BigInteger& b) const;
    bool operator==(const BigInteger& b) const;
    bool operator!=(const BigInteger& b) const;
    BigInteger& operator*=(const BigInteger& b);
    BigInteger& operator+=(const BigInteger& c);
    BigInteger& operator-=(const BigInteger& c);
    BigInteger& operator%=(const BigInteger& b);
    BigInteger& operator/=(const BigInteger& c);
    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);
    BigInteger abs() const;
    BigInteger operator-();
    std::string toString() const;
    explicit operator bool();
    friend std::istream& operator>>(std::istream&, BigInteger&);
    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    friend BigInteger operator*(const BigInteger& b, const BigInteger& a);
    friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator%(const BigInteger& a, const BigInteger& b);
    friend BigInteger operator+(const BigInteger& a, const BigInteger& c);
    friend BigInteger operator-(const BigInteger& a, const BigInteger& c);
private:
    std::vector<int> num;
    bool positive = true;
    void LevelUp();
    void ExtractZeros();
    void Dif(BigInteger& a, const BigInteger& b);
    void Sum(BigInteger& a, const BigInteger& b);
    int Compare(const BigInteger& a, int k = 1) const;
};

BigInteger::BigInteger() : positive(true) {}

BigInteger::BigInteger(int a)
{
    if (a < 0)
    {
        positive = false;
        a *= -1;
    }
    else if (a == 0)
    {
        num.push_back(0);
        positive = true;
    }
    while (a != 0)
    {
        num.push_back(a % 10);
        a /= 10;
    }
}

BigInteger::BigInteger(const std::string& s)
{
    positive = true;
    for (size_t i = s.length() - 1; i > 0; i--)
    {
        num.push_back(s[i] - '0');
    }
    if (s[0] == '-')
    {
        positive = false;
    }
    else
    {
        num.push_back(s[0] - '0');
    }
}

BigInteger operator-(const BigInteger& a, const BigInteger& c)
{
    BigInteger dif = a;
    return dif -= c;
}

BigInteger operator+(const BigInteger& a, const BigInteger& c)
{
    BigInteger sum = a;
    return sum += c;
}

BigInteger operator*(const BigInteger& b, const BigInteger& a)
{
    size_t length = a.num.size() + b.num.size() + 1;
    BigInteger c;
    c.num.resize(length, 0);
    for (size_t i = 0; i < a.num.size(); i++)
    {
        for (size_t j = 0; j < b.num.size(); j++)
        {
            c.num[i + j] += a.num[i] * b.num[j];
        }
    }
    for (size_t i = 0; i < length; i++)
    {
        if (i < length - 1)
        {
            c.num[i + 1] += c.num[i] / 10;
        }
        c.num[i] %= 10;
    }
    c.positive = a.positive == b.positive;
    c.ExtractZeros();
    return c;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b)
{
    BigInteger res;
    res.num.resize(a.num.size());
    BigInteger curValue;
    for (int i = int(a.num.size()) - 1; i >= 0; i--)
    {
        curValue.LevelUp();
        curValue.ExtractZeros();
        curValue.num[0] = a.num[i];
        int x = 0;
        int l = 0, r = 9;
        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInteger cur(0);
            cur = b.abs() * m;
            if (cur.Compare(curValue, 0) <= 0)
            {
                x = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        res.num[i] = x;
        curValue -= b.abs() * x;
    }
    res.positive = a.positive == b.positive;
    res.ExtractZeros();
    return res;
}

BigInteger operator%(const BigInteger& a, const BigInteger& b)
{
    BigInteger res;
    res.num.resize(a.num.size());
    BigInteger curValue;
    for (int i = int(a.num.size()) - 1; i >= 0; i--)
    {
        curValue.LevelUp();
        curValue.ExtractZeros();
        curValue.num[0] = a.num[i];
        int x = 0;
        int l = 0, r = 9;
        while (l <= r)
        {
            int m = (l + r) >> 1;
            BigInteger cur;
            cur = b.abs() * m;
            if (cur.Compare(curValue, 0) <= 0)
            {
                x = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        res.num[i] = x;
        curValue = curValue - b.abs() * x;
    }
    curValue.ExtractZeros();
    curValue.positive = a.positive;
    if (curValue.num.empty())
    {
        curValue.num.push_back(0);
    }
    return curValue;
}

std::istream& operator>>(std::istream& str, BigInteger& a)
{
    std::string s;
    str >> s;
    BigInteger b(s);
    a = b;
    return str;
}

std::ostream& operator<<(std::ostream& str, const BigInteger& a)
{
    std::string s;
    s = a.toString();
    str << s;
    return str;
}

bool BigInteger::operator<(const BigInteger& b) const
{
    return Compare(b) == -1;
}

bool BigInteger::operator>(const BigInteger& b) const
{
    return Compare(b) == 1;
}

bool BigInteger::operator<=(const BigInteger& b) const
{
    int comp = Compare(b);
    return comp == -1 || comp == 0;
}

bool BigInteger::operator>=(const BigInteger& b) const
{
    int comp = Compare(b);
    return comp == 1 || comp == 0;
}

bool BigInteger::operator==(const BigInteger& b) const
{
    return Compare(b) == 0;
}

bool BigInteger::operator!=(const BigInteger& b) const
{
    return Compare(b) != 0;
}

BigInteger& BigInteger::operator*=(const BigInteger& b)
{
    BigInteger rez = *this;
    return *this = rez * b;
}

BigInteger& BigInteger::operator+=(const BigInteger& c)
{
    if ((positive && c.positive) || (!positive && !c.positive))
    {
        Sum(*this, c);
        return *this;
    }
    if ((positive && !c.positive) || (!positive && c.positive))
    {
        if (this->Compare(c, 0) >= 0)
        {
            Dif(*this, c);
            return *this;
        }
        else
        {
            BigInteger tmpa = *this;
            BigInteger tmpb = c;
            Dif(tmpb, tmpa);
            return *this = tmpb;
        }
    }
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& c)
{
    if ((positive && c.positive) || (!positive && !c.positive))
    {
        if (this->Compare(c, 0) >= 0)
        {
            Dif(*this, c);
            return *this;
        }
        else
        {
            BigInteger tmpA = *this;
            BigInteger tmpB = c;
            Dif(tmpB, tmpA);
            tmpB.positive = !tmpB.positive;
            return *this = tmpB;
        }
    }
    else
    {
        Sum(*this, c);
        return *this;
    }
}

void BigInteger::LevelUp()
{
    num.insert(num.begin(), 0);
}

BigInteger& BigInteger::operator%=(const BigInteger& b)
{
    return *this = *this % b;
}

BigInteger& BigInteger::operator/=(const BigInteger& c)
{
    BigInteger rez = *this;
    return *this = rez / c;
}

BigInteger& BigInteger::operator++()
{
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger tmp = *this;
    ++(*this);
    return tmp;
}

BigInteger& BigInteger::operator--()
{
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger tmp = *this;
    --(*this);
    return tmp;
}

BigInteger BigInteger::abs() const
{
    BigInteger b = (*this);
    b.positive = true;
    return b;
}

BigInteger BigInteger::operator-()
{
    BigInteger b = *this;
    b.positive = !this->positive;
    if (num.size() == 1 && num[0] == 0)
    {
        b.positive = true;
        b.num[0] = 0;
        return b;
    }
    else
    {
        return b;
    }
}

std::string BigInteger::toString() const
{
    std::string s = positive ? "" : "-";
    if (num[0] == 0 && num.size() == 1)
    {
        s = '0';
        return s;
    }
    bool forwNuls = true;
    for (int i = int(num.size()) - 1; i >= 0; i--)
    {
        if (num[i] == 0 && forwNuls)
        {
            continue;
        }
        else
        {
            forwNuls = false;
            s += num[i] + '0';
        }
    }
    if (s.empty() || (s[0] == '-' && s.length() == 1))
    {
        s = '0';
    }
    return s;
}

BigInteger::operator bool()
{
    return *this != 0;
}

void BigInteger::ExtractZeros()
{
    while (!num.empty() && *num.rbegin() == 0)
    {
        num.pop_back();
    }
    if (num.empty())
    {
        positive = true;
        num.push_back(0);
    }
}

void BigInteger::Dif(BigInteger& a, const BigInteger& b)
{
    int carry = 0;
    for (size_t i = 0; i < b.num.size() || carry; ++i)
    {
        a.num[i] -= carry + (i < b.num.size() ? b.num[i] : 0);
        carry = a.num[i] < 0;
        if (carry) a.num[i] += 10;
    }
    a.ExtractZeros();
}

void BigInteger::Sum(BigInteger& a, const BigInteger& b)
{
    int carry = 0;
    for (size_t i = 0; i < std::max(a.num.size(), b.num.size()) || carry; ++i)
    {
        if (i == a.num.size())
        {
            a.num.push_back(0);
        }
        a.num[i] += carry + (i < b.num.size() ? b.num[i] : 0);
        carry = a.num[i] / 10;
        a.num[i] %= 10;
    }
    a.ExtractZeros();
}

int BigInteger::Compare(const BigInteger& a, int k) const
{
    int check = 1;
    if (k == 1)
    {
        if (positive && !a.positive)
        {
            return 1;
        }
        if (!positive && a.positive)
        {
            return -1;
        }
        if (!positive && !a.positive)
        {
            check = -1;
        }
    }
    if (num.size() < a.num.size())
    {
        return -1 * check;
    }
    if (num.size() > a.num.size())
    {
        return check;
    }
    for (size_t i(num.size()); i > 0; i--)
    {
        if (num[i - 1] < a.num[i - 1]) return -1 * check;
        if (num[i - 1] > a.num[i - 1]) return check;
    }
    return 0;
}
