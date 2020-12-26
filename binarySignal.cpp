//
// Created by Kurisu on 12/23/2020.
//
#include "binarySignal.h"

binarySignal::binarySignal() {
    this->size = 0;
}

void binarySignal::flush(){
    for (int i = 0; i < this->size; i++){
        this->data[i].level = 0;
        this->data[i].length = 0;
    }
    this->size = 0;
}

void binarySignal::fill(stringstream& ss){
    string substr;
    int index = 0;
    this->flush();
    while (getline(ss, substr, ',')){
        if (index >= MAX_SIZE) throw invalid_argument("Too much data\n");
        int count = 0;
        for (char c: substr){
            if (c == '^') count++;
        }
        if (count > 1) {this->flush(); throw invalid_argument("Invalid format (too many ^ symbols in substring)\n");}
        if (count == 0) {this->flush(); throw invalid_argument("Invalid format (^ symbol not found in substring)\n");}
        stringstream partstream(substr);
        string part;
        getline(partstream, part, '^');
        if (is_number(part)) this->data[index].level = (stoi(part, nullptr, 10) >= USHRT_MAX) ? USHRT_MAX : stoi(part, nullptr, 10);
        else {this->flush(); throw invalid_argument("Invalid format (level is empty or not numeric)\n");}
        getline(partstream, part, '^');
        if (is_number(part)) this->data[index].length = (stoi(part, nullptr, 10) >= UCHAR_MAX) ? UCHAR_MAX : stoi(part, nullptr, 10);
        else {this->flush(); throw invalid_argument("Invalid format (length is empty or not numeric)\n");}
        index++;
    }
    this->size = index;
}

binarySignal::binarySignal(unsigned short level) {
    for (auto & i : this->data){
        i.length = MAX_LENGTH;
        i.level = level;
    }
    this->size = MAX_SIZE;
}

/*
 * Format be like
 * "Level^length,Level^length so on...
 */
binarySignal::binarySignal(const string& data) {
    this->size = 0;
    stringstream ss(data);
    this->fill(ss);
}

ostream& operator<<(ostream &os, const binarySignal& bs) {
    for (int i = 0; i < bs.size; i++){
        os << bs.data[i].level << " " << (int)bs.data[i].length << endl;
    }
    return os;
}




void operator>>(istream &is, binarySignal& bs) {
    string input;
    stringstream ss;
    if (getline(is, input)){
        ss << input;
    }
    bs.fill(ss);
}

binarySignal& binarySignal::operator!(){
    static binarySignal out;
    out.flush();
    int current = 0;
    for(int i = 0; i < this->size; i++){
        out(current, (this->data[i].level) ? 0 : 1, this->data[i].length);
        current += this->data[i].length;
    }
    *this = out;
    return *this;
}

binarySignal& binarySignal::operator+=(binarySignal rhs){
    static binarySignal out;
    out.flush();
    if (this->size + rhs.size > MAX_SIZE) throw out_of_range("Resulting binarySignal is too big");
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
void binarySignal::operator()(int when, unsigned short level, unsigned char length) {
    int index;
    int curlen = 0;
    for (index = 0; curlen < when; index++){
        if (index >= this->size) throw out_of_range("Out of range");
        curlen += this->data[index].length;
    }
    index--;
    if (curlen == 0){
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
        if (this->size + 2 >= MAX_SIZE) throw out_of_range("Out of range");
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
        if (this->size + 1 >= MAX_SIZE) throw out_of_range("Out of range");
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

binarySignal& binarySignal::operator*=(int count){
    static binarySignal out;
    if (this->size*count >= MAX_SIZE) throw out_of_range("Resulting binarySignal is too big");
    int curlen = 0;
    for (int i = 0; i < this->size*count; i++){
        out(curlen, this->data[i%this->size].level, this->data[i%this->size].length);
        curlen += this->data[i%this->size].length;
    }
    *this = out;
    return *this;
}

void binarySignal::operator()(int when, int length) {
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
    for (int j = this->size; j < MAX_SIZE; j++){
        this->data[j].level = 0;
        this->data[j].length = 0;
    }
}

unsigned short binarySignal::getSize() const {
    return this->size;
}

struct state binarySignal::getState(int index) {
    if (index >= this->size) throw out_of_range("Out of range");
    return this->data[index];

}

