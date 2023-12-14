#pragma once

#include <string>
#include "vector.h"
#include <math.h>
#include <iostream>
class Bigint {
    std::string _str;
    std::string add (std::string str1, std::string str2) const;
    std::string subtract(std::string str1, std::string str2) const;
    std::string trim(std::string _str) const;
    std::string maximum(std::string str1, std::string str2) const;
    std::string multiply (string str1, string str2) const;
    std::string pow(string str1, string str2) const { //this will not work for negative powers 
        if (str2 == "0") return "1";
        string base = "1";
        while (str2 > "0") {
            base = multiply(base, str1);
            str2 = subtract(str2, "1");
        }
        return base;
    }
public:
    Bigint() {
        _str = '0';  //default value
    }
    Bigint(std::string s) {
        _str = s;
    }
    Bigint(long long int n) {
        _str = std::to_string(n);
    }
    Bigint(int n) {
        _str = std::to_string(n);
    }
    Bigint(long int n) {
        _str = std::to_string(n);
    }
    Bigint(const Bigint& n) {
        _str = n._str;
    }
    
    string str() {
        return _str;
    }

    operator string() {
        return this->_str;
    }
    Bigint operator % (const Bigint&  s) {
        Bigint temp = *this;
        if (temp < s) return temp;
        while (temp > s) 
            temp -= s;
        return temp;
    }
    Bigint operator % (int n) {
        Bigint temp = *this;
        if (temp < n) return temp;
        while (temp > n)
            temp -= n;
        return temp;
    }
    Bigint operator % (long long int n) {
        Bigint temp = *this;
        if (temp < n) return temp;
        while (temp > n)
            temp -= n;
        return temp;
    }
    static Bigint power(const Bigint&  a, const Bigint&  b) {
        return Bigint(a.pow(a._str, b._str));
    }
    static Bigint power(const Bigint& a, string b) {
        return Bigint(a.pow(a._str, b));
    }
    static Bigint power(const Bigint& a, int b) {
        return Bigint(a.pow(a._str, to_string(b)));
    }
    static Bigint power(const Bigint& a, long long int b) {
        return Bigint(a.pow(a._str, to_string(b)));
    }
    static Bigint power(int a, int b) {
        Bigint temp(a);
        return temp.pow(temp._str, to_string(b));
    }
    friend std::ostream& operator << (std::ostream& stream, const Bigint& n) {
        stream << n._str;
        return stream;
    }
    friend std::istream& operator >> (std::istream& stream, Bigint& n) {
        stream >> n._str;
        return stream;
    }
    Bigint operator + (Bigint const& n) const {
        Bigint ans;
        ans._str = add(_str, n._str);
        return ans;
    }
    Bigint operator + (long long int n2) const{
        Bigint ans;
        ans._str = add(_str, std::to_string(n2));
        return ans;
    }
    Bigint operator + (int n2) const{
        Bigint ans;
        ans._str = add(_str, std::to_string(n2));
        return ans;
    }
    Bigint& operator += (Bigint const n) {
        (*this)._str = add((*this)._str, n._str);
        return (*this);
    }
    Bigint& operator += (long long int const n) {
        (*this)._str = add((*this)._str, to_string(n));
        return (*this);
    }
    Bigint& operator += (int const n) {
        (*this)._str = add((*this)._str, to_string(n));
        return (*this);
    }
    Bigint operator - (Bigint const& n) {
        Bigint ans;
        ans._str = subtract(_str, n._str);
        return ans;
    }

    Bigint operator - (long long int n2) {
        Bigint ans;
        ans._str = subtract(_str, std::to_string(n2));
        return ans;
    }
    Bigint operator - (int n2) {
        Bigint ans;
        ans._str = subtract(_str, std::to_string(n2));
        return ans;
    }
    Bigint& operator++() {
        *this += 1;
        return *this;
    }
    Bigint operator++(int) {
        Bigint temp = *this;
        *this += 1;
        return temp;
    }
    Bigint& operator--() {
        *this -= 1;
        return *this;
    }
    Bigint operator--(int) {
        Bigint temp = *this;
        *this -= 1;
        return temp;
    }
    Bigint& operator = (const Bigint& n) {
        _str = n._str;
        return *this;
    }
    Bigint& operator = (long long int const n) {
        _str = to_string(n);
        return *this;
    }
    Bigint& operator = (int const n) {
        _str = to_string(n);
        return *this;
    }
    Bigint& operator -= (Bigint const n) {
        (*this)._str = subtract((*this)._str, n._str);
        return (*this);
    }
    Bigint& operator -= (long long int const n) {
        this->_str = subtract((*this)._str, to_string(n));
        return *this;
    }
    Bigint& operator -= (int const n) {
        this->_str = subtract((*this)._str, to_string(n));
        return *this;
    }


    //for Bigint
    bool operator >= (const Bigint& s) const{            
        return _str == maximum(_str, s._str);
    }

    bool operator <= (const Bigint& s) const{
        return s._str == maximum(_str, s._str);
    }

    bool operator < (const Bigint& s) const{
        if (s._str == _str) return false;
        return *this <= s;
    }

    bool operator > (const Bigint& s) const {
        if (s._str == _str) return false;
        return *this >= s;
    }

    bool operator == (const Bigint&  s) const {
        return _str == s._str;
    }
    bool operator != (const Bigint& s) const{
        return _str != s._str;
    }

    //for int
    bool operator >= (long long int n) {
        return _str == maximum(_str, to_string(n));
    }

    bool operator <= (long long int n) {
        return to_string(n) == maximum(_str, to_string(n));
    }

    bool operator > (long long int n) {
        if (*this == n) return false;
        string number = to_string(n);
        return _str == maximum(_str, number);
    }

    bool operator < (long long int n) {
        if (*this == n) return false;
        string number = to_string(n);
        return number == maximum(_str, number);
    }

    bool operator == (long long int n) {
        return _str == to_string(n);
    }
    bool operator != (long long int n) {
        return _str != to_string(n);
    }

    bool operator >= (int n) {
        return _str == maximum(_str, to_string(n));
    }

    bool operator <= (int n) {
        return to_string(n) == maximum(_str, to_string(n));
    }

    bool operator > (int n) {
        if (*this == n) return false;
        string number = to_string(n);
        return _str == maximum(_str, number);
    }

    bool operator < (int n) {
        if (*this == n) return false;
        string number = to_string(n);
        return number == maximum(_str, number);
    }

    bool operator == (int n) {
        return _str == to_string(n);
    }

    bool operator != (int n) {
        return _str != to_string(n);
    }

    Bigint operator * (const Bigint& s) {
        Bigint temp(multiply(this->_str,s._str));
        return temp;
    }

    Bigint operator * (long long int n) {
        Bigint temp(multiply(this->_str, to_string(n)));
        return temp;
    }
    Bigint operator * (int n) {
        Bigint temp(multiply(this->_str, to_string(n)));
        return temp;
    }
    Bigint& operator *= (const Bigint& s) {
        _str = multiply(this->_str, s._str);
        return *this;
    }


};
std :: string Bigint :: add (std :: string str1, std :: string str2) const{          // returns arithmetic addition of str1+str2
    std::string sum = "";

    if (str1.length() == 0 && str2.length() == 0) {
        sum = "0";
    }
    else if (str1[0] == '-' && str2[0] == '-') {
        sum = "-" + add(str1.erase(0, 1), str2.erase(0, 1)); 
    }
    else if (str1[0] == '-') {
        sum = subtract(str2, str1.erase(0, 1));
    }
    else if (str2[0] == '-') {
        sum = subtract(str1, str2.erase(0, 1));
    }
    else {
        int i, j, track_sum, carry = 0;
        for (i = str1.length() - 1, j = str2.length() - 1; i >= 0 && j >= 0; --i, --j) {
            track_sum = (str1[i] - 48)  + (str2[j] - 48) + carry;
            carry = track_sum / 10;
            sum = std::to_string(track_sum % 10) + sum;
        }
        if (i >= 0 && j < 0) { //if first number is left
            for (; i >= 0; --i) {
                track_sum = (str1[i] - 48) + carry;
                carry = track_sum / 10;
                sum = std::to_string(track_sum % 10) + sum;
            }
        }
        else if (j >= 0 && i < 0) { //if second number is left ie bigger just add it
            for (; j >= 0; --j) {
                track_sum = (str2[j] - 48) + carry;
                carry = track_sum / 10;
                sum = std::to_string(track_sum % 10) + sum;
            }
        }
        if (carry) {  //leftover carry
            sum = std::to_string(carry) + sum;
        }
    }
    return trim(sum);
}
std::string Bigint::subtract(std::string str1, std::string str2) const{                 // returns arithmetic subtraction of str1-str2
    std::string sum = "";
    if (str1 == str2) {
        return "0";
    }
    else if (str1[0] == '-' && str2[0] == '-') {
        Bigint t1(str1.substr(1));
        Bigint t2(str2.substr(1));
        std::string temp = subtract(t2._str, t1._str);  //this is -a - (-b) = -a + b = b - a
        Bigint mx = maximum(t2._str, t1._str);
        if (temp[0] != '-' && mx._str == t1._str)
            sum = "-" + temp;                      
        else
            sum = temp;
    }
    else if (str1[0] == '-') {
        sum = "-" + add(str1.substr(1), str2);  //this is - (a + b)
    }
    else if (str2[0] == '-') {
        sum = add(str1, str2.substr(1));    //this is a + b
    }
    else {
        if (str1.length() < str2.length()) {
            swap(str1, str2);
            sum = "-" + subtract(str1, str2); //means str1 > str2 hence ans will be -ve as both are +ve
            return trim(sum);
        }
        else if (_str.length() == str2.length()) {
            Bigint a(str1);
            Bigint b(str2);
            if (b > a) {  //if str2 bigger then solve it like a - b = -ve 
                swap(str1, str2);
                Bigint t1(str1);
                Bigint t2(str2);
                Bigint temp = subtract(str1, str2);
                sum = "-" + subtract(str1, str2);
                return trim(sum);
            }
        }
        int carry = 0, track_sum = 0;
        for (int i = str1.length() - 1, j = str2.length() - 1; i >= 0 || j >= 0; --i, --j) {
            int val2 = j >= 0 ? str2[j] - 48 : 0;
            int val1 = i >= 0 ? str1[i] - 48 : 0;
            track_sum = val1 - val2 - carry;
            if (track_sum < 0) {
                track_sum += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            sum = std::to_string(track_sum) + sum;
        }
    }
    return trim(sum);
}

std::string Bigint::trim(std::string str) const{                         // function to remove zeros
    if (str == "0")
        return str;
    if (str[0] == '-' || str[0] == '0') {
        for (int i = str[0] == '-' ? 1 : 0; str[i] == '0'; i++) //if first index is negative start checking from 2nd index else first index
            str = str.substr(1);
    }
    return str;
}
std::string Bigint::maximum(std::string str1, std::string str2) const {  
    std::string max = "";
    bool bothNeg = false;
    bool isMax = false; //assume  str1 is always greater
    if (str1[0] == '-' && str2[0] == '-') {
        bothNeg = true;
        str1 = str1.substr(1);
        str2 = str2.substr(1);
    }
    else if (str1[0] == '-') 
        return trim(str2);
    else if (str2[0] == '-') 
        return trim(str1);
    if (str1.length() == str2.length()) {
        for (int i = 0; i < str1.length(); i++) {
            if (str1[i] != str2[i]) {
                isMax = str1[i] > str2[i] ? false : true;
                break;
            }
        }
    }
    else if (str1.length() > str2.length()) {
        isMax = false;
    }
    else {
        isMax = true;
    }
    if (bothNeg) {
        if (!isMax)
            return ("-" + trim(str2));
        else
            return ("-" + trim(str1));
    }
    else {
        if (!isMax)
            return trim(str1);
        else
            return trim(str2);
    }
}
std::string Bigint::multiply(std::string str1, std::string str2) const{             // return arithmetic multiplication of str1*str2
    bool neg = false;
    string product = "";
    if (str1[0] == '-' && str2[0] == '-') {
        return product = multiply(str1.substr(1), str2.substr(1));
    }
    else if (str1[0] == '-') {
        neg = true;
        product = multiply(str1.substr(1), str2);
    }
    else if (str2[0] == '-') {
        neg = true;
        product = multiply(str1, str2.substr(1));
    }
    else {
        Vector<int> result(str1.length() + str2.length(), 0);  //makes a padding of zeros
        int in1 = 0;
        int in2 = 0;
        for (int i = str1.length() - 1; i >= 0; i--) {
            int carry = 0;
            int n1 = str1[i] - '0';
            in2 = 0;
            for (int j = str2.length() - 1; j >= 0; j--) {
                int n2 = str2[j] - '0';
                int sum = n1 * n2 + result[in1 + in2] + carry;
                carry = sum / 10;
                result[in1 + in2] = sum % 10;
                in2++;
            }
            if (carry > 0)
                result[in1 + in2] += carry;
            in1++;
        }
        int i = result.size() - 1;
        while (i >= 0 && result[i] == 0)
            i--;
        if (i == -1)
            return "0";
        while (i >= 0)
            product += std::to_string(result[i--]);
    }
    return (neg && product[0] != '0' ? '-' + product : product);
}