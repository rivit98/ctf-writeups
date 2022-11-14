// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE10
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public static class FLARE10
  {
    public static Random r = new Random();

    public static int flared_41(int mn, int mx)
    {
      // ISSUE: unable to decompile the method.
    }

    public static int flare_40(int mn, int mx)
    {
      try
      {
        return FLARE10.flared_41(mn, mx);
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
  }
}
