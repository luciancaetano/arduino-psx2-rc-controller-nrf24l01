#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <types.h>
#include <PSX.h>

#define CE_RF_PIN 9
#define CS_RF_PIN 10

// BK GND
// RED VCC
#define PS2_ATT_PIN  2 // yellow
#define PS2_CMD_PIN  3 // orange
#define PS2_DATA_PIN  4 // brown
#define PS2_CLK_PIN  5 // blue

#define CHAN_PIN_BIT_1 8
#define CHAN_PIN_BIT_2 A1
#define CHAN_PIN_BIT_3 A2
#define CHAN_PIN_BIT_4 A3
#define CHAN_PIN_BIT_5 A4
#define CHAN_PIN_BIT_6 A5
#define CHAN_PIN_BIT_7 A6
#define CHAN_PIN_BIT_8 A7

#define BUZZER_PIN 6 // PWM

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(CE_RF_PIN, CS_RF_PIN);
PS2Keys keyValues;
PSX psx;

int PSXerror;

PSX::PSXDATA PSXdata;

void readPSX();

void setup() {
  delay(10);

  pinMode(CHAN_PIN_BIT_1, INPUT);
  pinMode(CHAN_PIN_BIT_2, INPUT);
  pinMode(CHAN_PIN_BIT_3, INPUT);
  pinMode(CHAN_PIN_BIT_4, INPUT);
  pinMode(CHAN_PIN_BIT_5, INPUT);
  pinMode(CHAN_PIN_BIT_6, INPUT);
  pinMode(CHAN_PIN_BIT_7, INPUT);
  pinMode(CHAN_PIN_BIT_8, INPUT);

  delay(10);

  int channel = 0;
  channel |= digitalRead(CHAN_PIN_BIT_1) << 0;
  channel |= digitalRead(CHAN_PIN_BIT_2) << 1;
  channel |= digitalRead(CHAN_PIN_BIT_3) << 2;
  channel |= digitalRead(CHAN_PIN_BIT_4) << 3;
  channel |= digitalRead(CHAN_PIN_BIT_5) << 4;
  channel |= digitalRead(CHAN_PIN_BIT_6) << 5;
  channel |= digitalRead(CHAN_PIN_BIT_7) << 6;
  channel |= digitalRead(CHAN_PIN_BIT_8) << 7;


  psx.setupPins(PS2_DATA_PIN, PS2_CMD_PIN, PS2_ATT_PIN, PS2_CLK_PIN, 10);
  psx.config(PSXMODE_ANALOG);

  if(!radio.begin()) {
    while(1);
  }

  radio.openWritingPipe(pipe);
  radio.setChannel(channel);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
	radio.setPALevel(RF24_PA_MAX);
	radio.stopListening();

  tone(BUZZER_PIN, 196, 200);
}

void loop() {
  readPSX();

  radio.write(&keyValues, sizeof(keyValues));

  delay(10);
}

void readPSX() {
  PSXerror = psx.read(PSXdata);

  if(PSXerror == PSXERROR_SUCCESS) {
    keyValues.analogKeys.leftX = PSXdata.JoyLeftX;
    keyValues.analogKeys.leftY = PSXdata.JoyLeftY;
    keyValues.analogKeys.rghtX = PSXdata.JoyRightX;
    keyValues.analogKeys.rghtY = PSXdata.JoyRightY;

    keyValues.digitalKeys.bits.lf = PSXdata.buttons & PSXBTN_LEFT;
    keyValues.digitalKeys.bits.rt = PSXdata.buttons & PSXBTN_RIGHT;
    keyValues.digitalKeys.bits.up = PSXdata.buttons & PSXBTN_UP;
    keyValues.digitalKeys.bits.dn = PSXdata.buttons & PSXBTN_DOWN;
    keyValues.digitalKeys.bits.l1 = PSXdata.buttons & PSXBTN_L1;
    keyValues.digitalKeys.bits.r1 = PSXdata.buttons & PSXBTN_R1;
    keyValues.digitalKeys.bits.l2 = PSXdata.buttons & PSXBTN_L2;
    keyValues.digitalKeys.bits.r2 = PSXdata.buttons & PSXBTN_R2;
    keyValues.digitalKeys.bits.tr = PSXdata.buttons & PSXBTN_TRIANGLE;
    keyValues.digitalKeys.bits.cr = PSXdata.buttons & PSXBTN_CROSS;
    keyValues.digitalKeys.bits.sq = PSXdata.buttons & PSXBTN_SQUARE;
    keyValues.digitalKeys.bits.cl = PSXdata.buttons & PSXBTN_CIRCLE;
    keyValues.digitalKeys.bits.sl = PSXdata.buttons & PSXBTN_SELECT;
    keyValues.digitalKeys.bits.st = PSXdata.buttons & PSXBTN_START;
  }
}