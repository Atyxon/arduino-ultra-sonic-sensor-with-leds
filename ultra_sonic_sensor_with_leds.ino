class LED_Controlls{
  //Class responsible for controlling LEDS
  private:
    const int ledGreenPin = 9; // Declaration of constant variable for green LED pin
    const int ledYellowPin = 10; // Declaration of constant variable for yellow LED pin
    const int ledRedPin = 11; // Declaration of constant variable for red LED pin

  public:
    void SetupLeds(){
      // Set mode for all of LED pins
      // This cannot be executed in class constructor because LEDS would work incorrectly
      pinMode(ledGreenPin, OUTPUT);
      pinMode(ledYellowPin, OUTPUT);
      pinMode(ledRedPin, OUTPUT);
    }
    void SetLedGreen(){
      // Enable green LED and disable the remaining LEDS
      digitalWrite(ledGreenPin, HIGH);
      digitalWrite(ledYellowPin, LOW);
      digitalWrite(ledRedPin, LOW);
    }
    void SetLedYellow(){
      // Enable yellow LED and disable the remaining LEDS
      digitalWrite(ledGreenPin, LOW);
      digitalWrite(ledYellowPin, HIGH);
      digitalWrite(ledRedPin, LOW);
    }
    void SetLedRed(){
      // Enable red LED and disable the remaining LEDS
      digitalWrite(ledGreenPin, LOW);
      digitalWrite(ledYellowPin, LOW);
      digitalWrite(ledRedPin, HIGH);
    }
    void SetLedNone(){
      // Disable all LEDS
      digitalWrite(ledGreenPin, LOW);
      digitalWrite(ledYellowPin, LOW);
      digitalWrite(ledRedPin, LOW);
    }
};

LED_Controlls ledController;  // Create instance of LED controller
const int triggerPin = 2; // Declaration of constant variable for ultra sonic sensor trigger pin
const int echoPin = 4; // Declaration of constant variable for ultra sonic sensor echo pin

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(triggerPin, OUTPUT);  // Set trigger pin to output mode
  pinMode(echoPin, INPUT);  // Set echo pin to input mode
  ledController.SetupLeds();  // Setup LEDS modes
}

void loop() {
  long duration, distance;  // Declare duration in [μs] and distance in [cm] variables
  
  digitalWrite(triggerPin, HIGH); // Set trigger pin HIGH to trigger sensor
  delayMicroseconds(10);  // Wait for 10μs to start the ranging
  digitalWrite(triggerPin, LOW);  // Start ranging
  
  duration = pulseIn(echoPin, HIGH);  // Measure pulse duration time in [μs]
  distance = convertToDistance(duration);  // Convert duration time in [μs] into a distance in [cm]

  // Controlling LEDS according to distance
  if(distance <= 5)
    ledController.SetLedRed();
  else if(distance > 5 && distance <= 10)  
    ledController.SetLedYellow();
  else if(distance > 10 && distance <= 15)
    ledController.SetLedGreen();
  else if(distance > 15)
    ledController.SetLedNone();

  Serial.println(String(distance) + "cm");  // Printing distance in [cm] in serial monitor
  delay(100); // Waiting for 100ms to prevent trigger signal to the echo signal
}

long convertToDistance(long microseconds) {
  // Speed of sound is 29 microseconds per centimeter.
  // Ultra sonic signal travels out and back, so to find the distance of the object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
