#include "TrieNode.h"

//costructor
TrieNode::TrieNode() : isTerminal(false) 
{

}

// destructor
TrieNode::~TrieNode() 
{
    for (auto& child : children)
     {
        delete child.node;
    }
}
