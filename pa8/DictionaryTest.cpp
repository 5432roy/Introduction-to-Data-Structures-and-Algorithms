/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA8
 * DictionaryTest.cpp
 * The unitTest for Dictionary ADT (Red-Black Tree)
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

void test_size_and_clear() {
    Dictionary dict;
    check(dict.size() == 0, "Constructor for empty Dictionary");

    dict.setValue("apple", 5);
    check(dict.size() == 1, "Dictionary size after adding one item");

    dict.clear();
    check(dict.size() == 0, "Dictionary size after clear");
}

void test_setValue_and_contains() {
    Dictionary dict;
    dict.setValue("banana", 10);
    check(dict.contains("banana"), "Dictionary contains key after setValue");
    check(!dict.contains("apple"), "Dictionary does not contain non-existent key");
}

void test_getValue() {
    Dictionary dict;
    dict.setValue("cherry", 15);
    check(dict.getValue("cherry") == 15, "getValue returns correct value");
}

void test_equals() {
    Dictionary dict1, dict2;
    dict1.setValue("date", 20);
    dict2.setValue("date", 20);

    check(dict1.equals(dict2), "Two dictionaries with same elements are equal");

    dict2.setValue("elderberry", 25);
    check(!dict1.equals(dict2), "Two dictionaries with different elements are not equal");
}

void test_remove_root() {
    Dictionary dict;
    dict.setValue("30",0);
    dict.remove("30");
    check(dict.size() == 0, "Removing root from tree with only root");
    check(dict.to_string() == "", "Check if the root is correctly removed");

    dict.setValue("30",0);
    dict.setValue("10",0);
    dict.remove("30");
    check(dict.size() == 1, "Removing root from tree with children");
    check(dict.pre_string() == "10\n", "Color of node 10 should be root and BLACK");
}

void test_remove_one_red() {
    Dictionary dict;
    dict.setValue("30",0);
    dict.setValue("10",0);
    dict.setValue("40",0);
    dict.setValue("20",0);
    dict.remove("10");
    check(dict.pre_string() == "30\n20\n40\n", "Removing a node with red child");

    dict.setValue("10",0);
    dict.remove("10");
    check(dict.pre_string() == "30\n20\n40\n", "Removing a red leaf");
}

void test_remove_both_black_red_nephew1() {
    Dictionary dict;
    dict.setValue("30",0);
    dict.setValue("20",0);
    dict.setValue("40",0);
    dict.setValue("50",0);
    dict.remove("20");
    check(dict.pre_string() == "40\n30\n50\n", "Removing node with red nephew (RR Case)");
}

void test_remove_both_black_red_nephew2() {
    Dictionary dict;
    dict.setValue("30",0);
    dict.setValue("20",0);
    dict.setValue("40",0);
    dict.setValue("35",0);
    dict.remove("20");
    check(dict.pre_string() == "35\n30\n40\n", "Removing node with red nephew (RL case)");
}

void test_remove_both_black_red_nephew3() {
    Dictionary dict;
    dict.setValue("30",0);
    dict.setValue("20",0);
    dict.setValue("40",0);
    dict.setValue("15",0);
    dict.remove("40");
    check(dict.pre_string() == "20\n15\n30\n", "Removing node with red nephew (LL case)");
}

void test_remove_both_black_red_nephew4() {
    Dictionary dict;
    dict.setValue("30",0);
    dict.setValue("20",0);
    dict.setValue("40",0);
    dict.setValue("25",0);
    dict.remove("40");
    check(dict.pre_string() == "25\n20\n30\n", "Removing node with red nephew (LR case)");
}

int main() {
    test_size_and_clear();
    test_setValue_and_contains();
    test_getValue();
    test_equals();
    test_remove_root();
    test_remove_one_red();
    test_remove_both_black_red_nephew1();
    test_remove_both_black_red_nephew2();
    test_remove_both_black_red_nephew3();
    test_remove_both_black_red_nephew4();

    cout << "All tests completed." << endl;
    return 0;
}