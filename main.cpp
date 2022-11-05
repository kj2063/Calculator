#include "calculator.h"
#define MAX_STR_LENGTH 100

using namespace std;

int main(){
    char *formulaStr = new char[MAX_STR_LENGTH];

    cout << "Insert formula : ";
    cin.getline(formulaStr,MAX_STR_LENGTH,'\n');
    
    Calculate calculate(formulaStr);
    calculate.print();

    return 0;
}