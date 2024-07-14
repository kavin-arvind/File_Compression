#include "tree-encoding.cpp"
#include "constants.h"

// given a compressed binary string, convert it to the original string using the huffman tree
std::string inflate(std::string &compressed)
{ 
    treeEncodebits enc;
    int i = 0;
    i += GAMMA;
    int sz = enc.g(compressed.substr(0, GAMMA));

    string bitenc = compressed.substr(i, sz);
    i += sz;

    tree* huffman_tree = enc.bitDecode(bitenc);

    string output = "";
    tree* node = huffman_tree;

    while(i < compressed.size()){
        if(node->isLeaf()){
            output += node->value;
            node = huffman_tree;
            if(node->isLeaf()) break;
        }else{
            if(compressed[i] == '0') node = node->left;
            else{ node = node->right;}
            ++i;
        }
    }
    if(node->isLeaf()){
        output += node->value;
    }
    return output;
}

// given a string, compress it using the huffman tree and return the resulting binary string
std::string deflate(std::string &buf)
{
    map<char, double> freq_map = get_freqs(buf);
    tree* huffman_tree = huffman(freq_map);
    string output = "";
    treeEncodebits enc;
    string bitenc = enc.bitEncode(huffman_tree);

    output += enc.f(bitenc.size(), GAMMA);
    output += bitenc;

    map<char, string> conversion;
    huffman_tree->get_codes(conversion);
    for(int i = 0; i < buf.size(); ++i){
        output += conversion[buf[i]];
    }
    return output;
}