// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE02
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public class FLARE02
  {
    public static string flared_02(string c)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_03(string c)
    {
      try
      {
        return FLARE02.flared_02(c);
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, new object[1]
        {
          (object) c
        });
      }
    }

    public static string flared_03(string c)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_04(string c)
    {
      try
      {
        return FLARE02.flared_03(c);
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, new object[1]
        {
          (object) c
        });
      }
    }

    public static string flared_04(string f, string a)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_05(string f, string a)
    {
      try
      {
        return FLARE02.flared_04(f, a);
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, new object[2]
        {
          (object) f,
          (object) a
        });
      }
    }

    public static string flared_05(string r)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_06(string r)
    {
      try
      {
        try
        {
          return FLARE02.flared_05(r);
        }
        catch (InvalidProgramException ex)
        {
          return (string) FLARE15.flare_70(ex, new object[1]
          {
            (object) r
          });
        }
      }
      catch
      {
        return r;
      }
    }
  }
}
