#include <iostream>
#include "longint.h"

using namespace std;

// Offical Test file
int main( ) {

  // Test Constructors
  LongInt Default, Empty, MultipleZeros("-0000000000000000"), Large("0000001234567890123456789012345678901234567890"), InputEmpty, InputLarge, InputWithNonDigits, InputNegative, Regular("000100200300");
  // NonDigits("-No Digits, just letters");

  LongInt RegularCopy(Regular);

  cout << "Copy of 000100200300 = " << RegularCopy << endl;

  // Test input operator
  cout << "Test Input operator! Please follow input instructions for each item" << endl;
  cout << "Enter a large number for InputLarge: ";
  cin >> InputLarge;
  cout << "Enter 0 for InputEmpty: ";
  cin >> InputEmpty;
  // cout << "Enter a long string like '-this longint has no digits' for inputWithNonDigits: ";
  // cin >> InputWithNonDigits;
  cout << "\n" << endl;

  // Test output operator
  cout << "Test output operator!" << endl;
  cout << "InputLarge = " << InputLarge << endl;
  cout << "InputEmpty = " << InputEmpty << endl;
  cout << "InputWithNonDigits = " << InputWithNonDigits << endl;
  cout << "Check LonginDriver.cpp to see if these are correct" << endl;
  cout << "Default = " << Default << endl;
  cout << "MultipleZeros = " << MultipleZeros << " (despite the name it should only have one zero...)" << endl;
  cout << "Large = " << Large << endl;
  cout << "Regular = " << Regular << endl;
  // cout << "NonDigits = " << NonDigits << endl;
  cout << "\n" << endl;

  // Test + and -
  // Create simple numbers for easy checking
  LongInt hundred("100"), twohundred("200"), one("1"), negativeone("-1");
  cout << "+ and - operator!" << endl;

  //Test pos + pos
  cout << hundred << " + " << twohundred << " =  " << ( hundred + twohundred ) << endl;
  //Test pos + neg
  cout << hundred << " + " << negativeone << " =  " << ( hundred + negativeone ) << endl;
  //Test neg + pos
  cout << negativeone << " + " << hundred << " =  " << ( hundred + negativeone ) << endl;
  //Test neg + neg
  cout << negativeone << " + " << negativeone << " =  " << ( negativeone + negativeone ) << endl;

  // Test larger - smaller
  cout << twohundred << " - " << hundred << " =  " << ( twohundred - hundred ) << endl;
  // Test smaller - larger
  cout << hundred << " - " << twohundred << " =  " << ( hundred - twohundred ) << endl;
  // Test pos - neg
  cout << hundred << " - " << negativeone << " =  " << ( hundred - negativeone ) << endl;
  // Test neg - neg
  cout << negativeone << " - " << negativeone << " =  " << ( negativeone - negativeone ) << endl;
  // Test neg - pos
  cout << negativeone << " - " << hundred << " =  " << ( negativeone - hundred ) << endl;

  // Test large - something
  cout << Large << " - " << hundred << " =  " << ( Large - hundred ) << endl;

  // empty minus something
  cout << hundred << " - " << Empty << " =  " << ( hundred - Empty ) << endl;
  cout << "\n" << endl;

  // Test assigment
  cout << "= operator!" << endl;

  // Empty = something
  Empty = hundred;
  cout << "Assign 0 to " << hundred << " =  " << Empty << endl;
  // Empty = something
  Empty = Default;
  cout << "Assign " << Empty << " to " << Default << " =  " << Empty << endl;
  cout << "\n" << endl;

  // Test Binary logic
  cout << "100 == 100? " << (hundred == hundred) << endl;
  cout << "100 != 100? " << (hundred != hundred) << endl;
  cout << "100 != -1? " << (hundred == hundred) << endl;
  cout << "100 <= 100? " << (hundred <= hundred) << endl;
  cout << "100 >= 100? " << (hundred >= hundred) << endl;
  cout << "100 > -1 " << (hundred > negativeone) << endl;
  cout << "100 >= -1 " << (hundred >= negativeone) << endl;
  cout << "100 < -1 " << (hundred < negativeone) << endl;
  cout << "100 <= -1 " << (hundred <= negativeone) << endl;
  cout << "\n" << endl;
  
  // 

}