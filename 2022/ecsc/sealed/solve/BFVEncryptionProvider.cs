// Decompiled with JetBrains decompiler
// Type: Encryption.BFVEncryptionProvider
// Assembly: Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 32E80642-CBF3-4FE3-9C27-4881B0FDC1F7
// Assembly location: D:\sealed\Client.exe

using Microsoft.Research.SEAL;

namespace Encryption
{
  internal class BFVEncryptionProvider
  {
    private SEALContext Context { get; set; }

    private KeyGenerator Keygen { get; set; }

    public BFVEncryptionProvider()
    {
      EncryptionParameters parms = new EncryptionParameters(SchemeType.BFV);
      ulong polyModulusDegree = 4096;
      parms.PolyModulusDegree = polyModulusDegree;
      parms.CoeffModulus = CoeffModulus.BFVDefault(polyModulusDegree);
      parms.PlainModulus = new Modulus(512UL);
      this.Context = new SEALContext(parms);
      this.Keygen = new KeyGenerator(this.Context);
    }

    public PublicKey GetPublicKey() => this.Keygen.PublicKey;

    public SecretKey GetSecretKey() => this.Keygen.SecretKey;

    public Encryptor GetEncryptor() => new Encryptor(this.Context, this.GetPublicKey());

    public Decryptor GetDecryptor() => new Decryptor(this.Context, this.GetSecretKey());

    public Evaluator GetEvaluator() => new Evaluator(this.Context);

    public IntegerEncoder GetIntegerEncoder() => new IntegerEncoder(this.Context);

    public SEALContext GetSEALContext() => this.Context;
  }
}
