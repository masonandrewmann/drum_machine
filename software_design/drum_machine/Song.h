class Song
{
public:
  int32_t patterns[65] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  int32_t settings[65] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  //...
  // [48-63] pattern name in ascii

  char name[17] = "                \0";


  const int sdChipSelect = BUILTIN_SDCARD;
  const int flashChipSelect = 6;
  
  Song()
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
    CSV_Parser cp(/*format*/ "Lf", /*has_header*/ true, /*delimiter*/ ',');

    if (cp.readSDfile(path))
    {
      memcpy(patterns, (int32_t *)cp["patt"], 260);
      memcpy(settings, (float *)cp["sett"], 260);
      
      int ind = 0;
      for (int i = 48; i < 64; i++){
        if (settings[i] == 0){
          name[ind] = ' ';
        } else {
          name[ind] = settings[i];
        }

        ind += 1;
      }
//      name[0] = 'k';
      name[16] = '\0';
//      Serial.println(name);
      
    }
  }

 ///**************************************************************************************************
  // * Function printPattern
  // * -------------------------------------------------------------------------------------------------
  // * Overview: prints song on serial port up until -1
  // * Input:
  // * Output: Nothing
  // **************************************************************************************************/
  void printPattern()
  { // PRINTS PATTERN TO SERIAL MONITOR
    //      //print out the pattern
    Serial.println(name);
    for (int i = 0; i < 64; i++){
      if (patterns[i] == -1) break;
      Serial.print(patterns[i]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }

  ///**************************************************************************************************
  // * Function writeSongToSD
  // * -------------------------------------------------------------------------------------------------
  // * Overview: Writes a Pattern object to a CSV file on SD card
  // * Input:
  //          path: path on SD card to write pattern to
  // * Output:
  // **************************************************************************************************/
  void writeSongToSD(const char *path)
  {
    //move name to settings array
    int ind = 0;
      for (int i = 48; i < 64; i++){
        if(name[ind] == ' '){
          settings[i] = 0;
        } else {
          settings[i] = name[ind];
        }
        ind += 1;
      }
      
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
      myFile.println("patt,sett");
//      Serial.println("Headers written");

      // writing all pattern data to CSV
      for (int i = 0; i < 65; i++)
      {
        myFile.print(patterns[i]); // KICK
        myFile.print(",");
        myFile.println(settings[i]);
      }
      myFile.close();
    }
  }

  ///**************************************************************************************************
  // * Function clearSong
  // * -------------------------------------------------------------------------------------------------
  // * Overview: clears song by setting first pattern to 0 and second to -1
  // * Input: Nothing
  // * Output: Nothing
  // **************************************************************************************************/
  void clearSong()
  {
    for (int i = 0; i < 16; i++){
      patterns[i] = 0;
      settings[i] = 0;
    }
    patterns[1] = -1;
  }
};
