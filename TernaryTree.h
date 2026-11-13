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

    //Keep track of operations and number of nodes
    long long buildOperations = 0;
    long long numberOfNodes = 0;

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
    void autoCompleteHelper(const TernNode* node, std::vector<std::string>& words, std::string& word, long long& totalOperations) const {
        if (node == nullptr) {
            return;
        }
        totalOperations++;
        autoCompleteHelper(node->left, words, word, totalOperations);


        word.push_back(node->letter);
        totalOperations++;
        if (node->end_of_word) {
            words.push_back(word);
        }
        totalOperations++;
        autoCompleteHelper(node->middle, words, word, totalOperations);
        word.pop_back();

        totalOperations++;
        autoCompleteHelper(node->right, words, word, totalOperations);
    }

public:
    TernaryTree() {
        root = new TernNode();
        buildOperations = 2;
        numberOfNodes = 1;
    }
    ~TernaryTree() {
        destroy(root);
    }
    // presuming word has already been cleansed (all lower case and no symbols)
    void insert(const std::string& word) {
        int i = 0;
        if (root == nullptr) { // I don't this this counts as an operation?
            root = new TernNode();
            root->letter = word[i];
            numberOfNodes++;
        }
        buildOperations++;
        TernNode* temp = root;
        while (i < word.size()) { // for each word[i] to temp-> letter comparison count it as one operation

            // Apparently, you can increment stuff like this inside the if conditions, never knew
            if (buildOperations++, word[i] == temp->letter) { // if letter already exists here, progress down
                // because of indices, make sure we aren't out of bounds
                if (i + 1 >= word.size()) { // don't count as operation
                    break;
                }
                if (temp->middle == nullptr) {
                    temp->middle = new TernNode(); // make sure it exists first
                    temp->middle->letter = word[i + 1]; // the current letter is where we are at, so insert the NEXT letter
                    buildOperations++;
                    numberOfNodes++;
                }
                temp = temp->middle;
                buildOperations++;
                i++; //Only want to move to next letter if we actually inserted it
            }
            else if (buildOperations++, word[i] < temp->letter) { // move left if less than
                if (temp->left == nullptr) {
                    temp->left = new TernNode();
                    temp->left->letter = word[i]; // Should really make a better constructor later
                    buildOperations++;
                    numberOfNodes++;
                }
                temp = temp->left;
                buildOperations++;
            }
            else { // only right is left
                buildOperations++; // Does this count? Not exactly doing a lookup
                if (temp->right == nullptr) {
                    temp->right = new TernNode();
                    temp->right->letter = word[i];
                    buildOperations++;
                    numberOfNodes++;
                }
                temp = temp->right;
                buildOperations++;
            }
        }
        temp->end_of_word = true;
        buildOperations++;
    }


    [[nodiscard]] TernNode* search(const std::string& word, long long& searchOperations) const {
        TernNode* temp = root;
        int i = 0;
        while (i < word.size()) {
            if (!temp) {
                return nullptr;
            }
            if (searchOperations++, word[i] == temp->letter) {
                if (i + 1 >= word.size()) { // otherwise it accidentally increments to some nullptr
                    return temp;
                }
                temp = temp->middle;
                i++;
            }
            else if (searchOperations++, word[i] < temp->letter) {
                temp = temp->left;
            }
            else {
                searchOperations++;
                temp = temp->right;
            }
        }
        return temp;
    }

    void autoComplete(std::vector<std::string>& words, std::string& word, long long& searchOperations, long long& totalOperations) const {
        TernNode* temp = search(word, searchOperations);
        totalOperations = searchOperations;
        if (temp == nullptr) {
            return;
        }
        totalOperations++;
        // Just in case, because we start by going temp->middle
        if (temp->end_of_word) {
            words.push_back(word);
        }
        autoCompleteHelper(temp->middle, words, word, totalOperations);
    }

    //Get the total operations used to build the Trie
    long long getBuildOperations() const {
        return buildOperations;
    }

    //Get how much space the Trie uses in pointer units
    long long getSpace() const {
        return 3LL * numberOfNodes;
    }
};
#endif //CS_415_PROJECT_3_TERNARYTREE_H