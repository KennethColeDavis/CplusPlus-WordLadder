/*
 * File:    Graph.h
 * Course:  CS216-010
 * Project: Project 2
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
#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>

using namespace std;

const int NOPATH         = -1;
const int INVALID_VERTEX = -2;

template < typename T = string >
class Graph
{
  public:
    // Default constructor.
    Graph();

    // Check if an edge exists between v and w.
    bool hasEdge(T v, T w) const;

    // Add an edge beween v and w to the graph.
    void addEdge(T v, T w);

    // Add a key with no corresponding value
    void addVert(string word);

    // Reverse go_through map.
    // Return a vector of the words from source to destination.
    vector<T> reverseMap(map<T, T> go_through2, int pathLength, T destination2, T source) const;

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
    int BFS(T s, T t, map<T, int>& distance,
            map<T, T>& go_through) const;

  private:
    // Represents the mapping from a vertex u (the key) to a set of
    // vertices (the value) which directly connect to u.
    map<T, set<T>> adjMap;
};

#endif /* GRAPH_H */

#include "Graph.cpp" 
