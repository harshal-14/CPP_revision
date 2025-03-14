#include <iostream>

/*
Memory management issue
*/
class VehicleSensor {
    private:
        double* data;
        int size;
        
    public:
        VehicleSensor(int dataSize) {
            size = dataSize;
            data = new double[size];
            for (int i = 0; i < size; i++) {
                data[i] = 0.0;
            }
        }
        
        void updateData(double* newData, int newSize) {
            // Discard old data and use new data
            data = newData; // issue here call update data without freeing old memory data ws earlier pointing to.
            size = newSize; 
        }
        
        double getAverage() {
            double sum = 0.0;
            for (int i = 0; i < size; i++) {
                sum += data[i];
            }
            return sum / size; // Issue here if size is 0
        }
        
        ~VehicleSensor() {
            delete[] data;
        }
    };
    
    // Usage
    void processSensorData() {
        VehicleSensor* sensor = new VehicleSensor(10);
        double* newReadings = new double[20];
        
        for (int i = 0; i < 20; i++) {
            newReadings[i] = i * 0.5;
        }
        
        sensor->updateData(newReadings, 20);
        
        double avg = sensor->getAverage();
        std::cout << "Average reading: " << avg << std::endl;
        
        delete sensor; // memory leak here, sensor is getting delete but newReadings also pointing to data so double delete happening, use unique ptr and vector to avoid this issue.
    }