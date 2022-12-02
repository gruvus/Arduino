/*
last digit distribution of the micros() value to check resolution
	Due: 1us	Uno: 2us

*/


void last_digit_distribution() {

#ifdef ARDUINO_SAM_DUE
	const int N = 1000;	//Due: build fails at 23,772; run fails at 23,723
#else
	const int N = 100;	//Uno: 400 => 90% mem usage
#endif

	static long now, tims[N]; // static -> allocates at build time, can see RAM min use (as if global without static)
	static int digit_freq[11];	// 0..9 with 11th position used in normalization

	auto print_header = []() {
		// header
		for (int i = 0; i < 11; i++) { Serial.print(i); Serial.print("\t"); } 		Serial.print("\n");
		for (int i = 0; i < 11; i++) { Serial.print("===="); Serial.print("\t"); }	Serial.print("\n");

	};

	auto print_distribution = [&]() {
		int scale = min(N, 100);

		Serial.print("\nDistribution \tN = "); Serial.print(N); Serial.print(" samples");
		if (N > 100) { Serial.print("\tnormalized to "); Serial.print(scale); }
		Serial.print("\n\n");

		print_header();

		int m = 0, total = 0, d_freq[11];
		for (int j = 0; j < 10; j++)
		{
			total = total + digit_freq[j];	d_freq[j] = digit_freq[j];
		}
		// normalize last digit distribution
		d_freq[10] = total;

		for (int j = 0; j < 11; j++)
		{
			d_freq[j] = round((d_freq[j] * scale * 1.0) / total);
		}

		total = 0; // new normalized total; should be = scale
		for (int j = 0; j < 10; j++)
		{
			m = max(m, d_freq[j]);
			total = total + d_freq[j];
		}

		for (int k = 0; k < m; k++) {
			for (int i = 0; i < 11; i++) {
				if (i == 10 && k > 0) continue;
				if (d_freq[i] > 0) Serial.print(d_freq[i]);
				Serial.print("\t");
				d_freq[i]--;
			}
			Serial.print("\n");
		}

		Serial.print("\n");	Serial.println(total);

	};

	// main body
	{
		for (int i = 0; i < N; i++) { //collect N samples
			now = micros();
			tims[i] = now;
			//delayMicroseconds(rand() % 10);
		}

		for (int j = 0; j < 11; j++) { digit_freq[j] = 0; } // initialize counters

		// analyze
		for (int i = 0; i < N; i++) {
			//Serial.print(i); Serial.print("\t"); Serial.println(tims[i]);

			int last_digit = tims[i] % 10; digit_freq[last_digit]++;
			//Serial.print(i); Serial.print("\t");
			//Serial.print(tims[i]);  Serial.print("\t");
			//Serial.print(last_digit);  Serial.print("\t");
			//Serial.print(digit_freq[last_digit]); Serial.print("\n");
		}

		// print last digit distribution
		print_distribution();

	}
}




