// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.Properties.Resources
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;

namespace FlareOn.Backdoor.Properties
{
  [GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "16.0.0.0")]
  [DebuggerNonUserCode]
  [CompilerGenerated]
  internal class Resources
  {
    public static ResourceManager resourceMan;
    public static CultureInfo resourceCulture;

    internal Resources()
    {
    }

    [EditorBrowsable(EditorBrowsableState.Advanced)]
    internal static ResourceManager ResourceManager
    {
      get
      {
        if (FlareOn.Backdoor.Properties.Resources.resourceMan == null)
          FlareOn.Backdoor.Properties.Resources.resourceMan = new ResourceManager("FlareOn.Backdoor.Properties.Resources", typeof (FlareOn.Backdoor.Properties.Resources).Assembly);
        return FlareOn.Backdoor.Properties.Resources.resourceMan;
      }
    }

    [EditorBrowsable(EditorBrowsableState.Advanced)]
    internal static CultureInfo Culture
    {
      get => FlareOn.Backdoor.Properties.Resources.resourceCulture;
      set => FlareOn.Backdoor.Properties.Resources.resourceCulture = value;
    }
  }
}
