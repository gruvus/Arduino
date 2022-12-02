
//===========================================================
void build_values() {
    float x, y; int v, p, q;
    for (int i = 0; i <= OUT_MAX; i++) {   // ascending only
        switch (wave_form) {
            //---------------------------------
        case TRIANGLE:
            values[i] = round(fmap(i, OUT_MIN, OUT_MAX, DAC_LO, DAC_HI));
            break;
            //---------------------------------
        case SINE:
            x = fmap(i, OUT_MIN, OUT_MAX, -PI / 2, PI / 2);
            y = sin(x);
            v = round(fmap(y, -1.0, 1.0, DAC_LO, DAC_HI));
            values[i] = v;
            if (VERBOSE) {
                Serial.print(i); Serial.print("\t");
                Serial.print(x); Serial.print("\t");
                Serial.print(y); Serial.print("\t");
                Serial.print(v); Serial.print("\t");
                Serial.println();
            }
            break;
            //---------------------------------
        case SQUARE:
            //        values[i] = DAC_HI * (i % 2);
            values[i] = round(fmap((i % 2), OUT_MIN, OUT_MAX, DAC_LO, DAC_HI));
            break;

            //---------------------------------
        default:
            Serial.print("Waveform "); print_wave_name(); Serial.print(" not implemented, defaulting to RANDOM\n");
            wave_form = RANDOM;
            // falls through
            //---------------------------------
        case RANDOM:
            p = rand() % 256;
            q = round(fmap(p, 0, 255, OUT_MIN, OUT_MAX));
            v = round(fmap(q, OUT_MIN, OUT_MAX, DAC_LO, DAC_HI));
            values[i] = v;
            if (VERBOSE) {
                Serial.print(i); Serial.print("\t\t");
                Serial.print(p); Serial.print("\t");
                Serial.print(q); Serial.print("\t");
                Serial.print(v); Serial.print("\t");
                Serial.println();
            }

            break;

        } // switch
    } // for loop
    Serial.println("Finished building values");

} // void build_values()
