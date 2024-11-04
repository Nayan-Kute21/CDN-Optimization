#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>
#include <string>
#include <random>

class Movie;  // Forward declaration

class SkipListNode {
public:
    Movie* movie;
    std::vector<SkipListNode*> forward;

    // Constructor
    SkipListNode(Movie* movie, int level);
};

class SkipList {
private:
    int maxLevel;
    float probability;
    SkipListNode* header;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;

    // Helper methods
    int randomLevel();

public:
    // Constructor and Destructor
    SkipList(int maxLevel, float probability);
    ~SkipList();

    // SkipList operations
    void insert(Movie* movie);
    Movie* search(const std::string& movieName);
    void remove(const std::string& movieName);
};

#endif // SKIPLIST_H
