#include <iostream>
#include "stack.h"
#define MAX_STR_LENGTH 100

using namespace std;

// => reinterpret_cast<void *>() 
// In c++, there is some issue(or diffrence to use) at knowing "char *" addr. so, using this to cast, you can know the address of this pointer poting.
// ref at https://bigpel66.oopy.io/library/cpp/etc/5

class Calculate {
    char *infixStr;
    char *postfixStr;
    int stackSize;
    int postfixStrSize;

    void removeSpaceStr(char *initStr){
        int index = 0;
        
        for(int i=0; initStr[i]; i++){
            if(initStr[i] != ' '){
                if(isdigit(initStr[i]) == 0){
                    stackSize += 1;
                    postfixStrSize += 3;
                }
                initStr[index++] = initStr[i];
                postfixStrSize += 1;
            }
        }

        initStr[index] = '\0';
        infixStr = initStr;
        postfixStrSize += 2;
    };

    void changeToPostfix(char *infix){
        cout << "infix : " << infix << endl;
        cout << "stackSize : " << stackSize << endl;
        cout << "postfixStrSize : " << postfixStrSize << endl;
        Stack<char> stack(stackSize);
        postfixStr = new char[postfixStrSize];
        int index = -1;

        while(*infix != '\0'){
            if(*infix == '('){
                stack.push(*infix);
                infix++;
            }
            else if (*infix == ')'){
                while(*infix != '('){
                    postfixStr[++index] = stack.pop();
                    postfixStr[++index] = ' ';
                    infix++;
                }
            }
            else if(*infix == '+' || *infix == '-' || *infix == '/' || *infix == '*'){
                if(!stack.isEmpty() && priority(stack.getTop()) >= priority(*infix)){
                    while(priority(stack.getTop()) >= priority(*infix)){
                        postfixStr[++index] = stack.pop();
                        postfixStr[++index] = ' ';
                    }
                    stack.push(*infix);
                    infix++;
                }
                else{
                    stack.push(*infix);
                    infix++;
                }
            }
            else{
                while(*infix >= '0' && *infix <= '9'){
                    postfixStr[++index] = *infix;
                    infix++;
                }
                postfixStr[++index] = ' ';
            }
            cout << "stack => " << stack.getData() << endl;
        };
        while(!stack.isEmpty()){
            postfixStr[++index] = stack.pop();
            postfixStr[++index] = ' ';
            cout << "stack end => " << stack.getData() << endl;
        }

        postfixStr[index] = '\0';
        cout << "printPostFix => " << postfixStr << endl;
    };

    int priority(char operatorParam){
        switch(operatorParam){
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            default :
                return -1;
        };
    };

public:

    Calculate(char *initStr){
        stackSize = 0;
        postfixStrSize = 0;
        removeSpaceStr(initStr);
        changeToPostfix(infixStr);
    };

    ~Calculate(){
        cout << "class Removed" << endl;
    };

    void print(){
        cout << "Result : " << postfixStr << endl;
    }
};