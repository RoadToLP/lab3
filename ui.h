//
// Created by Kurisu on 12/20/2020.
//
#ifndef LAB3_UI_H
#define LAB3_UI_H
#include "dBinarySignal.h"
#include "state.h"
#include <vector>
using namespace std;
namespace ui{
    void init();
    void init(const string& hellomsg);
    extern dBinarySignal bs;
    vector<string> getInput();
    int decide(const vector<string>& command);
    int decideWA(const vector<string>& command);
    int decideWOA(const vector<string>& command);
    void help();
    void finalize();
}
#endif