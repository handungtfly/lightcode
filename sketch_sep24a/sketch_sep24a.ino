const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 5;
const int BledPin = 4;

int buttonState = 0;
int ledcolor = 0;
bool ButtonPressed = false;
bool ledsOff = false;
bool longPressTriggered = false;
String currentcolor = "led";

unsigned long pressStartTime = 0;
const unsigned long longPressTime = 2000; // 長按 2 秒觸發

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // 按鈕接 GND
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // --- 按下開始計時 ---
  if (buttonState == LOW && !ButtonPressed) {
    ButtonPressed = true;
    longPressTriggered = false;
    pressStartTime = millis();
  }

  // --- 按住中檢查長按 ---
  if (ButtonPressed && !longPressTriggered && buttonState == LOW) {
    unsigned long pressDuration = millis() - pressStartTime;

    if (pressDuration >= longPressTime) {
      // 🔥 長按2秒 → 立即關燈
      digitalWrite(RledPin, HIGH);
      digitalWrite(GledPin, HIGH);
      digitalWrite(BledPin, HIGH);
      ledsOff = true;
      currentcolor = "OFF";
      longPressTriggered = true;
      Serial.println("Long press (2s) -> LED OFF");
    }
  }

  // --- 放開按鈕 ---
  if (buttonState == HIGH && ButtonPressed) {
    ButtonPressed = false;

    if (!longPressTriggered) {
      // ✨ 短按：換色或開燈
      if (!ledsOff) {
        ledcolor++;
        if (ledcolor > 3) ledcolor = 0;

        if (ledcolor == 0) {         // 白 (R+G+B)
          digitalWrite(RledPin, LOW);
          digitalWrite(GledPin, LOW);
          digitalWrite(BledPin, LOW);
          currentcolor = "WHITE";
        } 
        else if (ledcolor == 1) {    // 黃 (R+G)
          digitalWrite(RledPin, LOW);
          digitalWrite(GledPin, LOW);
          digitalWrite(BledPin, HIGH);
          currentcolor = "YELLOW";
        } 
        else if (ledcolor == 2) {    // 青 (G+B)
          digitalWrite(RledPin, HIGH);
          digitalWrite(GledPin, LOW);
          digitalWrite(BledPin, LOW);
          currentcolor = "CYAN";
        } 
        else if (ledcolor == 3) {    // 藍 (B)
          digitalWrite(RledPin, HIGH);
          digitalWrite(GledPin, HIGH);
          digitalWrite(BledPin, LOW);
          currentcolor = "BLUE";
        }

        Serial.print("Current Color: ");
        Serial.println(currentcolor);
      } else {
        // 若目前關燈，再按一次恢復白色
        ledsOff = false;
        digitalWrite(RledPin, LOW);
        digitalWrite(GledPin, LOW);
        digitalWrite(BledPin, LOW);
        currentcolor = "WHITE";
        Serial.println("LED ON (from OFF)");
      }
    }
  }
}


