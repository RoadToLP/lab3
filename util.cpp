//
// Created by Kurisu on 12/23/2020.
//
#include "util.h"
bool is_number(const std::string& s){
    return !s.empty() && find_if(s.begin(), s.end(), [](unsigned char c) {return !isdigit(c);}) == s.end();
}
