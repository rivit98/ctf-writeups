// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE14
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Security.Cryptography;

namespace FlareOn.Backdoor
{
  public class FLARE14
  {
    public static IncrementalHash h = (IncrementalHash) null;
    public static string sh = "";
    public static bool _bool = true;
    public static List<byte[]> ListData;

    public static uint flared_51(string s)
    {
      // ISSUE: unable to decompile the method.
    }

    public static uint flare_51(string s)
    {
      try
      {
        return FLARE14.flared_51(s);
      }
      catch (InvalidProgramException ex)
      {
        return (uint) FLARE15.flare_70(ex, new object[1]
        {
          (object) s
        });
      }
    }

    public static FLARE07 flare_52()
    {
      try
      {
        return FLARE14.flared_56();
      }
      catch (InvalidProgramException ex1)
      {
        try
        {
          return (FLARE07) FLARE15.flare_70(ex1, (object[]) null);
        }
        catch (Exception ex2)
        {
          return FLARE07.B;
        }
      }
    }

    public static void flared_52(object sender, NotifyCollectionChangedEventArgs e)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_53(object sender, NotifyCollectionChangedEventArgs f)
    {
      try
      {
        FLARE14.flared_52(sender, f);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, new object[2]
        {
          sender,
          (object) f
        });
      }
    }

    public static string flared_53(string s)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_54(string s)
    {
      try
      {
        return FLARE14.flared_53(s);
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, new object[1]
        {
          (object) s
        });
      }
    }

    public static void flared_54()
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_55()
    {
      try
      {
        FLARE14.flared_54();
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static void flared_55(int i, string s)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_56(int i, string s)
    {
      try
      {
        FLARE14.flared_55(i, s);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, new object[2]
        {
          (object) i,
          (object) s
        });
      }
    }

    public static FLARE07 flared_56()
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flared_57()
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_57()
    {
      try
      {
        return FLARE14.flared_57();
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, (object[]) null);
      }
    }
  }
}
