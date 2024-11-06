#include "CDN_Node.hpp"
#include "Movie.hpp"
#include <iostream>

// Constructor
CDNNode::CDNNode(double x, double y, int skipListMaxLevel, float skipListProbability)
    : x(x), y(y), popularMovies(skipListMaxLevel, skipListProbability) {}

// Getters
double CDNNode::getX() const {
    return x;
}

double CDNNode::getY() const {
    return y;
}

// Stores a popular movie in the CDN node's skip list
void CDNNode::storePopularMovie(Movie* movie) {
        popularMovies.insert(movie);
        // std::cout << "Stored popular movie: " << movie->getName() << " in CDN node (" << x << ", " << y << ")\n";
}

// Fetches a movie if it's in the CDN node's popular movie list
Movie* CDNNode::fetchMovie(const std::string& movieName) {
    return popularMovies.search(movieName);
}

// Retrieves names of all movies in the CDN node's skip list
std::vector<std::string> CDNNode::get_movie_names() {
    return popularMovies.getAllNames();
}

// Checks if the skip list has reached a maximum capacity (for example, 10 movies in this case)
bool CDNNode::isFull() {
    return popularMovies.getsize() >= 10;  // Assuming max capacity is 10 movies
}

void CDNNode::remove_mov(const std::string& moviename)
{
    popularMovies.remove(moviename);
}