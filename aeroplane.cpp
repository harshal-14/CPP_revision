#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <cmath>

// Forward declarations
class Sensor;
class NavigationSystem;
class SensorData;

// --------------------------------
// Base Sensor Data class
// --------------------------------
class SensorData {
protected:
    double timestamp;
    std::string sensorId;

public:
    SensorData(double time, const std::string& id) : timestamp(time), sensorId(id) {}
    virtual ~SensorData() = default;
    
    double getTimestamp() const { return timestamp; }
    std::string getSensorId() const { return sensorId; }
    
    virtual void process() = 0;
};

// --------------------------------
// Radar Sensor Data
// --------------------------------
class RadarData : public SensorData {
private:
    std::vector<double> distances;
    std::vector<double> velocities;

public:
    RadarData(double time, const std::string& id) 
        : SensorData(time, id) {}
    
    void addReading(double distance, double velocity) {
        distances.push_back(distance);
        velocities.push_back(velocity);
    }
    
    void process() override {
        std::cout << "Processing radar data from " << sensorId << std::endl;
        // Actual processing logic would go here
    }
    
    size_t getReadingCount() const {
        return distances.size();
    }
};

// --------------------------------
// Base Sensor class
// --------------------------------
class Sensor {
protected:
    std::string id;
    bool isActive;
    double position[3]; // x, y, z coordinates

public:
    Sensor(const std::string& sensorId, double x, double y, double z)
        : id(sensorId), isActive(false) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
    }
    
    virtual ~Sensor() = default;
    
    virtual void initialize() {
        isActive = true;
        std::cout << "Sensor " << id << " initialized" << std::endl;
    }
    
    virtual void shutdown() {
        isActive = false;
        std::cout << "Sensor " << id << " shut down" << std::endl;
    }
    
    virtual std::unique_ptr<SensorData> collectData(double timestamp) = 0;
    
    bool isOperational() const {
        return isActive;
    }
    
    std::string getId() const {
        return id;
    }
};

// --------------------------------
// Radar Sensor
// --------------------------------
class RadarSensor : public Sensor {
private:
    double range;
    double fieldOfView; // in degrees
    
public:
    RadarSensor(const std::string& sensorId, double x, double y, double z, 
                double maxRange, double fov)
        : Sensor(sensorId, x, y, z), range(maxRange), fieldOfView(fov) {}
        
    void initialize() override {
        Sensor::initialize();
        std::cout << "Radar sensor calibrating..." << std::endl;
        // Specific radar initialization
    }
    
    std::unique_ptr<SensorData> collectData(double timestamp) override {
        if (!isActive) {
            return nullptr;
        }
        
        auto data = std::make_unique<RadarData>(timestamp, id);
        
        // Simulate collecting some data
        for (int i = 0; i < 10; i++) {
            double randomDistance = (rand() % 100) * range / 100.0;
            double randomVelocity = (rand() % 60) - 30.0; // -30 to 30
            data->addReading(randomDistance, randomVelocity);
        }
        
        return data;
    }
};

// --------------------------------
// Camera Sensor Data
// --------------------------------
class CameraData : public SensorData {
private:
    unsigned char* imageBuffer;
    size_t width;
    size_t height;
    
public:
    CameraData(double time, const std::string& id, size_t w, size_t h) 
        : SensorData(time, id), width(w), height(h) {
        // Allocate buffer for image data
        imageBuffer = new unsigned char[width * height * 3]; // RGB format
    }
    
    ~CameraData() override {
        delete[] imageBuffer;
    }
    
    // Deep copy constructor (Rule of Three/Five)
    CameraData(const CameraData& other)
        : SensorData(other.timestamp, other.sensorId), 
          width(other.width), height(other.height) {
        imageBuffer = new unsigned char[width * height * 3];
        memcpy(imageBuffer, other.imageBuffer, width * height * 3);
    }
    
    // Move constructor
    CameraData(CameraData&& other) noexcept
        : SensorData(other.timestamp, other.sensorId),
          width(other.width), height(other.height),
          imageBuffer(other.imageBuffer) {
        other.imageBuffer = nullptr;
        other.width = 0;
        other.height = 0;
    }
    
    // Prevent assignment for simplicity
    CameraData& operator=(const CameraData&) = delete;
    CameraData& operator=(CameraData&&) = delete;
    
    unsigned char* getBuffer() { return imageBuffer; }
    
    void process() override {
        std::cout << "Processing camera image " << width << "x" << height 
                  << " from " << sensorId << std::endl;
        // Image processing would go here
    }
};

// --------------------------------
// Camera Sensor
// --------------------------------
class CameraSensor : public Sensor {
private:
    size_t resolution[2]; // width, height
    
public:
    CameraSensor(const std::string& sensorId, double x, double y, double z,
                size_t width, size_t height)
        : Sensor(sensorId, x, y, z) {
        resolution[0] = width;
        resolution[1] = height;
    }
    
    std::unique_ptr<SensorData> collectData(double timestamp) override {
        if (!isActive) {
            return nullptr;
        }
        
        auto data = std::make_unique<CameraData>(timestamp, id, 
                                                resolution[0], resolution[1]);
        
        // Simulate filling image buffer with random data
        unsigned char* buffer = data->getBuffer();
        for (size_t i = 0; i < resolution[0] * resolution[1] * 3; i++) {
            buffer[i] = rand() % 256;
        }
        
        return data;
    }
};

// --------------------------------
// Navigation System
// --------------------------------
class NavigationSystem {
private:
    double position[3]; // lat, lon, altitude
    double velocity[3]; // vx, vy, vz
    double heading;     // in degrees
    
public:
    NavigationSystem() : heading(0.0) {
        for (int i = 0; i < 3; i++) {
            position[i] = 0.0;
            velocity[i] = 0.0;
        }
    }
    
    void updatePosition(double lat, double lon, double alt) {
        position[0] = lat;
        position[1] = lon;
        position[2] = alt;
    }
    
    void updateVelocity(double vx, double vy, double vz) {
        velocity[0] = vx;
        velocity[1] = vy;
        velocity[2] = vz;
    }
    
    void setHeading(double newHeading) {
        heading = newHeading;
    }
    
    double* getPosition() { return position; }
    double* getVelocity() { return velocity; }
    double getHeading() const { return heading; }
    
    double getGroundSpeed() const {
        return std::sqrt(velocity[0] * velocity[0] + velocity[1] * velocity[1]);
    }
};

// --------------------------------
// Obstacle
// --------------------------------
class Obstacle {
private:
    double position[3];
    double velocity[3];
    double radius;
    
public:
    Obstacle(double x, double y, double z, double r) : radius(r) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        
        for (int i = 0; i < 3; i++) {
            velocity[i] = 0.0;
        }
    }
    
    void setVelocity(double vx, double vy, double vz) {
        velocity[0] = vx;
        velocity[1] = vy;
        velocity[2] = vz;
    }
    
    double* getPosition() { return position; }
    double* getVelocity() { return velocity; }
    double getRadius() const { return radius; }
    
    void update(double deltaTime) {
        for (int i = 0; i < 3; i++) {
            position[i] += velocity[i] * deltaTime;
        }
    }
};

// --------------------------------
// Collision Avoidance System
// --------------------------------
class CollisionAvoidanceSystem {
private:
    std::vector<Obstacle> trackedObstacles;
    
public:
    void updateObstacles(const std::vector<std::unique_ptr<SensorData>>& sensorData) {
        // Process sensor data to update obstacle list
        // This would extract object information from various sensors
        
        // For demonstration, just process each data
        for (const auto& data : sensorData) {
            data->process();
        }
    }
    
    bool detectCollision(const NavigationSystem& nav, double timeHorizon) {
        // Project aircraft position
        double* position = nav.getPosition();
        double* velocity = nav.getVelocity();
        
        for (auto& obstacle : trackedObstacles) {
            double* obsPos = obstacle.getPosition();
            double* obsVel = obstacle.getVelocity();
            
            // Calculate relative positions at future time
            double futureDist = 0.0;
            for (int i = 0; i < 3; i++) {
                double relPos = (position[i] + velocity[i] * timeHorizon) - 
                               (obsPos[i] + obsVel[i] * timeHorizon);
                futureDist += relPos * relPos;
            }
            futureDist = std::sqrt(futureDist);
            
            // Check if distance is less than safety threshold
            if (futureDist < obstacle.getRadius() + 50.0) { // 50m safety buffer
                return true;
            }
        }
        
        return false;
    }
    
    void addObstacle(const Obstacle& obstacle) {
        trackedObstacles.push_back(obstacle);
    }
    
    size_t getObstacleCount() const {
        return trackedObstacles.size();
    }
};

// --------------------------------
// Main Airplane Class
// --------------------------------
class Airplane {
private:
    std::string callSign;
    NavigationSystem navSystem;
    CollisionAvoidanceSystem collisionSystem;
    std::vector<std::unique_ptr<Sensor>> sensors;
    
public:
    explicit Airplane(const std::string& id) : callSign(id) {}
    
    void addSensor(std::unique_ptr<Sensor> sensor) {
        sensors.push_back(std::move(sensor));
    }
    
    void initialize() {
        std::cout << "Initializing airplane " << callSign << std::endl;
        
        // Initialize all sensors
        for (auto& sensor : sensors) {
            sensor->initialize();
        }
    }
    
    void updateSystems(double deltaTime) {
        // Collect data from all sensors
        std::vector<std::unique_ptr<SensorData>> allSensorData;
        double currentTime = 0.0; // In a real system, this would be actual time
        
        for (auto& sensor : sensors) {
            if (sensor->isOperational()) {
                auto data = sensor->collectData(currentTime);
                if (data) {
                    allSensorData.push_back(std::move(data));
                }
            }
        }
        
        // Update collision avoidance system with sensor data
        collisionSystem.updateObstacles(allSensorData);
        
        // Check for potential collisions
        if (collisionSystem.detectCollision(navSystem, 30.0)) { // 30 sec lookahead
            std::cout << "COLLISION WARNING! Evasive action required." << std::endl;
            // Implement collision avoidance logic
        }
    }
    
    void setPosition(double lat, double lon, double altitude) {
        navSystem.updatePosition(lat, lon, altitude);
    }
    
    void setVelocity(double vx, double vy, double vz) {
        navSystem.updateVelocity(vx, vy, vz);
    }
    
    NavigationSystem& getNavSystem() {
        return navSystem;
    }
    
    void shutdown() {
        std::cout << "Shutting down airplane " << callSign << std::endl;
        
        // Shutdown all sensors in reverse order
        for (auto it = sensors.rbegin(); it != sensors.rend(); ++it) {
            (*it)->shutdown();
        }
    }
};

// Example of use
int main() {
    // Create an airplane
    Airplane airplane("AAL123");
    
    // Add sensors
    airplane.addSensor(std::make_unique<RadarSensor>("RADAR1", 0, 0, 0, 100.0, 120.0));
    airplane.addSensor(std::make_unique<CameraSensor>("CAM1", 1, 0, 0, 1920, 1080));
    
    // Initialize systems
    airplane.initialize();
    
    // Set position and velocity
    airplane.setPosition(37.7749, -122.4194, 10000); // San Francisco coordinates, 10000ft
    airplane.setVelocity(250, 0, 0); // 250 m/s eastward
    
    // Update systems
    for (int i = 0; i < 3; i++) {
        std::cout << "Update cycle " << (i+1) << std::endl;
        airplane.updateSystems(1.0); // 1 second timestep
    }
    
    // Shutdown
    airplane.shutdown();
    
    return 0;
}