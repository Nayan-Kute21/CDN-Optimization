#include "MainServer.hpp"

// Adds a new movie to the main server
void MainServer::addMovie(const std::string& name, std::string path) {
    // Insert the movie into the library using the movie name as the key
    movieLibrary[name] = Movie(name, path);
}

// Retrieves a movie by name from the main server
Movie* MainServer::getMovie(const std::string& movieName) {
    auto it = movieLibrary.find(movieName);
    if (it != movieLibrary.end()) {
        return &(it->second);  // Return a pointer to the Movie object if found
    }
    return nullptr;  // Return nullptr if the movie is not found
}
const std::vector<Movie*> MainServer::getAllMovies()
{
    std::vector<Movie*> movies;
    for(auto it: movieLibrary)
    {
        movies.push_back(&(it.second));
    }
    return movies;
}