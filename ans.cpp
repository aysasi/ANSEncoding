#include "ans.h"


int encodeRangeANS(int symbol, int previous_state, int cumuls[], int M, int fq[]) {
    int s_count = fq[symbol];
    int p = (previous_state / s_count);
    int next_state = p * M + cumuls[symbol] + (previous_state % s_count);
    return next_state;
}

void encode(int symbols[], int fq[], int cumuls[], int & state, int num_symbols, std::vector<short int> &  bitstream) {
    for (int i = 0; i < num_symbols; i++) {
        while (state >= 2 * fq[symbols[i]]) {
            bitstream.push_back((state % 2));
            state = state >> 1; //state = state/2
        }
        state = encodeRangeANS(symbols[i], state, cumuls, num_symbols, fq);
    }
}

DANS decodeRangeANS(int cumuls[], int M, int fq[], int state, int decode_arr []) {
    int slot = state % M;
    
    int st = decode_arr[slot];
    int previous_state = (state / M) * fq[st] + slot - cumuls[st];
    return { st, previous_state};
}

void decode(int & final_state, int fq[], int cumuls[], std::vector<short int> & bitstream, int num_symbols, int decode_arr[], std::vector<int> & ret) {
    
    for(int i = 0; i < num_symbols; i++) {
        DANS aux = decodeRangeANS(cumuls, num_symbols, fq, final_state, decode_arr);
        final_state = aux.prev_state;
        ret.push_back(aux.symbol);
        while (final_state < num_symbols) {
            int p = bitstream[bitstream.size()-1];
            bitstream.pop_back();
            final_state = (final_state << 1) | p; // state = state*2+p;
        }
    }

}
