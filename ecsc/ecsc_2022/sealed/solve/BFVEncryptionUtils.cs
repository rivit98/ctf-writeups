// Decompiled with JetBrains decompiler
// Type: Encryption.BFVEncryptionUtils
// Assembly: Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 32E80642-CBF3-4FE3-9C27-4881B0FDC1F7
// Assembly location: D:\sealed\Client.exe

using Microsoft.Research.SEAL;
using System;
using System.IO;
using System.Text;

namespace Encryption
{
  public static class BFVEncryptionUtils
  {
    public static string ParseCipherTextToBase64(Ciphertext ciphertext)
    {
      MemoryStream memoryStream = new MemoryStream();
      ciphertext.Save((Stream) memoryStream);
      memoryStream.Seek(0L, SeekOrigin.Begin);
      return new StreamReader(BFVEncryptionUtils.ConvertToBase64((Stream) memoryStream)).ReadToEnd();
    }

    public static Ciphertext ParseBase64EncodedCiphertextToCiphertext(
      string base64EncodedCiphertext)
    {
      EncryptionParameters parms = new EncryptionParameters(SchemeType.BFV);
      ulong polyModulusDegree = 4096;
      parms.PolyModulusDegree = polyModulusDegree;
      parms.CoeffModulus = CoeffModulus.BFVDefault(polyModulusDegree);
      parms.PlainModulus = new Modulus(512UL);
      SEALContext context = new SEALContext(parms);
      MemoryStream memoryStream = new MemoryStream(Convert.FromBase64String(base64EncodedCiphertext));
      Ciphertext ciphertextToCiphertext = new Ciphertext(context);
      ciphertextToCiphertext.Load(context, (Stream) memoryStream);
      return ciphertextToCiphertext;
    }

    public static string ParseSecretKeyToBase64(SecretKey secretKey)
    {
      MemoryStream memoryStream = new MemoryStream();
      secretKey.Save((Stream) memoryStream);
      memoryStream.Seek(0L, SeekOrigin.Begin);
      return new StreamReader(BFVEncryptionUtils.ConvertToBase64((Stream) memoryStream)).ReadToEnd();
    }

    public static string ParsePublicKeyToBase64(PublicKey publicKey)
    {
      MemoryStream memoryStream = new MemoryStream();
      publicKey.Save((Stream) memoryStream);
      memoryStream.Seek(0L, SeekOrigin.Begin);
      return new StreamReader(BFVEncryptionUtils.ConvertToBase64((Stream) memoryStream)).ReadToEnd();
    }

    public static SecretKey ParseBase64EncodedSecretKeyToSecretKey(
      string base64EncodedSecretKey)
    {
      EncryptionParameters parms = new EncryptionParameters(SchemeType.BFV);
      ulong polyModulusDegree = 4096;
      parms.PolyModulusDegree = polyModulusDegree;
      parms.CoeffModulus = CoeffModulus.BFVDefault(polyModulusDegree);
      parms.PlainModulus = new Modulus(512UL);
      SEALContext context = new SEALContext(parms);
      MemoryStream memoryStream = new MemoryStream(Convert.FromBase64String(base64EncodedSecretKey));
      SecretKey secretKeyToSecretKey = new SecretKey();
      secretKeyToSecretKey.Load(context, (Stream) memoryStream);
      return secretKeyToSecretKey;
    }

    public static PublicKey ParseBase64EncodedPublicKeyToPublicKey(
      string base64EncodedPublicKey)
    {
      EncryptionParameters parms = new EncryptionParameters(SchemeType.BFV);
      ulong polyModulusDegree = 4096;
      parms.PolyModulusDegree = polyModulusDegree;
      parms.CoeffModulus = CoeffModulus.BFVDefault(polyModulusDegree);
      parms.PlainModulus = new Modulus(512UL);
      SEALContext context = new SEALContext(parms);
      MemoryStream memoryStream = new MemoryStream(Convert.FromBase64String(base64EncodedPublicKey));
      PublicKey publicKeyToPublicKey = new PublicKey();
      publicKeyToPublicKey.Load(context, (Stream) memoryStream);
      return publicKeyToPublicKey;
    }

    private static Stream ConvertToBase64(Stream stream)
    {
      byte[] array;
      using (MemoryStream destination = new MemoryStream())
      {
        stream.CopyTo((Stream) destination);
        array = destination.ToArray();
      }
      return (Stream) new MemoryStream(Encoding.UTF8.GetBytes(Convert.ToBase64String(array)));
    }
  }
}
