#include "inf_int.h"
#include <regex>

/*
* In addition ans subtraction, the procedure produce result whose starts with 0
* We nees delete that
*/ 
void inf_int::erasePreZeros() {
    int numErase;
    for(numErase = 0; numErase < length; numErase++) {
        if (digits[numErase] != '0')
            break;
    }
    digits.erase(digits.begin(), digits.begin() + numErase);
    length = digits.length();
    if (length == 0) {
        digits = "0";
        length = 1;
    }
    if (digits == "0") {
        thesign = true;
    }
}

inf_int::inf_int(): inf_int("0") {}

inf_int::inf_int(int num): inf_int(to_string(num)) {}

inf_int::inf_int(const inf_int& copy): digits(copy.digits), length(copy.length), thesign(copy.thesign) {}

/*
* All data types can be converted to strings.
* We define one string constructor and use another string constructor in another.
*/
inf_int::inf_int(string num) {
    regex number("[+-]?[0-9]+");
    assert(regex_match(num, number));
    digits = num;
    thesign = digits[0] != '-';
    length = digits.length();
    if (!thesign || digits[0] == '+') {
        length--;
        digits = digits.substr(1, digits.size() - 1);
    }
}

// detructor. we don't use dynamic allocation
inf_int::~inf_int(){}

inf_int& inf_int::operator=(const inf_int& infInt) {
    digits = infInt.digits;
    length = infInt.length;
    thesign = infInt.thesign;
    return *this;
}

bool operator==(const inf_int& num1, const inf_int& num2) {
    return (num1.digits == num2.digits) && (num1.thesign == num2.thesign);
}

bool operator!=(const inf_int& num1 , const inf_int& num2) {
    return num1.digits != num2.digits || num1.thesign != num2.thesign;
}

bool operator>(const inf_int& num1, const inf_int& num2) {
    if (num1.thesign == true && num2.thesign == false) return true;
    if (num1.thesign == false && num2.thesign == true) return false;
    if (num1.length > num2.length) return (num1.thesign) ? true : false;
    if (num1.length < num2.length) return (num1.thesign) ? false : true;

    for(int i = 0; i < num1.length; i++) {
        if(num1.digits[i] > num2.digits[i]) return (num1.thesign) ? true : false;
        if(num1.digits[i] < num2.digits[i]) return (num1.thesign) ? false: true;
    }
    
    return false;
}

bool operator<(const inf_int& num1, const inf_int& num2) {
    if (num1.thesign == true && num2.thesign == false) return (num1.thesign) ? false : true;
    if (num1.thesign == false && num2.thesign == true) return (num1.thesign) ? true : false;
    if (num1.length > num2.length) return (num1.thesign) ? false : true;
    if (num1.length < num2.length) return (num1.thesign) ? true : false;

    for(int i = 0; i < num1.length; i++) {
        if(num1.digits[i] > num2.digits[i]) return (num1.thesign) ? false : true;
        if(num1.digits[i] < num2.digits[i]) return (num1.thesign) ? true : false;
    }
    
    return false;
}

/*
* Assumption
* num1.thesign == num2.thesign
*/
inf_int operator+(const inf_int& num1, const inf_int& num2) {
    // Ex 5+(-3) -> 5-3
    if (num1.thesign == true && num2.thesign == false) {
        inf_int copy = num2;
        copy.thesign = true;
        return operator-(num1, copy);
    }
    // Ex -3+5 -> 5-3
    if (num1.thesign == false && num2.thesign == true) {
        inf_int copy = num1;
        copy.thesign = true;
        return operator-(num2, copy);
    }
    int carry = 0;
    int digit1, digit2, result_digit;
    int iter = (num1.length < num2.length) ? num1.length : num2.length;
    inf_int result;
    result.thesign = num1.thesign;

    for(int i = 0; i < iter; i++) {
        digit1 = num1.digits[num1.length - i - 1] - '0';
        digit2 = num2.digits[num2.length - i - 1] - '0';

        result_digit = digit1 + digit2 + carry; 
        if (result_digit > 9) { 
            carry = 1;
            result_digit -= 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }
    result.digits = result.digits.substr(0, result.digits.length() - 1);

    for (int i = iter; i < num1.length; i++) {
        digit1 = num1.digits[num1.length - i - 1] - '0';
        result_digit = digit1 + carry; 
        if (result_digit > 9) { 
            carry = 1;
            result_digit -= 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    for (int i = iter; i < num2.length; i++) {
        digit2 = num2.digits[num2.length - i - 1] - '0';
        result_digit = digit2 + carry; 
        if (result_digit > 9) { 
            carry = 1;
            result_digit -= 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    if(carry) {
        result.digits = "1" + result.digits;
    }

    result.length = result.digits.length();

    result.erasePreZeros();
    return result;
}

/*
* Assumption
* num1 > num2 > 0 or num1 < num2 < 0
*/
inf_int operator-(const inf_int& num1, const inf_int& num2) {
    // Ex 3-(-2) -> 3 + 2
    if (num1.thesign == true && num2.thesign == false) {
        inf_int copy = num2;
        copy.thesign = true;
        return operator+(num1, copy);
    }
    // Ex -3-2 -> -3+(-2)
    if (num1.thesign == false && num2.thesign == true) {
        inf_int copy = num2;
        copy.thesign = false;
        return operator+(num1, copy);
    }
    // Ex 2-5 -> -(5-2)
    if ((num1.thesign) ? (num1 < num2) : (num1 > num2)) {
        inf_int result = operator-(num2, num1);
        result.thesign = !result.thesign;
        return result;
    }
    int carry = 0;
    int digit1, digit2, result_digit;
    int iter = (num1.length < num2.length) ? num1.length : num2.length;
    inf_int result;
    result.thesign = num1.thesign;

    for(int i = 0; i < iter; i++) {
        digit1 = num1.digits[num1.length - i - 1] - '0';
        digit2 = num2.digits[num2.length - i - 1] - '0';

        result_digit = digit1 - digit2 + carry; 
        if (result_digit < 0) { 
            carry = -1;
            result_digit += 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    result.digits = result.digits.substr(0, result.digits.length() - 1);

    for (int i = iter; i < num1.length; i++) {
        digit1 = num1.digits[num1.length - i - 1] - '0';
        result_digit = digit1 + carry; 
        if (result_digit < 0) { 
            carry = -1;
            result_digit += 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    for (int i = iter; i < num2.length; i++) {
        digit2 = num2.digits[num2.length - i - 1] - '0';
        result_digit = digit1 + carry; 
        if (result_digit < 0) { 
            carry = -1;
            result_digit += 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    assert(!carry);

    result.length = result.digits.length();
    result.erasePreZeros();
    
    return result;
}

inf_int operator*(const inf_int& num1, const inf_int& num2) {
    int digit1, digit2;
    inf_int result;
    // implement XOR logical operation using AND and OR

    for(int i = 0; i < num2.length; i++) {
        inf_int temp;
        temp.thesign = num1.thesign;
        digit2 = num2.digits[num2.length - i - 1] - '0';
        for(int j = 0; j < num1.length; j++) {
            digit1 = num1.digits[num1.length - j - 1] - '0';
            temp = digit1 * digit2;

            for(int ap = 0; ap < i + j; ap++) {
                temp.digits.append("0");
            }
            temp.length = temp.digits.length();
            result = result + temp;
        }
    }
    result.thesign = (num1.thesign == num2.thesign);
    result.erasePreZeros();
    return result;
}
// friend inf_int operator/(const inf_int& , const inf_int&); // not required

ostream& operator<<(ostream& os, const inf_int& num) {
    if (!num.thesign)
        os << "-";
    os << num.digits;
    return os;
}

istream& operator>>(istream& os, inf_int& num) {
    string input;
    os >> input;
    inf_int copy(input);
    num = copy;
    
    return os;
}
