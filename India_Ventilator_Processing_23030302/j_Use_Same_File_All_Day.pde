void Use_Same_Name_All_Day() {
  String Log_Filename_Prototype = "Kabako Ventilator Log 0000 Seconds yymmdd01.csv";
  //                                         1         2         3         4
  //                               01234567890123456789012345678901234567890123456
  String LogPath = sketchPath("") + "\\Logs\\";
  //  String Date_String = Calculate_Date_String_Of_Today();
  //  println("________");
  String End_Of_Filename = (Log_Filename_Prototype.substring(26, 35));
  //  println("a" + End_Of_Filename);  
  End_Of_Filename = End_Of_Filename + Calculate_Date_String_Of_Today();
  //  println("b" + End_Of_Filename);  
  End_Of_Filename = End_Of_Filename + Log_Filename_Prototype.substring(41, 47);
  //  println("c" + End_Of_Filename);
  String[] filenames = listFileNames(LogPath);
  //  printArray(filenames);
  //  println(LogPath);
  for (int j = 0; j < filenames.length; j++) { //Cycle through the filenames looking for log file for today's date.
    // A filename with the correct characters at the beginning of its name has been found.
    if (filenames[j].indexOf(Log_Filename_Prototype.substring(0, 22)) == 0) {
      int Position_Of_End_Character_Elapsed_Time = 0;
      if ( (Position_Of_End_Character_Elapsed_Time = filenames[j].indexOf(End_Of_Filename)) > 0 ) {
        Position_Of_End_Character_Elapsed_Time = Position_Of_End_Character_Elapsed_Time ;
        //        println("ET last character = " + Position_Of_End_Character_Elapsed_Time);
        // A filename with the correct characters at the end of its name has been found.
        // Get the Elapsed_Time from the filename.
        Total_Run_Time_Today = Integer.parseInt(filenames[j].substring(22, Position_Of_End_Character_Elapsed_Time));
        //        Total_Run_Time_Today = Integer.parseInt(filenames[j].substring(22,24));
        //       println("-" + Total_Run_Time_Today  + "-"); 
        loggerObject  = new Logger (sketchPath("") + "\\Logs\\" + filenames[j] );  // use new here please
        println(" LO#1 " + loggerObject);
        println("FileName is effectively: " + filenames[j]);
        FileName = filenames[j];
      }
    } else {
      //  FileName = Log_Filename_Prototype.substring(0, 34) +
      loggerObject  = new Logger (sketchPath("") + "\\Logs\\" + Log_Filename_Prototype.substring(0, 26) + End_Of_Filename);  // use new here please
      println(" LO#2 " + loggerObject);
      //      println("We made a loggerObject.");
    }
  }
  //  println(" LO#3 " + loggerObject);
  if (loggerObject == null) {  // No log file was found for today's date so we will create a loggerObject and when it gets logged to a file will be created.
    loggerObject  = new Logger (sketchPath("") + "\\Logs\\" + Log_Filename_Prototype.substring(0, 26) + End_Of_Filename);  // use new here please
    println(" LO#4 " + loggerObject);
    FileName =  Log_Filename_Prototype.substring(0, 26) + End_Of_Filename;
        println("FileName having found no files, is: " + FileName);
  }
  //  println("loggerObject hey = " + loggerObject);
  //  FileName = FileName + Date_String + "01.csv";
  //  loggerObject  = new Logger (sketchPath("") + "\\Logs\\" + FileName);  // use new here please
}

String Calculate_Date_String_Of_Today() {
  int Year_Short = year() - 2000;
  String Month = "0";
  int Month_Lead_Zero = month();
  if (Month_Lead_Zero < 10) {
    Month = Month + str(Month_Lead_Zero);
  } else {
    Month = str(Month_Lead_Zero);
  }
  String Day = "0";
  int Day_Lead_Zero = day();
  if (Day_Lead_Zero < 10) {
    Day = Day + str(Day_Lead_Zero);
  } else {
    Day = str(Day_Lead_Zero);
  }
  String Date_String =Year_Short + Month + Day;

  return(Date_String);
}

// This function returns all the files in a directory as an array of Strings  
String[] listFileNames(String dir) {
  File file = new File(dir);
  if (file.isDirectory()) {
    String names[] = file.list();
    return names;
  } else {
    // If it's not a directory
    return null;
  }
}
