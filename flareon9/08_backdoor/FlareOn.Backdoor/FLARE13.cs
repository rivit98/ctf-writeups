// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE13
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;
using System.Collections.Generic;

namespace FlareOn.Backdoor
{
  public class FLARE13
  {
    public static Dictionary<FLARE13.FLARE16, FLARE08> t;

    public static FLARE08 cs { get; private set; }

    public static void flared_48()
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_48()
    {
      try
      {
        FLARE13.flared_48();
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static FLARE08 flared_49(FLARE07 c)
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE08 flare_49(FLARE07 c)
    {
      try
      {
        return FLARE13.flared_49(c);
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE08) FLARE15.flare_70(ex, new object[1]
        {
          (object) c
        });
      }
    }

    public static FLARE08 flared_50(FLARE07 c)
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE08 flare_50(FLARE07 c)
    {
      try
      {
        return FLARE13.flared_50(c);
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE08) FLARE15.flare_70(ex, new object[1]
        {
          (object) c
        });
      }
    }

    public class FLARE16
    {
      private readonly FLARE08 cs;
      private readonly FLARE07 c;

      public FLARE16(FLARE08 cs, FLARE07 c)
      {
        this.cs = cs;
        this.c = c;
      }

      public override int GetHashCode() => 17 + 31 * this.cs.GetHashCode() + 31 * this.c.GetHashCode();

      public override bool Equals(object obj) => obj is FLARE13.FLARE16 flarE16 && this.cs == flarE16.cs && this.c == flarE16.c;
    }
  }
}
