#include "Movie.hpp"

Movie::Movie()
{
}
// Constructor to initialize a Movie object with a name and a poster image path
Movie::Movie(const std::string& name, std::string path)
    : name(name), image_path(path) {}

// Returns the name of the movie
std::string Movie::getName() const {
    return name;
}

// Returns the pointer to the movie's poster
std::string Movie::getPoster() const {
    return image_path;
}