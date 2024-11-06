#include "SkipList.hpp"
#include <iostream>

// Define Movie class with necessary properties for demonstration purposes
class Movie {
public:
    std::string name;
    // Additional properties can be added here

    // Constructor
    Movie(const std::string& name) : name(name) {}

    // Comparison for convenience
    bool operator==(const Movie& other) const {
        return name == other.name;
    }
};

// SkipListNode Constructor
SkipListNode::SkipListNode(Movie* movie, int level)
    : movie(movie), forward(level + 1, nullptr) {}

// SkipList Constructor
SkipList::SkipList(int maxLevel, float probability)
    : maxLevel(maxLevel), count(0), probability(probability), gen(std::random_device{}()), dist(0.0, 1.0) {
    header = new SkipListNode(nullptr, maxLevel);
}

// SkipList Destructor
SkipList::~SkipList() {
    SkipListNode* current = header;
    while (current) {
        SkipListNode* next = current->forward[0];
        delete current;
        current = next;
    }
}

// Generates a random level for the new node
int SkipList::randomLevel() {
    int level = 0;
    while (dist(gen) < probability && level < maxLevel) {
        level++;
    }
    return level;
}

// Inserts a movie into the skip list
void SkipList::insert(Movie* movie) {
    std::vector<SkipListNode*> update(maxLevel + 1);
    SkipListNode* current = header;

    // Traverse the list to find the insertion point
    for (int i = maxLevel; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->movie->name < movie->name) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // Determine the random level for the new node
    int level = randomLevel();
    SkipListNode* newNode = new SkipListNode(movie, level);

    // Insert the new node into the skip list
    for (int i = 0; i <= level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    count++;  // Increase the node count
}

// Searches for a movie in the skip list by name
Movie* SkipList::search(const std::string& movieName) {
    SkipListNode* current = header;
    
    // Traverse the list to find the movie
    for (int i = maxLevel; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->movie->name < movieName) {
            current = current->forward[i];
        }
    }

    // Move to the next node in the lowest level
    current = current->forward[0];
    
    // Check if the node contains the movie
    if (current != nullptr && current->movie->name == movieName) {
        return current->movie;
    }

    return nullptr;  // Movie not found
}

// Removes a movie from the skip list by name
void SkipList::remove(const std::string& movieName) {
    std::vector<SkipListNode*> update(maxLevel + 1);
    SkipListNode* current = header;

    // Traverse the list to find the node to remove
    for (int i = maxLevel; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->movie->name < movieName) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    
    // If the node is found, remove it
    if (current != nullptr && current->movie->name == movieName) {
        for (int i = 0; i <= maxLevel; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }
        delete current;
        count--;  // Decrease the node count
    }
}

int SkipList::getsize()
{
    return count;
}
std::vector<std::string> SkipList::getAllNames()
{
    std::vector<std::string> vec;
    return vec;
}
