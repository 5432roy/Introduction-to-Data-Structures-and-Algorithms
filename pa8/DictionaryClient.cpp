//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
   Dictionary A;
    A.setValue("c", 3);
    A.setValue("a", 1);
    A.setValue("b", 2);
    A.remove("a");
    if (A.size() != 2)
      return 1;
    A.setValue("e", 5);
    cout << A.pre_string() << endl;
    A.remove("c");
    if (A.size() != 2)
      return 2;

   return( EXIT_SUCCESS );
}