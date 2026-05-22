#include "pitches.h"

// 定義 7 顆 LED 接的 Pin 腳（避開 Pin 9）
const int ledPins[7] = {2, 3, 4, 5, 6, 7, 8}; 
const int buzzerPin = 10; // 蜂鳴器改接 Pin 9

// 原本的 8 個音符與節奏
int melody[] = {
  NOTE_B3, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_B3, 0, NOTE_B3, NOTE_B3
};
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};

// 8 個音符，控制 7 顆 LED
int LEDcontrol[8][7] = {
  {0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1}
};

void setup() {
  // 初始化 7 顆 LED 的 Pin 腳為輸出模式
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // 開始播放旋律與閃爍 LED
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // 【核心】用內層迴圈一口氣更新 7 顆 LED 的狀態
    for (int led = 0; led < 7; led++) {
      int state = LEDcontrol[thisNote][led];
      digitalWrite(ledPins[led], state == 1 ? HIGH : LOW);
    }

    // 計算音符持續時間並播放
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    // 等待音符播完
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // 停止當前音符
    noTone(buzzerPin);
  }

  // 播完後全部熄滅
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  // 只跑一次
}