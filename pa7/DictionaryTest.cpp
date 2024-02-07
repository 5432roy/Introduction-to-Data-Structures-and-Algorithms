/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA7
 * DictionaryTest.cpp
 * The unitTest for Dictionary ADT
*/
#include "Dictionary.h"
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

void test_constructors() {
   Dictionary dict;
   check(dict.size() == 0, "Constructor for empty Dictionary");
}

void test_insertion_and_search() {
   Dictionary dict;
   dict.setValue("apple", 1);
   dict.setValue("banana", 2);
   check(dict.contains("apple"), "Insertion and search - apple");
   check(dict.contains("banana"), "Insertion and search - banana");
   check(!dict.contains("cherry"), "Search for non-existent key");
}

void test_retrieval() {
   Dictionary dict;
   dict.setValue("apple", 1);
   check(dict.getValue("apple") == 1, "Retrieval of value for key 'apple'");
}

void test_iteration() {
   Dictionary dict;
   dict.setValue("apple", 1);
   dict.setValue("banana", 2);
   dict.setValue("cherry", 3);

   dict.begin();
   check(dict.hasCurrent(), "Iteration - begin");
   check(dict.currentKey() == "apple", "Iteration - currentKey at begin");

   dict.next();
   check(dict.currentKey() == "banana", "Iteration - next method");

   dict.end();
   check(dict.currentKey() == "cherry", "Iteration - end method");
}

void test_deletion() {
   Dictionary dict;
   dict.setValue("apple", 1);
   dict.remove("apple");
   check(!dict.contains("apple"), "Deletion of key 'apple'");
}

void test_clear() {
   Dictionary dict;
   dict.setValue("apple", 1);
   dict.clear();
   check(dict.size() == 0, "Clear method");
}

int main() {
   cout << "*************************" << endl;
   cout << "Starting Dictionary tests." << endl;

   test_constructors();
   test_insertion_and_search();
   test_retrieval();
   test_iteration();
   test_deletion();
   test_clear();

   cout << "*************************" << endl;
   cout << "All tests completed." << endl;
   return 0;
}
