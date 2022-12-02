

void setup() {
	Serial.begin(115200);
	Serial.print("\n\n\ <Study>  Pointers\n");
	Serial.print(" ============================\n\n");


	//pointers_A();

	derefStructPtr();
}
void loop() {}


void divide(byte& a, byte& b, byte& result) {
	result = a / b;
}

void divide(float& a, float& b, float& result) {
	result = a / b;
}

typedef unsigned int uint;

void pointers_A() {
	byte a, b, c, aa, bb, cc;

	a = 12; b = 3; c = 0;
	divide(a, b, c);

	Serial.print(a);  Serial.print("\t\t");
	Serial.print(b);  Serial.print("\t\t");
	Serial.print(c);  Serial.print("\t\t");
	Serial.print("\n");

	Serial.print(uint(&a), HEX);  Serial.print("\t");
	Serial.print(uint(&b), HEX);  Serial.print("\t");
	Serial.print(uint(&c), HEX);  Serial.print("\t");
	Serial.print("\n");

	byte* adr_a, * adr_b, * adr_c;
	adr_a = &a;   aa = *adr_a;	// aa= *(&a)
	adr_b = &b;   bb = *adr_b;
	adr_c = &c;   cc = *adr_c;

	Serial.print(uint(adr_a), HEX);  Serial.print("\t");
	Serial.print(uint(adr_b), HEX);  Serial.print("\t");
	Serial.print(uint(adr_c), HEX);  Serial.print("\t");
	Serial.print("\n");

	Serial.print(aa);  Serial.print("\t\t");
	Serial.print(bb);  Serial.print("\t\t");
	Serial.print(cc);  Serial.print("\t\t");
	Serial.print("\n");

	Serial.print("\n------------------------------------------\n\n");


	Serial.print(uint(&aa), HEX);  Serial.print("\t");
	Serial.print(uint(&bb), HEX);  Serial.print("\t");
	Serial.print(uint(&cc), HEX);  Serial.print("\t");
	Serial.print("\n\n");

	Serial.print(uint(adr_a), HEX);  Serial.print("\t");
	Serial.print(uint(adr_b), HEX);  Serial.print("\t");
	Serial.print(uint(adr_c), HEX);  Serial.print("\t");
	Serial.print("\n");

	adr_a = adr_a - 1;   aa = *adr_a;
	adr_b = adr_b - 1;   bb = *adr_b;
	adr_c = adr_c + 2;   cc = *adr_c;


	Serial.print(int(adr_a), HEX);  Serial.print("\t");
	Serial.print(int(adr_b), HEX);  Serial.print("\t");
	Serial.print(int(adr_c), HEX);  Serial.print("\t");
	Serial.print("\n");

	Serial.print(aa);  Serial.print("\t\t");
	Serial.print(bb);  Serial.print("\t\t");
	Serial.print(cc);  Serial.print("\t\t");
	Serial.print("\n");


}

//https://riptutorial.com/c/example/5408/dereferencing-a-pointer-to-a-struct
void derefStructPtr() {
	struct myStruct
	{
		int id;
		float val;
	};
	
	//typedef struct myStruct_t myStruct_t;

	myStruct s1 = { 1, 3.141593F };
	myStruct s2 = { 99,99.99 }, s3 = { 99,99.99 };

	myStruct* sptr; // uninitialized
	//myStruct* instance = &s1;
	sptr = &s1;


	auto loc_print = [](myStruct ms, char* name) {
		char* margin = "   ";
		Serial.print(margin);
		Serial.print(name); Serial.print("\t");
		Serial.print(ms.id);  Serial.print("\t");
		Serial.print(ms.val);  Serial.print("\n");
	};
	auto print_all = [&](char* msg) {
		Serial.print("\n "); Serial.print(msg); Serial.print("\n");
		loc_print(s1, "s1    ");
		loc_print(*sptr, "->s1  ");
		loc_print(s2, "s2    ");
		loc_print(s3, "s3    ");
	};

	print_all("initial values");

	s2.id = (*sptr).id; 
	s2.val = sptr->val;
	print_all("s2 copy of s1 via *sptr");

	s2.id = 2; s2.val = 2.71828;
	print_all("s2 modified");

	s1 = { 0,-1 };
	s2.id = 5; s2.val = 8.2;
	s3 = s2;
	print_all("s1, s2 modified, s3 = s2");

	s3 = (*sptr);
	print_all("s3 = (*sptr)");


}
