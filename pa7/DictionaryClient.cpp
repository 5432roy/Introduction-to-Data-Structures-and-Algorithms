//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int test() {
   Dictionary A;
   A.setValue("a", 1);
   A.setValue("b", 5);
   A.setValue("c", 16);
   A.setValue("d", 176);
   A.setValue("e", 3214);
   cout << A << endl;
   A.begin();
   cout << A.currentKey() << endl;
   A.next();
      cout << A.currentKey() << endl;
   A.next();
      cout << A.currentKey() << endl;

   if (A.currentKey() != "c" || A.currentVal() != 16)
      return 1;
   A.next();
   A.next();
   A.next();
   if (A.hasCurrent())
      return 2;
   return 0;
}

int main(){

   test();
   return( EXIT_SUCCESS );
}