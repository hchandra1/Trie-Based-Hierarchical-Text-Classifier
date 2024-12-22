#ifndef TRIE_H 
#define TRIE_H

#include "TrieNode.h"
#include <iostream>
#include <vector>
#include <string>


class illegal_exception //illegal exception class 
{
public:
    const char* what() const 
    { 
        return "illegal argument"; 
    }
};

class Trie {
private:
    TrieNode* root;  // the root node of the Trie
    int size;       

    //functions
    void traverse(TrieNode* node, const std::string& prefix, std::vector<std::string>& classifications) const;
    void deleteNodes(TrieNode* node);
    bool hasUpperCase(const std::string& str) const;
    std::string trim(const std::string& str) const;

public:
    Trie(); //cosntrucor
    ~Trie();//destrcuror

    std::string insert(const std::vector<std::string>& classification);
    std::string erase(const std::vector<std::string>& classification);
    std::string classify(const std::string& input);
    std::string print() const;
    std::string empty() const;
    std::string clear();
    std::string sizeStr() const;

    
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
};

#endif 
