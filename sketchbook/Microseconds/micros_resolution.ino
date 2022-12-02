/*

*/



void micros_delay_resolution() {

	const int N = 500, P_ITER = 40;    // samples per iteration; number of iterations


	static long prev = 0, now = 0, count = 0;
	static long dly, dly_increment, tims[N], difs[N];
	static int digit_freq[11];
	static float avg_dif, prev_avg;

	auto print_header = []() {
		Serial.print("pass"); Serial.print("\t");
		Serial.print("dly"); Serial.print("\t");
		Serial.print("avg"); Serial.print("\t");
		Serial.print("dev"); Serial.print("\t");
		Serial.print("incr"); Serial.print("\t");
		Serial.print("avg dif"); Serial.print("\t");
		Serial.println();		Serial.println();

	};
	auto print_line = [&](int p) {
		Serial.print(p); Serial.print("\t");
		Serial.print(dly); Serial.print("\t");
		Serial.print(avg_dif); Serial.print("\t");
		Serial.print(avg_dif - dly); Serial.print("\t");
		Serial.print(dly_increment); Serial.print("\t");
		if (p > 0) Serial.print(avg_dif - prev_avg); Serial.print("\t");
		Serial.println();
		Serial.flush(); delayMicroseconds(1); // this combination seems to mininize the basic loop time
	};

	//
	{
		print_header(); //once

		for (int p = 0; p < P_ITER; p++) { // do it P_ITER times
			dly_increment = p;
			dly = dly + dly_increment;
			for (int i = 0; i < N; i++) { //collect N samples
				now = micros(); tims[i] = now; difs[i] = now - prev; prev = now;
				delayMicroseconds(dly);
			}
			// analyze
			int sum_difs = 0; difs[0] = 0; // exclude the first difference
			for (int i = 0; i < N; i++) {
				//Serial.print(i); Serial.print("\t"); Serial.println(difs[i]);
				sum_difs = sum_difs + difs[i];
				int last_digit = tims[i] % 10; digit_freq[last_digit]++;
				//Serial.print(i); Serial.print("\t");
				//Serial.print(tims[i]);  Serial.print("\t");
				//Serial.print(last_digit);  Serial.print("\t");
				//Serial.print(digit_freq[last_digit]); Serial.print("\n");
			}
			avg_dif = float(sum_difs) / (N - 1); // average for this iteration

			print_line(p);	//print line to report
			// prepare next pass
			prev_avg = avg_dif;
		}
	}
}

