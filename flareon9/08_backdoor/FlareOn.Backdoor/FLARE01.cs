// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE01
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;

namespace FlareOn.Backdoor
{
  public class FLARE01
  {
    public static string flared_00(byte[] i)
    {
      // ISSUE: unable to decompile the method.
    }

    public static string flare_01(byte[] i)
    {
      try
      {
        return FLARE01.flared_00(i);
      }
      catch (InvalidProgramException ex)
      {
        return (string) FLARE15.flare_70(ex, new object[1]
        {
          (object) i
        });
      }
    }

    public static char flared_01(byte b)
    {
      // ISSUE: unable to decompile the method.
    }

    public static char flare_02(byte b)
    {
      try
      {
        return FLARE01.flared_01(b);
      }
      catch (InvalidProgramException ex)
      {
        return (char) FLARE15.flare_70(ex, new object[1]
        {
          (object) b
        });
      }
    }
  }
}
