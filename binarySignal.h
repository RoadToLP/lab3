//
// Created by Kurisu on 12/23/2020.
//

#ifndef LAB3_BINARYSIGNAL_H
#define LAB3_BINARYSIGNAL_H

#include <sstream>
#include <climits>
#include <numeric>
#include "state.h"
#include "util.h"
#define MAX_LENGTH 255
#define MAX_SIZE 200
using namespace std;
class binarySignal{
private:
    struct state data[MAX_SIZE];
    unsigned short size;
public:
    binarySignal();
    void flush();
    void fill(stringstream& ss);
    struct state getState(int index);
    [[nodiscard]] unsigned short getSize() const;
    explicit binarySignal(unsigned short level);
    explicit binarySignal(const string& data);
    friend ostream& operator<<(ostream& os, const binarySignal& bs);
    friend void operator>>(istream& is, binarySignal& bs);
    binarySignal& operator!();
    binarySignal& operator+=(binarySignal rhs);
    void operator()(int when, unsigned short level, unsigned char length);
    binarySignal& operator*=(int count);
    void operator()(int when, int length);
};

#endif //LAB3_BINARYSIGNAL_H
