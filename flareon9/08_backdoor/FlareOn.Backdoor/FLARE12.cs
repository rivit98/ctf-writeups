// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE12
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public class FLARE12
  {
    public static byte[] flared_47(byte[] p, byte[] d)
    {
      // ISSUE: unable to decompile the method.
    }

    public static byte[] flare_46(byte[] p, byte[] d)
    {
      try
      {
        return FLARE12.flared_47(p, d);
      }
      catch (InvalidProgramException ex)
      {
        return (byte[]) FLARE15.flare_71(ex, new object[2]
        {
          (object) p,
          (object) d
        }, FLARE15.d_m, FLARE15.d_b);
      }
    }
  }
}
