/*
 * File:    WordLadder.h
 * Course:  CS216-010
 * Project: Project2
 * Author:  Kenneth Davis
 * Date:    Aug 2023
 * Purpose: Declaration of the WordLadder class.
 */
#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "Graph.h"

using namespace std;

class WordLadder
{
    public:
    // Constructor for taking in vector of words and mapping to sets of strings according to
    // word length. 
    WordLadder (const vector <string >& words);

    // Add a new word to the collection.
    void insertWord (string newword);

    // Return a graph , the vertices of which are all of words with the
    // same length in the word list.
    // There is an edge between words if and only if they differ by a
    // single letter .
    Graph <string> getWordsGraph (int length) const ;

    // Return a vector of word , which represents a word ladder from
    // wordA to wordB , inclusive .
    // Any two adjacent words along the ladder differ only by one
    // character .
    vector <string> getLadder (string wordA , string wordB) const ;

    private:
    // Group all the words by the number of characters in each word.
    // The private data member `wordsByLength ` represents a mapping from
    // the length (key) to a vector of words of that length ( value ).
    map <int , set <string >> wordsByLength ;
};

#endif /* WORDLADDEr_H */
