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
    void autoCompleteHelper(const TrieNode* node, std::vector<std::string>& words, std::string& word) const {
        if (node == nullptr) {
            return;
        }
        if (node->end_of_word) {
            words.push_back(word);
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) { // Still needed despite the base case
                char ch = 'a' + i;
                word.push_back(ch);
                autoCompleteHelper(node->children[i], words, word);
                word.pop_back();
            }
        }
    }
public:
    ArrayTrie() {
        root = new TrieNode();
    }
    ~ArrayTrie() {
        destroy(root);
    }
    // presuming word has already been cleansed (all lower case and no symbols)
    void insert(const std::string& word) const {
        TrieNode* temp = root;
        for (char c : word) {
            int i = c - 'a';
            if (!temp->children[i]) {
                temp->children[i] = new TrieNode();
            }
            temp = temp->children[i];
        }
        temp->end_of_word = true;
    }
    // I think we should return a pointer here since we want to auto-complete any words
    [[nodiscard]] TrieNode* search(const std::string& word) const {
        TrieNode* temp = root;
        for (char c : word) {
            int i = c - 'a';
            if (!temp->children[i]) {
                return nullptr;
            }
            temp = temp->children[i];
        }
        return temp; // Note this returns regardless if its an end-of-word, because it needs to for auto-complete to work
    }
    // I am not doing delete, we aren't using it here
    // But I am doing an auto-complete function
    void autoComplete(std::vector<std::string>& words, std::string& word) const {
        TrieNode* temp;
        temp = search(word);
        autoCompleteHelper(temp, words, word);
    }

};
#endif //CS_415_PROJECT_3_ARRAYTRIE_H
