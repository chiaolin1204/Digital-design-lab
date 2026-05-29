// 1. 宣告變數與腳位陣列 (對應黑板第一行)
// 使用陣列將腳位 2 到 11 儲存起來，總共 10 顆 LED
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
const int numPins = 10; // LED 的總數量
const int sensorPin = A0; // 類比感測器接在 A0

void setup() {
  // 設定所有的 LED 腳位為輸出模式 (OUTPUT)
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // 2. 讀取類比訊號 (對應黑板第二行)
  int sensorRead = analogRead(sensorPin); // 讀取值範圍通常是 0 ~ 1023

  // 3. 數值映射 (對應黑板第三行)
  // 將 0~1023 的數值等比例轉換為 0~10 (對應要亮起的 LED 數量)
  int ledBar = map(sensorRead, 0, 1023, 0, 10);

  // 呼叫自訂函式來控制 LED 的亮滅
  ledControl(ledBar);
}

// 4. 自訂函式：控制 LED 亮起的數量 (對應黑板最後的 function)
void ledControl(int led_number) {
  // 迴圈跑過每一顆 LED
  for (int i = 0; i < numPins; i++) {
    // 如果當前的索引值小於應亮起的數量，就點亮它
    if (i < led_number) {
      digitalWrite(ledPins[i], HIGH);
    } 
    // 否則，就把它熄滅
    else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}