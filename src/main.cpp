#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <types.h>
#include <PS2X_lib.h>

#define CE_RF_PIN 9
#define CS_RF_PIN 10
#define NRF_SPICLOCK 500000 // 8mhz 16mhz/2 = RF24_SPI_SPEED / 2 = 500000

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

RF24 radio(CE_RF_PIN, CS_RF_PIN, NRF_SPICLOCK);
PS2X ps2x;
PS2Keys keyValues;

int PSXerror = 0;

void readPSX();

void setup() {
  PSXerror = ps2x.config_gamepad(PS2_CLK_PIN, PS2_CMD_PIN, PS2_ATT_PIN, PS2_DATA_PIN, false, false);

  if(PSXerror != 0) {
    while(true){    }
  }

  if(!radio.begin()) {
        while(true){    }
  }

  radio.openWritingPipe(pipe);
  radio.setChannel(77);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
	radio.setPALevel(RF24_PA_MAX);
	radio.stopListening();
}

void loop() {
  readPSX();

  radio.write(&keyValues, sizeof(keyValues));
}

void readPSX() {
  if(PSXerror > 0) return;

  ps2x.read_gamepad();

  keyValues.analogKeys.LX = ps2x.Analog(PSS_LX);
  keyValues.analogKeys.LY = ps2x.Analog(PSS_LY);

  keyValues.analogKeys.RX = ps2x.Analog(PSS_RX);
  keyValues.analogKeys.RY = ps2x.Analog(PSS_RY);

  keyValues.digitalKeys[BTN_L1] = ps2x.Button(PSB_L1) ? '1' : '0';
  keyValues.digitalKeys[BTN_L2] = ps2x.Button(PSB_L2) ? '1' : '0';
  keyValues.digitalKeys[BTN_R1] = ps2x.Button(PSB_R1) ? '1' : '0';
  keyValues.digitalKeys[BTN_R2] = ps2x.Button(PSB_R2) ? '1' : '0';
  keyValues.digitalKeys[BTN_L3] = ps2x.Button(PSB_L3) ? '1' : '0';
  keyValues.digitalKeys[BTN_R3] = ps2x.Button(PSB_R3) ? '1' : '0';
  keyValues.digitalKeys[BTN_UP] = ps2x.Button(PSB_PAD_UP) ? '1' : '0';
  keyValues.digitalKeys[BTN_DOWN] = ps2x.Button(PSB_PAD_DOWN) ? '1' : '0';
  keyValues.digitalKeys[BTN_LEFT] = ps2x.Button(PSB_PAD_LEFT) ? '1' : '0';
  keyValues.digitalKeys[BTN_RIGHT] = ps2x.Button(PSB_PAD_RIGHT) ? '1' : '0';
  keyValues.digitalKeys[BTN_TRIANGLE] = ps2x.Button(PSB_TRIANGLE) ? '1' : '0';
  keyValues.digitalKeys[BTN_CROSS] = ps2x.Button(PSB_CROSS) ? '1' : '0';
  keyValues.digitalKeys[BTN_SQUARE] = ps2x.Button(PSB_SQUARE) ? '1' : '0';
  keyValues.digitalKeys[BTN_CIRCLE] = ps2x.Button(PSB_CIRCLE) ? '1' : '0';
  keyValues.digitalKeys[BTN_SELECT] = ps2x.Button(PSB_SELECT) ? '1' : '0';
  keyValues.digitalKeys[BTN_START] = ps2x.Button(PSB_START) ? '1' : '0';
}