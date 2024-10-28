#include "map.hpp"
#include <cmath> // Include for sqrt and pow

// Method to add a CDN node to the map
void CDNMap::addNode(double x, double y, const string& data) {
    nodes[{x, y}] = CDN_Node(x, y, data);
}

// Method to search for nodes within a specified radius
vector<CDN_Node> CDNMap::searchNodes(double queryX, double queryY, double radius) {
    vector<CDN_Node> result;
    for (const auto& entry : nodes) {
        double distance = sqrt(pow(entry.second.x - queryX, 2) + pow(entry.second.y - queryY, 2));
        if (distance <= radius) {
            result.push_back(entry.second);
        }
    }
    return result;
}

// Method to delete a CDN node from the map
bool CDNMap::deleteNode(double x, double y) {
    auto it = nodes.find({x, y});
    if (it != nodes.end()) {
        nodes.erase(it);
        return true; // Node successfully deleted
    }
    return false; // Node not found
}