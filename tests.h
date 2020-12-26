//
// Created by Kurisu on 12/23/2020.
//

#ifndef LAB3_TESTS_H
#define LAB3_TESTS_H
#include <iostream>
#include <gtest/gtest.h>
#include "dBinarySignal.h"
#include "binarySignal.h"
#include <random>
#include <time.h>
TEST(dBinarySignal, Constructor){
    dBinarySignal bs;
    ASSERT_THROW(bs.getState(0), out_of_range);
    ASSERT_EQ(bs.getSize(), 0);
}

TEST(dBinarySignal, ConstructorAll){
    dBinarySignal bs(0);
    for (int i = 0; i < 200; i++){
        ASSERT_EQ(bs.getState(i).level, 0);
        ASSERT_EQ(bs.getState(i).length, 255);
    }
}

TEST(dBinarySignal, CopyConstructor){
    srand(time(nullptr));
    dBinarySignal bs;
    int curlen = 0;
    int l;
    for (int i = 0; i < 100; i++){
        l = random()%256;
        bs(curlen, random()%2, l);
        curlen += l;
    }
    dBinarySignal bs2(bs);
    ASSERT_EQ(bs.getSize(), bs2.getSize());
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(bs.getState(i).length, bs2.getState(i).length);
        ASSERT_EQ(bs.getState(i).level, bs2.getState(i).level);
    }
}

TEST(dBinarySignal, Fill){
    // >> operator works through fill(), so no need to test it. So if we use fill constructor, fill and >> will be tested simultaneously
    string toFill = "1^142,0^43,1^207,1^146,1^155,0^0,1^179,0^111,1^213,1^116,0^77,0^97,1^149,1^120,1^52,0^35,0^66,0^105,1^56,0^227,1^173,1^168,0^26,1^226,0^60,1^92,0^100,0^159,0^110,0^204,0^179,1^113,0^171,0^155,1^17,0^132,0^187,1^36,0^145,0^228,1^175,1^23,1^151,1^16,0^204,1^233,0^196,0^192,0^128,0^98,0^145,0^191,0^185,0^126,1^188,1^143,0^231,0^253,0^226,1^142,0^119,0^190,1^93,0^80,0^233,1^227,1^216,1^199,1^14,0^107,1^108,1^244,0^56,1^31,1^232,0^80,1^207,0^243,0^199,0^211,1^251,0^49,0^229,1^92,0^249,0^73,0^112,1^116,1^213,0^138,0^150,0^119,0^174,0^236,0^215,1^126,0^157,0^106,0^117,1^252";
    unsigned short levels[] = {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1};
    unsigned char lengths[] = {142, 43, 207, 146, 155, 0, 179, 111, 213, 116, 77, 97, 149, 120, 52, 35, 66, 105, 56, 227, 173, 168, 26, 226, 60, 92, 100, 159, 110, 204, 179, 113, 171, 155, 17, 132, 187, 36, 145, 228, 175, 23, 151, 16, 204, 233, 196, 192, 128, 98, 145, 191, 185, 126, 188, 143, 231, 253, 226, 142, 119, 190, 93, 80, 233, 227, 216, 199, 14, 107, 108, 244, 56, 31, 232, 80, 207, 243, 199, 211, 251, 49, 229, 92, 249, 73, 112, 116, 213, 138, 150, 119, 174, 236, 215, 126, 157, 106, 117, 252};
    dBinarySignal bs(toFill);
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
    ASSERT_EQ(bs.getSize(), 100);
}

TEST(dBinarySignal, equalOperator){
    string toFill = "1^142,0^43,1^207,1^146,1^155,0^0,1^179,0^111,1^213,1^116,0^77,0^97,1^149,1^120,1^52,0^35,0^66,0^105,1^56,0^227,1^173,1^168,0^26,1^226,0^60,1^92,0^100,0^159,0^110,0^204,0^179,1^113,0^171,0^155,1^17,0^132,0^187,1^36,0^145,0^228,1^175,1^23,1^151,1^16,0^204,1^233,0^196,0^192,0^128,0^98,0^145,0^191,0^185,0^126,1^188,1^143,0^231,0^253,0^226,1^142,0^119,0^190,1^93,0^80,0^233,1^227,1^216,1^199,1^14,0^107,1^108,1^244,0^56,1^31,1^232,0^80,1^207,0^243,0^199,0^211,1^251,0^49,0^229,1^92,0^249,0^73,0^112,1^116,1^213,0^138,0^150,0^119,0^174,0^236,0^215,1^126,0^157,0^106,0^117,1^252";
    dBinarySignal bs(toFill);
    dBinarySignal bs2;
    bs2 = bs;
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(bs.getState(i).level, bs2.getState(i).level);
        ASSERT_EQ(bs.getState(i).length, bs2.getState(i).length);
    }
    ASSERT_EQ(bs2.getSize(), 100);
}

TEST(dBinarySignal, ostreamOperator){
    stringstream os;
    string toFill = "1^21,1^231,1^194,1^154,1^186,1^232,0^252,0^26,1^84,1^43,0^101,0^7,0^235,0^230,1^191,1^111,0^177,1^31,1^172,1^229,0^13,0^173,1^124,0^192,1^18,1^240,0^121,1^209,1^232,1^139,1^35,1^129,1^51,0^192,1^207,1^1,1^184,0^153,1^34,0^17,0^30,1^0,1^73,1^19,1^208,1^162,0^115,0^105,1^113,1^46,1^144,0^213,0^182,0^173,0^219,1^15,1^232,1^120,0^83,1^21,0^110,1^96,0^12,1^61,0^39,1^166,0^106,1^184,1^228,1^217,0^155,1^239,1^117,1^39,1^146,1^176,0^166,0^54,0^50,1^19,0^216,1^82,0^238,1^126,0^154,1^67,0^22,0^255,0^60,1^167,0^222,1^13,0^92,0^234,0^205,0^129,0^215,1^40,0^166,0^98";
    string ostoeq = "1 21\n1 231\n1 194\n1 154\n1 186\n1 232\n0 252\n0 26\n1 84\n1 43\n0 101\n0 7\n0 235\n0 230\n1 191\n1 111\n0 177\n1 31\n1 172\n1 229\n0 13\n0 173\n1 124\n0 192\n1 18\n1 240\n0 121\n1 209\n1 232\n1 139\n1 35\n1 129\n1 51\n0 192\n1 207\n1 1\n1 184\n0 153\n1 34\n0 17\n0 30\n1 0\n1 73\n1 19\n1 208\n1 162\n0 115\n0 105\n1 113\n1 46\n1 144\n0 213\n0 182\n0 173\n0 219\n1 15\n1 232\n1 120\n0 83\n1 21\n0 110\n1 96\n0 12\n1 61\n0 39\n1 166\n0 106\n1 184\n1 228\n1 217\n0 155\n1 239\n1 117\n1 39\n1 146\n1 176\n0 166\n0 54\n0 50\n1 19\n0 216\n1 82\n0 238\n1 126\n0 154\n1 67\n0 22\n0 255\n0 60\n1 167\n0 222\n1 13\n0 92\n0 234\n0 205\n0 129\n0 215\n1 40\n0 166\n0 98\n";
    dBinarySignal bs(toFill);
    os << bs;
    ASSERT_EQ(os.str(), ostoeq);
}

TEST(dBinarySignal, negOperator){
    string toFill = "1^142,0^43,1^207,1^146,1^155,1^179,0^111,1^213,1^116,0^77,0^97,1^149,1^120,1^52,0^35,0^66,0^105,1^56,0^227,1^173,1^168,0^26,1^226,0^60,1^92,0^100,0^159,0^110,0^204,0^179,1^113,0^171,0^155,1^17,0^132,0^187,1^36,0^145,0^228,1^175,1^23,1^151,1^16,0^204,1^233,0^196,0^192,0^128,0^98,0^145,0^191,0^185,0^126,1^188,1^143,0^231,0^253,0^226,1^142,0^119,0^190,1^93,0^80,0^233,1^227,1^216,1^199,1^14,0^107,1^108,1^244,0^56,1^31,1^232,0^80,1^207,0^243,0^199,0^211,1^251,0^49,0^229,1^92,0^249,0^73,0^112,1^116,1^213,0^138,0^150,0^119,0^174,0^236,0^215,1^126,0^157,0^106,0^117,1^252";
    unsigned short levels[] = {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1};
    unsigned char lengths[] = {142, 43, 207, 146, 155, 179, 111, 213, 116, 77, 97, 149, 120, 52, 35, 66, 105, 56, 227, 173, 168, 26, 226, 60, 92, 100, 159, 110, 204, 179, 113, 171, 155, 17, 132, 187, 36, 145, 228, 175, 23, 151, 16, 204, 233, 196, 192, 128, 98, 145, 191, 185, 126, 188, 143, 231, 253, 226, 142, 119, 190, 93, 80, 233, 227, 216, 199, 14, 107, 108, 244, 56, 31, 232, 80, 207, 243, 199, 211, 251, 49, 229, 92, 249, 73, 112, 116, 213, 138, 150, 119, 174, 236, 215, 126, 157, 106, 117, 252};
    dBinarySignal bs(toFill);
    !bs;
    for (int i = 0; i < 99; i++){
        ASSERT_EQ(bs.getState(i).level, (levels[i]) ? 0 : 1);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
    ASSERT_EQ(bs.getSize(), 99);
}

TEST(dBinarySignal, appendOperator){
    string toFill1 = "1^123,0^31";
    string toFill2 = "0^21,0^34";
    unsigned short levels[] = {1, 0, 0, 0};
    unsigned char lengths[] = {123, 31, 21, 34};
    dBinarySignal bs1(toFill1);
    dBinarySignal bs2(toFill2);
    bs1 += bs2;
    for (int i = 0; i < 4; i++){
        ASSERT_EQ(bs1.getState(i).level, levels[i]);
        ASSERT_EQ(bs1.getState(i).length, lengths[i]);
    }
    ASSERT_EQ(bs1.getSize(), 4);
}

TEST(dBinarySignal, multiplyOperator){
    string toFill = "1^123,0^31";
    unsigned short levels[] = {1, 0, 1, 0, 1, 0, 1, 0};
    unsigned char lengths[] = {123, 31, 123, 31, 123, 31, 123, 31};
    dBinarySignal bs(toFill);
    bs *= 4;
    ASSERT_EQ(bs.getSize(), 8);
    for (int i = 0; i < 8; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
}

TEST(dBinarySignal, insertOperator){
    dBinarySignal bs;
    bs(0, 1, 20);
    bs(15, 0, 5);
    bs(25, 1, 15);
    unsigned short levels[] = {1, 0, 1, 1};
    unsigned char lengths[] = {15, 5, 5, 15};
    ASSERT_EQ(bs.getSize(), 4);
    for (int i = 0; i < 4; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }

}

TEST(dBinarySignal, removeOperator){
    dBinarySignal bs;
    bs(0, 1, 20);
    bs(15, 0, 5);
    bs(25, 1, 15);
    bs(3, 5);
    bs(5, 10);
    unsigned short levels[] = {1, 1, 1};
    unsigned char lengths[] = {5, 5, 15};
    ASSERT_EQ(bs.getSize(), 3);
    for (int i = 0; i < 3; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
}

TEST(binarySignal, Constructor){
    binarySignal bs;
    ASSERT_THROW(bs.getState(0), out_of_range);
    ASSERT_EQ(bs.getSize(), 0);
}

TEST(binarySignal, ConstructorAll){
    binarySignal bs(0);
    for (int i = 0; i < 200; i++){
        ASSERT_EQ(bs.getState(i).level, 0);
        ASSERT_EQ(bs.getState(i).length, 255);
    }
}

TEST(binarySignal, CopyConstructor){
    srand(time(nullptr));
    binarySignal bs;
    int curlen = 0;
    int l;
    for (int i = 0; i < 100; i++){
        l = random()%256;
        bs(curlen, random()%2, l);
        curlen += l;
    }
    binarySignal bs2(bs);
    ASSERT_EQ(bs.getSize(), bs2.getSize());
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(bs.getState(i).length, bs2.getState(i).length);
        ASSERT_EQ(bs.getState(i).level, bs2.getState(i).level);
    }
}

TEST(binarySignal, Fill){
    // >> operator works through fill(), so no need to test it. So if we use fill constructor, fill and >> will be tested simultaneously
    string toFill = "1^142,0^43,1^207,1^146,1^155,0^0,1^179,0^111,1^213,1^116,0^77,0^97,1^149,1^120,1^52,0^35,0^66,0^105,1^56,0^227,1^173,1^168,0^26,1^226,0^60,1^92,0^100,0^159,0^110,0^204,0^179,1^113,0^171,0^155,1^17,0^132,0^187,1^36,0^145,0^228,1^175,1^23,1^151,1^16,0^204,1^233,0^196,0^192,0^128,0^98,0^145,0^191,0^185,0^126,1^188,1^143,0^231,0^253,0^226,1^142,0^119,0^190,1^93,0^80,0^233,1^227,1^216,1^199,1^14,0^107,1^108,1^244,0^56,1^31,1^232,0^80,1^207,0^243,0^199,0^211,1^251,0^49,0^229,1^92,0^249,0^73,0^112,1^116,1^213,0^138,0^150,0^119,0^174,0^236,0^215,1^126,0^157,0^106,0^117,1^252";
    unsigned short levels[] = {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1};
    unsigned char lengths[] = {142, 43, 207, 146, 155, 0, 179, 111, 213, 116, 77, 97, 149, 120, 52, 35, 66, 105, 56, 227, 173, 168, 26, 226, 60, 92, 100, 159, 110, 204, 179, 113, 171, 155, 17, 132, 187, 36, 145, 228, 175, 23, 151, 16, 204, 233, 196, 192, 128, 98, 145, 191, 185, 126, 188, 143, 231, 253, 226, 142, 119, 190, 93, 80, 233, 227, 216, 199, 14, 107, 108, 244, 56, 31, 232, 80, 207, 243, 199, 211, 251, 49, 229, 92, 249, 73, 112, 116, 213, 138, 150, 119, 174, 236, 215, 126, 157, 106, 117, 252};
    binarySignal bs(toFill);
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
    ASSERT_EQ(bs.getSize(), 100);
}

TEST(binarySignal, ostreamOperator){
    stringstream os;
    string toFill = "1^21,1^231,1^194,1^154,1^186,1^232,0^252,0^26,1^84,1^43,0^101,0^7,0^235,0^230,1^191,1^111,0^177,1^31,1^172,1^229,0^13,0^173,1^124,0^192,1^18,1^240,0^121,1^209,1^232,1^139,1^35,1^129,1^51,0^192,1^207,1^1,1^184,0^153,1^34,0^17,0^30,1^0,1^73,1^19,1^208,1^162,0^115,0^105,1^113,1^46,1^144,0^213,0^182,0^173,0^219,1^15,1^232,1^120,0^83,1^21,0^110,1^96,0^12,1^61,0^39,1^166,0^106,1^184,1^228,1^217,0^155,1^239,1^117,1^39,1^146,1^176,0^166,0^54,0^50,1^19,0^216,1^82,0^238,1^126,0^154,1^67,0^22,0^255,0^60,1^167,0^222,1^13,0^92,0^234,0^205,0^129,0^215,1^40,0^166,0^98";
    string ostoeq = "1 21\n1 231\n1 194\n1 154\n1 186\n1 232\n0 252\n0 26\n1 84\n1 43\n0 101\n0 7\n0 235\n0 230\n1 191\n1 111\n0 177\n1 31\n1 172\n1 229\n0 13\n0 173\n1 124\n0 192\n1 18\n1 240\n0 121\n1 209\n1 232\n1 139\n1 35\n1 129\n1 51\n0 192\n1 207\n1 1\n1 184\n0 153\n1 34\n0 17\n0 30\n1 0\n1 73\n1 19\n1 208\n1 162\n0 115\n0 105\n1 113\n1 46\n1 144\n0 213\n0 182\n0 173\n0 219\n1 15\n1 232\n1 120\n0 83\n1 21\n0 110\n1 96\n0 12\n1 61\n0 39\n1 166\n0 106\n1 184\n1 228\n1 217\n0 155\n1 239\n1 117\n1 39\n1 146\n1 176\n0 166\n0 54\n0 50\n1 19\n0 216\n1 82\n0 238\n1 126\n0 154\n1 67\n0 22\n0 255\n0 60\n1 167\n0 222\n1 13\n0 92\n0 234\n0 205\n0 129\n0 215\n1 40\n0 166\n0 98\n";
    binarySignal bs(toFill);
    os << bs;
    ASSERT_EQ(os.str(), ostoeq);
}

TEST(binarySignal, negOperator){
    string toFill = "1^142,0^43,1^207,1^146,1^155,1^179,0^111,1^213,1^116,0^77,0^97,1^149,1^120,1^52,0^35,0^66,0^105,1^56,0^227,1^173,1^168,0^26,1^226,0^60,1^92,0^100,0^159,0^110,0^204,0^179,1^113,0^171,0^155,1^17,0^132,0^187,1^36,0^145,0^228,1^175,1^23,1^151,1^16,0^204,1^233,0^196,0^192,0^128,0^98,0^145,0^191,0^185,0^126,1^188,1^143,0^231,0^253,0^226,1^142,0^119,0^190,1^93,0^80,0^233,1^227,1^216,1^199,1^14,0^107,1^108,1^244,0^56,1^31,1^232,0^80,1^207,0^243,0^199,0^211,1^251,0^49,0^229,1^92,0^249,0^73,0^112,1^116,1^213,0^138,0^150,0^119,0^174,0^236,0^215,1^126,0^157,0^106,0^117,1^252";
    unsigned short levels[] = {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1};
    unsigned char lengths[] = {142, 43, 207, 146, 155, 179, 111, 213, 116, 77, 97, 149, 120, 52, 35, 66, 105, 56, 227, 173, 168, 26, 226, 60, 92, 100, 159, 110, 204, 179, 113, 171, 155, 17, 132, 187, 36, 145, 228, 175, 23, 151, 16, 204, 233, 196, 192, 128, 98, 145, 191, 185, 126, 188, 143, 231, 253, 226, 142, 119, 190, 93, 80, 233, 227, 216, 199, 14, 107, 108, 244, 56, 31, 232, 80, 207, 243, 199, 211, 251, 49, 229, 92, 249, 73, 112, 116, 213, 138, 150, 119, 174, 236, 215, 126, 157, 106, 117, 252};
    binarySignal bs(toFill);
    !bs;
    for (int i = 0; i < 99; i++){
        ASSERT_EQ(bs.getState(i).level, (levels[i]) ? 0 : 1);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
    ASSERT_EQ(bs.getSize(), 99);
}

TEST(binarySignal, appendOperator){
    string toFill1 = "1^123,0^31";
    string toFill2 = "0^21,0^34";
    unsigned short levels[] = {1, 0, 0, 0};
    unsigned char lengths[] = {123, 31, 21, 34};
    binarySignal bs1(toFill1);
    binarySignal bs2(toFill2);
    bs1 += bs2;
    for (int i = 0; i < 4; i++){
        ASSERT_EQ(bs1.getState(i).level, levels[i]);
        ASSERT_EQ(bs1.getState(i).length, lengths[i]);
    }
    ASSERT_EQ(bs1.getSize(), 4);
}

TEST(binarySignal, multiplyOperator){
    string toFill = "1^123,0^31";
    unsigned short levels[] = {1, 0, 1, 0, 1, 0, 1, 0};
    unsigned char lengths[] = {123, 31, 123, 31, 123, 31, 123, 31};
    binarySignal bs(toFill);
    bs *= 4;
    ASSERT_EQ(bs.getSize(), 8);
    for (int i = 0; i < 8; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
}

TEST(binarySignal, insertOperator){
    binarySignal bs;
    bs(0, 1, 20);
    bs(15, 0, 5);
    bs(25, 1, 15);
    unsigned short levels[] = {1, 0, 1, 1};
    unsigned char lengths[] = {15, 5, 5, 15};
    ASSERT_EQ(bs.getSize(), 4);
    for (int i = 0; i < 4; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }

}

TEST(binarySignal, removeOperator){
    binarySignal bs;
    bs(0, 1, 20);
    bs(15, 0, 5);
    bs(25, 1, 15);
    bs(3, 5);
    bs(5, 10);
    unsigned short levels[] = {1, 1, 1};
    unsigned char lengths[] = {5, 5, 15};
    ASSERT_EQ(bs.getSize(), 3);
    for (int i = 0; i < 3; i++){
        ASSERT_EQ(bs.getState(i).level, levels[i]);
        ASSERT_EQ(bs.getState(i).length, lengths[i]);
    }
}
int runTests(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
#endif //LAB3_TESTS_H
