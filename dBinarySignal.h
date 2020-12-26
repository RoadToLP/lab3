//
// Created by Kurisu on 12/25/2020.
//

#ifndef LAB3_DBINARYSIGNAL_H
#define LAB3_DBINARYSIGNAL_H
#include <sstream>
#include <climits>
#include <numeric>
#include "state.h"
#include "util.h"
#define MAX_LENGTH 255
#define MAX_SIZE 200
using namespace std;
class dBinarySignal{
private:
    struct state* data;
    unsigned short size;
    void resize(int size);
public:
    dBinarySignal();
    dBinarySignal(const dBinarySignal& old);
    void flush();
    ~dBinarySignal();
    struct state getState(int index);
    void fill(stringstream& ss);
    [[nodiscard]] unsigned short getSize() const;
    explicit dBinarySignal(unsigned short level);
    explicit dBinarySignal(const string& data);
    friend ostream& operator<<(ostream& os, const dBinarySignal& bs);
    friend void operator>>(istream& is, dBinarySignal& bs);
    dBinarySignal& operator=(const dBinarySignal& rhs);
    dBinarySignal& operator!();
    dBinarySignal& operator+=(dBinarySignal rhs);
    void operator()(int when, unsigned short level, unsigned char length);
    dBinarySignal& operator*=(int count);
    void operator()(int when, int length);
};
#endif //LAB3_DBINARYSIGNAL_H
