
#ifdef ARDUINO_SAM_DUE
const int N = 10000;
#else
const int N = 10000;	// attention to max 16bit int
#endif

//----------------------------------------------
void last_digit_distribution() {

	static int digit_freq[10];	// 0..9 

	auto print_header = []() {
		// header
		for (int i = 0; i < 10; i++) { Serial.print(i); Serial.print("\t"); } 		Serial.print("Total\n");
		for (int i = 0; i < 11; i++) { Serial.print("====="); Serial.print("\t"); }	Serial.print("\n");
	};

	auto print_distribution = [&]() {
		int scale = min(N, 100);

		Serial.print("\nDistribution \tN = "); Serial.print(N); Serial.print(" samples");
		if (N > 100) { Serial.print("\tnormalized to "); Serial.print(scale); }
		Serial.print("\n\n");

		print_header();

		int total = 0; int d_freq_norm[10]; // normalized version

		for (int j = 0; j < 10; j++)
		{
			total += digit_freq[j];	// count for total, must be = N (number of samples)
			d_freq_norm[j] = digit_freq[j];	// copy
		}

		// normalize distribution relative to the total
		for (int j = 0; j < 10; j++)
		{
			d_freq_norm[j] = round((float)d_freq_norm[j] / total * scale);
			//d_freq_norm[j] = round(d_freq_norm[j] * 1.0F / total * scale);
			//d_freq_norm[j] = round(1.0F * d_freq_norm[j] * scale / total);
		}

		int m = 0; // max count (histogram height, for printing)
		total = 0; // new normalized total; should be = scale (may be off due to rounding errors) 
		for (int j = 0; j < 10; j++) // only look at digits
		{
			m = max(m, d_freq_norm[j]); // longest bar
			total += d_freq_norm[j];
		}
		// print
		for (int k = 0; k < m; k++) { // longest bar sets number of lines
			for (int i = 0; i < 10; i++) { // for each line

				if (d_freq_norm[i] > 0) { // skip if zero
					if (k == 0) {
						Serial.print(d_freq_norm[i]); // show the value on the first line	
					}
					else {
						Serial.print("#");	// draw the column
					}
				}
				Serial.print("\t");			// move to next column
				if (k == 0 && i == 9) Serial.print(total);	// only print total on first line
				d_freq_norm[i]--;
			}
			Serial.print("\n");		// finished line
		}

		Serial.print("\n");

	};

	auto print_histogram = [&]() {
		int scale = min(N, 100);

		// header
		{
			Serial.print("\nDistribution \tN = "); Serial.print(N); Serial.print(" samples");
			if (N > 100) { Serial.print("\tnormalized to "); Serial.print(scale); }
			Serial.print("\n\n");
			for (int i = 0; i < 10; i++) { Serial.print(i); Serial.print("\t"); } 		Serial.print("Total\n");
			for (int i = 0; i < 11; i++) { Serial.print("====="); Serial.print("\t"); }	Serial.print("\n");
			Serial.print("\n");
		}

		// normalize distribution relative to the total number of samples
		int m = 0;			// max count (histogram height, for printing)
		int total = 0;		// normalized total; should be = scale (may be off due to rounding errors) 
		for (int j = 0; j < 10; j++)
		{
			digit_freq[j] = round((float)digit_freq[j] / N * scale);
			m = max(m, digit_freq[j]); // how big the tallest bar
			total += digit_freq[j];
		}

		// print histogram
		for (int k = m; k > 0; k--) { // tallest bar sets number of lines
			for (int i = 0; i < 10; i++) { // draw line k
				if (digit_freq[i] >= k) { // is this (i) bar at this (k) level?
					Serial.print("#");	// draw its column
				}
				Serial.print("\t");			// move to next column
			}
			//Serial.print(k);
			Serial.print("\n");		// finished the line
		}

		// footer
		{
			for (int i = 0; i < 11; i++) { Serial.print("====="); Serial.print("\t"); }	Serial.print("\n");
			for (int i = 0; i < 10; i++) { Serial.print(digit_freq[i]); Serial.print("\t"); }
			Serial.print(total); Serial.print("\n");
		}
	};


	// ****************  main body *************************************
	{
		for (int j = 0; j < 10; j++) { digit_freq[j] = 0; } // initialize counters

		for (int i = 0; i < N; i++) { //collect N samples
			int last_digit;
			
			//last_digit = (2 * rand()) % 10;	// 2*rand() will exceed INT_MAX
			//last_digit = (uint(2) * rand()) % 10;

			//last_digit = (4*random_int(1000,1999)) % 10;

			last_digit = rand() % 10;
			digit_freq[last_digit]++;		// count
		}

		// print last digit distribution
		print_histogram();


	}
}

void test_random_numbers() {
	Serial.print("test_random_numbers\t \n");
	Serial.print(RAND_MAX); Serial.print("\n");

	for (int i = 0; i < 100; i++) {
		int r = random_int(1, 10);
		Serial.print("random int\t");	Serial.print(r);	Serial.print("\t");
		Serial.print("\n");
	}
	Serial.print("\n");
}

int random_int(int a, int b) {

	//int r = a + rand() % (b - a + 1);
	//return r;

	return a + rand() % (b - a + 1);
}
