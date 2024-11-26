/*
 *course:  CS216-010
 *Project: Project 2
 *Author:  Kenneth Davis
 *Date:    Aug 4, 2024
 *Purpose: Demonstrate a complex  Word Ladder, using any length words 
 *
 *         Create a Graph, by reading in the collection of words from an input
 *         file.
 *         Each vertex is labeled by the word. If two words are only
 *         different by a single letter, there is an edge between them.
 *         Repeatedly ask the user to choose a source vertex(word1), then a
 *         destination vertex(word2) (type enter to quit)
 *         Calculate the length of the "Word Ladder" from word1 to word2.
 *         This is the number of vertex in the path from the
 *         source to the destination in the Graph.
 *         Display the "Word Ladder" from word1 to word2. This is the
 *         the shortest path from the source to the destination in the Graph
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>  // For the transform() function
#include "Graph.h"
#include "WordLadder.h"

using namespace std;

// Declare a global constant, which defines the required number of command-line
// arguments, including the program itself.
const int ARGUMENTS = 2;

int main(int argc, char* argv[])
{
    // Check whether the number of command-line arguments match the requirement.
    if (argc != ARGUMENTS)
    {
        cout << "Warning: This program takes exactly " << ARGUMENTS - 1
             << " command-line argument." << endl;
        cout << "Usage: " << argv[0] << " <inputfile_name>" << endl;
        return 1;
    }

    ifstream in_file;
    in_file.open(argv[1]);
    // Check whether we can successfully open the input file.
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        return 2;
    }

    // Read data from the input file, assuming "good data" from the input file
    // Each line of the input file constains one word from an English
    // dictionary.
    string         word;
    vector<string> words;

    while (in_file >> word)
    {
        // Convert each word to lower-case.
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
    }
    // Close the input file.
    in_file.close();
    
    //Define strings for while loop.
    string word1 = "init";
    string word2 = "init";

    //Declare WordLadder object with correct constructor.
    WordLadder ladderByLength(words); 

    //Over Arching while-loop.
    while (!word1.empty() && !word2.empty())
    {   
        cout << endl << endl;
        cout << "Welcome to the CS 216 Word Ladder!" << endl;
        cout << "Please give me two English words, and I will convert the "
             << "first into the second by modifying one letter at a time." << endl;
        cout << "Please type the FIRST four-letter word "
             << "(or type Enter to quit): " << endl;
        //Get word one and check if empty.
        getline(cin, word1);
        if (word1.empty())
        {   
            continue;
        }   
        //Get word two and check if empty.
        cout << "Please type the SECOND four-letter word "
             << "(or type Enter to quit): " << endl;

        getline(cin, word2);
        if (word2.empty())
        {   
            continue;
        }

        //Store word1 and word2 for output to user later.
        string word1A = word1;
        string word2A = word2;

        // convert both word1 and word2 to all lower-case letters
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);


        // Deal with invalid inputs.
        if (word1 == word2)
        {
            cout<<"The two words should be different."<<endl; //Make sure words are different.
            continue;
        }
        else if (word1.length()!=word2.length()) //Make sure words are same length.
        {
            cout<<"The two words must be the same length!"<<endl;
            cout << "There is no path from [" << word1A << "] to [" << word2A << "]" << endl;
            continue;
        }

        //Define Graph for adjacent words and necessary maps for BFS.
        Graph<string> adjacent = ladderByLength.getWordsGraph(word1.length());
        map<string, int>    distance;                                                                 
        map<string, string> go_through;                                                               
        int dis = adjacent.BFS(word1, word2, distance, go_through);

        // Find Word Ladder or tell user there is none.
        if (dis==NOPATH)
        {
            cout << "There is no path from [" << word1A << "] to [" << word2A << "]" << endl;
        }
        else 
        {
            //Declare vector for path and use WordLadder object to get the path.
            vector<string> path = ladderByLength.getLadder(word1, word2);

            // Integer defenition for for-loop.
            int vecSize = path.size();

            //Output statement for if there is a path
            cout << "The ladder distance from [" << word1A << "] to [" << word2A << "] is " << dis << " steps." << endl;
            cout << "A ladder from [" << word1A << "] to [" << word2A << "]:" << endl;

            for (int i = 0; i<=vecSize-2; i++)
            {
                cout<<path[i];

                //Limit outputs for each line
                if (i % 6 == 0 && i != 0)
                    cout<<endl;
                cout<<" ---> ";
            }
            //Print destination (so there isn't an extra arrow). 
            cout<<path[vecSize-1];
        }
}
cout << "Thank you for using this program! Goodbye." << endl;
return 0;
}
