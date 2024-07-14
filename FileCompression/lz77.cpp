#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <bits/stdc++.h>
#include "constants.h"
using std::string, std::bitset, std::unordered_map;
typedef unsigned long ulg;

// a struct for the backreference. A casting operator to string that can used (it is not optimal) as encoding is provided for convenience.
struct backref{
    ulg offset, length;
    backref(const ulg &offset, const ulg &length): offset(offset), length(length){}
    operator string() const{
        return encode_backref();
    }
    string encode_backref() const{
        return string(1, -1) + bitset<15>(offset).to_string() + string(1, -1) + bitset<8>(length-3).to_string() + string(1, -1);
    }
};

// find the longest match for buf[i:i+lookahead_size] as a substring in the window buf[max(i-window_size,0):] and return appropriate backreference. Note that the longest match can exceed buf[i], that is, for buf=aaaa the longest match at i = 1 returns (0, 3).
backref find_longest_match(const string &buf, ulg i, ulg window_size, ulg lookahead_size, unordered_map<string, ulg> &window_map) {
    ulg max_match_len = 0;
    ulg best_offset = 0;

    for (ulg j = (i < window_size) ? 0 : (i - window_size); j < i; ++j) {
        string substring = buf.substr(j, lookahead_size);
        auto it = window_map.find(substring);

        if (it != window_map.end()) {
            ulg match_start = it->second;
            ulg match_len = 0;

            while (match_len < lookahead_size && i + match_len < buf.size() && buf[match_start + match_len] == buf[i + match_len]) {
                match_len++;
            }

            if (match_len > max_match_len) {
                max_match_len = match_len;
                best_offset = i - match_start;
            }
        }

        // Add current substring to the map
        window_map[buf.substr(j, lookahead_size)] = j;
    }

    if (max_match_len >= MIN_MATCH_LENGTH) {
        return backref(best_offset, max_match_len);
    }
    return backref(0,0);

}

// Compress the string using LZ77 and return the compressed binary string containing characters and string encodings of backreferences.
string deflate_lz77(const string &infile_str) {
    string output = "";
    ulg i = 0;
    unordered_map<string, ulg> window_map;

    while (i < infile_str.size()) {
        backref bk = find_longest_match(infile_str, i, WINDOW_SIZE, 258, window_map);
        if (bk.length >= MIN_MATCH_LENGTH) {
            output += string(bk);
            i += bk.length;
        } else {
            output += infile_str[i];
            i++;
        }
    }

    return output;
}

// Decompress the string (contains string encodings of backreferences, etc.) using LZ77 and return the original string.
string inflate_lz77(const string &compressed) {
    string output = "";
    ulg i = 0;

    while (i < compressed.size()) {
        if (compressed[i] != char(-1)) {
            output += compressed[i++];
        } else {
            ++i;
            string offset_str = "";
            while (compressed[i] != char(-1)) {
                offset_str += compressed[i++];
            }
            ++i;
            string length_str = "";
            while (compressed[i] != char(-1)) {
                length_str += compressed[i++];
            }
            ++i;

            ulg offset = bitset<15>(offset_str).to_ulong();
            ulg length = bitset<8>(length_str).to_ulong() + 3;

            for (ulg j = 0; j < length; ++j) {
                output += output[output.size() - offset];
            }
        }
    }

    return output;
}
