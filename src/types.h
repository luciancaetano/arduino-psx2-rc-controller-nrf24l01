typedef struct Analogs {
	unsigned int LX;
	unsigned int LY;
	unsigned int RX;
	unsigned int RY;
};

typedef union Digitals{
	unsigned int L1 : 1;
	unsigned int L2 : 1;
	unsigned int R1 : 1;
	unsigned int R2 : 1;
	unsigned int L3 : 1;
	unsigned int R3 : 1;
	unsigned int UP : 1;
	unsigned int DOWN : 1;
	unsigned int LEFT : 1;
	unsigned int RIGHT : 1;
	unsigned int TRIANGLE : 1;
	unsigned int CROSS : 1;
	unsigned int SQUARE : 1;
	unsigned int CIRCLE : 1;
	unsigned int SELECT : 1;
	unsigned int START : 1;
} ;

struct PS2Keys {
	Analogs analogKeys;
	Digitals digitalKeys;
};

