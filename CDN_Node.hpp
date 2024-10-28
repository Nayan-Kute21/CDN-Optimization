#ifndef CDN_NODE_H
#define CDN_NODE_H

#include <string>

using namespace std; // Using namespace std

// Class representing a CDN node
class CDN_Node {
public:
    double x; // X coordinate
    double y; // Y coordinate
    string data; // Placeholder for data associated with the node

    // Constructor to initialize the CDN node
    CDN_Node(double x, double y, const string& data);
};

#endif // CDN_NODE_H