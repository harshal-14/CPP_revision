#include <iostream>
#include <cmath>
#include <mutex>

class VehicleState {
    private:
        double position[3];  // x, y, z
        double velocity[3];  // vx, vy, vz
        std::mutex mutex;
        
    public:
        VehicleState() {
            // Initialize to zeros
            for (int i = 0; i < 3; i++) {
                position[i] = 0.0;
                velocity[i] = 0.0;
            }
        }
        
        void updatePosition(double x, double y, double z) {
            std::lock_guard<std::mutex> lock(mutex);
            position[0] = x;
            position[1] = y;
            position[2] = z;
        }
        
        void updateVelocity(double vx, double vy, double vz) {
            std::lock_guard<std::mutex> lock(mutex);
            velocity[0] = vx;
            velocity[1] = vy;
            velocity[2] = vz;
        }
        
        // Return a copy of the position data, not a reference
        std::array<double, 3> getPosition() {
            std::lock_guard<std::mutex> lock(mutex);
            return {position[0], position[1], position[2]};
        }
        
        // Return a copy of the velocity data, not a reference
        std::array<double, 3> getVelocity() {
            std::lock_guard<std::mutex> lock(mutex);
            return {velocity[0], velocity[1], velocity[2]};
        }
        
        double calculateSpeed() {
            std::lock_guard<std::mutex> lock(mutex);
            return sqrt(velocity[0]*velocity[0] + 
                       velocity[1]*velocity[1] + 
                       velocity[2]*velocity[2]);
        }
    };