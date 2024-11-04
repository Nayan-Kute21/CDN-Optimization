#include "CDN_Manager.hpp"
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

// Constructor
CDNManager::CDNManager() {
    // Initialize random seed for selecting random movies
    std::srand(std::time(0));
}

// Destructor
CDNManager::~CDNManager() {
    // Delete all dynamically allocated CDN nodes
    for (auto& [key, node] : cdnNodes) {
        delete node;
    }
}

// Adds a new CDN node at the specified (x, y) coordinates and initializes with random popular movies
void CDNManager::addCDNNode(double x, double y) {
    std::string key = std::to_string(x) + "," + std::to_string(y);  // Unique key based on coordinates
    cdnNodes[key] = new CDNNode(x, y);

    // Initialize CDN node with a few random popular movies
    initializeCDNNodeWithPopularMovies(cdnNodes[key], 3); // Adjust number of movies as needed
}

// Adds a movie to the main server's library
void CDNManager::addMovieToMainServer(const std::string& movieName, std::string imagepath) {
    mainServer.addMovie(movieName, imagepath);
}

// Marks a movie as popular and stores it in all CDN nodes
void CDNManager::markMovieAsPopular(const std::string& movieName) {
    Movie* movie = mainServer.getMovie(movieName);
    if (movie) {
        for (auto& [key, cdnNode] : cdnNodes) {
            cdnNode->storePopularMovie(movie);
        }
    }
}

// Initializes a CDN node with a random selection of popular movies
void CDNManager::initializeCDNNodeWithPopularMovies(CDNNode* cdnNode, int numMovies) {
    const auto& allMovies = mainServer.getAllMovies();  // Assume MainServer has this function
    std::vector<Movie*> randomMovies;

    for (int i = 0; i < numMovies && !allMovies.empty(); ++i) {
        int randomIndex = std::rand() % allMovies.size();
        randomMovies.push_back(allMovies[randomIndex]);
    }

    for (Movie* movie : randomMovies) {
        cdnNode->storePopularMovie(movie);
    }
}

std::string getKeyFromValue(const std::unordered_map<std::string, CDNNode*>& map, const CDNNode* node) {
    for (const auto& pair : map) {
        if (pair.second == node) {
            return pair.first;  // return the key if the value matches
        }
    }
}
// Handles a movie request based on the user's location and radius
Movie* CDNManager::requestMovie(const std::string& movieName, double userX, double userY, double radius) {
    auto nodesInRange = findCDNNodesInRadius(userX, userY, radius);

    // Check each CDN node in range for the requested movie
    while (!nodesInRange.empty()) {
        CDNNode* node = nodesInRange.top();  // Closest node
        nodesInRange.pop();

        Movie* movie = node->fetchMovie(movieName);
        if (movie) {
            return movie;  // Return if found in CDN node
        }

        // Increment request count for the movie in this node
        std::string requestKey = getKeyFromValue(cdnNodes, node) + "_" + movieName;
        requestCount[requestKey]++;

        // If request count exceeds threshold, add movie to this CDN node
        if (requestCount[requestKey] >= requestThreshold) {
            movie = mainServer.getMovie(movieName);
            if (movie) {
                node->storePopularMovie(movie);
                requestCount[requestKey] = 0;  // Reset request count after adding
                return movie;
            }
        }
    }

    // If not found in any CDN node, retrieve from the main server
    return mainServer.getMovie(movieName);
}

// Helper function to find all CDN nodes within a specified radius using a min-heap
std::priority_queue<CDNNode*, std::vector<CDNNode*>, DistanceComparator>
CDNManager::findCDNNodesInRadius(double userX, double userY, double radius) {
    DistanceComparator comp(userX, userY);
    std::priority_queue<CDNNode*, std::vector<CDNNode*>, DistanceComparator> nodesInRange(comp);

    for (auto& [key, node] : cdnNodes) {
        double dx = node->getX() - userX;
        double dy = node->getY() - userY;
        double distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= radius) {
            nodesInRange.push(node);  // Add node to the min-heap if within radius
        }
    }
    return nodesInRange;
}