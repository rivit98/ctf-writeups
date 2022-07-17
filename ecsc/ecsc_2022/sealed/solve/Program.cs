// Decompiled with JetBrains decompiler
// Type: Client.Program
// Assembly: Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 32E80642-CBF3-4FE3-9C27-4881B0FDC1F7
// Assembly location: D:\sealed\Client.exe

using Encryption;
using Microsoft.Research.SEAL;
using System;
using System.Collections.Generic;
using System.Device.Location;
using System.IO;
using Newtonsoft.Json;

namespace Client
{
    public class Item
    {
        public string guid { get; set; }
        public string latitude { get; set; }
        public string longitude { get; set; }
    }
    public class Program
  {
    private static void Main(string[] args)
    {
      string path = "D:\\sealed\\publickey.key";
      SecretKey secretKeyToSecretKey = BFVEncryptionUtils.ParseBase64EncodedSecretKeyToSecretKey(File.ReadAllText("D:\\sealed\\secretkey.key"));
      PublicKey publicKeyToPublicKey = BFVEncryptionUtils.ParseBase64EncodedPublicKeyToPublicKey(File.ReadAllText(path));
      BFVEncryptionProvider encryptionProvider = new BFVEncryptionProvider();
      Decryptor decryptor = new Decryptor(encryptionProvider.GetSEALContext(), secretKeyToSecretKey);
      IntegerEncoder encoder = new IntegerEncoder(encryptionProvider.GetSEALContext());
      
        using (StreamReader r = new StreamReader("D:\\sealed\\sent.json"))
        {
            string json = r.ReadToEnd();
            Item item = JsonConvert.DeserializeObject<Item>(json);

				string base64EncodedCiphertext2 = item.latitude;
                string base64EncodedCiphertext1 = item.longitude;

                Ciphertext ciphertextToCiphertext1 = BFVEncryptionUtils.ParseBase64EncodedCiphertextToCiphertext(base64EncodedCiphertext1);
                Ciphertext ciphertextToCiphertext2 = BFVEncryptionUtils.ParseBase64EncodedCiphertextToCiphertext(base64EncodedCiphertext2);
                Plaintext plaintext3 = new Plaintext();
                Plaintext plaintext4 = new Plaintext();
                decryptor.Decrypt(ciphertextToCiphertext2, plaintext3);
                decryptor.Decrypt(ciphertextToCiphertext1, plaintext4);
                string str3 = encoder.DecodeInt32(plaintext4).ToString();
                string str4 = encoder.DecodeInt32(plaintext3).ToString();
                double num1 = Convert.ToDouble(str3);
                double num2 = Convert.ToDouble(str4);
                double longitude = num1 / 1000000.0;
                double latitude = num2 / 1000000.0;
                Console.WriteLine("You are: {0} meters away from target position!", new GeoCoordinate(latitude, longitude));
                Console.ReadLine();

            }

        }
  }
}
