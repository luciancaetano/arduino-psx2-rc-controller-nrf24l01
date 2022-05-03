typedef struct Analogs {
	unsigned int leftX;
	unsigned int leftY;
	unsigned int rghtX;
	unsigned int rghtY;
};

typedef union Digitals{
	struct {
		unsigned int l1 : 1;
		unsigned int l2 : 1;
		unsigned int r1 : 1;
		unsigned int r2 : 1;
		unsigned int up : 1;
		unsigned int dn : 1;
		unsigned int lf : 1;
		unsigned int rt : 1;
		unsigned int tr : 1;
		unsigned int cr : 1;
		unsigned int sq : 1;
		unsigned int cl : 1;
		unsigned int sl : 1;
		unsigned int st : 1;
	} bits;
	unsigned int onoff;
} ;

struct PS2Keys {
	Analogs analogKeys;
	Digitals digitalKeys;
};

