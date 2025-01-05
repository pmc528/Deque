#include "longint.h"

using namespace std;

// Input operator overloading
istream& operator>>(istream &input, LongInt &rhs) {
    // Assuming that user may have a chance to re-input the number again
    // It's neccessary to reset everything if it happens
    rhs.negative = false;
    rhs.digits.clear();

    // Create the string the receive the input from user
    string str;
    input >> str;

    // Initialize the index and set it as 0
    int index = 0;

    // Handle the case if that's negative number
    if (str[index] == '-') {
        rhs.negative = true;
        index++;
    } else rhs.negative = false;

    // Input numbers to the queue
    for (; index < str.size(); index++)
        if (isdigit(str[index])) rhs.digits.addBack(str[index]);

    // Handle the invalid input by removing 0s
    rhs.remove0s();

    return input;
}

// Output operator overloading
ostream& operator<<(ostream &output, const LongInt &rhs) {
    // copy w/ copy constructor
    LongInt rhs_copy = rhs;

    // Showing the value
    if (rhs_copy.negative) output << "-";
    while (!rhs_copy.digits.isEmpty()) //loop while the rhs copy is not empty
        output << rhs_copy.digits.removeFront(); //print one char at a time

    return output;
}

// Constructor
LongInt::LongInt(const string str) {
    int index = 0; //uses index to check for negative at index 0 and also uses it as starting point in the for loop below

    //In the case of negative number
    if (str[index] == '-') {
        negative = true;
        index++;
    } else negative = false;

    // Input numbers to the queue from back
    for (; index < str.size(); index++)
        if (isdigit(str[index])) digits.addBack(str[index]);

    //clean up by removing any 0's
    remove0s();
}

// Copy Constructor
LongInt::LongInt(const LongInt &rhs) {
    //initialize variables
    negative = rhs.negative;
    digits = rhs.digits;
}

// Default Constructor
LongInt::LongInt() {
    digits.addFront('0'); //default 0
    negative = false; //default false
}

// Destructor
LongInt::~LongInt( ) {
    //set to false and clear deque
    negative = false;
    digits.clear();
}

// arithmetic operator +
//this function uses a carry variable to help w/ the addition of values
//takes into account cases when: lhs.size() > rhs.size(), lhs.size() < rhs.size() and lhs.size() == rhs.size()
//also takes into account when one side is neg or if both are negative
LongInt LongInt::operator+( const LongInt &rhs ) const {
    int carry = 0; char num;
    LongInt lhs_copy = *this;
    LongInt rhs_copy = rhs;

    //handle odd cases
    // positive lhs + negative rhs should be: lhs - rhs
    if (!lhs_copy.negative && rhs_copy.negative) {
        rhs_copy.negative = false;
        return lhs_copy - rhs_copy;
    }
    // negative lhs + positive rhs should be: rhs - lhs
    if (lhs_copy.negative && !rhs_copy.negative) {
        lhs_copy.negative = false;
        return rhs_copy - lhs_copy;
    }

    // Procedure for calculation (+)
    //variable size checks to see if the lhs coyp is less than or equal to rhs copy and sets size accordingly
    int size = (lhs_copy.digits.size() <= rhs_copy.digits.size()) ? lhs_copy.digits.size() : rhs_copy.digits.size();

    // program will initialize the object to 0 so we need to empty the queue
    LongInt longInt; longInt.digits.clear();

    //loop through to add each element starting from the back and add sum total to digit variable
    for (int i = 0; i < size; i++) {
        int leftnum = CharToInt(lhs_copy.digits.removeBack());
        int rightnum = CharToInt(rhs_copy.digits.removeBack());
        num = IntToChar(( leftnum + rightnum + carry ) % 10);
        longInt.digits.addFront(num);
        carry = (leftnum + rightnum + carry) / 10;
    }

    // assess the char length difference between lhs and rhs
    size = lhs_copy.digits.size() - rhs_copy.digits.size();
    if (size == 0) { //is the size between lhs and rhs the same?
        // if the input is 99 + 11, etc
        if (carry == 1) {
            longInt.digits.addFront(IntToChar(carry));
        }
        // change negative flag to true if both lhs and rhs are negative
        if (lhs_copy.negative && rhs_copy.negative) {
            longInt.negative = true;
        }
        return longInt;
    }

    // cases where lhs bigger than rhs
    size = (size < 0) ? (size) * (-1) : size; //keep size as positive int
    for (int i = 0; i < size; i++) {
        //this section takes into account if lhs.size() >= rhs.size()
        //since rhs has run out of values, it loops through to keep adding lhs back value to carry and re-calculating carry with each iteration
        if (lhs_copy.digits.size() >= rhs_copy.digits.size()) { //check if lhs_copy is greater or equal to rhs_copy
            int leftnum = CharToInt(lhs_copy.digits.removeBack());
            num = IntToChar(leftnum + carry);
            longInt.digits.addFront(num);
            carry = (leftnum + carry) / 10;
        } else {
            //this section takes into account if rhs.size() > lhs.size()
            //with each iteration in the for loop this will remove value at back and add to carry and add that total to the longint final result
            int rightnum = CharToInt(rhs_copy.digits.removeBack());
            num = IntToChar(rightnum + carry);
            longInt.digits.addFront(num);
            carry = (rightnum + carry) / 10; //re-calculate carry w/ each iteration
        }
    }
    // in a case such as: 99 + 1, bring the extra 1 to front
    if (carry == 1) longInt.digits.addFront(IntToChar(carry));

    // if both values are negative then neg flag should be switched to true
    if (lhs_copy.negative && rhs_copy.negative) {
        longInt.negative = true;
    }
    return longInt;
}

// arithmetic operators -
//this function uses a temp variable to represent borrowing during subtraction of values
//takes into account cases when: lhs.size() > rhs.size(), lhs.size() < rhs.size() and lhs.size() == rhs.size()
//also takes into account if one or both values are negative
LongInt LongInt::operator-( const LongInt &rhs ) const {
    int temp = 0; char num;
    LongInt lhs_copy = *this;
    LongInt rhs_copy = rhs;

    // positive lhs - negative rhs should be: lhs + rhs
    if (!lhs_copy.negative && rhs_copy.negative) {
        lhs_copy.negative = false; rhs_copy.negative = false;
        return lhs_copy + rhs_copy;
    }

    // negative lhs - positive rhs should be: -(lhs + rhs).
    if (lhs_copy.negative && !rhs_copy.negative) {
        lhs_copy.negative = false; rhs_copy.negative = false;
        LongInt ans = lhs_copy + rhs_copy;
        ans.negative = true;
        return ans;
    }

    // negative lhs - negative rhs should be: rhs - lhs
    if (lhs_copy.negative && rhs_copy.negative) {
        lhs_copy.negative = false; rhs_copy.negative = false;
        return rhs_copy - lhs_copy;
    }

    // when rhs > lhs, then swap them and add '-' to make negative
    if (rhs_copy > lhs_copy) {
        LongInt result = rhs_copy - lhs_copy;
        result.negative = true;
        return result;
    }

    // calculating '-'
    //checks if lhs_copy <= rhs_copy and then sets size variable accordingly
    int size = (lhs_copy.digits.size() <= rhs_copy.digits.size()) ? lhs_copy.digits.size() : rhs_copy.digits.size();

    // clear the default 0 value
    LongInt longInt; longInt.digits.clear();

    //loop through to start subtraction starting with value from the back. use 'temp' variable to store borrowed value during subtraction
    for (int i = 0; i < size; i++) {
        int leftnum = CharToInt(lhs_copy.digits.removeBack());
        int rightnum = CharToInt(rhs_copy.digits.removeBack());
        if (leftnum - rightnum < 0) {
            if (temp == 0) {
                num = IntToChar(10 + leftnum - rightnum);
                temp++;
                longInt.digits.addFront(num);
            } else {
                num = IntToChar(10 + leftnum - rightnum - temp);
                longInt.digits.addFront(num);
            }
        } else {
            if (leftnum - rightnum - temp < 0) {
                num = IntToChar(10 + leftnum - rightnum - temp);
            }
            else {
                num = IntToChar(leftnum - rightnum - temp);
                temp = 0;
            }
            longInt.digits.addFront(num);
        }
    }

    // remove unwanted zeros
    longInt.remove0s();

    // compare the size of lhs_copy and rhs_copy
    // don't execute if the size is 0
    size = lhs_copy.digits.size() - rhs_copy.digits.size();
    size = (size < 0) ? (size) * (-1) : size; //update size var and keep it positive
    for (int i = 0; i < size; i++) {
        //if lhs_copy.size() >= rhs_copy.size() then take from lhs back value
        if (lhs_copy.digits.size() >= rhs_copy.digits.size()) {
            int leftnum = CharToInt(lhs_copy.digits.removeBack());
            if (leftnum - temp < 0) {
                num = IntToChar(10 + leftnum - temp);
            }
            else {
                num = IntToChar(leftnum - temp);
                temp = 0;
            }
            longInt.digits.addFront(num);
        } else { //else if lhs_copy.size() < rhs_copy.size() then take from rhs back value
            int rightnum = CharToInt(rhs_copy.digits.removeBack());
            if (rightnum - temp < 0) {
                num = IntToChar(10 + rightnum - temp);
            }
            else {
                num = IntToChar(rightnum - temp);
                temp = 0;
            }
            longInt.digits.addFront(num);
        }
    }

    // clean up unwanted zeros
    longInt.remove0s();

    return longInt;
}

// Assignment operator
const LongInt& LongInt::operator=( const LongInt &rhs ) {
    negative = rhs.negative;
    digits = rhs.digits; // using assignment operator from Deque class
    return *this;
}

// Logical binary operator <
bool LongInt::operator<( const LongInt & rhs ) const {
  return !(*this >= rhs);
}

// Logical binary operator <=
bool LongInt::operator<=( const LongInt & rhs ) const {
  return !(*this > rhs);
}

// Logical binary operator >
bool LongInt::operator>( const LongInt & rhs ) const {
    // compare the the length of the number first, then compare the '-'
    if (digits.size() > rhs.digits.size()) {
        if (negative) {
            return false;
        }
        else {
            return true;
        }
    } else if (digits.size() < rhs.digits.size()) {
        if (rhs.negative) {
            return true;
        }
        else return false;
    } else if (digits.size() == rhs.digits.size()) {
        if (!negative && rhs.negative) {
            return true;
        }
        else if (negative && !rhs.negative) {
            return false;
        }
    }

    // compare digit by digit if those number having the same length
    LongInt lhs_copy = *this;
    LongInt rhs_copy = rhs;
    int leftNum, rightNum;
    while (!lhs_copy.digits.isEmpty()) {
        leftNum = CharToInt(lhs_copy.digits.removeFront());
        rightNum = CharToInt(rhs_copy.digits.removeFront());
        if (!negative && !rhs.negative) {
            if (leftNum > rightNum) {
                return true;
            }
            else if (leftNum < rightNum) return false;
        } else {
            if (leftNum > rightNum) {
                return false;
            }
            else if (leftNum < rightNum) {
                return true;
            }
        }
    }

    // return false if the they're equal
    return false;
}

// Logical binary operator >=
bool LongInt::operator>=( const LongInt & rhs ) const {
  return (*this > rhs || *this == rhs);
}

// Logical binary operator ==
bool LongInt::operator==( const LongInt & rhs ) const {
    // compare length of the number fisrt
    if (digits.size() != rhs.digits.size()) return false;
    // Compareing the '-'
    if (negative != rhs.negative) return false;

    // compare digit by digit if those number having the same length
    LongInt lhs_copy = *this;
    LongInt rhs_copy = rhs;
    int leftNum, rightNum;
    while (!lhs_copy.digits.isEmpty()) {
        leftNum = CharToInt(lhs_copy.digits.removeFront());
        rightNum = CharToInt(rhs_copy.digits.removeFront());
        if (leftNum != rightNum) return false;
    }

    // Return ture if they're equal
    return true;
}

bool LongInt::operator!=( const LongInt & rhs ) const {
  return !(*this == rhs);
}

// Private methods
//Purpose: clean up zeros
void LongInt::remove0s( ) {
    // Handle the case if that's 0 or 000000000000, etc
    char currentFront = this->digits.getFront();
    if (currentFront == '0') {
        // Remove 0's from front element until currentFront is non longer 0 and digis is empty
        for (; currentFront == '0' && !this->digits.isEmpty(); currentFront = this->digits.removeFront());
        // Need to push back the digit poped out before
        this->digits.addFront(currentFront);
        //if 0 is the only value then ensure negative is set to false
        if (this->digits.size() == 1 && this->digits.getFront() == '0')
            this->negative = false;
    }
}

// Function for converting char to int
int LongInt::CharToInt(const char c) const {
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return 0;
    }
}

// Function for converting integer to char
char LongInt::IntToChar(const int c) const {
    switch (c) {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        default:
            return '0';
    }
}
