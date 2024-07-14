#include "huffman-zip.cpp"
// #include "rle.cpp"

int main(){
    string a = "kavin";
    
    string comp = deflate(a);
    std::cout<<comp<<std::endl;
    string decom = inflate(comp);
    std::cout<<decom<<std::endl;
    std::cout<<(a == decom)<<std::endl;
}