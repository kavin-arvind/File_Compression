#ifndef HUFFMAN
#define HUFFMAN

#include <bits/stdc++.h>
using std::cout, std::endl, std::string;
using std::map, std::set, std::pair, std::make_pair;

class cmp{
    public:
    bool operator()(const std::pair<double, class tree*>& a, const std::pair<double, class tree*>& b){
        return a.first > b.first;
    }
};

// a node of the huffman tree. Already written, observe what is going on.
class tree{
public:
    string value = "┐"; // ┐/0/1/character. for now we just use just ┐.
    tree *left = nullptr, *right = nullptr;

    tree(){}
    tree(char value): value(1, value){}
    tree(tree *left): left(left){}
    //tree(char value, tree *left):left(left), value(1, value){}
    tree(tree *left, tree *right): left(left), right(right){}
    
    static tree *merge_trees(tree *left, tree *right){
        return new tree(left, right);
    }

    void print(const string &prefix="", bool isLeftChild=false){
        cout << prefix << (prefix==""?"└──":(isLeftChild? "├─0":"└─1"));
        // cout << "value:" << value << "|" << endl;
        if (isLeaf()) cout << "─[" << value << "]" << endl; else cout << value << endl;
        if (left) left->print(prefix + (isLeftChild?"│  ":"   "), true);
        if (right) right->print(prefix + (isLeftChild?"│  ":"   "), false);
    }
    bool isLeaf() const{ return !(left && right); }
    void get_codes(map<char, string> &map_in_progress, const string &prefix="") const{
        if (left){
            if (left->isLeaf()) map_in_progress[left->value[0]] = prefix + "0";
            else left->get_codes(map_in_progress, prefix + "0");
        }
        if (right){ 
            if (right->isLeaf()) map_in_progress[right->value[0]] = prefix + "1";
            else right->get_codes(map_in_progress, prefix + "1");
        }
    }
    ~tree() {
        delete left; delete right;
    }
};

// this returns the huffman tree using passed map of character to frequency
tree *huffman(const map<char, double> &freq_map)
{ 
    std::priority_queue<std::pair<double , class tree*>, std::vector<std::pair<double , class tree*>>, cmp > prio;
    for(map<char, double>::const_iterator it = freq_map.begin(); it != freq_map.end(); ++it){
        class tree* n = new tree((*it).first);
        prio.push(std::pair<double, tree*> ((*it).second, n));
    }

    while(prio.size() > 1){
        std::pair<double, class tree*> a = prio.top(); prio.pop();
        std::pair<double, class tree*> b = prio.top(); prio.pop();

        prio.push(std::pair<double, class tree*> (a.first + b.first, tree::merge_trees(a.second, b.second)));
    }
    // prio.top().second->print();
    return prio.top().second;
}

// compute the frequencies of characters in the string. For part 3, make sure to skip over backreferences and also set highest priority to the special character.
map<char, double> get_freqs(const string &buf) 
{ 
    map<char, double> mp;
    for(int i = 0 ; i < buf.size(); ++i){
        mp[buf[i]]++;
    }
    return mp;
}

#endif