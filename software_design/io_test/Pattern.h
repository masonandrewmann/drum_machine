class Pattern {
  public:
    int32_t pattern[16][16] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    float velocity[16][16] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int32_t parameter[14][16] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    const int sdChipSelect = BUILTIN_SDCARD;
    const int flashChipSelect = 6;
    Pattern(){
    }

    void readFromSD(const char* path){ // READS PATTERN FROM CSV ON SD CARD
//      if (!SD.begin(sdChipSelect)) {
//        Serial.println("Card failed, or not present");
//      }

      // format for drum pattern
//      CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLL", /*has_header*/ true, /*delimiter*/ ','); // for 8 innst pattern
        CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLLLfLLfLLfLLfLLfLLfLLfLLfL", /*has_header*/ true, /*delimiter*/ ','); // for 16 innst pattern
//        CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLL LLLLLLLLLLLLLLLLLLLLLLLL", /*has_header*/ true, /*delimiter*/ ','); // for 16 innst pattern

      if (cp.readSDfile(path)) {

      // copy pattern to internal memory
        memcpy(pattern[0],(int32_t*)cp["kk"], 64);
        memcpy(pattern[1],(int32_t*)cp["s"], 64);
        memcpy(pattern[2],(int32_t*)cp["c1"], 64);
        memcpy(pattern[3],(int32_t*)cp["c2"], 64);
        memcpy(pattern[4],(int32_t*)cp["g"], 64);
        memcpy(pattern[5],(int32_t*)cp["d1"], 64);
        memcpy(pattern[6],(int32_t*)cp["d2"], 64);
        memcpy(pattern[7],(int32_t*)cp["d3"], 64);
        memcpy(pattern[8],(int32_t*)cp["d4"], 64);
        memcpy(pattern[9],(int32_t*)cp["d5"], 64);
        memcpy(pattern[10],(int32_t*)cp["d6"], 64);
        memcpy(pattern[11],(int32_t*)cp["d7"], 64);
        memcpy(pattern[12],(int32_t*)cp["d8"], 64);
        memcpy(pattern[13],(int32_t*)cp["d9"], 64);
        memcpy(pattern[14],(int32_t*)cp["d10"], 64);
        memcpy(pattern[15],(int32_t*)cp["d11"], 64);

//        memcpy(instSteps[0],(int32_t*)cp["kk"], 64);
//        memcpy(instSteps[1],(int32_t*)cp["s"], 64);
//        memcpy(instSteps[2],(int32_t*)cp["c1"], 64);
//        memcpy(instSteps[3],(int32_t*)cp["c2"], 64);
//        memcpy(instSteps[4],(int32_t*)cp["g"], 64);
//        memcpy(instSteps[5],(int32_t*)cp["d1"], 64);
//        memcpy(instSteps[6],(int32_t*)cp["d2"], 64);
//        memcpy(instSteps[7],(int32_t*)cp["d3"], 64);
      // dont know why the above memcpy doesn't work but this for loop is fine for now!
//      for (int i = 0; i < 16; i++){
//        for (int j = 0; j < 16; j++){
//          instSteps[i][j] = pattern[i][j];
//        }
//      }

//  int32_t *numbers = (int32_t*)cp["dv2"];
//  
//      for (int i = 0; i < 16; i++){
//        Serial.println(numbers[i]);
////        Serial.println((int32_t*)cp["d4v"][i]);
//      }

      // copy velocities to internal memory
        memcpy(velocity[0],(float*)cp["kv"], 64);
        memcpy(velocity[1],(float*)cp["sv"], 64);
        memcpy(velocity[2],(float*)cp["c1v"], 64);
        memcpy(velocity[3],(float*)cp["c2v"], 64);
        memcpy(velocity[4],(float*)cp["gv"], 64);
        memcpy(velocity[5],(float*)cp["d1v"], 64);
        memcpy(velocity[6],(float*)cp["d2v"], 64);
        memcpy(velocity[7],(float*)cp["d3v"], 64);
        memcpy(velocity[8],(float*)cp["d4v"], 64);
        memcpy(velocity[9],(float*)cp["d5v"], 64);
        memcpy(velocity[10],(float*)cp["d6v"], 64);
        memcpy(velocity[11],(float*)cp["d7v"], 64);
        memcpy(velocity[12],(float*)cp["d8v"], 64);
        memcpy(velocity[13],(float*)cp["d9v"], 64);
        memcpy(velocity[14],(float*)cp["d10v"], 64);
        memcpy(velocity[15],(float*)cp["d11v"], 64);

      // copy digital voice parameters to internal memory
        memcpy(parameter[0],(int32_t*)cp["d1p"], 64);
        memcpy(parameter[1],(int32_t*)cp["d1pp"], 64);
        memcpy(parameter[2],(int32_t*)cp["d2p"], 64);
        memcpy(parameter[3],(int32_t*)cp["d2pp"], 64);
        memcpy(parameter[4],(int32_t*)cp["d3p"], 64);
        memcpy(parameter[5],(int32_t*)cp["d3pp"], 64);
        memcpy(parameter[6],(int32_t*)cp["d4p"], 64);
        memcpy(parameter[7],(int32_t*)cp["d5p"], 64);
        memcpy(parameter[8],(int32_t*)cp["d6p"], 64);
        memcpy(parameter[9],(int32_t*)cp["d7p"], 64);
        memcpy(parameter[10],(int32_t*)cp["d8p"], 64);
        memcpy(parameter[11],(int32_t*)cp["d9p"], 64);
        memcpy(parameter[12],(int32_t*)cp["d10p"], 64);
        memcpy(parameter[13],(int32_t*)cp["d11p"], 64);
      }
    }

    void readFromFlash(const char* path){ // READS PATTERN FROM CSV ON SD CARD

      // format for drum pattern
//      CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLL", /*has_header*/ true, /*delimiter*/ ','); // for 8 innst pattern
        CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLLLfLLfLLfLLfLLfLLfLLfLLfL", /*has_header*/ true, /*delimiter*/ ','); // for 16 innst pattern
//        CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLL LLLLLLLLLLLLLLLLLLLLLLLL", /*has_header*/ true, /*delimiter*/ ','); // for 16 innst pattern

      if (cp.readSDfile(path)) {

      // copy pattern to internal memory
        memcpy(pattern[0],(int32_t*)cp["kk"], 64);
        memcpy(pattern[1],(int32_t*)cp["s"], 64);
        memcpy(pattern[2],(int32_t*)cp["c1"], 64);
        memcpy(pattern[3],(int32_t*)cp["c2"], 64);
        memcpy(pattern[4],(int32_t*)cp["g"], 64);
        memcpy(pattern[5],(int32_t*)cp["d1"], 64);
        memcpy(pattern[6],(int32_t*)cp["d2"], 64);
        memcpy(pattern[7],(int32_t*)cp["d3"], 64);
        memcpy(pattern[8],(int32_t*)cp["d4"], 64);
        memcpy(pattern[9],(int32_t*)cp["d5"], 64);
        memcpy(pattern[10],(int32_t*)cp["d6"], 64);
        memcpy(pattern[11],(int32_t*)cp["d7"], 64);
        memcpy(pattern[12],(int32_t*)cp["d8"], 64);
        memcpy(pattern[13],(int32_t*)cp["d9"], 64);
        memcpy(pattern[14],(int32_t*)cp["d10"], 64);
        memcpy(pattern[15],(int32_t*)cp["d11"], 64);

//        memcpy(instSteps[0],(int32_t*)cp["kk"], 64);
//        memcpy(instSteps[1],(int32_t*)cp["s"], 64);
//        memcpy(instSteps[2],(int32_t*)cp["c1"], 64);
//        memcpy(instSteps[3],(int32_t*)cp["c2"], 64);
//        memcpy(instSteps[4],(int32_t*)cp["g"], 64);
//        memcpy(instSteps[5],(int32_t*)cp["d1"], 64);
//        memcpy(instSteps[6],(int32_t*)cp["d2"], 64);
//        memcpy(instSteps[7],(int32_t*)cp["d3"], 64);
      // dont know why the above memcpy doesn't work but this for loop is fine for now!
//      for (int i = 0; i < 16; i++){
//        for (int j = 0; j < 16; j++){
//          instSteps[i][j] = pattern[i][j];
//        }
//      }

//  int32_t *numbers = (int32_t*)cp["dv2"];
//  
//      for (int i = 0; i < 16; i++){
//        Serial.println(numbers[i]);
////        Serial.println((int32_t*)cp["d4v"][i]);
//      }

      // copy velocities to internal memory
        memcpy(velocity[0],(float*)cp["kv"], 64);
        memcpy(velocity[1],(float*)cp["sv"], 64);
        memcpy(velocity[2],(float*)cp["c1v"], 64);
        memcpy(velocity[3],(float*)cp["c2v"], 64);
        memcpy(velocity[4],(float*)cp["gv"], 64);
        memcpy(velocity[5],(float*)cp["d1v"], 64);
        memcpy(velocity[6],(float*)cp["d2v"], 64);
        memcpy(velocity[7],(float*)cp["d3v"], 64);
        memcpy(velocity[8],(float*)cp["d4v"], 64);
        memcpy(velocity[9],(float*)cp["d5v"], 64);
        memcpy(velocity[10],(float*)cp["d6v"], 64);
        memcpy(velocity[11],(float*)cp["d7v"], 64);
        memcpy(velocity[12],(float*)cp["d8v"], 64);
        memcpy(velocity[13],(float*)cp["d9v"], 64);
        memcpy(velocity[14],(float*)cp["d10v"], 64);
        memcpy(velocity[15],(float*)cp["d11v"], 64);

      // copy digital voice parameters to internal memory
        memcpy(parameter[0],(int32_t*)cp["d1p"], 64);
        memcpy(parameter[1],(int32_t*)cp["d1pp"], 64);
        memcpy(parameter[2],(int32_t*)cp["d2p"], 64);
        memcpy(parameter[3],(int32_t*)cp["d2pp"], 64);
        memcpy(parameter[4],(int32_t*)cp["d3p"], 64);
        memcpy(parameter[5],(int32_t*)cp["d3pp"], 64);
        memcpy(parameter[6],(int32_t*)cp["d4p"], 64);
        memcpy(parameter[7],(int32_t*)cp["d5p"], 64);
        memcpy(parameter[8],(int32_t*)cp["d6p"], 64);
        memcpy(parameter[9],(int32_t*)cp["d7p"], 64);
        memcpy(parameter[10],(int32_t*)cp["d8p"], 64);
        memcpy(parameter[11],(int32_t*)cp["d9p"], 64);
        memcpy(parameter[12],(int32_t*)cp["d10p"], 64);
        memcpy(parameter[13],(int32_t*)cp["d11p"], 64);
      }
    }

    void printPattern(){ // PRINTS PATTERN TO SERIAL MONITOR
//      //print out the pattern
      for (int i = 0 ; i < 16; i++){
        for (int j = 0; j < 16; j++){
        Serial.print(pattern[j][i]);
        Serial.print(" ");
        }
        Serial.println(" ");
      }

      //print out the velocities
      for (int i = 0 ; i < 16; i++){
        for (int j = 0; j < 16; j++){
          Serial.print(velocity[j][i]);
          Serial.print(" ");
        }
        Serial.println(" ");
      }
//
//      //print out the digital voice parameters
      for (int i = 0 ; i < 16; i++){
        for (int j = 0; j < 14; j++){
        Serial.print(parameter[j][i]);
        Serial.print(" ");
        }
      Serial.println(" ");
      }
    }


///**************************************************************************************************
// * Function writePatternToSD
// * -------------------------------------------------------------------------------------------------
// * Overview: Writes a Pattern object to a csv file on SD card
// * Input:
//          patt: Pattern object to be written to SD Card
//          path: path on SD card to write object to ( in format 'FILEPATH/NAME.TXT'
// * Output:
// **************************************************************************************************/
void writePatternToSD(const char* path)
{
  //clear out old data file
  if (SD.exists(path))
  {
    Serial.println("Removing old csv");
    SD.remove(path);
    Serial.println("Done");
  }

  //create new file
  File myFile = SD.open(path, FILE_WRITE);
  if (myFile){
    Serial.println("Writing headers to new CSV");
    myFile.println("kk,kv,s,sv,c1,c1v,c2,c2v,g,gv,d1,d1v,d1p,d1pp,d2,d2v,d2p,d2pp,d3,d3v,d3p,d3pp,d4,d4v,d4p,d5,d5v,d5p,d6,d6v,d6p,d7,d7v,d7p,d8,d8v,d8p,d9,d9v,d9p,d10,d10v,d10p,d11,d11v,d11p");
    Serial.println("Headers written");

    //writing data
    for (int i = 0; i < 16; i++){
      myFile.print(pattern[0][i]); //KICK
      myFile.print(",");
      myFile.print(velocity[0][i]);
      myFile.print(",");

      myFile.print(pattern[1][i]); //SNARE
      myFile.print(",");
      myFile.print(velocity[1][i]);
      myFile.print(",");

      myFile.print(pattern[2][i]); //CYNARE 1
      myFile.print(",");
      myFile.print(velocity[2][i]);
      myFile.print(",");

      myFile.print(pattern[3][i]); //CCYNARE 2
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

      myFile.print(pattern[8][i]); // DIGITAL VOICE 4
      myFile.print(",");
      myFile.print(velocity[8][i]);
      myFile.print(",");
      myFile.print(parameter[6][i]);
      myFile.print(",");

      myFile.print(pattern[9][i]); // DIGITAL VOICE 5
      myFile.print(",");
      myFile.print(velocity[9][i]);
      myFile.print(",");
      myFile.print(parameter[7][i]);
      myFile.print(",");

      myFile.print(pattern[10][i]); // DIGITAL VOICE 6
      myFile.print(",");
      myFile.print(velocity[10][i]);
      myFile.print(",");
      myFile.print(parameter[8][i]);
      myFile.print(",");

      myFile.print(pattern[11][i]); // DIGITAL VOICE 7
      myFile.print(",");
      myFile.print(velocity[11][i]);
      myFile.print(",");
      myFile.print(parameter[9][i]);
      myFile.print(",");

      myFile.print(pattern[12][i]); // DIGITAL VOICE 8
      myFile.print(",");
      myFile.print(velocity[12][i]);
      myFile.print(",");
      myFile.print(parameter[10][i]);
      myFile.print(",");

      myFile.print(pattern[13][i]); // DIGITAL VOICE 9
      myFile.print(",");
      myFile.print(velocity[13][i]);
      myFile.print(",");
      myFile.print(parameter[11][i]);
      myFile.print(",");

      myFile.print(pattern[14][i]); // DIGITAL VOICE 10
      myFile.print(",");
      myFile.print(velocity[14][i]);
      myFile.print(",");
      myFile.print(parameter[12][i]);
      myFile.print(",");

      myFile.print(pattern[15][i]); // DIGITAL VOICE 11
      myFile.print(",");
      myFile.print(velocity[15][i]);
      myFile.print(",");
      myFile.println(parameter[13][i]);
  }

  myFile.close();
  }
}
};
