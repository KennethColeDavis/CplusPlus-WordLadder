# Course: CS216-010
# Project: Project 2
# Date: Aug 1, 2024
# Purpose: Implement and use a makefile to run Project2
# Author: Kenneth Davis



Project2: Project2.o Graph.o WordLadder.o
	g++ $^ -o $@

Prpject2.o: Project2.cpp
	g++ -c Project2.cpp -o $@

Graph.o: Graph.cpp Graph.h
	g++ -c $< -o $@

WordLadder.o: WordLadder.cpp WordLadder.h
	g++ -c $< -o $@

#Build clean capability
.PHONY: clean
clean:
	rm -i *.o
	rm `find ./ -type f -executable`
