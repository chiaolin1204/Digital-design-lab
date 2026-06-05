#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

const int row[] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
const int col[] = {
  COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};

byte scan[8][8] = {
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1}
};

byte circle[8][8] = {
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,1,1,1,0,0}
};

byte H[8][8] = {
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0}
};

byte A[8][8] = {
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {0,1,1,1,1,1,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0}
};

byte previousState=1, presentState=1, patternNumber=0;
byte incomingByte = 0; // 初始設為 0

void setup()
{
  Serial.begin(9600);
  
  for (byte i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
  }
  for (byte i = 0; i < 8; i++) {
    pinMode(col[i], OUTPUT);
  }  

  pinMode(2, INPUT_PULLUP);
}

void loop()
{ 
  // 處理序列埠讀取，並過濾換行字元
  if (Serial.available() > 0){
    byte tempByte = Serial.read();
    // 忽略換行符號(\n)與歸位符號(\r)
    if (tempByte != '\n' && tempByte != '\r') {
      incomingByte = tempByte;
    }
  }
  
  // 根據收到的字元顯示圖案
  if(incomingByte == 'c')
    showPattern(circle);
  else if(incomingByte == 'H')
    showPattern(H);
  else if(incomingByte == 'A')
    showPattern(A);
}

void showPattern(byte matrix[8][8]){
  for(byte i = 0; i < 8; i++){
    // 1. 設定該行的 LED 狀態 (亮起)
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], 1 - scan[i][j]);
      digitalWrite(col[j], matrix[i][j]); 
    }
    
    // 2. 加上微小延遲，讓肉眼產生視覺暫留 (非常重要！)
    delay(2); 

    // 3. 關閉該行的 LED，準備換下一行
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], HIGH);
      digitalWrite(col[j], LOW);  
    }
  }
}