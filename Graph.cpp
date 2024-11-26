/*
 * File:    Graph.cpp
 * Course:  CS216-010
 * Project: Lab 7
 * Author:  Kenneth Davis
 * Date     Aug 4, 2024
 * Purpose: Declaration of the Graph class.
 *          This class represents an undirected Graph, with no edge weights,
 *          using adjacent map representation.
 *          It contains one private data member: adjMap
 *          which represents the mapping from a vertex u (the key) to a set of
 *          vertices (the value) which directly connect to u.
 *
 */
#ifndef GRAPH_CPP
#define GRAPH_CPP


#include <iostream>
#include <map>
#include <set>
#include <queue>
#include "Graph.h"
using namespace std;
 

// Default constructor.
template <typename T>
Graph<T>::Graph()
{
// We want adjMap to be empty to start
}

// Check if an edge exists between v and w.
template<typename T>
bool Graph<T>::hasEdge(T v, T w) const
{
    //Assume no edge.
    bool found=false;

    //Found intial vertex.
    if (adjMap.count(v)>0)
            found = true;
        
    //If first criteria (source vertex is a key in adjMap) is true. 
    if (found) 
        {
            //Initialize and define a set equivalet to the adjacent verticies. 
            set<T> adjacent =  adjMap.at(v);

            if (adjacent.count(w)>0)// If the edge we are looking for is in the equvalent set.
                 found=true;
            else
                found=false;
        }
    return found;
}

// Add an edge beween v and w to the graph.
template<typename T>
void Graph<T>::addEdge(T v, T w)
{
    if(!hasEdge(v, w)) //If the edge is not already present in adjMap.
    {
        //Insert edges both ways because the graph we are making is undirected.
        adjMap[v].insert(w);
        adjMap[w].insert(v);
    }
}

// Add a key value with no corresponding value.
template<typename T>
void Graph<T>::addVert(string word)
{
    // Add Key.
    adjMap[word];
}

// Reverse go_through map
// Return a vector of the words from source to destination.
template<typename T>
vector<T> Graph<T>::reverseMap(map<T, T> go_through2, int pathLength, T destination, T source) const
{
    // Define vector to return, string for the for loop, and necesary variables for function.
    vector<T> reversed(pathLength);
    string nextVert = destination;
    int lastElement = pathLength -1;

    // Set first and last element and change value for the for-loop.
    reversed[0]=source;
    reversed[lastElement]= destination;
    lastElement--;

    //Insert the path in revered order.
    for (int i=lastElement; i>0; i--)
    {
        reversed[i] = go_through2[nextVert];
        nextVert = go_through2[nextVert];
    }
    
    return reversed;
}

    // Apply BFS traversal to find the shortest path from the given source `s`
    // to destination `t`.
    // Return the distance from `s` to `t`.
    // If `s` or `t` does not exist, return INVALID_VERTEX (=-2)
    // If there is no path from `s` to `t`, return NOPATH (=-1)
    // Store the shortest path distance from the given source `s` to vertex `w`
    // in `distance` (map<w, distance>).
    // Store which vertex to go through next on the shortest path to the given
    // source `s` in `go_through` (map<w, v>).
    // Here a pair <w, v> in `go_through` represents on the shortest path
    // from `w` to the given source `s`,
    // it needs to take the path: w-->v...-->s
template<typename T>
int Graph<T>::BFS(T s, T t, map<T, int>& distance, map<T, T>& go_through) const
{
    //Check if adjMap has both verticies looking for.
    if (adjMap.count(s)==0 ||adjMap.count(t)==0)
    {
        cout<<"Invalid source vertex and/or destination vertex ."<<endl;
        return -1;
    }

    // Set all distances to -1 in distance map.
    for (auto it = adjMap.begin(); it!= adjMap.end(); it++)
    {
        distance[it->first]=-1;
    }

    //Declare queue.
    queue<T> Q;

    //Set distance map equal to 0 for the source.
    distance[s]=1;

    go_through[s] =  s; //Set the first value of go through map to map s to s
    Q.push(s);// Push s onto the queue for further evaluation.

    T current = s; //Set current equal the source vertex.
    while (!Q.empty() && current != t)
    {
        //Set current to the front of the queue and pop it off the queue
        //to make sure we evaluate each vertex in the graph.
        current = Q.front();
        Q.pop();
        
        //Range based for loop that will traverse through the set of adjacent verticies.
        for (auto adjacent : adjMap.at(current))
        {
            if (distance[adjacent] ==-1) // If unvisted.
            {
                distance[adjacent] = distance[current]+1; // Update distance for adjacent vertex in reference to current distance from source.
                go_through[adjacent] = current; // Insert where the adjacent vertex came from.
                Q.push(adjacent); //Enqueue adjacent vertex/verticies.
            }
        }
    }
//Return the value accounted for with distance map correlated to desitnation,if it 
//is not visited will return -1.
return distance[t];
}

#endif //GRAPH_CPP
