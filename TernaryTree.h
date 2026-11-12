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
        if (root == nullptr) {
            root = new TernNode();
            root->letter = word[0];
        }
        TernNode* temp = root;
        for (char c : word) {
            if (c == temp->letter) { // if letter already exists here, progress down
                if (temp->middle == nullptr) {
                    temp->middle = new TernNode(); // make sure it exists first
                }
                temp = temp->middle;
            }
            else if (c < temp->letter) { // move left if less than
                if (temp->left == nullptr) {
                    temp->left = new TernNode();
                }
                temp = temp->left;
            }
            else { // only right is left
                if (temp->right == nullptr) {
                    temp->right = new TernNode();
                }
                temp = temp->right;
            }
            temp->letter = c; // if not already
        }
        temp->end_of_word = true;
    }


    [[nodiscard]] TernNode* search(const std::string& word) const {
        TernNode* temp = root;
        for (char c : word) {
            if (!temp) {
                return nullptr;
            }
            if (c == temp->letter) {
                temp = temp->middle;
            }
            else if (c < temp->letter) {
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