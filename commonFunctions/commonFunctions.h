#include <string>

#pragma once

using namespace std;

namespace commonFunctions{
    void print(string givenString, bool recievingInput=false);
    int count(string original, char target, int length);
    bool isNumber(string inputNum);
    string exponent(string num);
    string getNumber(string counter);
    string checkInt(string num);
}
