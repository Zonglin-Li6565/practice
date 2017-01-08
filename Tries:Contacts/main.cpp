#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Trie {
public:
    Trie();
    virtual ~Trie();
    virtual void insert(string new_string);
    virtual vector<string> find(string part);
    virtual int find_num_possible(string part);

protected:
    class TrieNode {
    public:
        TrieNode * children[26];
        char node_key;
        bool is_word;
        string word;
        vector<int> child_meta;
        int num_possible;

        TrieNode(char key) : node_key(key){
            for (int i = 0; i < 26; i ++)
                children[i] = NULL;
            is_word = false;
            num_possible = 0;
        }
        ~TrieNode(); 
    };

private:
    void find_helper(TrieNode * root, vector<string> & result);
    TrieNode * root;
};

Trie::TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i ++)
        delete children[i];
}

Trie::Trie() {
    root = new TrieNode(' ');
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(string new_string) {
    TrieNode * current = root;
    for (auto s : new_string) {
        if (current->children[s - 'a'] == NULL) {
            current->children[s - 'a'] = new TrieNode(s);
            current->child_meta.push_back(s - 'a');
        }
        current->num_possible ++;
        current = current->children[s - 'a'];
    }
    current->is_word = true;
    current->word = new_string;
    current->num_possible ++;
}

void Trie::find_helper(TrieNode * root, vector<string> & result) {
    if (root->is_word)
        result.push_back(root->word);
    for (int i = 0; i < root->child_meta.size(); i++) {
        find_helper(root->children[root->child_meta[i]], result);
    }
}

vector<string> Trie::find(string part) {
    vector<string> result;
    TrieNode * current = root;
    for (auto s : part) {
        if (current->children[s - 'a'] == NULL)
            return result;
        current = current->children[s - 'a'];
    }
    if (current->is_word) {
        result.push_back(current->word);
    }
    for (int i = 0; i < current->child_meta.size(); i++) {
        find_helper(current->children[current->child_meta[i]], result);
    }
    return result;
}

int Trie::find_num_possible(string part) {
    TrieNode * current = root;
    for (auto s : part) {
        if (current->children[s - 'a'] == NULL)
            return 0;
        current = current->children[s - 'a'];
    }
    return current->num_possible;
}

int main(){
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    int n;
    cin >> n;
    Trie trie;
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        if (op == "add") {
            trie.insert(contact);
        }
        if (op == "find") {
            // vector<string> result = trie.find(contact);
            // cout << result.size() << endl;
            // for (auto a : result)
            //     cout << a << endl;
            cout << trie.find_num_possible(contact) << endl;
        }
    }
    return 0;
}
