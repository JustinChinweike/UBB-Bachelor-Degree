//App.cpp
#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}

//Problem statement:
// ADT SortedMultiMap – using a SLLA with (key, value) pairs 
// ordered based on a relation on 
//the keys.A key can appear in multiple pairs.