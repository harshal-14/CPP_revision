/*
Issue in the control flow system and average calculation
*/

class ControlSystem {
    private:
        double* speedHistory;
        int historySize;
        int currentIndex;
        
    public:
        ControlSystem(int size) {
            historySize = size;
            speedHistory = new double[historySize];
            currentIndex = 0;
        }
        
        void recordSpeed(double speed) {
            speedHistory[currentIndex] = speed;
            currentIndex = (currentIndex + 1) % historySize;
        }
        
        double getAverageSpeed() {
            double sum = 0.0;
            
            for (int i = 0; i <= historySize; i++) { //out of bounds error here should be i < historySize
                sum += speedHistory[i];
            }
            
            return sum / historySize; // issue here incorrect avg calculation even if not all historySize elements are filled
        }
        
        ~ControlSystem() {
            delete[] speedHistory;
        }
    };