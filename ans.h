#ifndef ans_h
#define ans_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

typedef struct{
    int symbol;
    int prev_state;
} DANS;

DANS decodeRangeANS(int cumuls[], int M, int fq[], int state, int c_fun[]);
void decode(int & final_state, int fq[], int cumuls[], std::vector<short int> & bitstream, int num_symbols, int c_fun[], std::vector<int> & ret);

int encodeRangeANS(int code, int previous_state, int cumuls[], int M, int fq[]);
void encode(int symbols[], int fq[], int cumuls[], int & state, int num_symbols, std::vector<short int> &  bitstream);

#endif /* ans_h */
