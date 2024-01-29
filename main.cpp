#include <iostream>
#include <random>
#include <time.h>
#include <fstream>
#include <fcntl.h>

#include "ans.h"

//#define PRINT_VALUES


int main(int argc, const char * argv[]) {
    
    const int len_alphabet = 256; //alphabet = {0,..., len_alphabet-1}
    const int num_symbols = 1000000; //number of symbols to encode
    int symbols[num_symbols] = { 0 }; //all symbols must be in alphabet
    int frequencies[len_alphabet] = { 0 }; //this distribution has to be different from the uniform, otherwise it does not encode a lot
    int cumuls[len_alphabet+1] = { 0 };
    
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(128.0, 25);
    
    
    for (int i = 0; i < num_symbols; i++) {
        bool correct = false;
        double number = 0.0;
        while(!correct) {
            number = distribution(generator);
            if ((number>= 0.0) && ((int)number < len_alphabet-1))
                correct = true;
        }
        symbols[i] = int(number);
    }
    
    clock_t t1;
    clock_t t2;
    // Encoding
    
    t1 = clock();
    
    for (int i = 0; i < num_symbols; i++)
        frequencies[symbols[i]]++;
    
    for (int i= 1; i < len_alphabet+1; i++)
        cumuls[i] = cumuls[i-1] + frequencies[i-1];
    
    std::vector<short int> bitstream;
    int state = num_symbols;
    encode(symbols, frequencies, cumuls, state, num_symbols, bitstream);
    
    t1 = clock() - t1;
    double time_taken = ((double)t1)/CLOCKS_PER_SEC;
    
    std::cout << "Num symbols: " << num_symbols << std::endl;
    std::cout << "Length encoded bitstream: " << bitstream.size() << " bits" << std::endl;
    std::cout << "Length not encoded bitstream (8 bits per symbol): " << num_symbols*8 << " bits" << std::endl;
    std::cout << "Time taken to encode: " << time_taken << " seconds" << std::endl;
    std::cout << "Bitstream is: " << (1 - ((float) bitstream.size() / (float)(num_symbols*8)))*100 << "% smaller" << std::endl << std::endl;
    
    #ifdef PRINT_VALUES
        std::cout << "Bitstream:\t";
        for (int i = bitstream.size()-1; i >= 0 ; i--) //the symbols are decoded in reverse order
            std::cout << bitstream[i];
        std::cout << std::endl << std::endl;
    #endif
    
    
    // Decoder
    t2 = clock();
    
    int decode_arr[num_symbols] = { 0 };
    for (int i= 1; i < len_alphabet+1; i++) {
        for (int j = cumuls[i-1]; j < cumuls[i]; j++)
            decode_arr[j] = i-1;
    }
    
    std::vector<int> values;
    decode(state, frequencies, cumuls, bitstream, num_symbols, decode_arr, values);
    
    
    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;
    
    
    #ifdef PRINT_VALUES
        std::cout << "Decoded bitstream symbols:\t";
        for (int i = values.size()-1; i >= 0 ; i--) //the symbols are decoded in reverse order
            std::cout << values[i] << ", ";
        std::cout << std::endl;
        
        std::cout << "Original symbols:\t\t\t";
        for (int i = 0; i < num_symbols ; i++) //the symbols are decoded in reverse order
            std::cout << symbols[i] << ", ";
        std::cout << std::endl << std::endl;
    #endif
    
    std::cout << "Time taken to decode: " << time_taken2 << " seconds" << std::endl;
    std::cout << "Total program time: " << time_taken2 + time_taken << " seconds" << std::endl;
    
    return 0;
}
