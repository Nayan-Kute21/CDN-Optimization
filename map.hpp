#ifndef CDN_MAP_H
#define CDN_MAP_H

#include <map>
#include <vector>
#include "CDN_Node.hpp" // Include the CDNNode header

using namespace std; // Using namespace std

// Class representing a map of CDN nodes
class CDNMap {
private:
    map<pair<double, double>, CDN_Node> nodes; // Map to store CDN nodes

public:
    // Method to add a CDN node to the map
    void addNode(double x, double y, const string& data);
    // Method to delete a CDN Node from the map
    bool deleteNode(double x, double y);
    // Method to search for nodes within a specified radius
    vector<CDN_Node> searchNodes(double queryX, double queryY, double radius);
};

#endif // CDN_MAP_H