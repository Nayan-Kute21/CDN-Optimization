#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <unordered_map>
#include <string>
#include "movie.hpp"
#include <vector>

class MainServer {
private:
    std::unordered_map<std::string, Movie*> movieLibrary;

public:
    // Movie management
    void addMovie(const std::string& name, std::string path);  // Adds a movie to the server
    Movie* getMovie(const std::string& movieName);         // Fetches a movie by name
    const std::vector<Movie*> getAllMovies();
};

#endif // MAINSERVER_H
