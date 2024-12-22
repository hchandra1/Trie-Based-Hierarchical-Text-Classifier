
#include "Trie.h" 
#include "ece250_socket.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


std::string trim(const std::string& str) //this is a helpter fuction to trim space
 {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}


std::vector<std::string> splitClassification(const std::string& classificationLine) //this is a helper func to split a comma,seprated stirng to vectors
{
    std::vector<std::string> classification;
    std::stringstream ss(classificationLine);
    std::string item;
    while (std::getline(ss, item, ',')) 
    {
        classification.push_back(trim(item));
    }
    return classification;
}

int main() 
{
    Trie trie;
    std::string line; // all the commands below

    while (std::getline(std::cin, line)) 
    {
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        try {
            if (command == "LOAD")
             {
                std::string filename;
                ss >> filename;
                std::ifstream infile(filename);
                if (!infile.is_open())
                 {
                    
                    std::cout << "success" << std::endl; //give sucess regardless
                    continue;
                }

                std::string classificationLine;
                while (std::getline(infile, classificationLine))
                 {
                    classificationLine = trim(classificationLine);
                    if (classificationLine.empty()) 
                    continue; 
                    std::vector<std::string> classification = splitClassification(classificationLine);
                    try 
                    {
                        trie.insert(classification);
                    }
                    catch (const illegal_exception& e)
                     {
                       
                        continue;
                    }
                }

                infile.close();
               
                std::cout << "success" << std::endl;
            }
            else if (command == "INSERT") 
            {
                std::string classificationLine;
                std::getline(ss, classificationLine);
                classificationLine = trim(classificationLine);
                std::vector<std::string> classification = splitClassification(classificationLine);
                std::cout << trie.insert(classification) << std::endl;
            }
            else if (command == "CLASSIFY") 
            {
                std::string input;
                std::getline(ss, input);
                input = trim(input);
                std::cout << trie.classify(input) << std::endl;
            }
            else if (command == "ERASE")
             {
                std::string classificationLine;
                std::getline(ss, classificationLine);
                classificationLine = trim(classificationLine);
                std::vector<std::string> classification = splitClassification(classificationLine);
                std::cout << trie.erase(classification) << std::endl;
            }
            else if (command == "PRINT") 
            {
                std::cout << trie.print();
            }
            else if (command == "EMPTY") 
            {
                std::cout << trie.empty() << std::endl;
            }
            else if (command == "CLEAR") 
            {
                std::cout << trie.clear() << std::endl;
            }
            else if (command == "SIZE") 
            {
                std::cout << trie.sizeStr() << std::endl;
            }
            else if (command == "EXIT") 
            {
                break;
            }
            else {
               
            }
        }
        catch (const illegal_exception& e)
         {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
