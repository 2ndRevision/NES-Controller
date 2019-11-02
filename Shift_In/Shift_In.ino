// For more like this follow us on Instagram @2ndRevsion
// Or look for us on YouTube, 2ndRevision

// Define pins
#define LATCH_PIN 2 // Orange 
#define DATA_PIN  3 // Yellow
#define CLOCK_PIN 4 // Red

#define RESET_INDEX B00000001


// The register that we will be reading into
byte controller1 = 0;
byte temp = 0;
byte index = 0;

// One shot flag
byte flag = false;

void setup() {
  // Start UART coms with the computer
  Serial.begin(9600);

  // Define pin modes
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  // Initialize Pins
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  delay(500);
}

void loop() {
  // Asynchronously read in all parrallel inputs
  digitalWrite(LATCH_PIN, HIGH);
  delay(5);
  // Latch in Serial read output.
  // First shift is already available (A Button)
  digitalWrite(LATCH_PIN, LOW);

  // Reset our register
  controller1 = 0;
  index = RESET_INDEX;

  // Loop through bit shift from NES Controller
  while(index != B00000000){
    
    // Shift last round of received bit to the left
    controller1 = (controller1 << 1);
    
    // Read in the new bit
    temp = digitalRead(DATA_PIN);
    
    // OR the new bit with the other received bits into the LSB
    controller1 = controller1 | (temp & B00000001);

    // Clock the shift register to prepare for new bit
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(2);
    digitalWrite(CLOCK_PIN, LOW);

    // Increment the index
    index = (index << 1);
  }

  if ((~controller1) & B10000000){
    Serial.println("A Button pressed");
    //flag = true;
  }
  if ((~controller1) & B01000000){
    Serial.println("B Button pressed");
    //flag = true;
  }
  if ((~controller1) & B00100000){
    Serial.println("Select Button pressed");
    //flag = true;
  }
  if ((~controller1) & B00010000){
    Serial.println("Start Button pressed");
    //flag = true;
  }
  if ((~controller1) & B00001000){
    Serial.println("Up Button pressed");
    //flag = true;
  }
  if ((~controller1) & B00000100){
    Serial.println("Down Button pressed");
    //flag = true;
  }
  if ((~controller1) & B00000010){
    Serial.println("Left Button pressed");
    //flag = true;
  }
  if ((~controller1) & B00000001){
    Serial.println("Right Button pressed");
    //flag = true;
  }
}
