#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{	
    struct TrieNode* children[26];
    int isEndOfWord;
    int count;
};

// Initializes a trie node
struct TrieNode* createNode()
{
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        newNode->isEndOfWord = 0;
        newNode->count = 0;
        for (int i = 0; i < 26; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct TrieNode* root, char *word)
{
    struct TrieNode* node = root;
    for (int i = 0; word[i]; i++)
    {
        int index = word[i] - 'a';
        
        if(index < 0 || index >= 26)
        {
            printf("Error: Invalid character in word: %c\n", word[i]); 
            return; 
            
        }
        //int number_of_children = 12; 
        //node->children = (Node**)calloc(number_of_children, sizeof(Node*)); 
        if (!node->children[index])
        {
            node = node->children[index] = createNode();
        }
        node = node ->children[index];
        
    }
    node->isEndOfWord = 1;
    node->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode* root, char *word)
{
    struct TrieNode* node = root;
    for (int i = 0; word[i]; i++)
    {
        int index = word[i] - 'a';
        if (index < 0 || index <= 26 || !node->children[index]) 
    
        {
            return 0; 
        }
        node = node->children[index]; 
    }
    return (node && node->isEndOfWord) ? node->count : 0;
    
            
     }
        
    // Deallocates the trie structure
void deallocateTrie(struct TrieNode* root)
{
    if (!root)
    {
        return;
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i])
        {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Reads the dictionary from a file and stores words in pInWords array
int readDictionary(char *filename, char **pInWords)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening the file.\n");
        return 0;
    }

    int numWords = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character
        pInWords[numWords] = strdup(buffer);
        numWords++;
    }

    fclose(fp);
    return numWords;
}

int main(void)
{
    char *inWords[256];
	
    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *pTrie = createNode();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Test words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    deallocateTrie(pTrie);

    return 0;
}
