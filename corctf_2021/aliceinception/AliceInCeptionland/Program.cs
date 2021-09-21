// Decompiled with JetBrains decompiler
// Type: AliceInCeptionland.Program
// Assembly: AliceInCeptionland, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 01DC5997-384E-427D-A025-8486AE92950A
// Assembly location: D:\corctf\aliceinception\AliceInCeptionland.exe

using AliceInCeptionland.Properties;
using System;
using System.IO;
using System.Reflection;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;

namespace AliceInCeptionland
{
  internal static class Program
  {
    [STAThread]
    private static void Main()
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      BaseGame baseGame = new BaseGame();
      Application.Run((Form) baseGame);
      if (string.IsNullOrEmpty(baseGame.Foo) || string.IsNullOrEmpty(baseGame.Bar))
        return;
      byte[] numArray1 = (byte[]) null;
      byte[] numArray2 = (byte[]) null;
      using (MD5 md5 = MD5.Create())
        numArray1 = md5.ComputeHash(Encoding.ASCII.GetBytes(baseGame.Foo));
      using (SHA256 shA256 = SHA256.Create())
        numArray2 = shA256.ComputeHash(Encoding.ASCII.GetBytes(baseGame.Bar));
      using (Aes aes = Aes.Create())
      {
        aes.IV = numArray1;
        aes.Key = numArray2;
        aes.Padding = PaddingMode.PKCS7;
        ICryptoTransform decryptor = aes.CreateDecryptor(aes.Key, aes.IV);
        using (MemoryStream memoryStream = new MemoryStream())
        {
          using (CryptoStream cryptoStream = new CryptoStream((Stream) memoryStream, decryptor, CryptoStreamMode.Write))
          {
            byte[] aliceInCeptiondream = Resources.AliceInCeptiondream;
            cryptoStream.Write(aliceInCeptiondream, 0, aliceInCeptiondream.Length);
            cryptoStream.FlushFinalBlock();
            Application.Run((Form) new DeepDream(Assembly.Load(memoryStream.ToArray())));
          }
        }
      }
    }
  }
}
