// expmain.cpp
//
// ICS 46 Spring 2018
// Project #4: Set the Controls for the Heart of the Sun
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.
#include <iostream>
#include "WordChecker.hpp"
#include "ListSet.hpp"

int main()
{
    ListSet<std::string> set;
    set.add("word");
    WordChecker checker{set};
    std::vector<std::string> vec = checker.findSuggestions("ispell");
    std::cout << vec.size() << std::endl;
    for (int i = 0; i < vec.size(); ++ i)
        {
        std::cout << vec[i] << std::endl;
        }
    std::cout << "End" << std::endl;
    return 0;
}

