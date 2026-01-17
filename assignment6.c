/* COP 3502C Programming Assignment 6
This program is written by: Chen-An Chang */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    int nodeFreq;          // Frequency of the string at this node
    int sumPrefixFreq;     // Total frequency of words with this prefix
    int maxChildFreq;      // Max frequency in child nodes
    struct TrieNode *child[ALPHABET_SIZE]; // Pointers to child nodes
} TrieNode;

// Function to create a new Trie Node
TrieNode* createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->nodeFreq = 0;
    node->sumPrefixFreq = 0;
    node->maxChildFreq = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->child[i] = NULL;
    }
    return node;
}

// Insert a word into the Trie
void insertWord(TrieNode *root, const char *word, int frequency) {
    TrieNode *current = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->child[index] == NULL) {
            current->child[index] = createNode();
        }
        current = current->child[index];
        current->sumPrefixFreq += frequency;
        if (current->maxChildFreq < frequency) {
            current->maxChildFreq = frequency;
        }
    }
    current->nodeFreq += frequency;
}

// Query the most likely next letters for a given prefix
void queryPrefix(TrieNode *root, const char *prefix) {
    TrieNode *current = root;

    // Traverse to the end of the prefix
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (current->child[index] == NULL) {
            printf("unrecognized prefix\n");
            return;
        }
        current = current->child[index];
    }

    // Analyze child to find the most likely next letters
    char result[ALPHABET_SIZE + 1];
    int resultCount = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->child[i] != NULL &&
            current->child[i]->sumPrefixFreq == current->maxChildFreq) {
            result[resultCount++] = 'a' + i;
        }
    }

    if (resultCount == 0) {
        printf("unrecognized prefix\n");
    } else {
        result[resultCount] = '\0';
        printf("%s\n", result);
    }
}

// Free the Trie
void freeTrie(TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->child[i] != NULL) {
            freeTrie(root->child[i]);
        }
    }
    free(root);
}

// Main function to process commands
int main() {
    TrieNode *root = createNode();
    int n;
    scanf("%d", &n); // Number of commands

    for (int i = 0; i < n; i++) {
        int commandType;
        scanf("%d", &commandType);

        if (commandType == 1) { // Insert command
            char word[100];
            int frequency;
            scanf("%s %d", word, &frequency);
            insertWord(root, word, frequency);
        } else if (commandType == 2) { // Query command
            char prefix[100];
            scanf("%s", prefix);
            queryPrefix(root, prefix);
        }
    }

    freeTrie(root); // Clean up memory
    return 0;
}
