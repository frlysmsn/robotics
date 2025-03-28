#define in1 16   // GPIO16
#define in2 17   // GPIO17
#define in3 18   // GPIO18
#define in4 19   // GPIO19
#define EnA 5    // GPIO5 (PWM)
#define EnB 4    // GPIO4 (PWM)

#define IR_LEFT 34   // GPIO34 (Input Only)
#define IR_RIGHT 35  // GPIO35 (Input Only)

// Define PWM channels
#define PWM_A_CHANNEL  0
#define PWM_B_CHANNEL  1
#define PWM_FREQ  1000  // 1 kHz frequency
#define PWM_RES   8     // 8-bit resolution

void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);
    
    // Configure PWM
    ledcSetup(PWM_A_CHANNEL, PWM_FREQ, PWM_RES);
    ledcSetup(PWM_B_CHANNEL, PWM_FREQ, PWM_RES);
    
    // Attach PWM channels to motor enable pins
    ledcAttachPin(EnA, PWM_A_CHANNEL);
    ledcAttachPin(EnB, PWM_B_CHANNEL);
    
    ledcWrite(PWM_A_CHANNEL, 100); // Set initial speed
    ledcWrite(PWM_B_CHANNEL, 100);
    
    stopMotors();
    delay(1000);
}

void loop() {
    int leftSensor = digitalRead(IR_LEFT);
    int rightSensor = digitalRead(IR_RIGHT);

    if (leftSensor == 0 && rightSensor == 0) {
        forward();
    } else if (leftSensor == 0 && rightSensor == 1) {
        turnRight();
    } else if (leftSensor == 1 && rightSensor == 0) {
        turnLeft();
    } else {
        stopMotors();
    }
}

void forward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnRight() {
    ledcWrite(PWM_A_CHANNEL, 100); 
    ledcWrite(PWM_B_CHANNEL, 150);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnLeft() {
    ledcWrite(PWM_A_CHANNEL, 150); 
    ledcWrite(PWM_B_CHANNEL, 100);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void stopMotors() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}