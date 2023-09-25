// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE05
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public class FLARE05
  {
    public static string A;
    public static int B;
    public static int C;
    public static int D;
    public static byte[] E;
    public static int F;
    public static int G;
    public static byte[] H;

    public static FLARE07 flared_19()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE07 flare_19()
    {
      try
      {
        return FLARE05.flared_19();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE07) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static FLARE07 flared_20()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE07 flare_20()
    {
      try
      {
        return FLARE05.flared_20();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE07) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static FLARE07 flared_21()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE07 flare_21()
    {
      try
      {
        return FLARE05.flared_21();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE07) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static FLARE07 flared_22()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE07 flare_22()
    {
      try
      {
        return FLARE05.flared_22();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE07) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static bool flared_23(out FLARE07 r)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_23(out FLARE07 r)
    {
      try
      {
        return FLARE05.flared_23(out r);
      }
      catch (InvalidProgramException ex)
      {
        r = FLARE07.B;
        object[] a = new object[1]{ (object) r };
        bool flag = (bool) FLARE15.flare_70(ex, a);
        r = (FLARE07) a[0];
        return flag;
      }
    }

    public static bool flared_24(out FLARE07 r)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_24(out FLARE07 r)
    {
      try
      {
        return FLARE05.flared_24(out r);
      }
      catch (InvalidProgramException ex)
      {
        r = FLARE07.B;
        object[] a = new object[1]{ (object) r };
        bool flag = (bool) FLARE15.flare_70(ex, a);
        r = (FLARE07) a[0];
        return flag;
      }
    }

    public static bool flared_25(out FLARE07 r)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_25(out FLARE07 r)
    {
      try
      {
        return FLARE05.flared_25(out r);
      }
      catch (InvalidProgramException ex)
      {
        r = FLARE07.B;
        object[] a = new object[1]{ (object) r };
        bool flag = (bool) FLARE15.flare_70(ex, a);
        r = (FLARE07) a[0];
        return flag;
      }
    }

    public static bool flared_26(out FLARE07 r)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_26(out FLARE07 r)
    {
      try
      {
        return FLARE05.flared_26(out r);
      }
      catch (InvalidProgramException ex)
      {
        r = FLARE07.B;
        object[] a = new object[1]{ (object) r };
        bool flag = (bool) FLARE15.flare_70(ex, a);
        r = (FLARE07) a[0];
        return flag;
      }
    }

    public static bool flared_27()
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_27()
    {
      try
      {
        return FLARE05.flared_27();
      }
      catch (InvalidProgramException ex)
      {
        return (bool) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static void flared_28(byte[] s)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_28(byte[] s)
    {
      try
      {
        FLARE05.flared_28(s);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, new object[1]
        {
          (object) s
        });
      }
    }

    public static void flared_29(FLARE06.DomT dt, string d)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_29(FLARE06.DomT dt, string d)
    {
      try
      {
        FLARE05.flared_29(dt, d);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, new object[2]
        {
          (object) dt,
          (object) d
        });
      }
    }

    public static bool flared_30(out byte[] r)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_30(out byte[] r)
    {
      try
      {
        try
        {
          return FLARE05.flared_30(out r);
        }
        catch (InvalidProgramException ex)
        {
          r = (byte[]) null;
          object[] a = new object[1]{ (object) r };
          bool flag = (bool) FLARE15.flare_70(ex, a);
          r = (byte[]) a[0];
          return flag;
        }
      }
      catch
      {
        ++FLARE05.B;
        r = (byte[]) null;
        return false;
      }
    }

    public static bool flared_31(Func<bool> fn)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_31(Func<bool> fn)
    {
      try
      {
        return FLARE05.flared_31(fn);
      }
      catch (InvalidProgramException ex)
      {
        return (bool) FLARE15.flare_70(ex, new object[1]
        {
          (object) fn
        });
      }
    }

    public static bool flared_32(byte[] d)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_32(byte[] d)
    {
      try
      {
        return FLARE05.flared_32(d);
      }
      catch (InvalidProgramException ex)
      {
        return (bool) FLARE15.flare_70(ex, new object[1]
        {
          (object) d
        });
      }
    }

    public static bool flared_33(byte[] r)
    {
    }

    public static bool flare_33(byte[] r)
    {
      try
      {
        return FLARE05.flared_33(r);
      }
      catch (InvalidProgramException ex)
      {
        return (bool) FLARE15.flare_70(ex, new object[1]
        {
          (object) r
        });
      }
    }

    public static bool flared_34(int s)
    {
      // ISSUE: unable to decompile the method.
    }

    public static bool flare_34(int s)
    {
      try
      {
        return FLARE05.flared_34(s);
      }
      catch (InvalidProgramException ex)
      {
        return (bool) FLARE15.flare_70(ex, new object[1]
        {
          (object) s
        });
      }
    }
  }
}
