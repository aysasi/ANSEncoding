# ANS Encoding and Decoding
This repository includes a C++ implementation of a simple Asymetric Numeral Systems

This repository contains a C++ implementation of a simple binary entropy coding algorithm based on Asymmetric Numeral Systems (ANS). ANS is a variant of arithmetic coding that operates on a range of probabilities for symbols.


## Main Functions
### Encode
```cpp
int encodeRangeANS(int symbol, int previous_state, int cumuls[], int M, int fq[]);
```
Encodes a symbol within the ANS range and returns the next state.

```cpp
void encode(int symbols[], int fq[], int cumuls[], int & state, int num_symbols, std::vector<short int> & bitstream);
```
Encodes a sequence of symbols into a bitstream using ANS.

### Decode

```cpp
DANS decodeRangeANS(int cumuls[], int M, int fq[], int state, int c_fun []);
```
   
Decodes an ANS state into a symbol and a previous state.
```cpp
void decode(int & final_state, int fq[], int cumuls[], std::vector<short int> & bitstream, int num_symbols, int c_fun[], std::vector<int> & ret);
```

Decodes a bitstream into symbols using ANS.

## Usage
You can use these functions in your own project by providing symbols, frequencies, initial states, and other necessary parameters.
This example uses a random number generator to create a set of symbols based on a non-uniform distribution. In this case, a normal distribution is used, but users can choose any distribution or file to encode.




