/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA6
 * BigIntegerTest.cpp
 * The unitTest for BigInteger Class
*/

#include "BigInteger.h"
#include "List.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void reportTest(const string& testName, bool result) {
   cout << testName << ": " << (result ? "PASSED" : "FAILED") << endl;
}

void check(bool condition, const string& message) {
   if (!condition) {
      reportTest(message, false);
      assert(condition);
   } else {
      reportTest(message, true);
   }
}

// Test constructors
void test_constructors() {
   BigInteger zero;
   check(zero.to_string() == "0", "Constructor for zero BigInteger");

   BigInteger num1(12345);
   check(num1.to_string() == "12345", "Constructor with long");

   BigInteger num2("-67890");
   check(num2.to_string() == "-67890", "Constructor with string");

   BigInteger copyNum(num1);
   check(copyNum.to_string() == "12345", "Copy constructor");
}

// Test arithmetic operations
void test_arithmetic() {
   BigInteger num1(123);
   BigInteger num2(456);

   BigInteger sum = num1 + num2;
   check(sum.to_string() == "579", "Addition test");

   BigInteger diff = num1 - num2;
   check(diff.to_string() == "-333", "Subtraction test");

   BigInteger product = num1 * num2;
   check(product.to_string() == "56088", "Multiplication test");
}

// Test comparison operations
void test_comparison() {
   BigInteger num1(123);
   BigInteger num2(456);

   check(num1 < num2, "Less than test");
   check(num2 > num1, "Greater than test");

   BigInteger num3(123);
   check(num1 == num3, "Equal test");
}

// Test string conversion
void test_to_string() {
   BigInteger num1(12345);
   check(num1.to_string() == "12345", "To string conversion");

   BigInteger num2(-67890);
   check(num2.to_string() == "-67890", "To string negative number");
}

void test_large_addition() {
   BigInteger big1("123456789");
   BigInteger big2("987654321");

   BigInteger sum = big1 + big2;
   check(sum.to_string() == "1111111110", "Addition with large numbers");
}

void test_large_subtraction() {
   BigInteger big1("1000000000");
   BigInteger big2("123456789");

   BigInteger diff = big1 - big2;
   check(diff.to_string() == "876543211", "Subtraction with large numbers");
}

void test_large_multiplication() {
   BigInteger big1("123456789");
   BigInteger big2("987654321");

   BigInteger product = big1 * big2;
   check(product.to_string() == "121932631112635269", "Multiplication with large numbers");
}

void test_operations_with_zero() {
   BigInteger zero;
   BigInteger big("123456789");

   check((zero + big).to_string() == "123456789", "Adding zero");
   check((big - zero).to_string() == "123456789", "Subtracting zero");
   check((zero * big).to_string() == "0", "Multiplying by zero");
}

void test_negative_arithmetic() {
   BigInteger neg1("-123456789");
   BigInteger neg2("-987654321");

   check((neg1 + neg2).to_string() == "-1111111110", "Addition with negative numbers");
   check((neg1 - neg2).to_string() == "864197532", "Subtraction with negative numbers");
   check((neg1 * neg2).to_string() == "121932631112635269", "Multiplication with negative numbers");
}

void test_large_comparisons() {
   BigInteger big1("123456789123456789");
   BigInteger big2("987654321987654321");

   check(big1 < big2, "Less than with large numbers");
   check(big2 > big1, "Greater than with large numbers");
}

void test_invalid_string() {
   try {
      BigInteger invalid1("");
      check(false, "Empty string should throw an exception");
   } catch (std::invalid_argument& e) {
      check(true, "Empty string throws invalid_argument");
   }

   try {
      BigInteger invalid2("1$5");
      check(false, "String with non-numeric characters should throw an exception");
   } catch (std::invalid_argument& e) {
      check(true, "String with non-numeric characters throws invalid_argument");
   }
}

void test_large_numbers_different_signs() {
   BigInteger bigPositive("1000000000");
   BigInteger bigNegative("-123456789");

   check((bigPositive + bigNegative).to_string() == "876543211", "Addition with large numbers of different signs");
   check((bigPositive - bigNegative).to_string() == "1123456789", "Subtraction with large numbers of different signs");
   check((bigPositive * bigNegative).to_string() == "-123456789000000000", "Multiplication with large numbers of different signs");
}


int main() {
   test_constructors();
   test_arithmetic();
   test_comparison();
   test_to_string();
   test_large_addition();
   test_large_subtraction();
   test_large_multiplication();
   test_operations_with_zero();
   test_negative_arithmetic();
   test_large_comparisons();
   test_invalid_string();
   test_large_numbers_different_signs();
   
   cout << "*************************" << endl;
   cout << "All tests completed." << endl;
   return 0;
}