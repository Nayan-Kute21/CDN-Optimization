#ifndef CDNNODE_H
#define CDNNODE_H

#include <string>
#include "SkipList.hpp"

class CDNNode {
private:
    double x, y;  // Coordinates of the CDN node
    SkipList popularMovies;

public:
    // Constructor
    CDNNode(double x, double y, int skipListMaxLevel = 4, float skipListProbability = 0.5f);

    // Getters
    double getX() const;
    double getY() const;

    // Movie management
    void storePopularMovie(Movie* movie);      // Stores a popular movie in the CDNNode
    Movie* fetchMovie(const std::string& movieName);  // Fetches a movie if it's popular
};

#endif // CDNNODE_H