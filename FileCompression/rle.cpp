#include "rle.h"
#include <bits/stdc++.h>
// Constructor
rle::rle(int gamma): gamma(gamma){}

string stringmultiply(string str, int n){
    string output;
    for(int i = 0; i < n; ++i){
        output += str;
    }
    return output;
}
// Convert integer to gamma-bit binary string
string rle::f(int i)
{ 
    string s = "";
    int decimal = 0;
    while(i > 0 && decimal < gamma){
        decimal++;
        s += std::to_string(i%2);
        i = i/2;
    }
    while(decimal < gamma){
        decimal++;
        s+= "0";
    }
    std::reverse(s.begin(), s.end());
    return s;
}

// Convert gamma-bit binary string to integer
int rle::g(string i)
{ 
    int num = 0;
    for(int j = 0; j < i.size(); ++j){
        if(i[j] == '1'){num += 1 << (i.size() - 1 - j);}
    }
    return num;
}

// Compress the input file
string rle::compress(string input_string)
{ 
    string output = "";
    if(input_string.size() == 0) return "";

    output += input_string[0];
    int count = 1;

    for(int i = 1; i < input_string.size(); ++i){
        if(input_string[i] != '1' && input_string[i] != '0') continue;
        if(count == 1 << gamma){
            output += f(count - 1);
            output += f(0);
            count = 1;
        }
        //else{
            if(input_string[i-1] == input_string[i]){
                count++;
            } else{
                output += f(count);
                count = 1;
            }
        //}
    }
    output += f(count);
    return output;
}
// Decompress the input file
string rle::decompress(string input_string)
{ 
    if(input_string.size() == 0) return "";
    string output = "";
    char curr = input_string[0];
    for(int i = 1; i < input_string.size(); i += gamma){
        int num_times = g(input_string.substr(i, gamma));
        // std::cout<<"times: = "<<num_times<<std::endl;
        if(num_times > 0)output += std::string(num_times, curr);
        if(curr == '1') curr = '0';
        else if(curr == '0'){curr = '1';}
    }
    return output;
}