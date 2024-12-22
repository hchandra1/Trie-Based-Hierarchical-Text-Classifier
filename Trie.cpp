#include "Trie.h"
#include "ece250_socket.h" 
#include <sstream>
#include <algorithm>

Trie::Trie() : root(new TrieNode()), size(0) 
{

} // this is my construcor which intialzies the trie with a root node and sets the size to 0


Trie::~Trie() // this is my descturor which clears all the nodes in trie to free memeory and delete the root node
{
    clear();
    delete root;
}


bool Trie::hasUpperCase(const std::string& str) const // this is an extra helper fucntion to check for uppercase and returns true if any charcater is upper case
{
    return std::any_of(str.begin(), str.end(), ::isupper);
}

std::string Trie::trim(const std::string& str) const  //this is once again a helpter fuction to trim leading and trailing spaces and returns the string without any whitepasces
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}


std::string Trie::insert(const std::vector<std::string>& classification) // this is the insert fuction and takes vector of strigns represnting classfication path and returns sucess if insert is a sucess or fail if it fails
{
    try
     {
        
        for (const auto& cls : classification) // checks for illegral arguments and makes uses of illegal_exception as well here
         {
            if (hasUpperCase(cls)) 
            {
                throw illegal_exception();
            }
        }

        TrieNode* current = root;
        for (const auto& cls : classification) 
        {
            bool found = false;
            TrieNode* child = nullptr;

            
            for (auto& childNode : current->children) 
            {
                if (childNode.className == cls) 
                {
                    child = childNode.node;
                    found = true;
                    break;
                }
            }

            // if not found this creates a new child node and adds to current node childrens.
            if (!found) 
            {
                if (current->children.size() >= 15) 
                {
                    return "failure"; // Maximum of 15 subclasses allowed.
                }
                child = new TrieNode();
                current->children.emplace_back(cls, child);
            }

         
            current = child;
        }

        
        if (current->isTerminal) 
        {
            return "failure"; // checks if classification alreayd exisits and reutns failure if it does exsisit already. 
        }

        
        current->isTerminal = true;
        size++;
        return "success";
    }
    catch (const illegal_exception& e) 
    {
        return e.what(); 
    }
}


std::string Trie::erase(const std::vector<std::string>& classification) // this is my erase fucntion to erase classifciton from a trie and retudsn sucess if true and fail otherwise.
 {
    try { // same logic as prev fucntion
       
        for (const auto& cls : classification)
         {
            if (hasUpperCase(cls)) 
            {
                throw illegal_exception();
            }
        }

        TrieNode* current = root;
        std::vector<TrieNode*> path; // this is to the keep track of node along the clasification path.
        path.push_back(root);

      
        for (const auto& cls : classification) 
        {
            bool found = false;
            TrieNode* child = nullptr;

            for (auto& childNode : current->children)
             {
                if (childNode.className == cls)
                 {
                    child = childNode.node;
                    found = true;
                    break;
                }
            }

            if (!found) 
            {
                return "failure"; //once again same type of logic used in the previous fucntions
            }

            current = child;
            path.push_back(current);
        }

      
        if (!current->isTerminal) 
        {
            return "failure"; 
        }

        
        current->isTerminal = false;
        size--;

        
        for (int i = classification.size(); i >= 1; --i) // this part is to remvoe node that are no longer part of any classifitoon.
        {
            TrieNode* node = path[i];
            TrieNode* parent = path[i - 1];

            if ((node->children.empty()) && (!node->isTerminal)) 
            {
                auto it = std::find_if(parent->children.begin(), parent->children.end(), [&](const ChildNode& childNode) 
                    {
                        return childNode.className == classification[i - 1];
                    });

                if (it != parent->children.end()) 
                {
                    delete it->node;
                    parent->children.erase(it);
                }
            }
            else 
            {
                break; 
            }
        }

        return "success";
    }
    catch (const illegal_exception& e) 
    {
        return e.what(); 
    }
}


std::string Trie::classify(const std::string& input) // this is my classify fucntion which returns the classfiction path as string or failure if no match is found
 {
    try {
   
        if (hasUpperCase(input)) 
        {
            throw illegal_exception();
        }

        TrieNode* current = root;
        std::string classificationPath;

        while (current)
         {
            std::vector<std::string> candidates;
            for (const auto& childNode : current->children)
             {
                candidates.push_back(childNode.className);
            }

            if (candidates.empty())
            {
                break; 
            }

            
            std::string optionsStr;
            for (size_t i = 0; i < candidates.size(); ++i)
            {
                optionsStr += candidates[i];
                if (i != candidates.size() - 1) 
                {
                    optionsStr += ",";
                }
            }

           
            std::string selectedClass = labelText(input, optionsStr);
            if (selectedClass.empty()) {
                break; 
            }

           
            if (!classificationPath.empty()) 
            {
                classificationPath += ",";
            }
            classificationPath += selectedClass;

           
            bool found = false;
            for (const auto& childNode : current->children) 
            {
                if (childNode.className == selectedClass)
                 {
                    current = childNode.node;
                    found = true;
                    break;
                }
            }

            if (!found) 
            {
                break; // the selected class is not found in children.
            }
        }

        // this returns the classification path or "failure" if no match is found.
        if (classificationPath.empty()) 
        {
    return "failure";
     } 
     else 
    {
    return classificationPath;
    }

    }
    catch (const illegal_exception& e) 
    {
        return e.what(); // this returns the exception message for illegal arguments.
    }
}


void Trie::traverse(TrieNode* node, const std::string& prefix, std::vector<std::string>& classifications) const // this is my traverse function which is also a helpter fuctnion and this collects the terminal classifitons into a vector 
{
    
    if (node->isTerminal && node->children.empty()) 
    {
        classifications.push_back(prefix);
    }

    for (const auto& childNode : node->children)
     {
        std::string newPrefix = prefix.empty() ? childNode.className : prefix + "," + childNode.className;
        traverse(childNode.node, newPrefix, classifications);
    }
}


std::string Trie::print() const  // this is the print fucniton which prints a string with classifcations separated by underscores.
{
    std::vector<std::string> classifications;
    traverse(root, "", classifications);

    if (classifications.empty())
     {
        return "trie is empty\n"; 
    }

    std::ostringstream oss;
    for (const auto& cls : classifications)
     {
        oss << cls << "_"; 
    }
    oss << "\n"; 

    return oss.str();
}


std::string Trie::empty() const // function to check if its empty and returns empty 1 if its empty and empty 0 if its not empty
{
    if (size == 0) 
    {
        return "empty 1"; 
    } 
    else 
    {
        return "empty 0"; 
    }
}



std::string Trie::clear() // this function clears trie and deletes all nodes and resets the size to zero
{
    deleteNodes(root);
    root->children.clear();
    size = 0;
    return "success";
}


std::string Trie::sizeStr() const // this fucntion gets the szie of trie as a string and returns the no of classifitons in the trie.
{
    return "number of classifications is " + std::to_string(size);
}

// Helper function to delete nodes recursively
void Trie::deleteNodes(TrieNode* node) 
{
    for (auto& childNode : node->children) 
    {
        if (childNode.node)
         {
            deleteNodes(childNode.node);
            delete childNode.node;
            childNode.node = nullptr;
        }
    }
}
