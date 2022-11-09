#include <iostream>
#include "stack.h"

using namespace std;

// => reinterpret_cast<void *>() 
// In c++, there is some issue(or diffrence to use) at knowing "char *" addr. so, using this to cast, you can know the address of this pointer pointing.
// ref at https://bigpel66.oopy.io/library/cpp/etc/5

class Calculate {
    char *infixStr;
    char *postfixStr;
    int transStackSize;
    int postfixStrSize;
    int calcStackSize;
    int result;

    void removeSpaceStr(char *initStr){
        int index = 0;
        
        for(int i=0; initStr[i]; i++){
            if(initStr[i] != ' '){
                if(isdigit(initStr[i]) == 0){
                    transStackSize += 1;
                    calcStackSize += 1;
                    postfixStrSize += 3;
                }
                else{
                    postfixStrSize += 1;
                }
                initStr[index++] = initStr[i];
            }
        }

        initStr[index] = '\0';
        infixStr = initStr;
        calcStackSize += 1;
    };

    void changeToPostfix(char *infix){
        Stack<char> stack(transStackSize);
        postfixStr = new char[postfixStrSize];
        int index = -1;

        while(*infix != '\0'){
            if(*infix == '('){
                stack.push(*infix);
                infix++;
            }
            else if (*infix == ')'){
                while(stack.getTop() != '('){
                    postfixStr[++index] = stack.pop();
                    postfixStr[++index] = ' ';
                }
                stack.pop();
                infix++;
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
        };
        while(!stack.isEmpty()){
            postfixStr[++index] = stack.pop();
            postfixStr[++index] = ' ';
        }
        
        postfixStr[index] = '\0';
        
    };

    int calc(char *postfix){
        Stack<int> stack(calcStackSize);

        for(int i = 0; postfix[i]; i++){
            if(postfix[i] != ' ' ){
                if(isdigit(postfix[i]) != 0){
                    int number = changeToInt(&postfix[i], &i);
    
                    stack.push(number);
                }
                else{
                    int num2 = stack.pop();
                    int num1 = stack.pop();
                    
                    int calcNum;

                    switch(postfix[i]){
                        case '+' : 
                            calcNum = num1+num2;
                            break;
                        case '-' :
                            calcNum = num1-num2;
                            break;
                        case '*' :
                            calcNum = num1*num2;
                            break;
                        case '/' :
                            calcNum = num1/num2;
                            break;
                    }

                    stack.push(calcNum);
                }
            }
        }

        return stack.getTop();
    };

    int changeToInt(char *num, int *index){
        char numArr[20];
        int i;

        for( i=0 ; num[i] != ' ' ; i++){
            numArr[i] = num[i];
            *index += 1;
        }

        numArr[i] = '\0';
    
        return stoi(numArr);
    }

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

    Calculate(char *initStr) : transStackSize{0}, calcStackSize{0}, postfixStrSize{0}{
        removeSpaceStr(initStr);
        changeToPostfix(infixStr);
        result = calc(postfixStr);
    };

    ~Calculate(){};

    void print(){
        cout << "Result : " << result << endl;
    }
};