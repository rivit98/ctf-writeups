// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE11
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public class FLARE11
  {
    public static uint[] state;
    public static uint f;
    public static uint m;
    public static uint u;
    public static uint s;
    public static uint b;
    public static uint t;
    public static uint c;
    public static uint l;
    public static uint index;
    public static uint lower_mask;
    public static uint upper_mask;

    public static void flared_42(uint s = 5489)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_41(uint s = 5489)
    {
      try
      {
        FLARE11.flared_42(s);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, new object[1]
        {
          (object) s
        });
      }
    }

    public static void flared_43()
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_42()
    {
      try
      {
        FLARE11.flared_43();
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static uint flared_44()
    {
      // ISSUE: unable to decompile the method.
    }

    public static uint flare_43()
    {
      try
      {
        return FLARE11.flared_44();
      }
      catch (InvalidProgramException ex)
      {
        return (uint) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static int flared_45(int mn, int mx)
    {
      // ISSUE: unable to decompile the method.
    }

    public static int flare_44(int mn, int mx)
    {
      try
      {
        return FLARE11.flared_45(mn, mx);
      }
      catch (InvalidProgramException ex)
      {
        return (int) FLARE15.flare_70(ex, new object[2]
        {
          (object) mn,
          (object) mx
        });
      }
    }

    public static uint flared_46(long n)
    {
      // ISSUE: unable to decompile the method.
    }

    public static uint flare_45(long n)
    {
      try
      {
        return FLARE11.flared_46(n);
      }
      catch (InvalidProgramException ex)
      {
        return (uint) FLARE15.flare_70(ex, new object[1]
        {
          (object) n
        });
      }
    }
  }
}
