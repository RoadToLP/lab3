//
//
// Created by Kurisu on 12/23/2020.
//
#include <iostream>
#include "dBinarySignal.h"

dBinarySignal::dBinarySignal() {
    this->data = new struct state[0];
    this->size = 0;
}

void dBinarySignal::flush(){
    delete[] this->data;
    this->data = new struct state[0];
    this->size = 0;
}

void dBinarySignal::fill(stringstream& ss){
    string substr;
    int index = 0;
    this->flush();
    while (getline(ss, substr, ',')){
        int count = 0;
        for (char c: substr){
            if (c == '^') count++;
        }
        if (count > 1) {this->flush(); throw invalid_argument("Invalid format (too many ^ symbols in substring)\n");}
        if (count == 0) {this->flush(); throw invalid_argument("Invalid format (^ symbol not found in substring)\n");}
        stringstream partstream(substr);
        string part;
        getline(partstream, part, '^');
        this->resize(index+1);
        this->size = index+1;
        if (is_number(part)) this->data[index].level = (stoi(part, nullptr, 10) >= USHRT_MAX) ? USHRT_MAX : stoi(part, nullptr, 10);
        else {this->flush(); throw invalid_argument("Invalid format (level is empty or not numeric)\n");}
        getline(partstream, part, '^');
        if (is_number(part)) this->data[index].length = (stoi(part, nullptr, 10) >= UCHAR_MAX) ? UCHAR_MAX : stoi(part, nullptr, 10);
        else {this->flush(); throw invalid_argument("Invalid format (length is empty or not numeric)\n");}
        index++;
    }
}

dBinarySignal::dBinarySignal(unsigned short level) {
    this->data = new struct state[MAX_SIZE];
    this->size = MAX_SIZE;
    for (int i = 0;  i < this->size; i++){
        this->data[i].length = MAX_LENGTH;
        this->data[i].level = level;
    }
}

/*
 * Format be like
 * "Level^length,Level^length so on...
 */
dBinarySignal::dBinarySignal(const string& data) {
    this->data = new struct state[0];
    this->size = 0;
    stringstream ss(data);
    this->fill(ss);
}

ostream& operator<<(ostream &os, const dBinarySignal& bs) {
    for (int i = 0; i < bs.size; i++){
        os << bs.data[i].level << " " << (int)bs.data[i].length << endl;
    }
    return os;
}




void operator>>(istream &is, dBinarySignal& bs) {
    string input;
    stringstream ss;
    if (getline(is, input)){
        ss << input;
    }
    bs.fill(ss);
}

dBinarySignal& dBinarySignal::operator!(){
    static dBinarySignal out;
    out.flush();
    int current = 0;
    for(int i = 0; i < this->size; i++){
        out(current, (this->data[i].level) ? 0 : 1, this->data[i].length);
        current += this->data[i].length;
    }
    *this = out;
    return *this;
}

dBinarySignal& dBinarySignal::operator+=(dBinarySignal rhs){
    dBinarySignal out;
    out.flush();
    this->resize(this->size + rhs.size);
    int curlen = 0;
    for (int i = 0; i < this->size; i++){
        out(curlen, this->data[i].level, this->data[i].length);
        curlen += this->data[i].length;
    }
    for (int i = 0; i < rhs.size; i++){
        out(curlen, rhs.data[i].level, rhs.data[i].length);
        curlen += rhs.data[i].length;
    }
    *this = out;
    return *this;
}
void dBinarySignal::operator()(int when, unsigned short level, unsigned char length) {
    int index;
    int curlen = 0;
    for (index = 0; curlen < when; index++){
        if (index >= this->size) throw out_of_range("Out of range");
        curlen += this->data[index].length;
    }
    index--;
    if (curlen == 0){
        this->resize(this->size+1);
        for (int i = this->size-1; i >= 0; i--){
            this->data[i+1] = this->data[i];
        }
        this->data[0].length = length;
        this->data[0].level = level;
        this->size++;
        return;
    }
    int delta = curlen - when;
    if (delta){
        this->resize(this->size + 2);
        this->data[index].length -= delta;
        for (int i = this->size-1; i > index; i--){
            this->data[i+2] = this->data[i];
        }
        this->data[index+2].length = delta;
        this->data[index+2].level = this->data[index].level;
        this->data[index+1].level = level;
        this->data[index+1].length = length;
        this->size+=2;
    } else {
        this->resize(this->size+1);
        if (index == this->size-1){
            this->data[index+1].length = length;
            this->data[index+1].level = level;
        } else {
            for (int i = this->size-1; i > index; i--){
                this->data[i+1] = this->data[i];
            }
            this->data[index+1].length = length;
            this->data[index+1].level = level;
        }
        this->size++;
    }
}

dBinarySignal& dBinarySignal::operator*=(int count){
    dBinarySignal out;
    int curlen = 0;
    for (int i = 0; i < this->size*count; i++){
        out(curlen, this->data[i%this->size].level, this->data[i%this->size].length);
        curlen += this->data[i%this->size].length;
    }
    this->resize(this->size*count);
    for (int i = 0; i < this->size*count; i++){
        this->data[i] = out.data[i];
    }
    this->size = out.size;
    return *this;
}

void dBinarySignal::operator()(int when, int length) {
    int index;
    int curlen = 0;
    for (index = 0; curlen < when; index++){
        curlen += this->data[index].length;
        if (index >= this->size) throw out_of_range("Out of range");
    }
    int preSum = 0;
    for (int i = index; preSum < length; i++){
        preSum += this->data[i].length;
        if (i > this->size) throw out_of_range("Out of range");
    }
    index--;
    int delta = curlen - when;
    if (delta){
        this->data[index].length -= (length <= delta) ? length : delta;
        length -= delta;
        if (length <= 0) return;
    }
    int i;
    for (i = 1; length > 0; i++){
        length -= this->data[i+index].length;
        this->data[index+i].length = 0;
    }
    i-=1;
    this->data[index+i].length -= length;
    for (int j = index+1; j+i+((length) ? -1 : 0)+((index==-1) ? 1 : 0) <= this->size; j++){
        this->data[j] = this->data[j+i+((length) ? -1 : 0)];
    }
    this->size -= i+((length)?-1:0);
    this->resize(this->size);
}

unsigned short dBinarySignal::getSize() const {
    return this->size;
}

dBinarySignal::dBinarySignal(const dBinarySignal &old) {
    this->data = new struct state[old.size];
    for(int i = 0; i < old.size; i++){
        this->data[i] = old.data[i];
    }
    this->size = old.size;
}

void dBinarySignal::resize(int nsize) {
    auto* old = new struct state[this->size];
    for (int i = 0;  i < this->size; i++){
        old[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new struct state[nsize];
    for (int i = 0; i < this->size; i++){
        this->data[i] = old[i];
    }
    delete[] old;
}

dBinarySignal &dBinarySignal::operator=(const dBinarySignal& rhs){
    this->resize(rhs.size);
    for(int i = 0; i < rhs.size; i++){
        this->data[i] = rhs.data[i];
    }
    this->size = rhs.size;
    return *this;
}

struct state dBinarySignal::getState(int index) {
    if (index >= this->size) throw out_of_range("Out of range");
    return this->data[index];
}

dBinarySignal::~dBinarySignal() {
    delete this->data;
    this->size = 0;
}

// Created by Kurisu on 12/25/2020.
//

