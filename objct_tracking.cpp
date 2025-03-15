#include <iostream>

struct Obstacle {
    int id;
    double x, y, z;
    double velocity;
};

class ObstacleTracker {
private:
    Obstacle** obstacles;
    int maxObstacles;
    int count;
    
public:
    ObstacleTracker(int max) {
        std::cout << "ObstacleTracker constructor called" << std::endl;
        maxObstacles = max;
        obstacles = new Obstacle*[maxObstacles]; // array of pointers to Obstacle
        std::cout << "ObstacleTracker allocated array at:" << obstacles << std::endl;
        count = 0;
    }
    
    // Copy constructor
    ObstacleTracker(const ObstacleTracker& other) {
        std::cout << "ObstacleTracker copy constructor called" << std::endl;
        maxObstacles = other.maxObstacles;
        count = other.count;
        std::cout << "ObstacleTracker copy constructor other count:" << other.count << std::endl;
        obstacles = new Obstacle*[maxObstacles];
        
        // Deep copy of obstacles
        for (int i = 0; i < count; i++) {
            obstacles[i] = new Obstacle(*(other.obstacles[i])); // Create new Obstacle with contents of original
        }
    }
    
    // Assignment operator
    ObstacleTracker& operator=(const ObstacleTracker& other) {
        std::cout << "ObstacleTracker assignment operator called" << std::endl;
        if (this != &other) { // Self-assignment check
            // Clean up existing resources
            for (int i = 0; i < count; i++) {
                delete obstacles[i];
            }
            delete[] obstacles;
            
            // Copy from other
            maxObstacles = other.maxObstacles;
            count = other.count;
            obstacles = new Obstacle*[maxObstacles];
            
            // Deep copy of obstacles
            for (int i = 0; i < count; i++) {
                obstacles[i] = new Obstacle(*(other.obstacles[i]));
            }
        }
        return *this;
    }
    
    void addObstacle(double x, double y, double z, double vel) {
        if (count < maxObstacles) {
            Obstacle* obs = new Obstacle;
            obs->id = count;
            obs->x = x;
            obs->y = y;
            obs->z = z;
            obs->velocity = vel;
            
            obstacles[count++] = obs;
        }
    }
    
    ~ObstacleTracker() {
        // Delete each obstacle object
        for (int i = 0; i < count; i++) {
            delete obstacles[i];
        }
        // Then delete the array of pointers
        delete[] obstacles;
    }
};