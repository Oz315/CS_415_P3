#include <iostream>
#include <fstream>
#include <cctype>
#include "ArrayTrie.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <case_1_or_2>" << endl;
    }

    string flag = argv[2];
    if (flag != "1" && flag != "2") {
        cerr << flag << " is not a valid flag, 1 or 2" << endl;
        return 1;
    }

    ifstream input;
    input.open(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file " << argv[1] << endl;
        return 1;
    }

    string word;
    string cleansedWord;
    if (flag == "1") {
        ArrayTrie* trie = new ArrayTrie();
        while (input >> word) {
            for (char c : word) {
                if (isalpha(c)) {
                    char lo_c = static_cast<char>(tolower(c));
                    cleansedWord.push_back(lo_c);
                }

            }
            trie->insert(cleansedWord);
            cleansedWord = "";
        }
        input.close();

        //Print the operations and space used to build the Trie
        cout << "Time taken to build the standard Trie is "
             << trie->getBuildOperations()
             << " operations and space occupied by it is "
             << trie->getSpace()
             << " pointer units" << endl;

        string userInput;
        vector<string> words;

        cout << "Enter search string: ";
        cin >> userInput;
        while (userInput != "0") { // user shouldn't be inputting numbers anyway
           //Keep track of the search and auto-complete operations
           long long searchOperations = 0;
           long long totalOperations = 0;

           //Search for the prefix and get the matching words
           trie->autoComplete(words, userInput, searchOperations, totalOperations);

           //Print how many operations the search took
           cout << "Time taken to search in the standard Trie is "
                << searchOperations << " operations" << endl;

           //Print the words that match prefix
           cout << "Auto-complete results using standard Trie are: ";
           for (int i = 0; i < words.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << words[i];
           }
           cout << endl;

           //Print the total operations for auto-complete
           cout << "Time taken to find auto-complete results in the standard Trie is "
                << totalOperations << " operations" << endl;
            words.clear();

            cout << "\n\n(To quit type '0') Enter search string: ";
            cin >> userInput;
        }
        delete trie;
    }
    else if (flag == "2") {
        cout << "Not yet implemented..." << endl;
    }
    cout << "Done!" << endl;
    return 0;
}
