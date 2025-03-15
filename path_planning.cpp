# include <vector>
#include <cmath> // for sqrt


struct Point {
    double x, y;
};

// Calculate distance between two points (extracted as utility function)
double calculateDistance(const Point& p1, const Point& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return std::sqrt(dx*dx + dy*dy);
}

double calculatePathLength(const std::vector<Point>& path) {
    double length = 0.0;
    
    // Handle empty paths or single point paths
    if (path.size() <= 1) {
        return 0.0;
    }
    
    // Use size_t to match the return type of size()
    for (size_t i = 0; i < path.size() - 1; i++) {
        length += calculateDistance(path[i], path[i+1]);
    }
    
    return length;
}

std::vector<Point> optimizePath(const std::vector<Point>& originalPath, double minDistance = 1.0) {
    std::vector<Point> optimized;
    
    // Handle empty paths
    if (originalPath.empty()) {
        return optimized;
    }
    
    // Add first point
    optimized.push_back(originalPath[0]);
    
    // Skip points that are too close to each other
    for (size_t i = 1; i < originalPath.size(); i++) {
        double distance = calculateDistance(originalPath[i], optimized.back());
        
        if (distance > minDistance) {
            optimized.push_back(originalPath[i]);
        }
    }
    
    // Always include the last point if it's not already included and the original has more than one point
    if (originalPath.size() > 1 && 
        (optimized.back().x != originalPath.back().x || optimized.back().y != originalPath.back().y)) {
        optimized.push_back(originalPath.back());
    }
    
    return optimized;
}