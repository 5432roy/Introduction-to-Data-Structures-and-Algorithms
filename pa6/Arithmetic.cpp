/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA6
 * Arithmetic.cpp
 * The main program for this project.
 * This program will take two string as the input of the BigInteger and do the basic arithmetic opertaion
*/
#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " <input> <output>" << endl;
        return EXIT_FAILURE;
    }

    ifstream in;
    ofstream out;

    in.open(argv[1]);
    if(!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if(!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    string string_A;
    string empty_line;
    string string_B;

    getline(in, string_A);
    getline(in, empty_line);
    getline(in, string_B);

    BigInteger A = BigInteger(string_A), B = BigInteger(string_B);

    cout << A << endl << endl;

    cout << B << endl << endl;

    cout << A + B << endl << endl;

    cout << A - B << endl << endl;

    cout << A - A << endl << endl;

    cout << 3 * A - 2 * B << endl << endl;

    cout << A * B << endl << endl;

    cout << A * A << endl << endl;

    cout << B * B << endl << endl;

    cout << 9 * A * A * A * A + 16 * B * B * B * B * B << endl << endl;
    
    in.close();
    out.close();

    return EXIT_SUCCESS;
}