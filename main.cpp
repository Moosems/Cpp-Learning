#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

bool firstPrint = true, *fP;

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

int main(){
    srand(time(0));
    for (int i = 0; i<100; i++){
        print(std::to_string((rand() % 6) + 1));
    }
    return 0;
}
