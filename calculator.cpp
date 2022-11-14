#include <iostream>
#include <math.h>
#include <string>
#include <map>
using namespace std;

bool firstPrint = true, *fP;
char allowedNonNumbers[3] = {'.', '-', '+'};

void print(std::string givenString, bool recievingInput = false){
    std::string printString = givenString;
    if (firstPrint == false){
        printString = "\n%s", printString.c_str();
    }
    if (recievingInput == false){
        printString += "\n";
    }
    printf("%s", printString.c_str());
}

int count(std::string original, char target, int length){
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
}

bool isNumber(std::string inputNum){
    int length = inputNum.length();
    int nonNumberCount = sizeof(allowedNonNumbers) / sizeof(char);
    int counts[nonNumberCount];
    for (int i = 0; i < nonNumberCount; i++){
        counts[i] = count(inputNum, allowedNonNumbers[i], length);
    }
    for (int i = 0; i < length; i++){
        char currentChar = inputNum[i];
        if ((std::isdigit(currentChar) == 0) && not (std::find(std::begin(allowedNonNumbers), std::end(allowedNonNumbers), currentChar) != std::end(allowedNonNumbers))){
            return false;
        }
    }
    for (int i = 0; i < nonNumberCount; i++){
        if ((counts[i] > 1) || (length == counts[i])){
            return false;
        }
    }
    return true;
}

std::string getNumber(std::string counter){
    std::string printString = "Please give the " + counter + " number to be used in the operation: ";
    std::string mediator;
    print(printString, true);
    std::getline(std::cin, mediator);
    if ((mediator == "") || (isNumber(mediator) == false)){
        print("Cannot enter non-number");
        exit(0);
    }
    return mediator;
}

std::string checkInt(std::string num){
    if (std::stoi(num) - std::stof(num) == std::stof(num)){
        return std::to_string(std::stoi(num));
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
}

int main(){
    std::string operation;
    std::string stringToUse;
    map<std::string, std::string> names;
    map<std::string, std::string> outputNums;
    names["+"] = "sum";
    names["-"] = "difference";
    names["*"] = "product";
    names["/"] = "quotient";
    print("This is a simple calculator I wrote in C++\nPlease give your operator here (+, -, *, /): ", true);
    std::getline(std::cin, operation);
    if ((operation != "+") && (operation != "-") && (operation != "*") && (operation != "/")){
        print("That is not a valid operation. Shutting down");
        return 0;
    }
    outputNums["firstNum"] = getNumber("first");
    outputNums["secondNum"] = getNumber("second");
    switch (operation[0]) {
        case '+':
            outputNums["thirdNum"] = std::to_string(std::stof(outputNums.find("firstNum")->second)+std::stof(outputNums.find("secondNum")->second));
            stringToUse = names.find("+")->second;
            break;
        case '-':
            outputNums["thirdNum"] = std::to_string(std::stof(outputNums.find("firstNum")->second)-std::stof(outputNums.find("secondNum")->second));
            stringToUse = names.find("-")->second;
            break;
        case '*':
            outputNums["thirdNum"] = std::to_string(std::stof(outputNums.find("firstNum")->second)*std::stof(outputNums.find("secondNum")->second));
            stringToUse = names.find("*")->second;
            break;
        default:
            outputNums["thirdNum"] = std::to_string(std::stof(outputNums.find("firstNum")->second)/std::stof(outputNums.find("secondNum")->second));
            stringToUse = names.find("/")->second;
            break;
    }
    std::string printString = "The " + stringToUse + " of " + checkInt(outputNums.find("firstNum")->second) + operation + checkInt(outputNums.find("secondNum")->second) + " is " + checkInt(outputNums.find("thirdNum")->second);
    print(printString);
    delete fP;
    return 0;
}


// Whole command: g++ calculator.cpp -o calculator; ./calculator
