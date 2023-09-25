// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE03
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public class FLARE03
  {
    public static int min_alive_delay = 2160000;
    public static int max_alive_delay = 2880000;
    public static int min_comm_delay = 0;
    public static int max_comm_delay = 1;
    public static int min_check_delay = 180000;
    public static int max_check_delay = 270000;
    public static int min_retry_delay = 30000;
    public static int max_retry_delay = 42000;
    public static int max_try = 7;
    public static int task_timeout = 15000;
    public static int send_count = 12;
    public static string chars_domain = "abcdefghijklmnopqrstuvwxyz0123456789";
    public static string chars_counter = "amsjl6zci20dbt35guhw7n1fqvx4k8y9rpoe";
    public static string alive_key = "flareon";
    public static string[] _domains = new string[1]
    {
      "flare-on.com"
    };
    public static int? _agent_id = new int?();
    public static int _counter;
    public static int _max_counter = 46656;

    public static void flared_06()
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_07()
    {
      try
      {
        FLARE03.flared_06();
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static void flared_07(int a)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_08(int a)
    {
      try
      {
        FLARE03.flared_07(a);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, new object[1]
        {
          (object) a
        });
      }
    }

    public static void flared_08()
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_09()
    {
      try
      {
        FLARE03.flared_08();
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static int flared_09()
    {
      // ISSUE: unable to decompile the method.
    }

    public static int flare_10()
    {
      try
      {
        return FLARE03.flared_09();
      }
      catch (InvalidProgramException ex)
      {
        return (int) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static int? flared_10()
    {
      // ISSUE: unable to decompile the method.
    }

    public static int? flare_11()
    {
      try
      {
        return FLARE03.flared_10();
      }
      catch (InvalidProgramException ex)
      {
        return (int?) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static bool flared_11()
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_12()
    {
      try
      {
        try
        {
          return FLARE03.flared_11();
        }
        catch (InvalidProgramException ex)
        {
          return (bool) FLARE15.flare_70(ex, (object[]) null);
        }
      }
      catch (Exception ex)
      {
        return false;
      }
    }

    public static bool flared_12()
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_13()
    {
      try
      {
        try
        {
          return FLARE03.flared_12();
        }
        catch (InvalidProgramException ex)
        {
          return (bool) FLARE15.flare_70(ex, (object[]) null);
        }
      }
      catch (Exception ex)
      {
        return false;
      }
    }

    public static string flared_13()
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_14()
    {
      try
      {
        return FLARE03.flared_13();
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static string flared_14()
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_15()
    {
      try
      {
        return FLARE03.flared_14();
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static string flared_15(string d)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_16(string drive)
    {
      try
      {
        return FLARE03.flared_15(drive);
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, new object[1]
        {
          (object) drive
        });
      }
    }

    public static string flared_16()
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_17()
    {
      try
      {
        return FLARE03.flared_16();
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, (object[]) null);
      }
    }
  }
}
