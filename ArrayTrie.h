//
// Created by Oscar on 11/4/2026.
//

#ifndef CS_415_PROJECT_3_ARRAYTRIE_H
#define CS_415_PROJECT_3_ARRAYTRIE_H
#include <string>
#include <vector>

class ArrayTrie {
private:
    struct TrieNode {
        bool end_of_word = false;
        std::vector<TrieNode*> children{26, nullptr};
    };
    TrieNode *root;

    //Keep track of operations and number of nodes
    long long buildOperations = 0;
    long long numberOfNodes = 0;

    void destroy(const TrieNode *node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                destroy(node->children[i]);
            }
        }
        delete node;
    }
    void autoCompleteHelper(const TrieNode* node, 
        std::vector<std::string>& words, std::string& word,
    long long& totalOperations) const {
        if (node == nullptr) {
            return;
        }

        //Count checking if this is the end of a word
        totalOperations++;

        if (node->end_of_word) {
            words.push_back(word);
        }
        for (int i = 0; i < 26; i++) {

            //Count each child position, even if it is empty
            totalOperations++;

            if (node->children[i] != nullptr) { // Still needed despite the base case
                char ch = 'a' + i;
                word.push_back(ch);
                autoCompleteHelper(node->children[i], words, word, totalOperations);
                word.pop_back();
            }
        }
    }
public:
    ArrayTrie() {
        root = new TrieNode();

        //Count the root nodes and its creation
        numberOfNodes = 1;
        buildOperations = 2;
    }
    ~ArrayTrie() {
        destroy(root);
    }
    // presuming word has already been cleansed (all lower case and no symbols)
    void insert(const std::string& word) {
        if (word.empty()) {
            return;
        }

        TrieNode* temp = root;

        for (char c : word) {
            int i = c - 'a';

            //Count looking at the child position
            buildOperations++;
            TrieNode* next = temp->children[i];

            if (next == nullptr) {

                //Make a new node if one isn't there
                next = new TrieNode();
                buildOperations++;

                //Connect the new node to the current one
                temp->children[i] = next;
                buildOperations++;

                //Count the new node for space
                numberOfNodes++;
            }

            temp = next;
        }

        //Mark the end of the word
        temp->end_of_word = true;
        buildOperations++;
    }

    // I think we should return a pointer here since we want to auto-complete any words
    [[nodiscard]] TrieNode* search(const std::string& word,
         long long& searchOperations) const {
        TrieNode* temp = root;

        for (char c : word) {
            int i = c - 'a';

            //Count checking the child position
            searchOperations++;

            if (!temp->children[i]) {
                return nullptr;
            }
            temp = temp->children[i];
        }
        return temp; // Note this returns regardless if its an end-of-word, because it needs to for auto-complete to work
    }

    //Check if the whole word exists in Trie
    bool containsWord(const std::string& word, long long& searchOperations) const{
        TrieNode* temp = search(word, searchOperations);

        if (temp == nullptr) {
            return false;
        }

        //Count checking the end of the word
        searchOperations++;
        return temp->end_of_word;
    }

    // I am not doing delete, we aren't using it here
    // But I am doing an auto-complete function
    void autoComplete(std::vector<std::string>& words, std::string& word,
    long long& searchOperations, long long& totalOperations) const {
        words.clear();
        TrieNode* temp = search(word, searchOperations);
        totalOperations = searchOperations;
        autoCompleteHelper(temp, words, word, totalOperations);
    }

    //Get the total operations used to build the Trie
    long long getBuildOperations() const {
        return buildOperations;
    }

    //Get how much space the Trie uses in pointer units
    long long getSpace() const {
        return 26LL * numberOfNodes;
    }

};
#endif //CS_415_PROJECT_3_ARRAYTRIE_H
