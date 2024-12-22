#ifndef TRIENODE_H
#define TRIENODE_H

#include <vector>
#include <string>

class TrieNode; 

// since we werent allowed to use strucs i used class
class ChildNode 
{
public:
    std::string className;
    TrieNode* node;

    // cosntrucor
    ChildNode(const std::string& name, TrieNode* child)
        : className(name), node(child) {}

    // destrcutor
    ~ChildNode() = default;
};

class TrieNode
 {
public:
    std::vector<ChildNode> children; 
    bool isTerminal;

    //construcor
    TrieNode();

    //destrucor
    ~TrieNode();
};

#endif // TRIENODE_H
