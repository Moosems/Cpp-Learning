#include "commonFunctions.h"
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

namespace commonFunctions{
    bool firstPrint = true, *fP;
    char allowedNonNumbers[4] = {'.', '-', '^', '*'}, *aNN;

    void print(string givenString, bool recievingInput){
        string printString = givenString;
        if (firstPrint == false){
            printString = "\n%s", printString.c_str();
        }
        if (recievingInput == false){
            printString += "\n";
        }
        printf("%s", printString.c_str());
    };
    int count(string original, char target, int length){
        int count = 0;
        if (length <= 0){
            length = original.length();
        }
        for (int i = 0; i < length; i++){
            if (original[i] == target){
                count += 1;
            }
        }
        return count;
    };
    bool isNumber(string inputNum){
        int length = inputNum.length();
        int nonNumberCount = sizeof(allowedNonNumbers) / sizeof(char);
        int counts[nonNumberCount];
        int sumOfCounts = 0;
        for (int i = 0; i < nonNumberCount; i++){
            counts[i] = count(inputNum, allowedNonNumbers[i], length);
            sumOfCounts += counts[i];
        }
        bool onlyAllowedNonNumbers = true;
        for (int i = 0; i < length; i++){
            char currentChar = inputNum[i];
            if (isdigit(currentChar) == 0){
                if (not (find(begin(allowedNonNumbers), end(allowedNonNumbers), currentChar) != end(allowedNonNumbers))){
                    // -.3^-.2 doesn't pass and it returns false partly cause it has multiple negatives & multiple .'s
                    return false;
                }
            }
        }
        for (int i = 0; i < nonNumberCount; i++){
            if ((counts[i] > 1) || (length == sumOfCounts)){
                //TODO: Check that the placement of the decimals aren't next to each other instead of invalidating multiple
                return false;
            }
        }
        return true;
    };
    string exponent(string num){
        bool exponent = false;
        int length = num.length();
        int exponentCount = count(num, '^', length);
        string result;
        if (exponentCount > 1){
            print("Too many ^'s");
            exit(0);
        }else if(exponentCount == 1){
            int index = num.find('^');
            float firstNum = stof(string(num.begin(), num.begin()+index));
            float secondNum = stof(string(num.begin()+index + 1, num.end()));
            result = to_string(pow(firstNum, secondNum));
        }else{
            result = num;
        }
        return result;
    };
    string getNumber(string counter){
        string printString = "Please give the " + counter + " number to be used in the operation: ";
        string mediator;
        print(printString, true);
        // Uses string because it removes the necessity of try/catch and allows for better checking and more versatility with the tradeoff of mental sanity
        getline(cin, mediator);
        mediator = exponent(mediator);
        if ((mediator == "") || (isNumber(mediator) == false)){
            print("Cannot enter non-number");
            exit(0);
        }
        return mediator;
    };
    string checkInt(string num){
        char firstChar = num[0];
        if (firstChar == '.'){
            num = "0" + num;
        }else if (firstChar == '-'){
            if (num[1] == '.'){
                num = "-0." + string(num.begin() + 2, num.end());
            }
        }
        if (stoi(num) - stof(num) == stof(num)){
            return to_string(stoi(num));
        }else{
            for (int i = num.length()-1; i >= 0; i--){
                if (num[i] == '0'){
                    num.erase(i, 1);
                }
            }
            if (num[num.length()-1] == '.'){
                num += '0';
            }
            return num;
        }
    };
}
