/* ptr problems*/

struct LanePoint {
    double x, y;
};

class LaneDetector {
private:
    LanePoint* leftLane;
    LanePoint* rightLane;
    int pointCount;
    
public:
    LaneDetector(int count) {
        pointCount = count;
        leftLane = new LanePoint[pointCount]; 
        rightLane = new LanePoint[pointCount];
    }
    
    LanePoint* getLeftLane() {
        return leftLane; // dangling ptr issue if not handled properly
    }
    
    LanePoint* getRightLane() {
        return rightLane; // dangling ptr issue if not handled properly
    }
    
    void processImage(const unsigned char* imageData) {
        // Simulate lane detection
        for (int i = 0; i < pointCount; i++) {
            leftLane[i].x = i * 0.1;
            leftLane[i].y = -1.0 + (i * 0.01);
            
            rightLane[i].x = i * 0.1;
            rightLane[i].y = 1.0 - (i * 0.01);
        }
    }
    
    ~LaneDetector() {
        delete leftLane; //issue here delete[] should be used as leftLane is an array
        delete rightLane; // same here
    }
};

/* 
solution could be instread of raw pointers use vector for safe getters and copy constructor to create deep copy with assignment operators 
*/