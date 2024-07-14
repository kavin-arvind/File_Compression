#include "huffman-tree.cpp"

class treeEncode {
private:
    tree* buildHelper(std::string& preorder, std::string& inorder, int &preindex, int instart, int inend, std::map<char, int>& mp){
        if(instart > inend) return nullptr;

        int index = (*mp.find(preorder[preindex])).second;

        tree* node = new tree(preorder[preindex]);
        preindex++;
        node->left = buildHelper(preorder, inorder, preindex, instart, index - 1, mp);
        node->right = buildHelper(preorder, inorder, preindex, index + 1, inend, mp);

        return node;
    }
    void preorderHelper(tree* Node, std::string& s){
        if(Node == nullptr) return;

        s += Node->value;
        preorderHelper(Node->left, s);
        preorderHelper(Node->right, s);
    }
    void inorderHelper(tree* Node, std::string& s){
        if(Node == nullptr) return;

        inorderHelper(Node->left, s);
        s += Node->value;
        inorderHelper(Node->right, s);
    }
public:
    tree* buildTree(std::string& preorder, std::string& inorder) {
        if(preorder.size() != inorder.size()) return nullptr;
        if(preorder.size() == 0) return nullptr;

        std::map<char, int> mp;
        for(int i = 0; i < inorder.size(); ++i){
            mp[inorder[i]] = i;
        }

        int ind = 0;
        return buildHelper(preorder, inorder, ind, 0, inorder.size() - 1, mp);
    }

    std::string preorder(tree* headNode){
        string s = "";
        preorderHelper(headNode, s);
        return s;
    }
    
    std::string inorder(tree* headNode){
        string s = "";
        inorderHelper(headNode, s);
        return s;
    }
    
    string f(int i, int gamma)
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

    int g(string i)
    { 
        int num = 0;
        for(int j = 0; j < i.size(); ++j){
            if(i[j] == '1'){num += 1 << (i.size() - 1 - j);}
        }
        return num;
    }
};

class treeEncodebits {
private:
    void bitEncodeHelper(tree* Node, std::string &st){
        if(Node == nullptr) return;
        if(Node->isLeaf()){st += '1'; st += Node->value; return;}
        st += '0';
        bitEncodeHelper(Node->left, st);
        bitEncodeHelper(Node->right, st);
    }
    tree* bitDecodeHelper(std::string &encoded, double &i){
        if(i >= encoded.size()) return nullptr;
        if(encoded[i] == '1'){
            i++;
            tree* node = new tree(encoded[i]);
            i++;
            return node;
        }
        else if(encoded[i] == '0'){
            tree* node = new tree();
            i++;
            node->left = bitDecodeHelper(encoded, i);
            node->right = bitDecodeHelper(encoded, i);
            return node;
        }
        return nullptr;
    }
public:
    std::string bitEncode(tree* headNode){
        std::string st = "";
        bitEncodeHelper(headNode, st);
        return st;
    }
    tree* bitDecode(std::string &encoded){
        double i = 0;
        return bitDecodeHelper(encoded, i);
    }
    string f(int i, int gamma)
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

    int g(string i)
    { 
        int num = 0;
        for(int j = 0; j < i.size(); ++j){
            if(i[j] == '1'){num += 1 << (i.size() - 1 - j);}
        }
        return num;
    }
};