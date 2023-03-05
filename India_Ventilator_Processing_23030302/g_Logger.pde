// https://forum.processing.org/beta/num_1196069582.html

import java.io.*;

class Logger
{
  String m_fileName;

  Logger(String fileName)
  {
    m_fileName = fileName;
  }

  void log(String line)
  {
    PrintWriter pw = null;
    try
    {
      pw = GetWriter();
      pw.println(line);
      println(line);
    }
    catch (IOException e)
    {
      e.printStackTrace(); // Dumb and primitive exception handling...
      println("ouch 1");
    }
    finally
    {
      if (pw != null)
      {
        pw.close();
      }
    }
  }

  void log(String[] lines)
  {
    PrintWriter pw = null;
    try
    {
      pw = GetWriter();
      for (int i = 0; i < lines.length; i++)
      {
        pw.println(lines[i]);
      }
    }
    catch (IOException e)
    {
      e.printStackTrace(); // Dumb and primitive exception handling...
      println("ouch 2");
    }
    finally
    {
      if (pw != null)
      {
        pw.close();
      }
    }
  }

  void log(String errorMessage, StackTraceElement[] ste)
  {
    PrintWriter pw = null;
    try
    {
      pw = GetWriter();
      pw.println(errorMessage);
      for (int i = 0; i < ste.length; i++)
      {
        pw.println("\tat " + ste[i].getClassName() + "." + ste[i].getMethodName() +
          "(" + ste[i].getFileName() + ":" + ste[i].getLineNumber() + ")"
          );
      }
    }                         
    catch (IOException e)
    {
      e.printStackTrace(); // Dumb and primitive exception handling...
      println("ouch 3");
    }
    finally
    {
      if (pw != null)
      {
        pw.close();
      }
    }
  }

  private PrintWriter GetWriter() throws IOException
  {
    // FileWriter with append, BufferedWriter for performance
    // (although we close each time, not so efficient...), PrintWriter for convenience
    return new PrintWriter(new BufferedWriter(new FileWriter(m_fileName, true)));
  }

  void rename() {
    int  Total_Run_Time_Since_Last_Run_Command_old=0;
    //    File f_old= new File(sketchPath("") + FileName);
    //    File f_new= new File(sketchPath("") +NewFileName);
    File f_old= new File(sketchPath("") + "\\Logs\\" + FileName);
    println("existing FileName to be renamed - " + FileName);
    File f_new= new File(sketchPath("") + "\\Logs\\" + NewFileName);
    println("the new Filename for renaming - " + NewFileName);    
    boolean success = f_old.renameTo(f_new); 
    //    boolean success = file.renameTo(file2);
    println("Success was " + success);
    f_old=f_new;
    Total_Run_Time_Since_Last_Run_Command_old=Total_Run_Time_Today;
  }
}
