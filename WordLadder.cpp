/*
 * File:    WordLadder.h                                                                              
 * Course:  CS216-010
 * Project: Project2
 * Author:  Kenneth Davis
 * Date:    Aug 2023
 * Purpose: Declaration of the WordLadder class.                                                      
 */

#ifndef WORDLADDER_CPP
#define WORDLADDER_CPP

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include "Graph.h"
#include "WordLadder.h"
using namespace std;

// Constructor for taking in vector of words and mapping to sets of strings according to
// word length.
WordLadder::WordLadder(const vector <string >& words)
{
    for (int i = 0; i<words.size(); i++)
    {
        insertWord(words[i]);
    }
}
// Add a new word to the collection.
void WordLadder::insertWord(string newWord)
{
    int wordLength = newWord.length();
    wordsByLength[wordLength].insert(newWord);
}

    // Return a graph , the vertices of which are all of words with the
    // same length in the word list.
    // There is an edge between words if and only if they differ by a
    // single letter .
Graph<string>WordLadder::getWordsGraph(int length) const
{
    // Declare object to work on and return.
    Graph<string> wordsG;

    //Define set of words that are a given length.
    set<string> wordsSet = wordsByLength.at(length);

    //Convert set of words to a vector of words.
    vector<string> words (wordsSet.begin(), wordsSet.end());

    //Add all Verticies to Graph
    for (int i=0; i<words.size(); i++)
    {
        wordsG.addVert(words[i]);
    }

    // Iterate over each character position.
    for (unsigned long i = 0; i < length; i++)
    {
        // Remove one character in specified position, to get a bucket name.
        // Assigning the word to the resulting bucket. Presence of two words
        // in the same bucket means that they differ by only one letter.
        map<string, set<string>> repBucket;
        for (size_t j = 0; j < words.size(); j++)
        {
            string rep = words[j];
            rep[i]     = '?';
            repBucket[rep].insert(words[j]);
        }

        // Next create a Graph by adding edges between words in occupying the
        // same bucket.
        for (auto it = repBucket.begin(); it != repBucket.end(); it++)
        {
            set<string> oneBucket = it->second;
            for (auto itr1 = oneBucket.begin(); itr1 != oneBucket.end(); itr1++)
            {
                for (auto itr2 = oneBucket.begin(); itr2 != oneBucket.end();
                     itr2++)
                {
                    if (*itr1 != *itr2)
                    {
                        wordsG.addEdge(*itr1, *itr2);
                    }
                }
            }
        }
    }
    return wordsG;
}

    // Return a vector of words, which represents a minimum word ladder from
    // wordA to wordB , inclusive .
    // Any two  adjacent words along the ladder differ only by one
    // character .
vector <string> WordLadder::getLadder(string wordA, string wordB) const
{
    // Declare vector to work on and return.
    vector <string> returnLadder;

    // Make sure words are the same length or return an empty vector.
    if (wordA.length()!=wordB.length())
        return returnLadder;

    // Graph to work on which will hold connections for words of 
    // given length
    Graph<string> temp = getWordsGraph(wordA.length());

    // Declare necessary maps to call BFS and get distance from
    // wordA to WordB
    map<string, string> go_through2;
    map<string, int> distance2;
    int dis = temp.BFS(wordA, wordB, distance2, go_through2);
    
    returnLadder = temp.reverseMap(go_through2, dis, wordB, wordA);

    return returnLadder;
}


#endif /*WORDLADDER_CPP*/
