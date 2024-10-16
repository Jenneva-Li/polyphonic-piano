#include <synth.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
synth edgar;

const byte NOTE_C = 1;
const byte NOTE_D = 2;
const byte NOTE_E = 4;
const byte NOTE_F = 8;
const byte NOTE_G = 16;

const int NOTE_FREQS[] = {2093, 2349, 2637, 2793, 3135};

void sweep() {
    float frequency = 1000;

    for (int i = 0; i < 1000; i++) {
        Serial.println(frequency);
        edgar.setFrequency(0, frequency);
        edgar.trigger(0);
        delay(200);
        frequency += 100;
    }
}

void lightup(byte value) {
    if (value & 1) {
        pinMode(A1, OUTPUT);
        digitalWrite(A1, LOW);
    }
    if (value & 2) {
        pinMode(A2, OUTPUT);
        digitalWrite(A2, LOW);
    }
    if (value & 4) {
        pinMode(A3, OUTPUT);
        digitalWrite(A3, LOW);
    }
    if (value & 8) {
        pinMode(A4, OUTPUT);
        digitalWrite(A4, LOW);
    }
    if (value & 16) {
        pinMode(A5, OUTPUT);
        digitalWrite(A5, LOW);
    }
}

void allOff() {
    for (byte i = 1; i <= 5; i++) {
        pinMode(A0 + i, INPUT);
        digitalWrite(A0 + i, HIGH);
    }
}

byte voiceIndex = 0;

void play(int freq) {
    edgar.setFrequency(voiceIndex, freq);
    edgar.trigger(voiceIndex);
    voiceIndex++;
    if (voiceIndex == 4) {
        voiceIndex = 0;
    }
}

void setup() {
    Serial.begin(250000);
    lcd.begin(16, 2);
    lcd.print("Not A Jup-8");
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);

    edgar.begin(CHA);
    for (byte i = 0; i < 4; i++) {
        edgar.setupVoice(i, SINE, 60, ENVELOPE0, 100, 64);
    }

    allOff();
    pinMode(A0, INPUT);
}

byte prevButtonState[5] = {0};
byte songStep = 1;
byte nextValue = 0;
byte highScore = 0;

void loop() {
    byte currentButtonState[5];
    int tuningValue = analogRead(A0);
    int pbend = (tuningValue / 1024.0) * 500 - 33;

    lightup(nextValue);
    allOff();

    lcd.setCursor(0, 1);
    lcd.print(highScore);

    for (byte i = 0; i < 5; i++) {
        currentButtonState[i] = digitalRead(A1 + i);
    }

    byte v = ~(currentButtonState[0] * 1 + currentButtonState[1] * 2 +
                currentButtonState[2] * 4 + currentButtonState[3] * 8 +
                currentButtonState[4] * 16 + 32 + 64 + 128);

    Serial.println(v);

    if (v != 0) {
        if (nextValue != 0 && v == nextValue) {
            nextValue = 0;
            highScore++;
        } else {
            highScore = 0;
            lcd.setCursor(0, 1);
            lcd.print("          ");
        }
    } else {
        if (nextValue == 0) {
            nextValue = song1[songStep];
            songStep++;
            if (songStep > song1[0]) {
                songStep = 1;
            }
        }
    }

    for (byte i = 0; i < 5; i++) {
        if (currentButtonState[i] == 0) {
            if (prevButtonState[i] == 0) {
                continue;
            }
            prevButtonState[i] = 0;
            play(NOTE_FREQS[i] + pbend);
        } else {
            prevButtonState[i] = 1;
        }
    }
}
