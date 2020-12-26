//
// Created by Kurisu on 12/22/2020.
//

#include "ui.h"
#include "tests.h"
#include <string>
#include <iostream>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

dBinarySignal ui::bs;

void ui::finalize() {
    cout << "Goodbye!" << endl;
}

void ui::help(){
    cout << "getRadius - get current radius of circle\n"
            "setRadius [r] - set current radius of circle\n"
            "getDistance [theta] - get distance from center of circle to point of evolvent on current angle THETA\n"
            "getPoint [theta] - get point of evolvent on current angle THETA\n"
            "getLength [theta] - get length of curve up to current angle THETA\n"
            "getCurvature [theta] - get curvature of evolvent on current angle THETA\n"
            "exit - exit application\n"
            "runTests - run google test set\n";

}


void ui::init(){
    cout << "Welcome to Evolvent testing UI!" << endl;
}
void ui::init(const string& hellomsg){
    cout << hellomsg << endl;
}
vector<string> ui::getInput(){
    cout << bs;
    if (!cin){
        cin.clear();
        cin.sync();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    string input;
    char* cinput = readline("> ");
    input = string(cinput);
    if (!input.empty())
        add_history(cinput);
    free(cinput);
    vector<string> tokens; //Well, we can use dynamicArray
    stringstream sinput(input);
    string part;
    while(getline(sinput, part, ' ')){
        tokens.push_back(part);
    }
    return tokens;
}
int ui::decide(const vector<string>& command){
    if (command.size() > 1) {
        return ui::decideWA(command);
    } else if (command.size() == 1){
        return ui::decideWOA(command);
    }
    return 0;
}
int ui::decideWA(const vector<string>& command){
    if (command[0] == "fill"){
        try {
            cin >> bs;
        } catch (const invalid_argument& e){
            cerr << e.what();
        }
    } else if (command[0] == "neg"){
        bs = !bs;
    } else if (command[0] == "multiply"){
        try {
            int multiplier;
            multiplier = stol(command[1]);
            bs *= multiplier;
        } catch (const out_of_range& e){
            cerr << e.what();
        }
    } else if (command[0] == "insert"){
        try {
            int when;
            unsigned short level;
            unsigned char length;
            when = stoi(command[1]);
            level = stoi(command[2]);
            length = stoi(command[3]);
            bs(when, level, length);
        } catch (const exception& e){
            cerr << e.what();
        }
    } else if (command[0] == "remove"){
        try{
            int when;
            unsigned int length;
            when = stoi(command[1]);
            length = stoi(command[2]);
            bs(when, length);
        } catch (const exception& e){
            cerr << e.what();
        }
    } else if (command[0] == "runTests"){
        runTests();
    }
    return 0;
}
int ui::decideWOA(const vector<string>& command){
    return 0;
}

