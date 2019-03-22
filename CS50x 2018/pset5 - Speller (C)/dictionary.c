// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

#define CHARINDEX ch - 65
#define APINDEX 26

unsigned int wordCount;

//Declaring the structure for each field of a node of the trie which will store the dictionary's words
typedef struct trie_node
{
    struct trie_node* children[27];
    bool isEndOfWord;
}trie_node;

void free_node(trie_node* node);

trie_node* head = NULL;

//Will create and return a new node of the trie
trie_node* getNewNode()
{
    trie_node* temp = (trie_node*)malloc(27 * sizeof(trie_node));

    if(temp == NULL)
        return NULL;

    temp -> isEndOfWord = false;

    for(int i = 0; i < 27; i++)
        temp -> children[i] = NULL;

    return temp;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    trie_node* temp;

    int i, ch;

    for(temp = head, i = 0; word[i] != '\0'; i++)
    {
        ch = toupper(word[i]);

        if(ch != '\'')
        {
            if(temp -> children[CHARINDEX] == NULL)
                break;
            else
                temp = temp -> children[CHARINDEX];
        }
        else
        {
            if(temp -> children[APINDEX] == NULL)
                break;
            else
                temp = temp -> children[APINDEX];
        }

    }

    if(word[i] == '\0' && temp -> isEndOfWord == true)
        return true;
    else
        return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* ptr = fopen(dictionary, "r");

    if(ptr == NULL)
        return false;

    //Loading each word in the dictionary into a Trie
    head = getNewNode(); //Head Node
    trie_node* temp = head;

    for(char ch = fgetc(ptr); ; ch = fgetc(ptr))
    {
         if(ch != '\n' && ch != EOF)
        {
            ch = toupper(ch);
            if(ch != '\'')
            {
                if(temp -> children[CHARINDEX] == NULL)
                {
                    temp -> children[CHARINDEX] = getNewNode();
                    if(temp == NULL)
                        return false;

                    temp = temp -> children[CHARINDEX];
                }
                else
                    temp = temp -> children[CHARINDEX];
            }
            else
            {
                if(temp -> children[APINDEX] == NULL)
                {
                    temp -> children[APINDEX] = getNewNode();
                    if(temp == NULL)
                        return false;

                    temp = temp -> children[APINDEX];
                }
                else
                    temp = temp -> children[APINDEX];
            }
        }

        else if(ch == '\n' || ch == EOF)
        {
            wordCount++;
            temp -> isEndOfWord = true;
            temp = head;
        }

        if(ch == EOF)
            break;

    }

    wordCount--;

    fclose(ptr);
    ptr = NULL;

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(head == NULL)
        return 0;
    else
        return wordCount;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if(head == NULL)    //If the dictionary isn't loaded yet, returns false.
        return false;

    free_node(head);
    return true;
}

void free_node(trie_node* node)
{
    if(node == NULL)
        return;

    for(int i = 0; i < 27; i++)
        free_node(node -> children[i]);

    free(node);
}