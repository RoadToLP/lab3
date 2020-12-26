#include <iostream>
#include "ui.h"
int main(int argc, char* argv[]){
    ui::init();

    vector<string> command;
    int ex = 0;
    while(!ex){
        command = ui::getInput();
        ex = ui::decide(command);
    }
    ui::finalize();
}