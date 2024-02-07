/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA8
 * WordFrequency.cpp
 * The second client program for this project.
 * Count the frequency of each words and keep the words in a Dictionary base on Red-Black Tree
*/

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int token_count, line_count;
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string tokenBuffer;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789";

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    Dictionary dict;

    // read each line of input file, then count and print tokens 
    line_count = 0;
    while( getline(in, line) )  {
        line_count++;
        len = line.length();
        
        // get tokens in this line
        token_count = 0;
        tokenBuffer = "";

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);

        while(token[0] != 13 &&  token!="" ){
            // update token buffer
            tokenBuffer += token+"\n";
            token_count++;

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);

            token = line.substr(begin, end-begin);
        }

        // print tokens in this line
        if(tokenBuffer.length() > 0) {
            string str = "";
            for(size_t i = 0; i < tokenBuffer.length(); i++) {
                if(tolower(tokenBuffer[i]) < 97 || tolower(tokenBuffer[i] > 122)) {
                    if(str != "") {
                        dict.setValue(str, dict.contains(str) ? dict.getValue(str) + 1 : 1);
                    }
                    str = "";
                } else {
                    str += tolower(tokenBuffer[i]);
                }
            }
        }
    }

    out << dict << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
