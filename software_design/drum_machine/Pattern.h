class Pattern
{
public:
  int32_t pattern[21][16] = {
      // array of active steps for each instrument
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0 - BD
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1 - S
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2 - CYN1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3 - CYN2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4 - GLITCH
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5 - DIGI1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6 - DIGI2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7 - DIGI3
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8 - SMP1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 9 - SMP2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 10 - SMP3
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 11 - SMP4
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 12 - SMP5
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 13 - SMP6
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 14 - SMP7
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 15 - SMP8
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 16 - Organ Chords
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 17 - Guitar chords
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 18 - Guitar Oneshots
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 19 - Organ notes
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 20 - Breaks
  };
  float velocity[21][16] = {
      // array of volumes per step for each instrument
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // BD
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // S
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // CYN1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // CYN2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // GLITCH
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DIGI1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DIGI2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DIGI3
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP3
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP4
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP5
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP6
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP7
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SMP8
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Organ Chords
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Guitar chords
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Guitar Oneshots
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Organ notes
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Breaks
  };
  float parameter[33][16] = {
      // array of parameters by step for each instrument
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0 - DIGI1 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1 -DIGI1 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2 - DIGI2 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3 - DIGI2 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4 - DIGI3 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5 - DIGI3 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6 - SMP1 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7 - SMP1 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8 - SMP2 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 9 - SMP2 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 10 - SMP3 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 11 - SMP3 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 12 - SMP4 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 13 - SMP4 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 14 - SMP5 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 15 - SMP5 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 16 - SMP6 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 17 - SMP6 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 18 - SMP7 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 19 - SMP7 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 20 - SMP8 P1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 21 - SMP8 P2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 22 - Organ chords p1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 23 - Organ chords p2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 24 - Guitar chords p1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 25 - Guitar chords p2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 26 - Guitar oneshots p1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 27 - Guitar oneshots p2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 28 - organ notes p1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 29 - organ notes p2
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 30 - break pitch
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 31 - break p1
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 32 - break p2
  };

  float settings[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // array of global settings for pattern
  // [0] tempo
  // [1] kit number
  // [2]
  // [3]
  // [4]
  // [5]
  // [6]
  // [7]
  // [8]
  // [9]
  // [10]
  // [11]
  // [12]
  // [13]
  // [14]
  // [15]

  const int sdChipSelect = BUILTIN_SDCARD;
  const int flashChipSelect = 6;
  Pattern()
  {
  }

  ///**************************************************************************************************
  // * Function readFromSD
  // * -------------------------------------------------------------------------------------------------
  // * Overview: reads pattern from CSV on SD card
  // * Input:
  // *      const char* path: path of CSV to read on SD card
  // * Output: Nothing
  // **************************************************************************************************/
  void readFromSD(const char *path) // READS PATTERN FROM CSV ON SD CARD
  {
    // format for drum pattern: data types of each column in CSV
    CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLLLfffLfffLfffLfffLfffLfffLfffLffffLfffLfffLfffLfffLffff", /*has_header*/ true, /*delimiter*/ ',');

    if (cp.readSDfile(path))
    {
      // copy steps to internal memory
      memcpy(pattern[0], (int32_t *)cp["kk"], 64);
//      int32_t *numm = (int32_t*)cp["s"];
//      for (int i = 0; i < 16; i++){
//        pattern[0][i] = numbers[i];
//      }
      memcpy(pattern[1], (int32_t *)cp["s"], 64);
      memcpy(pattern[2], (int32_t *)cp["c1"], 64);
      memcpy(pattern[3], (int32_t *)cp["c2"], 64);
      memcpy(pattern[4], (int32_t *)cp["g"], 64);
      memcpy(pattern[5], (int32_t *)cp["d1"], 64);
      memcpy(pattern[6], (int32_t *)cp["d2"], 64);
      memcpy(pattern[7], (int32_t *)cp["d3"], 64);
      memcpy(pattern[8], (int32_t *)cp["s1"], 64);
      memcpy(pattern[9], (int32_t *)cp["s2"], 64);
      memcpy(pattern[10], (int32_t *)cp["s3"], 64);
      memcpy(pattern[11], (int32_t *)cp["s4"], 64);
      memcpy(pattern[12], (int32_t *)cp["s5"], 64);
      memcpy(pattern[13], (int32_t *)cp["s6"], 64);
      memcpy(pattern[14], (int32_t *)cp["s7"], 64);
      memcpy(pattern[15], (int32_t *)cp["s8"], 64);
      memcpy(pattern[16], (int32_t *)cp["oc"], 64);
      memcpy(pattern[17], (int32_t *)cp["gc"], 64);
      memcpy(pattern[18], (int32_t *)cp["go"], 64);
      memcpy(pattern[19], (int32_t *)cp["on"], 64);
      memcpy(pattern[20], (int32_t *)cp["br"], 64);

      // copy velocities to internal memory
      memcpy(velocity[0], (float *)cp["kv"], 64);
      memcpy(velocity[1], (float *)cp["sv"], 64);
      memcpy(velocity[2], (float *)cp["c1v"], 64);
      memcpy(velocity[3], (float *)cp["c2v"], 64);
      memcpy(velocity[4], (float *)cp["gv"], 64);
      memcpy(velocity[5], (float *)cp["d1v"], 64);
      memcpy(velocity[6], (float *)cp["d2v"], 64);
      memcpy(velocity[7], (float *)cp["d3v"], 64);
      memcpy(velocity[8], (float *)cp["s1v"], 64);
      memcpy(velocity[9], (float *)cp["s2v"], 64);
      memcpy(velocity[10], (float *)cp["s3v"], 64);
      memcpy(velocity[11], (float *)cp["s4v"], 64);
      memcpy(velocity[12], (float *)cp["s5v"], 64);
      memcpy(velocity[13], (float *)cp["s6v"], 64);
      memcpy(velocity[14], (float *)cp["s7v"], 64);
      memcpy(velocity[15], (float *)cp["s8v"], 64);
      memcpy(velocity[16], (float *)cp["ocv"], 64);
      memcpy(velocity[17], (float *)cp["gcv"], 64);
      memcpy(velocity[18], (float *)cp["gov"], 64);
      memcpy(velocity[19], (float *)cp["onv"], 64);
      memcpy(velocity[20], (float *)cp["brv"], 64);

      // copy parameters to internal memory
      memcpy(parameter[0], (float *)cp["d1p"], 64);
      memcpy(parameter[1], (float *)cp["d1pp"], 64);
      memcpy(parameter[2], (float *)cp["d2p"], 64);
      memcpy(parameter[3], (float *)cp["d2pp"], 64);
      memcpy(parameter[4], (float *)cp["d3p"], 64);
      memcpy(parameter[5], (float *)cp["d3pp"], 64);
      memcpy(parameter[6], (float *)cp["s1p"], 64);
      memcpy(parameter[7], (float *)cp["s1pp"], 64);
      memcpy(parameter[8], (float *)cp["s2p"], 64);
      memcpy(parameter[9], (float *)cp["s2pp"], 64);
      memcpy(parameter[10], (float *)cp["s3p"], 64);
      memcpy(parameter[11], (float *)cp["s3pp"], 64);
      memcpy(parameter[12], (float *)cp["s4p"], 64);
      memcpy(parameter[13], (float *)cp["s4pp"], 64);
      memcpy(parameter[14], (float *)cp["s5p"], 64);
      memcpy(parameter[15], (float *)cp["s5pp"], 64);
      memcpy(parameter[16], (float *)cp["s6p"], 64);
      memcpy(parameter[17], (float *)cp["s6pp"], 64);
      memcpy(parameter[18], (float *)cp["s7p"], 64);
      memcpy(parameter[19], (float *)cp["s7pp"], 64);
      memcpy(parameter[20], (float *)cp["s8p"], 64);
      memcpy(parameter[21], (float *)cp["s8pp"], 64);
      memcpy(parameter[22], (float *)cp["ocp1"], 64);
      memcpy(parameter[23], (float *)cp["ocp2"], 64);
      memcpy(parameter[24], (float *)cp["gcp1"], 64);
      memcpy(parameter[25], (float *)cp["gcp2"], 64);
      memcpy(parameter[26], (float *)cp["gop1"], 64);
      memcpy(parameter[27], (float *)cp["gop2"], 64);
      memcpy(parameter[28], (float *)cp["onp1"], 64);
      memcpy(parameter[29], (float *)cp["onp2"], 64);
      memcpy(parameter[30], (float *)cp["brpi"], 64);
      memcpy(parameter[31], (float *)cp["brp1"], 64);
      memcpy(parameter[32], (float *)cp["brp2"], 64);

      // copy settings to internal memory
      memcpy(settings, (float *)cp["sett"], 64);
    }
  }

  ///**************************************************************************************************
  // * Function printPattern
  // * -------------------------------------------------------------------------------------------------
  // * Overview: prints pattern to Serial port
  // * Input: Nothingg
  // * Output: Nothing
  // **************************************************************************************************/
  void printPattern()
  { // PRINTS PATTERN TO SERIAL MONITOR
    //      //print out the pattern
    for (int i = 0; i < 16; i++)
    {
      for (int j = 0; j < 21; j++)
      {
        Serial.print(pattern[j][i]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }

    // print out the velocities
    for (int i = 0; i < 16; i++)
    {
      for (int j = 0; j < 21; j++)
      {
        Serial.print(velocity[j][i]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }
    // print out the digital voice parameters
    for (int i = 0; i < 16; i++)
    {
      for (int j = 0; j < 33; j++)
      {
        Serial.print(parameter[j][i]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }

    // print out settings
    for (int i = 0; i < 16; i++)
    {
      Serial.print(settings[i]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }

  ///**************************************************************************************************
  // * Function writePatternToSD
  // * -------------------------------------------------------------------------------------------------
  // * Overview: Writes a Pattern object to a CSV file on SD card
  // * Input:
  //          path: path on SD card to write pattern to
  // * Output:
  // **************************************************************************************************/
  void writePatternToSD(const char *path)
  {
    // clear out old data file
    if (SD.exists(path))
    {
//      Serial.println("Removing old csv");
      SD.remove(path);
//      Serial.println("Done");
    }

    // create new file
    File myFile = SD.open(path, FILE_WRITE);
    if (myFile)
    {
//      Serial.println("Writing headers to new CSV"); // writing header row to CSV
      myFile.println("kk,kv,s,sv,c1,c1v,c2,c2v,g,gv,d1,d1v,d1p,d1pp,d2,d2v,d2p,d2pp,d3,d3v,d3p,d3pp,s1,s1v,s1p,s1pp,s2,s2v,s2p,s2pp,s3,s3v,s3p,s3pp,s4,s4v,s4p,s4pp,s5,s5v,s5p,s5pp,s6,s6v,s6p,s6pp,s7,s7v,s7p,s7pp,s8,s8v,s8p,s8pp,sett,oc,ocv,ocp1,ocp2,gc,gcv,gcp1,gcp2,go,gov,gop1,gop2,on,onv,onp1,onp2,br,brv,brpi,brp1,brp2");
//      Serial.println("Headers written");

      // writing all pattern data to CSV
      for (int i = 0; i < 16; i++)
      {
        myFile.print(pattern[0][i]); // KICK
        myFile.print(",");
        myFile.print(velocity[0][i]);
        myFile.print(",");

        myFile.print(pattern[1][i]); // SNARE
        myFile.print(",");
        myFile.print(velocity[1][i]);
        myFile.print(",");

        myFile.print(pattern[2][i]); // CYNARE 1
        myFile.print(",");
        myFile.print(velocity[2][i]);
        myFile.print(",");

        myFile.print(pattern[3][i]); // CCYNARE 2
        myFile.print(",");
        myFile.print(velocity[3][i]);
        myFile.print(",");

        myFile.print(pattern[4][i]); // GLITCH
        myFile.print(",");
        myFile.print(velocity[4][i]);
        myFile.print(",");

        myFile.print(pattern[5][i]); // DIGITAL VOICE 1
        myFile.print(",");
        myFile.print(velocity[5][i]);
        myFile.print(",");
        myFile.print(parameter[0][i]);
        myFile.print(",");
        myFile.print(parameter[1][i]);
        myFile.print(",");

        myFile.print(pattern[6][i]); // DIGITAL VOICE 2
        myFile.print(",");
        myFile.print(velocity[6][i]);
        myFile.print(",");
        myFile.print(parameter[2][i]);
        myFile.print(",");
        myFile.print(parameter[3][i]);
        myFile.print(",");

        myFile.print(pattern[7][i]); // DIGITAL VOICE 3
        myFile.print(",");
        myFile.print(velocity[7][i]);
        myFile.print(",");
        myFile.print(parameter[4][i]);
        myFile.print(",");
        myFile.print(parameter[5][i]);
        myFile.print(",");

        myFile.print(pattern[8][i]); // SAMPLE VOICE 1
        myFile.print(",");
        myFile.print(velocity[8][i]);
        myFile.print(",");
        myFile.print(parameter[6][i]);
        myFile.print(",");
        myFile.print(parameter[7][i]);
        myFile.print(",");

        myFile.print(pattern[9][i]); // SAMPLE VOICE 2
        myFile.print(",");
        myFile.print(velocity[9][i]);
        myFile.print(",");
        myFile.print(parameter[8][i]);
        myFile.print(",");
        myFile.print(parameter[9][i]);
        myFile.print(",");

        myFile.print(pattern[10][i]); // SAMPLE VOICE 3
        myFile.print(",");
        myFile.print(velocity[10][i]);
        myFile.print(",");
        myFile.print(parameter[10][i]);
        myFile.print(",");
        myFile.print(parameter[11][i]);
        myFile.print(",");

        myFile.print(pattern[11][i]); // SAMPLE VOICE 4
        myFile.print(",");
        myFile.print(velocity[11][i]);
        myFile.print(",");
        myFile.print(parameter[12][i]);
        myFile.print(",");
        myFile.print(parameter[13][i]);
        myFile.print(",");

        myFile.print(pattern[12][i]); // SAMPLE VOICE 5
        myFile.print(",");
        myFile.print(velocity[12][i]);
        myFile.print(",");
        myFile.print(parameter[14][i]);
        myFile.print(",");
        myFile.print(parameter[15][i]);
        myFile.print(",");

        myFile.print(pattern[13][i]); // SAMPLE VOICE 6
        myFile.print(",");
        myFile.print(velocity[13][i]);
        myFile.print(",");
        myFile.print(parameter[16][i]);
        myFile.print(",");
        myFile.print(parameter[17][i]);
        myFile.print(",");

        myFile.print(pattern[14][i]); // SAMPLE VOICE 7
        myFile.print(",");
        myFile.print(velocity[14][i]);
        myFile.print(",");
        myFile.print(parameter[18][i]);
        myFile.print(",");
        myFile.print(parameter[19][i]);
        myFile.print(",");

        myFile.print(pattern[15][i]); // SAMPLE VOICE 8
        myFile.print(",");
        myFile.print(velocity[15][i]);
        myFile.print(",");
        myFile.print(parameter[20][i]);
        myFile.print(",");
        myFile.print(parameter[21][i]);
        myFile.print(",");

        myFile.print(settings[i]);
        myFile.print(",");

        myFile.print(pattern[16][i]); // Organ chords
        myFile.print(",");
        myFile.print(velocity[16][i]);
        myFile.print(",");
        myFile.print(parameter[22][i]);
        myFile.print(",");
        myFile.print(parameter[23][i]);
        myFile.print(",");

        myFile.print(pattern[17][i]); // Guitar chords
        myFile.print(",");
        myFile.print(velocity[17][i]);
        myFile.print(",");
        myFile.print(parameter[24][i]);
        myFile.print(",");
        myFile.print(parameter[25][i]);
        myFile.print(",");

        myFile.print(pattern[18][i]); // Guitar oneshots
        myFile.print(",");
        myFile.print(velocity[18][i]);
        myFile.print(",");
        myFile.print(parameter[26][i]);
        myFile.print(",");
        myFile.print(parameter[27][i]);
        myFile.print(",");

        myFile.print(pattern[19][i]); // Organ notes
        myFile.print(",");
        myFile.print(velocity[19][i]);
        myFile.print(",");
        myFile.print(parameter[28][i]);
        myFile.print(",");
        myFile.print(parameter[29][i]);
        myFile.print(",");

        myFile.print(pattern[20][i]); // breaks
        myFile.print(",");
        myFile.print(velocity[20][i]);
        myFile.print(",");
        myFile.print(parameter[30][i]);
        myFile.print(",");
        myFile.print(parameter[31][i]);
        myFile.print(",");
        myFile.println(parameter[32][i]);
      }
      myFile.close();
    }
  }

  ///**************************************************************************************************
  // * Function clearPattern
  // * -------------------------------------------------------------------------------------------------
  // * Overview: clears pattern by deactivating all steps and setting volume, and parameters to neutral values
  // *           tempo is set to 120 BPM
  // * Input: Nothing
  // * Output: Nothing
  // **************************************************************************************************/
  void clearPattern()
  {
    for (int i = 0; i < 16; i++)
    {
      for (int j = 0; j < 21; j++)
      {
        pattern[j][i] = 0;
        velocity[j][i] = 0;
      }

      for (int j = 0; j < 33; j++)
      {
        parameter[j][i] = 0;
      }
      settings[i] = 0;
    }
    settings[0] = 120; // set tempo to 120 BPM
  }
};
