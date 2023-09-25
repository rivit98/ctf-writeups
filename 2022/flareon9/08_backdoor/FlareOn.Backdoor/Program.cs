// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.Program
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;
using System.Threading;

namespace FlareOn.Backdoor
{
  public class Program
  {
    public Program() => new Thread((ThreadStart) (() => Program.Main(Environment.GetCommandLineArgs()))).Start();

    public static void flared_38(string[] args)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void Main(string[] args)
    {
      try
      {
        try
        {
          FLARE15.flare_74();
          Program.flared_38(args);
        }
        catch (InvalidProgramException ex)
        {
          FLARE15.flare_70(ex, new object[1]
          {
            (object) args
          });
        }
      }
      catch
      {
      }
    }

    public static FLARE07 flared_39()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE07 flare_72()
    {
      try
      {
        return Program.flared_39();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE07) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static FLARE07 flared_40()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE07 flare_73()
    {
      try
      {
        return Program.flared_40();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE07) FLARE15.flare_70(ex, (object[]) null);
      }
    }
  }
}
