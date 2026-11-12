//
// Created by oscar on 11/9/2026.
//

#ifndef CS_415_PROJECT_3_TERNARYTREE_H
#define CS_415_PROJECT_3_TERNARYTREE_H
#include <string>
#include <vector>
class TernaryTree {
private:
    struct TernNode {
        char letter = '\0';
        bool end_of_word = false;
        TernNode *left = nullptr;
        TernNode *right = nullptr;
        TernNode *middle = nullptr;
    };
    TernNode *root;

    void destroy(const TernNode *node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        destroy(node->middle);
        delete node;
    }

    // Difficult to imagine but the important thing to note is words on a Ternary Trie will
    // be in the middle, once we go left or right, it becomes a different word which is why
    // we add the letter before going into middle and then remove it when we go right
    // So the recursive calling order doesn't matter, I just had it go left, middle, right
    // because then it at least saves the words in alphabetical order
    void autoCompleteHelper(const TernNode* node, std::vector<std::string>& words, std::string& word) const {
        if (node == nullptr) {
            return;
        }
        autoCompleteHelper(node->left, words, word);
        word.push_back(node->letter);
        if (node->end_of_word) {
            words.push_back(word);
        }
        autoCompleteHelper(node->middle, words, word);
        word.pop_back();
        autoCompleteHelper(node->right, words, word);
    }

public:
    TernaryTree() {
        root = new TernNode();
    }
    ~TernaryTree() {
        destroy(root);
    }
    // presuming word has already been cleansed (all lower case and no symbols)
    void insert(const std::string& word) {
        int i = 0;
        if (root == nullptr) {
            root = new TernNode();
            root->letter = word[i];
        }
        TernNode* temp = root;
        while (i < word.size()) { // for each word[i] to temp-> letter comparison count it as one operation
            if (word[i] == temp->letter) { // if letter already exists here, progress down
                // because of indices, make sure we aren't out of bounds
                if (i + 1 >= word.size()) { // don't count as operation
                    break;
                }
                if (temp->middle == nullptr) {
                    temp->middle = new TernNode(); // make sure it exists first
                    temp->middle->letter = word[i + 1]; // the current letter is where we are at, so insert the NEXT letter
                }
                temp = temp->middle;
                i++; //Only want to move to next letter if we actually inserted it
            }
            else if (word[i] < temp->letter) { // move left if less than
                if (temp->left == nullptr) {
                    temp->left = new TernNode();
                    temp->left->letter = word[i]; // Should really make a better constructor later
                }
                temp = temp->left;
            }
            else { // only right is left
                if (temp->right == nullptr) {
                    temp->right = new TernNode();
                    temp->right->letter = word[i];
                }
                temp = temp->right;
            }
        }
        temp->end_of_word = true;
    }


    [[nodiscard]] TernNode* search(const std::string& word) const {
        TernNode* temp = root;
        int i = 0;
        while (i < word.size()) {
            if (!temp) {
                return nullptr;
            }
            if (word[i] == temp->letter) {
                if (i + 1 >= word.size()) { // otherwise it accidentally increments to some nullptr
                    return temp;
                }
                temp = temp->middle;
                i++;
            }
            else if (word[i] < temp->letter) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return temp;
    }

    void autoComplete(std::vector<std::string>& words, std::string& word) const {
        TernNode* temp = search(word);
        if (temp == nullptr) {
            return;
        }
        autoCompleteHelper(temp->middle, words, word);
    }
};
#endif //CS_415_PROJECT_3_TERNARYTREE_H