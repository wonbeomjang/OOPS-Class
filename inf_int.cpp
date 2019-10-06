#include "inf_int.h"

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
}

inf_int::inf_int(): digits("0"), length(1), thesign(true) {}

inf_int::inf_int(int num) {
    digits = to_string(num);
    thesign = digits.substr(0, 1) != "-";
    length = digits.length();
    if (!thesign) {
        length--;
        digits = digits.substr(1, digits.size() - 1);
    }
}

inf_int::inf_int(const char* num){
    digits = num;
    thesign = digits.substr(0, 1) != "-";
    length = digits.length();
    if (!thesign) {
        length--;
        digits = digits.substr(1, digits.size() - 1);
    }
}

inf_int::inf_int(const inf_int& copy): digits(copy.digits), length(copy.length), thesign(copy.thesign) {}

inf_int::~inf_int(){}

inf_int& inf_int::operator=(const inf_int& infInt) {
    digits = infInt.digits;
    length = infInt.length;
    thesign = infInt.thesign;
    return *this;
}

bool operator==(const inf_int& num1, const inf_int& num2) {
    if (num1.thesign != num2.thesign)
        return false;
    return num1.digits == num2.digits;
}

bool operator!=(const inf_int& num1 , const inf_int& num2) {
    if (num1.thesign != num2.thesign)
        return true;
    return num1.digits != num2.digits;
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

inf_int operator+(const inf_int& num1, const inf_int& num2) {
    if (num1.thesign == true && num2.thesign == false) {
        inf_int copy = num2;
        copy.thesign = true;
        return operator-(num1, copy);
    }
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
        digit1 = atoi(&num1.digits.substr(num1.length - i - 1, 1)[0]);
        digit2 = atoi(&num2.digits.substr(num2.length - i - 1, 1)[0]);

        result_digit = digit1 + digit2 + carry; 
        if (result_digit > 10) { 
            carry = 1;
            result_digit -= 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }
    result.digits = result.digits.substr(0, result.digits.length() - 1);

    for (int i = iter; i < num1.length; i++) {
        digit1 = atoi(&num1.digits.substr(num1.length - i - 1, 1)[0]);
        result_digit = digit1 + carry; 
        if (result_digit > 10) { 
            carry = 1;
            result_digit -= 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    for (int i = iter; i < num2.length; i++) {
        digit2 = atoi(&num2.digits.substr(num2.length - i - 1, 1)[0]);
        result_digit = digit2 + carry; 
        if (result_digit > 10) { 
            carry = 1;
            result_digit -= 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    result.length = result.digits.length();

    result.erasePreZeros();
    return result;
}

inf_int operator-(const inf_int& num1, const inf_int& num2) {
    if (num1.thesign == true && num2.thesign == false) {
        inf_int copy = num2;
        copy.thesign = true;
        return operator+(num1, copy);
    }
    if (num1.thesign == false && num2.thesign == true) {
        inf_int copy = num2;
        copy.thesign = false;
        return operator+(num1, copy);
    }
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
        digit1 = atoi(&num1.digits.substr(num1.length - i - 1, 1)[0]);
        digit2 = atoi(&num2.digits.substr(num2.length - i - 1, 1)[0]);

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
        digit1 = atoi(&num1.digits.substr(num1.length - i - 1, 1)[0]);
        result_digit = digit1 + carry; 
        if (result_digit < 0) { 
            carry = -1;
            result_digit += 10;
        }
        else carry = 0;
        result.digits = to_string(result_digit) + result.digits;
    }

    for (int i = iter; i < num2.length; i++) {
        digit2 = atoi(&num2.digits.substr(num2.length - i - 1, 1)[0]);
        result_digit = digit1 + carry; 
        if (result_digit < 10) { 
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
    int carry = 0;
    int digit1, digit2, result_digit;
    inf_int result;
    // implement XOR logical operation using AND and OR
    result.thesign = (num1.thesign || num2.thesign) && !(num1.thesign && num2.thesign);
    result.thesign = !result.thesign;

    for(int i = 0; i < num2.length; i++) {
        inf_int temp;
        temp.thesign = num1.thesign;
        digit2 = atoi(&num2.digits.substr(num2.length - i - 1, 1)[0]);
        for(int j = 0; j < num1.length; j++) {
            digit1 = atoi(&num1.digits.substr(num1.length - j - 1, 1)[0]);
            result_digit = digit1 * digit2 + carry;
            carry = result_digit / 10;
            result_digit %= 10;
            temp.digits = to_string(result_digit);

            for(int ap = 0; ap < i + j; ap++) {
                temp.digits.append("0");
            }
            temp.length = temp.digits.length();
            result = result + temp;
        }
    }

    if (carry) {
        result.digits = to_string(carry) + result.digits;
    }

    return result;
}
// friend inf_int operator/(const inf_int& , const inf_int&); // not required

ostream& operator<<(ostream& os, const inf_int& num) {
    string out;
    if (num.thesign)
        out = num.digits;
    else
        out = "-" + num.digits;
    
    os << out;
    return os;
}
// friend istream& operator>>(istream& , inf_int&);    // not required
