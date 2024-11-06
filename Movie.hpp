#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
    std::string image_path;  // path of movie poster
    std::string name;   // movie name

public:
    // Constructor
    Movie();
    Movie(const std::string& name, std::string path);

    // Getters
    std::string getName() const;
    std::string getPoster() const;
};

#endif // MOVIE_H
