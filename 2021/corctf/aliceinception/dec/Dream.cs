// Decompiled with JetBrains decompiler
// Type: AliceInCeptiondream.Dream
// Assembly: AliceInCeptiondream, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: ADF31087-0316-4A22-BAA3-A85087F9E96A
// Assembly location: D:\corctf\aliceinception\dec.exe

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;

namespace AliceInCeptiondream
{

    public class Dream
    {
        public static void Main()
        {
            Dream.Encode();
        }
        private static readonly string[] rm = new string[256]
    {
      null,
      null,
      null,
      null,
      "\u000F",
      "\u0005\u0006\u0005\u0005\u0006",
      "\u001D\u001D\u001D\u001D\u001D",
      "\u0015\u0015\u0015\u0016\u0016",
      "nmmnmn",
      "ffff",
      "~}}~",
      "uvvu",
      "\0",
      "FFFF",
      "^]]^",
      "UVVU",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\f\u000F\f\u000F\f\f",
      "\u0004\a\u0004\u0004\a\u0004",
      "\u001F\u001C\u001C\u001C\u001C",
      "\u0014\u0014\u0014\u0014\u0017",
      "ol",
      "gg",
      "||\u007F|",
      "twtt",
      "OL",
      "GG",
      "\\\\_\\",
      "TWTT",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\0",
      "\0",
      "\u001C\u001C\u001F\u001F\u001F",
      "\u0017\u0017\u0017\u0014\u0014\u0014",
      "olll",
      "dggg",
      "|\u007F|",
      "wwtt",
      "OLLL",
      "DGGG",
      "\\_\\",
      "WWTT",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\0",
      "\u0005\u0006\u0005\u0006\u0005",
      "\u001D\u001D\u001D\u001E\u001E",
      "\u0016\u0015\u0016\u0015\u0016\u0015",
      "nmnm",
      "fef",
      "}}}",
      "\0",
      "NMNM",
      "FEF",
      "]]]",
      "\0",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\n\n\n\n\n",
      "\u0001\u0001\u0002\u0002\u0001\u0001",
      "\u001A\u001A\u001A\u001A\u0019",
      "\0",
      "ijj",
      "babb",
      "y",
      "\0",
      "IJJ",
      "BABB",
      "Y",
      "\0",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\0",
      "\0\u0003\u0003\u0003\u0003\0",
      "\u001B\u001B\u001B\u001B\u001B",
      "\u0010\u0013\u0013\u0013\u0010",
      "k",
      "``",
      "{{x",
      "\0",
      "K",
      "@@",
      "[[X",
      "\0",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\b\v\b\b\b",
      "\0\u0003\0\u0003\0\u0003",
      "\u001B\u0018\u0018\u0018\u0018",
      "\0",
      "hhkh",
      "c`",
      "xxx{",
      "\0",
      "HHKH",
      "C@",
      "XXX[",
      "\0",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      "\t\n\n\n\n\t",
      "\u0002\u0001\u0001\u0002\u0001",
      "\u001A\u001A\u0019\u0019\u0019",
      "\u0011\u0011\u0012\u0012\u0011\u0011",
      "jji",
      "bbb",
      "yzz",
      "qqrrqr",
      "JJI",
      "BBB",
      "YZZ",
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null
    };
        private static readonly ulong xm = 1056017893861212352;

        public static string Encode()
        {
            byte[] enc = { 0x3c, 0x3c, 0xf1, 0xdf, 0x89, 0xfe, 0x83, 0x2a, 0xef, 0xcc, 0x22, 0xfc, 0x82, 0x1, 0x7c, 0xd5, 0x7b, 0xef, 0x1, 0xdf, 0x54, 0x23, 0x5e, 0x21, 0x41, 0x41, 0x22, 0xd7, 0x8a, 0x9d, 0x88, 0xcf, 0xef, 0x3c, 0xf1, 0xc, 0x82, 0x9e, 0xe3, 0x2a, 0xe4, 0xef, 0x1, 0xdf, 0xa1, 0x95, 0x1c, 0xd5, 0x1b, 0x7b, 0x22, 0xfc, 0x82, 0x43, 0x3e, 0xf7, 0xef, 0x41, 0x8c, 0xdf, 0x8a, 0x9d, 0x80, 0x21, 0x1, 0xef, 0x64, 0xf9, 0xa4, 0x95, 0x26, 0x8f, 0xef, 0x18, 0xd5, 0x28, 0x82, 0x32, 0x4f, 0x21, 0x7b, 0x1b, 0xd6, 0x4b, 0x82, 0x1, 0x7c, 0xd5, 0x7b, 0xef, 0x1, 0xdf, 0x25, 0x52, 0x88, 0xf7, 0x59, 0x39, 0x22, 0x71, 0x2c, 0x95, 0x80, 0x29, 0xe7, 0xef, 0xcc, 0xdf, 0x8, 0x1f, 0x88, 0x8, 0xa6, 0xef, 0xd5, 0x28, 0x75, 0x95, 0xf8, 0x21, 0x48, 0x28, 0x22, 0xf6, 0xcb, 0x95, 0xf8, 0x21, 0xcc, 0xef, 0xf4, 0x69, 0x54, 0x95, 0x26, 0x8f, 0xef, 0xe7, 0x2a, 0xd7, 0x82, 0x1a, 0x67, 0xae, 0x0, 0x60, 0xad };
            Console.WriteLine(enc.Length);
            byte[] numArray = new byte[8]
{
          (byte) (Dream.xm & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 8 & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 16 & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 24 & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 32 & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 40 & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 48 & (ulong) byte.MaxValue),
          (byte) (Dream.xm >> 56 & (ulong) byte.MaxValue)
};

            byte[] dexored = new byte[147];
            for (int index = 0; index < enc.Length; ++index)
                dexored[index] = (byte)(enc[index] ^ (uint)numArray[index % numArray.Length]);


            var mapping = new Dictionary<char, List<byte>>();
            for (byte c = 0x20; c < 0x7e; c++)
            {
                var cc = (char)c;
                try
                {
                    var result = fm(cc);
                    for (int i = 0; i < result.Length; i++)
                    {
                    }
                    mapping.Add(cc, result.Select(x => (byte)x).ToList());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Failed");
                }
            }

            var groups = dexored.Aggregate(new List<List<byte>> { new List<byte>() },
                                   (list, value) =>
                                   {
                                       if (value != 47)
                                       {

                                           list.Last().Add(value);
                                       }
                                       if (value == 47) list.Add(new List<byte>());
                                       return list;
                                   });

            var found = new List<char>();
            groups.ForEach(g => {
                foreach (var item in mapping)
                {
                    if (g.SequenceEqual(item.Value))
                    {
                        found.Add(item.Key);
                        break;
                    }
                }
            });

            Console.WriteLine(string.Join("", found.ToArray()));

            // Sleeperio Sleeperio Disappeario Instanterio!
            // corctf{4l1c3_15_1n_d33p_tr0ubl3_b3c4us3_1_d1d_n0t_s4v3_h3r!!:c}

            Console.ReadLine();
            return "";
        }

        private static char fl(char c) => (char)rol((byte)c, 3);

        private static char fr(char c) => (char)ror((byte)c, 5);

        private static string fx(char c, string x) => new string(x.Select(y => (char)((byte)y ^ (uint)(byte)c)).ToArray());

        private static string fm(char c) => string.Join("", new string[1]
                    {
        fx(c, new string(rm[ fl(c)].Select(new Func<char, char>(fr)).ToArray()))
                    });

        public static byte[] Decrypt(byte[] ciphertext, string secret)
        {
            byte[] numArray1 = (byte[])null;
            byte[] numArray2 = (byte[])null;
            using (MD5 md5 = MD5.Create())
                numArray1 = md5.ComputeHash(Encoding.ASCII.GetBytes(secret));
            using (SHA256 shA256 = SHA256.Create())
                numArray2 = shA256.ComputeHash(Encoding.ASCII.GetBytes(secret));
            using (Aes aes = Aes.Create())
            {
                aes.IV = numArray1;
                aes.Key = numArray2;
                aes.Padding = PaddingMode.PKCS7;
                ICryptoTransform decryptor = aes.CreateDecryptor(aes.Key, aes.IV);
                using (MemoryStream memoryStream = new MemoryStream())
                {
                    using (CryptoStream cryptoStream = new CryptoStream((Stream)memoryStream, decryptor, CryptoStreamMode.Write))
                    {
                        cryptoStream.Write(ciphertext, 0, ciphertext.Length);
                        cryptoStream.FlushFinalBlock();
                        return memoryStream.ToArray();
                    }
                }
            }
        }

        private static byte ror(byte v, byte s)
        {
            byte num = (byte)((uint)s % 8U);
            return (byte)((int)v << (int)num | (int)v >> 8 - (int)num);
        }

        private static byte rol(byte v, byte s)
        {
            byte num = (byte)((uint)s % 8U);
            return (byte)((int)v >> (int)num | (int)v << 8 - (int)num);
        }
    }
}
