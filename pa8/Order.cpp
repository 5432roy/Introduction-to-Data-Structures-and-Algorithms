/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA/
 * Order.cpp
 * One client program for the dictionary ADT
*/
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;


int main(int argc, char* argv[]){

    ifstream in;
    ofstream out;
    string line;

    if (argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    in.open(argv[1]);
    if (!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    int i = 1;
    Dictionary D;
    while(getline(in, line)){
        line.erase(line.length() - 1);
        D.setValue(line, i);
        i++;
    }

    out << D << endl;    
    out << D.pre_string() <<endl;

    in.close();
    out.close();

    return(EXIT_SUCCESS);

}