#include "CDN_Manager.hpp"
#include <filesystem> // For reading files in the directory
#include <string>
#include <iostream>
namespace fs = std::filesystem;

int main() {
    CDNManager manager;

    // Path to the directory containing movie images
    std::string movieDirectoryPath = "path/to/your/movie_images";

    // Reading all movie images from the directory and adding them to the main server
    for (const auto& entry : fs::directory_iterator(movieDirectoryPath)) {
        if (entry.is_regular_file()) {
            std::string movieName = entry.path().stem().string();  // Extract movie name from file name
            std::string imagePath = entry.path().string();          // Full path to the image file
            manager.addMovieToMainServer(movieName, imagePath);
        }
    }

    // Add CDN nodes at specific locations
    manager.addCDNNode(10.0, 10.0);
    manager.addCDNNode(50.0, 50.0);
    manager.addCDNNode(100.0, 100.0);

    // User requests a movie
    std::string requestedMovie = "MovieName"; // Replace with the movie name you want to request
    double userX = 20.0;                      // User's x-coordinate
    double userY = 20.0;                      // User's y-coordinate
    double searchRadius = 30.0;               // Search radius for nearby CDN nodes

    Movie* movie = manager.requestMovie(requestedMovie, userX, userY, searchRadius);

    // Check if the movie was found
    if (movie) {
        std::cout << "Movie fetched: " << movie->getName() << std::endl;
    } else {
        std::cout << "Requested movie is not available." << std::endl;
    }

    return 0;
}
