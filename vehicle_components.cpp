class Vehicle {
    public:
        double speed;
        double position;
        
        Vehicle() {
            speed = 0.0;
            position = 0.0;
        }
        
        virtual ~Vehicle() {} // Add virtual destructor
        
        virtual void update(double deltaTime) {
            position += speed * deltaTime;
        }
    };
    
    class AutonomousVehicle : public Vehicle {
    private:
        double targetSpeed;
        
    public:
        AutonomousVehicle() {
            targetSpeed = 0.0;
        }
        
        void setTargetSpeed(double target) {
            targetSpeed = target;
        }
        
        void update(double deltaTime) override { // Fixed override syntax
            // Adjust speed toward target
            if (speed < targetSpeed) {
                speed += 2.0 * deltaTime;
                if (speed > targetSpeed) speed = targetSpeed;
            } else if (speed > targetSpeed) {
                speed -= 2.0 * deltaTime;
                if (speed < targetSpeed) speed = targetSpeed;
            }
            
            // Call base class update instead of duplicating code
            Vehicle::update(deltaTime);
        }
    };