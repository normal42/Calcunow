#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//calc class is used to store variables ascii characters
//keeps track of variables being assigned int value

class calc{
    protected:
        unsigned char val;
        bool used;

    public:
        //No argument constructor
        //Class will be inserted 26 times into table
        calc() {
            val = 0;
            //Check if val a-z are set.
            used = false;
        }
    
        bool get_used () {return used; }
    
        void set_val (int a) {
            val = a;
            used = true;
        }
    
        unsigned char get_val () {
            unsigned char temp = val;
            //val increments. If 0 it has wrapped around, throw error
            val++;
            if (val == 0) throw runtime_error("Bad!");
            return temp;
        }
};

//vector stores pointers to 26 calc class objects
vector<calc*> table;

void set_value(char var, int val) {
    int temp = var - 'a';
    //Check if value already set
    //If value is is outside 255 ascii characters, throw an error
    if(table.at(temp)->get_used() || val < 0 || val > 255) throw runtime_error("Bad!");
    table.at(temp)->set_val(val);
};

unsigned char get_val(string value) {
    if(isdigit(value[0])) {
        return stoi(value);
    } else {
        unsigned char placeHolder = value[0]- 'a';
        //check if value has not been set. If not set throw error
        if(!table.at(placeHolder)->get_used()) throw runtime_error("Bad!");
        return table.at(placeHolder)->get_val();
    }
};

int math(vector<string> input) {
    int counter = 1;
    //counter will be used to incremement he variables
    int value= get_val(input.at(0));
//value is equal to the value grabbed from user's input
    while(counter < (int) input.size()) {
        char operand = input.at(counter).at(0);
        counter++;
//this is incrementing the input by one everytime it's used
        unsigned char second_var = get_val(input.at(counter));
// creating a second variable and grabbing the input then incrementing it through counter
        counter++;
//these are just operand functions that executes as needed
        if (operand == '+') {
            value = value + second_var;
        }
        if (operand == '-') {
            value = value - second_var;
        }
        if (operand == '*') {
            value = value * second_var;
        }
        if (operand == '/') {
            //If attempting to divide by 0, throw error
            if(second_var == 0) throw runtime_error("Bad!");
            value = value / second_var;
        }
        if (operand == '%') {
            value = value % second_var;
        }
        if (operand == '^') {
            //0 to the power of 0, or variable to the power of 0, throw error
            if(value == 0 || second_var == 0)
                throw runtime_error("Invalid Input!");
            else value = pow(value,second_var);
        }
    }
    return value;
}
