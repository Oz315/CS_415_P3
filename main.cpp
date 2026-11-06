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

        string userInput;
        vector<string> words;

        cout << "Enter search string: ";
        cin >> userInput;
        while (userInput != "0") { // user shouldn't be inputting numbers anyway
            trie->autoComplete(words, userInput);
            cout << "Auto-complete results using standard Trie are:";
            for (int i = 0; i < words.size(); i++) {
                cout << words[i] << ", ";
            }
            words.clear();
            cout << "\n\n(To quit type '0') Enter search string:";
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
