#include <iostream>


using namespace std;

class Calculate {
    char *formularStr;

    void removeSpaceStr(char *initStr){
        int index = 0;

        for(int i=0; initStr[i]; i++){
            if(initStr[i] != ' '){
                initStr[index++] = initStr[i];
            }
        }

        initStr[index] = '\0';
        formularStr = initStr;
    }

public:
    Calculate(char initStr[]){
        removeSpaceStr(initStr);
    };

    ~Calculate(){
        cout << "class Removed" << endl;
    };

    void print(){
        cout << "Result : " << formularStr << endl;
    }
};