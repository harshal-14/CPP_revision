/*
Inheritance issues
*/

#include <iostream>

class Sensor {
    public:
        virtual void initialize() {
            std::cout << "Sensor initializing" << std::endl;
        }
        
        void calibrate() {
            std::cout << "Sensor calibrating" << std::endl;
        }
        
        virtual double getReading() {
            return 0.0;
        }
        
        virtual ~Sensor() { // should be virtual destructor with virtual keyword over here
            std::cout << "Sensor destructor" << std::endl;
        }
    };
    
    class LidarSensor : public Sensor {
    private:
        double* pointCloud;
        int size;
        
    public:
        LidarSensor(int cloudSize) {
            size = cloudSize;
            pointCloud = new double[size * 3]; // x, y, z for each point, initialized but never filled with data values
        }
        
        void initialize() { // override keyword should have been there
            std::cout << "LidarSensor initializing" << std::endl;
            // Initialize hardware
        }
        
        double getReading() {
            // Return average distance
            return 42.0;
        }
        
        ~LidarSensor() override { // use override for destructor 
            delete[] pointCloud;
            std::cout << "LidarSensor destructor" << std::endl;
        }
    };
    
    void useSensor() {
        Sensor* sensor = new LidarSensor(100);
        sensor->initialize();
        sensor->calibrate();
        std::cout << "Reading: " << sensor->getReading() << std::endl;
        delete sensor;
    }