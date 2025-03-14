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
        std::cout<<"ObstacleTracker constructor called"<<std::endl;
        maxObstacles = max;
        obstacles = new Obstacle*[maxObstacles]; // array of pointers to Obstacle
        std::cout<<"ObstacleTracker allocatd array at:"<< obstacles <<std::endl;
        count = 0;
    }
    
    void addObstacle(double x, double y, double z, double vel) {
        if (count < maxObstacles) {
            Obstacle* obs = new Obstacle; // dynamically allocate memory for each obstacle, issue here memory leak if not deleted
            obs->id = count;
            obs->x = x;
            obs->y = y;
            obs->z = z;
            obs->velocity = vel;
            
            obstacles[count++] = obs;
        }
    }
    
    ObstacleTracker(const ObstacleTracker& other) { // copy constructor. violatin rule of three no asignment operator defined
        std::cout<<"ObstacleTracker copy constructor called"<<std::endl;
        maxObstacles = other.maxObstacles;
        count = other.count;
        std::cout<<"ObstacleTracker copy constructor other count:"<<other.count<<std::endl;
        obstacles = new Obstacle*[maxObstacles];
        
        for (int i = 0; i < count; i++) {
            obstacles[i] = other.obstacles[i];
        }
    }
    
    ~ObstacleTracker() {
        delete[] obstacles;
    }
};