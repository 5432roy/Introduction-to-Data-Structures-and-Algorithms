/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA6
 * BigInteger.cpp
 * Implementation of the Big integer using List ADT
*/
#include <cctype>
#include <string>
#include <sstream>
#include <iomanip>
#include "BigInteger.h"

using namespace std;

#define BASE 1000000000
#define POW 9
#define ZEROS "000000000"

/* Exported type */
BigInteger::BigInteger() {
    signum = 0;
}

BigInteger::BigInteger(long x) {
    if(x == 0) {
        signum = 0;
    }
    if(x > 0) {
        signum = 1;
        digits.insertBefore(x);
    }
    if(x < 0) {
        signum = -1;
        digits.insertBefore(-x);
    }
}

BigInteger::BigInteger(string s) {
    if(s.length() == 0) {
        throw invalid_argument("BigInteger: Constructor: empty string");
    }

    bool has_value = false, is_negative = false;
    long cur = 0;
    int count = s.length() - 1, index = 0, length = s.length();

    if(s[index] == '+' || s[index] == '-') {
        is_negative = s[index] == '-';
        index += 1;
        count -= 1;
    }

    if(index == length) {
        throw invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    while(index < length){
        if(((int)s[index] - '0') == -35) {
            digits.insertBefore(cur);
            break;
        }
        if(!isdigit(s[index])) {
            throw invalid_argument("BigInteger: Constructor: non-numeric string");
        }

        has_value |= s[index] != '0';
        cur = cur * 10 + int(s[index] - '0');

        if(count % POW == 0) {
            digits.insertBefore(cur);
            cur = 0;
        }

        count -= 1;
        index += 1;

    }
    signum = is_negative ? -1 : 1;

    if(!has_value) {
        makeZero();
    }

    digits.moveFront();

    while(digits.position() < digits.length() && digits.peekNext() == 0) {
        digits.eraseAfter();
    }

}

BigInteger::BigInteger(const BigInteger& N) {
    signum = N.sign();
    digits = N.digits;
}


/** Access functions **/

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if(sign() == 0) {
        return -(N.sign());
    }

    if(N.sign() == 0) {
        return sign();
    }

    if(sign() != N.sign()) {
        return sign() > N.sign();
    }

    List this_digits = this->digits, N_digits = N.digits;

    if(this_digits.length() != N_digits.length()) {
        int absolute_comp = this_digits.length() > N_digits.length() ? 1 : -1;
        return sign() == 1 ? absolute_comp : -absolute_comp;
    }

    this_digits.moveFront();
    N_digits.moveFront();

    while(this_digits.position() < this_digits.length()) {
        ListElement this_element = this_digits.moveNext(), N_element = N_digits.moveNext();

        if(this_element == N_element) {
            continue;
        }

        return this_element > N_element ? sign() : -sign();
    }

    return 0;
}


/* Manipulation procedures */

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum *= -1;
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger res;

    if(sign() == 0) {
        res = N;
        return res;
    }

    if(N.sign() == 0) {
        res = *this;
        return res;
    }

    List this_digits = digits, N_digits = N.digits;
    this_digits.moveBack();
    N_digits.moveBack();

    ListElement carry_over = 0;


    if(sign() == N.sign()) {
        res.signum = sign();

        while(this_digits.position() > 0 || N_digits.position() > 0) {
            if(this_digits.position() > 0 && N_digits.position() > 0) {
                ListElement cur_sum = 
                    this_digits.movePrev() + N_digits.movePrev() + carry_over;
                carry_over = cur_sum / BASE;
                cur_sum %= BASE;
                res.digits.insertAfter(cur_sum);
                continue;
            }

            if(this_digits.position() > 0) {
                ListElement cur_sum = this_digits.movePrev() + carry_over;
                carry_over = cur_sum / BASE;
                cur_sum %= BASE;
                res.digits.insertAfter(cur_sum);
                continue;
            }

            if(N_digits.position() > 0) {
                ListElement cur_sum = N_digits.movePrev() + carry_over;
                carry_over = cur_sum / BASE;
                cur_sum %= BASE;
                res.digits.insertAfter(cur_sum);
                continue;
            }
        }
        if(carry_over != 0) {
            res.digits.insertAfter(carry_over);
        }
    }

    if(sign() != N.sign()) {
        res.signum = sign();
        while(this_digits.position() > 0 || N_digits.position() > 0) {
            if(this_digits.position() > 0 && N_digits.position() > 0) {
                ListElement cur_sum = 
                    this_digits.movePrev() - N_digits.movePrev() + carry_over;
                carry_over = cur_sum / BASE;
                cur_sum %= BASE;
                if(cur_sum < 0) {
                    cur_sum += BASE;
                    carry_over -= 1;
                }
                res.digits.insertAfter(cur_sum);
                continue;
            }

            if(this_digits.position() > 0) {
                ListElement cur_sum = this_digits.movePrev() + carry_over;
                carry_over = cur_sum / BASE;
                cur_sum %= BASE;
                if(cur_sum < 0) {
                    cur_sum += BASE;
                    carry_over -= 1;
                }
                res.digits.insertAfter(cur_sum);
                continue;
            }

            if(N_digits.position() > 0) {
                ListElement cur_sum = -N_digits.movePrev() + carry_over;
                carry_over = cur_sum / BASE;
                cur_sum %= BASE;
                if(cur_sum < 0) {
                    cur_sum += BASE;
                    carry_over -= 1;
                }
                res.digits.insertAfter(cur_sum);
                continue;
            }
        }
        if(carry_over != 0) {
            res.digits.insertAfter(carry_over);
        }

        if(res.digits.front() < 0) {
            res.digits.moveFront();
            res.digits.eraseAfter();
            res.signum = 1;
            string str = "1";
            for(int i = 0; i < res.digits.length(); i++) {
                str += ZEROS;
            }
            BigInteger temp = BigInteger(str);
            res = temp - res;
            res.signum = N.sign();
        }

    }

    res.digits.moveFront();

    while(res.digits.position() < res.digits.length() && res.digits.peekNext() == 0) {
        res.digits.eraseAfter();
    }

    if(res.digits.length() == 0) {
        res.signum = 0;
    }


    return res;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger negate_N = N;
    negate_N.negate();
    return add(negate_N);
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger res;

    res.signum = sign() * N.sign();

    if(res.sign() == 0) {
        return res;
    }

    List this_digits = digits, N_digits = N.digits;
    this_digits.moveBack();

    for(int i = this_digits.length() + N_digits.length(); i > 0; i--) {
        res.digits.insertBefore(0);
    }

    ListElement carry_over = 0;

    for(int i = 0; i < this_digits.length(); i++) {
        N_digits.moveBack();

        while(N_digits.position() > 0) {
            ListElement cur = this_digits.peekPrev() * N_digits.movePrev() + carry_over + res.digits.peekPrev();
            carry_over = cur / BASE;
            cur %= BASE;
            res.digits.setBefore(cur);
            res.digits.movePrev();
        }

        if(carry_over != 0) {
            res.digits.setBefore(carry_over);
            carry_over = 0;
        }

        this_digits.movePrev();
        res.digits.moveBack();
        
        for(int j = 0; j <= i; j++) {
            res.digits.movePrev();
        }
    }

    res.digits.moveFront();

    while(res.digits.position() < res.digits.length() && res.digits.peekNext() == 0) {
        res.digits.eraseAfter();
    }

    if(res.digits.length() == 0) {
        res.signum = 0;
    }

    return res;
}


/* Other functions */
std::string BigInteger::to_string() {
    if(sign() == 0) {
        return "0";
    }
    
    string str = "";
    
    if(sign() == -1) {
        str += "-";
    }

    digits.moveFront();


    while(digits.position() != digits.length()) {
        ListElement cur = digits.moveNext();

        if(digits.position() != 1) {
            ostringstream oss;
            oss << setfill('0') << std::setw(POW) << cur;
            str += oss.str();
        } else {
            str += std::to_string(cur);
        }
    }
    return str;
}

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1;
}

bool operator<=(const BigInteger& A, const BigInteger& B){
    return A.compare(B) != 1;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) != -1;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return B;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}