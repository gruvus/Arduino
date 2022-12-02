void TimingLoop() {

	//#define T1_prescale_factor(a)  T1_prescale_factor_old(a) //2104 256
	//#define T1_prescale_factor(a)  T1_prescale_factor_new(a)
	//#define T1_prescale_factor(a)  T1_prescale_factor_def(a)
		//T1_prescale_factor(T1_PSCALE_1);

	volatile float a = 2, b = 3, c = 0, d = 0;

	while (micros()) {
		ToggleSyncPin;
		//dlyMicros(5);
		//a=-a;
		SetTimingPin;
		{
			//c = a / b;
			c = round(a / b);
			//d = c;
		}
		ClearTimingPin;

		dlyMicros(5);

	}
	//dpr(c);
	//dpr(d);
}

// 11:00pm 11/17/22

