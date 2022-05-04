typedef struct Analogs {
	unsigned int LX;
	unsigned int LY;
	unsigned int RX;
	unsigned int RY;
};

typedef union Digitals{
	unsigned char L1 : 1;
	unsigned char L2 : 1;
	unsigned char R1 : 1;
	unsigned char R2 : 1;
	unsigned char L3 : 1;
	unsigned char R3 : 1;
	unsigned char UP : 1;
	unsigned char DOWN : 1;
	unsigned char LEFT : 1;
	unsigned char RIGHT : 1;
	unsigned char TRIANGLE : 1;
	unsigned char CROSS : 1;
	unsigned char SQUARE : 1;
	unsigned char CIRCLE : 1;
	unsigned char SELECT : 1;
	unsigned char START : 1;
} ;

struct PS2Keys {
	Analogs analogKeys;
	Digitals digitalKeys;
};

