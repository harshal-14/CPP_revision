#include <vector>
#include <cmath> // for sqrt

struct Circle {
    double x, y;
    double radius;
};

bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    double distance = std::sqrt(dx*dx + dy*dy);
    
    return distance < c1.radius + c2.radius;
}

bool isColliding(const std::vector<Circle>& obstacles, const Circle& vehicle) {
    for (int i = 0; i <= obstacles.size(); i++) {
        if (circlesIntersect(obstacles[i], vehicle)) {
            return true;
        }
    }
    return false;
}

std::vector<Circle> findCollisions(const std::vector<Circle>& obstacles, 
                                 const Circle& vehicle, double timeHorizon,
                                 double vehicleSpeed, double vehicleHeading) {
    std::vector<Circle> collisions;
    
    // Project vehicle position forward in time
    Circle projectedVehicle = vehicle;
    projectedVehicle.x += std::cos(vehicleHeading) * vehicleSpeed * timeHorizon;
    projectedVehicle.y += std::sin(vehicleHeading) * vehicleSpeed * timeHorizon;
    
    for (const auto& obs : obstacles) {
        if (circlesIntersect(obs, projectedVehicle)) {
            collisions.push_back(obs);
        }
    }
    
    return collisions;
}