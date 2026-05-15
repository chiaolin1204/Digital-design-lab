// 共陽極數組：0 代表亮，1 代表滅
byte seven_seg_digits[10][7] = { 
  { 0,0,0,0,0,0,1 }, // 0
  { 1,0,0,1,1,1,1 }, // 1
  { 0,0,1,0,0,1,0 }, // 2
  { 0,0,0,0,1,1,0 }, // 3
  { 1,0,0,1,1,0,0 }, // 4
  { 0,1,0,0,1,0,0 }, // 5
  { 0,1,0,0,0,0,0 }, // 6
  { 0,0,0,1,1,1,1 }, // 7
  { 0,0,0,0,0,0,0 }, // 8
  { 0,0,0,0,1,0,0 }  // 9
};

const int buttonPin = 12;
int lastButtonState = HIGH; 
int num = 0;

void setup() {
  Serial.begin(9600);
  
  // 設定 Pin 2~8 為輸出
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); // 共陽極初始化：先讓所有段位熄滅
  }

  pinMode(buttonPin, INPUT_PULLUP);
  
  // 剛開始顯示 0
  sevenSegWrite(num);
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);
    ++pin;
  }
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // 偵測按鈕被按下的那一瞬間 (從 HIGH 變 LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    num++;
    if (num > 9) {
      num = 0;
    }
    
    sevenSegWrite(num); 
    ///Serial.print("目前數字: ");
    Serial.println(num);
    
    delay(1000); // 防彈跳延遲
  }

  lastButtonState = buttonState; 
}