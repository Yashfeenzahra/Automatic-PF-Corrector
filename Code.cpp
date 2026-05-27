#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define RX_PIN       10   // Connect to PZEM Tx
#define TX_PIN       11   // Connect to PZEM Rx

#define RELAY1_PIN    4  // Relay 1 pin (first capacitor)
#define RELAY2_PIN    5  // Relay 2 pin (second capacitor)

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
SoftwareSerial pzemSWSerial(RX_PIN, TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);

void setup() {
  Serial.begin(9600);

  // Initialize relay pins
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH);  // Relay OFF
  digitalWrite(RELAY2_PIN, HIGH);  // Relay OFF

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PF Test Starting");
  delay(2000);

  byte addr = pzem.readAddress();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Addr: 0x");
  if (addr < 0x10) lcd.print('0');
  lcd.print(addr, HEX);
  Serial.print("Device Address: 0x");
  Serial.println(addr, HEX);
  delay(2000);

  // --- Measure initial PF ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Meas PF...");
  Serial.println("\n[1] Measuring Initial PF...");
  delay(2000);

  float pf = pzem.pf();
  if (isnan(pf)) {
    lcd.setCursor(0, 1);
    lcd.print("Error reading PF");
    Serial.println("Error reading power factor");
    return;
  }

  lcd.setCursor(0, 1);
  lcd.print("PF: ");
  lcd.print(pf, 3);
  Serial.print("Initial PF: ");
  Serial.println(pf, 3);
  delay(3000);

  // --- Check if correction needed ---
  if (pf >= 0.95) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PF OK");
    lcd.setCursor(0, 1);
    lcd.print("No action needed");
    Serial.println("PF >= 0.95 — No correction needed.");
  } else {
    Serial.println("PF < 0.95 — Starting correction...");

    // --- Step 1: Turn ON Relay 1 ---
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Relay1 ON...");
    digitalWrite(RELAY1_PIN, LOW); // Activate Relay 1
    delay(5000);  // wait for stabilization

    // Re-measure PF
    float pf1 = pzem.pf();
    lcd.setCursor(0, 1);
    lcd.print("PF1: ");
    lcd.print(pf1, 3);
    Serial.print("PF after Relay1: ");
    Serial.println(pf1, 3);
    delay(3000);

    if (pf1 >= 0.90) {
      Serial.println("PF corrected with Relay1 only.");
    } else {
      // --- Step 2: Turn ON Relay 2 ---
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Relay2 ON...");
      digitalWrite(RELAY2_PIN, LOW); // Activate Relay 2
      delay(5000);  // wait again

      float pf2 = pzem.pf();
      lcd.setCursor(0, 1);
      lcd.print("PF2: ");
      lcd.print(pf2, 3);
      Serial.print("PF after Relay2: ");
      Serial.println(pf2, 3);
      delay(3000);
    }

    lcd.setCursor(0, 0);
    lcd.print("Correction Done");
  }
}

void loop() {
  // Test runs once
}
