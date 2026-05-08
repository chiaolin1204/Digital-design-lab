
int pin=13;
void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin, OUTPUT);
  pinMode(12, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(pin, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(12, LOW); 
  delay(500);                      // wait for a second
  digitalWrite(pin, LOW);  
  digitalWrite(12, HIGH);  // turn the LED off by making the voltage LOW
  delay(500);                      // wait for a second
}// put your setup code here, to run once:



