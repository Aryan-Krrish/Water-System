#define HUMIDITY_SENSOR A0
#define LIGHT_SENSOR A2       // LDR connected to A2
#define ULTRASONIC_PIN A3     // Grove ultrasonic sensor connected to A3

#define MOTOR_PIN 9
#define LED_MOTOR_ON 3
#define LED_MOTOR_OFF 4

#define BUZZER_PIN 13
#define LED_DAYNIGHT 6        // LED ON when bright (inverted logic)

int humidityThresholdLow = 200;
int humidityThresholdHigh = 400;
int lightThreshold = 600;

bool motorOverride = false;
bool motorState = false;

bool lightOverride = false;
bool lightState = false;

bool buzzerOverride = false;
bool buzzerState = false;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 1000;  // Send data every 1 second

void setup() {
    pinMode(HUMIDITY_SENSOR, INPUT);
    pinMode(LIGHT_SENSOR, INPUT);

    pinMode(MOTOR_PIN, OUTPUT);
    pinMode(LED_MOTOR_ON, OUTPUT);
    pinMode(LED_MOTOR_OFF, OUTPUT);

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_DAYNIGHT, OUTPUT);

    Serial.begin(9600);   // USB serial monitor
        Serial1.begin(9600);  // HC-05 serial communication
    randomSeed(analogRead(0));  // Random seed for buzzer tones

    Serial.println("System ready.");
}

void loop() {
    // --- Bluetooth Command Handling ---
    if (Serial1.available()) {
        char cmd = Serial1.read();

        Serial.print("Received command: ");
        Serial.println(cmd);

        switch (cmd) {
            case '1': motorOverride = true;  motorState = true;  break;
            case '2': motorOverride = true;  motorState = false; break;
            case '3': motorOverride = false; break;

            case '4': lightOverride = true;  lightState = true;  break;
            case '5': lightOverride = true;  lightState = false; break;
            case '6': lightOverride = false; break;

            case '7': buzzerOverride = true;  buzzerState = true;  break;
            case '8': buzzerOverride = true;  buzzerState = false; break;
            case '9': buzzerOverride = false; break;
        }
    }

    // --- Humidity Reading and Motor Control ---
    int humidityValue = analogRead(HUMIDITY_SENSOR);
    Serial.print("Humidity: ");
    Serial.println(humidityValue);

    if (motorOverride) {
        digitalWrite(MOTOR_PIN, motorState ? HIGH : LOW);
        digitalWrite(LED_MOTOR_ON, motorState ? HIGH : LOW);
        digitalWrite(LED_MOTOR_OFF, motorState ? LOW : HIGH);
    } else {
        if (humidityValue < humidityThresholdLow) {
            digitalWrite(MOTOR_PIN, HIGH);
            digitalWrite(LED_MOTOR_ON, HIGH);
            digitalWrite(LED_MOTOR_OFF, LOW);
        } else {
            digitalWrite(MOTOR_PIN, LOW);
            digitalWrite(LED_MOTOR_ON, LOW);
            digitalWrite(LED_MOTOR_OFF, HIGH);
        }
    }

    delay(50);

    // --- Ultrasonic Sensor (Grove, A3) ---
    pinMode(ULTRASONIC_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_PIN, LOW);

    pinMode(ULTRASONIC_PIN, INPUT);
    long duration = pulseIn(ULTRASONIC_PIN, HIGH, 30000);
    float distance = duration * 0.017;  // Speed of sound (cm/us) / 2

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // --- Buzzer Control ---
    if (buzzerOverride) {
        if (buzzerState) {
            tone(BUZZER_PIN, 2000); // buzzer ON manual
        } else {
            noTone(BUZZER_PIN);
        }
    } else {
        if (distance > 0 && distance < 50) {
            int frequency = random(1000, 4000);
            tone(BUZZER_PIN, frequency);
            delay(500);
            noTone(BUZZER_PIN);
            delay(500);
        } else {
            noTone(BUZZER_PIN);
        }
    }

    // --- Light Sensor and Day/Night LED ---
    int lightValue = analogRead(LIGHT_SENSOR);
    Serial.print("Light: ");
    Serial.println(lightValue);

    if (lightOverride) {
        digitalWrite(LED_DAYNIGHT, lightState ? HIGH : LOW);
    } else {
        if (lightValue >= lightThreshold) {
            digitalWrite(LED_DAYNIGHT, HIGH);  // BRIGHT
        } else {
            digitalWrite(LED_DAYNIGHT, LOW);   // DARK
        }
    }

    // --- Send data via Bluetooth every second ---
    if (millis() - lastSendTime >= sendInterval) {
        lastSendTime = millis();
        Serial1.print("H:");
        Serial1.print(humidityValue);
        Serial1.print(" L:");
        Serial1.print(lightValue);
        Serial1.print(" D:");
        Serial1.print(distance);
        Serial1.println("cm");
    }
}
