typedef struct Analogs {
	unsigned int LX; // -255...0...255
	unsigned int LY; // -255...0...255
	unsigned int RX; // -255...0...255
	unsigned int RY; // -255...0...255
};

#define BTN_L1 0
#define BTN_L2 1
#define BTN_R1 2
#define BTN_R2 3
#define BTN_L3 4
#define BTN_R3 5
#define BTN_UP 6
#define BTN_DOWN 7
#define BTN_LEFT 8
#define BTN_RIGHT 9
#define BTN_TRIANGLE 10
#define BTN_CROSS 11
#define BTN_SQUARE 12
#define BTN_CIRCLE 13
#define BTN_SELECT 14
#define BTN_START 15


typedef struct PS2Keys {
	char digitalKeys[16];
	Analogs analogKeys;
};

