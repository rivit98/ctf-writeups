﻿// Decompiled with JetBrains decompiler
// Type: FlareOn.Backdoor.FLARE09
// Assembly: FlareOn.Backdoor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 18DABA5E-F976-4D91-A021-29D52AEA6D82
// Assembly location: D:\flareon9\08_backdoor\FlareOn.Backdoor.exe

using System;
using System.IO;
using System.Runtime.InteropServices;

namespace FlareOn.Backdoor
{
  public class FLARE09
  {
    public static FLARE09.IMAGE_DOS_HEADER dosHeader;
    public static FLARE09.IMAGE_FILE_HEADER fileHeader;
    public static FLARE09.IMAGE_OPTIONAL_HEADER32 optionalHeader32;
    public static FLARE09.IMAGE_OPTIONAL_HEADER64 optionalHeader64;
    public static FLARE09.IMAGE_SECTION_HEADER[] imageSectionHeaders;

    public static void flared_35(string f)
    {
      // ISSUE: unable to decompile the method.
    }

    public static void flare_37(string f)
    {
      try
      {
        FLARE09.flared_35(f);
      }
      catch (InvalidProgramException ex)
      {
        FLARE15.flare_71(ex, new object[1]
        {
          (object) f
        }, FLARE15.pe_m, FLARE15.pe_b);
      }
    }

    public static FLARE09 flared_36()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE09 flare_38()
    {
      try
      {
        return FLARE09.flared_36();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE09) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static FLARE09 flared_37()
    {
      // ISSUE: unable to decompile the method.
    }

    public static FLARE09 flare_39()
    {
      try
      {
        return FLARE09.flared_37();
      }
      catch (InvalidProgramException ex)
      {
        return (FLARE09) FLARE15.flare_70(ex, (object[]) null);
      }
    }

    public static T FromBinaryReader<T>(BinaryReader reader)
    {
      GCHandle gcHandle = GCHandle.Alloc((object) reader.ReadBytes(Marshal.SizeOf(typeof (T))), GCHandleType.Pinned);
      T structure = (T) Marshal.PtrToStructure(gcHandle.AddrOfPinnedObject(), typeof (T));
      gcHandle.Free();
      return structure;
    }

    public bool Is32BitHeader
    {
      get
      {
        ushort num = 256;
        return ((int) num & (int) this.FileHeader.Characteristics) == (int) num;
      }
    }

    public FLARE09.IMAGE_FILE_HEADER FileHeader => FLARE09.fileHeader;

    public FLARE09.IMAGE_OPTIONAL_HEADER32 OptionalHeader32 => FLARE09.optionalHeader32;

    public FLARE09.IMAGE_OPTIONAL_HEADER64 OptionalHeader64 => FLARE09.optionalHeader64;

    public FLARE09.IMAGE_SECTION_HEADER[] ImageSectionHeaders => FLARE09.imageSectionHeaders;

    public DateTime TimeStamp
    {
      get
      {
        DateTime time = new DateTime(1970, 1, 1, 0, 0, 0);
        time = time.AddSeconds((double) FLARE09.fileHeader.TimeDateStamp);
        return time + TimeZone.CurrentTimeZone.GetUtcOffset(time);
      }
    }

    public struct IMAGE_DOS_HEADER
    {
      public ushort e_magic;
      public ushort e_cblp;
      public ushort e_cp;
      public ushort e_crlc;
      public ushort e_cparhdr;
      public ushort e_minalloc;
      public ushort e_maxalloc;
      public ushort e_ss;
      public ushort e_sp;
      public ushort e_csum;
      public ushort e_ip;
      public ushort e_cs;
      public ushort e_lfarlc;
      public ushort e_ovno;
      public ushort e_res_0;
      public ushort e_res_1;
      public ushort e_res_2;
      public ushort e_res_3;
      public ushort e_oemid;
      public ushort e_oeminfo;
      public ushort e_res2_0;
      public ushort e_res2_1;
      public ushort e_res2_2;
      public ushort e_res2_3;
      public ushort e_res2_4;
      public ushort e_res2_5;
      public ushort e_res2_6;
      public ushort e_res2_7;
      public ushort e_res2_8;
      public ushort e_res2_9;
      public uint e_lfanew;
    }

    public struct IMAGE_DATA_DIRECTORY
    {
      public uint VirtualAddress;
      public uint Size;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct IMAGE_OPTIONAL_HEADER32
    {
      public ushort Magic;
      public byte MajorLinkerVersion;
      public byte MinorLinkerVersion;
      public uint SizeOfCode;
      public uint SizeOfInitializedData;
      public uint SizeOfUninitializedData;
      public uint AddressOfEntryPoint;
      public uint BaseOfCode;
      public uint BaseOfData;
      public uint ImageBase;
      public uint SectionAlignment;
      public uint FileAlignment;
      public ushort MajorOperatingSystemVersion;
      public ushort MinorOperatingSystemVersion;
      public ushort MajorImageVersion;
      public ushort MinorImageVersion;
      public ushort MajorSubsystemVersion;
      public ushort MinorSubsystemVersion;
      public uint Win32VersionValue;
      public uint SizeOfImage;
      public uint SizeOfHeaders;
      public uint CheckSum;
      public ushort Subsystem;
      public ushort DllCharacteristics;
      public uint SizeOfStackReserve;
      public uint SizeOfStackCommit;
      public uint SizeOfHeapReserve;
      public uint SizeOfHeapCommit;
      public uint LoaderFlags;
      public uint NumberOfRvaAndSizes;
      public FLARE09.IMAGE_DATA_DIRECTORY ExportTable;
      public FLARE09.IMAGE_DATA_DIRECTORY ImportTable;
      public FLARE09.IMAGE_DATA_DIRECTORY ResourceTable;
      public FLARE09.IMAGE_DATA_DIRECTORY ExceptionTable;
      public FLARE09.IMAGE_DATA_DIRECTORY CertificateTable;
      public FLARE09.IMAGE_DATA_DIRECTORY BaseRelocationTable;
      public FLARE09.IMAGE_DATA_DIRECTORY Debug;
      public FLARE09.IMAGE_DATA_DIRECTORY Architecture;
      public FLARE09.IMAGE_DATA_DIRECTORY GlobalPtr;
      public FLARE09.IMAGE_DATA_DIRECTORY TLSTable;
      public FLARE09.IMAGE_DATA_DIRECTORY LoadConfigTable;
      public FLARE09.IMAGE_DATA_DIRECTORY BoundImport;
      public FLARE09.IMAGE_DATA_DIRECTORY IAT;
      public FLARE09.IMAGE_DATA_DIRECTORY DelayImportDescriptor;
      public FLARE09.IMAGE_DATA_DIRECTORY CLRRuntimeHeader;
      public FLARE09.IMAGE_DATA_DIRECTORY Reserved;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct IMAGE_OPTIONAL_HEADER64
    {
      public ushort Magic;
      public byte MajorLinkerVersion;
      public byte MinorLinkerVersion;
      public uint SizeOfCode;
      public uint SizeOfInitializedData;
      public uint SizeOfUninitializedData;
      public uint AddressOfEntryPoint;
      public uint BaseOfCode;
      public ulong ImageBase;
      public uint SectionAlignment;
      public uint FileAlignment;
      public ushort MajorOperatingSystemVersion;
      public ushort MinorOperatingSystemVersion;
      public ushort MajorImageVersion;
      public ushort MinorImageVersion;
      public ushort MajorSubsystemVersion;
      public ushort MinorSubsystemVersion;
      public uint Win32VersionValue;
      public uint SizeOfImage;
      public uint SizeOfHeaders;
      public uint CheckSum;
      public ushort Subsystem;
      public ushort DllCharacteristics;
      public ulong SizeOfStackReserve;
      public ulong SizeOfStackCommit;
      public ulong SizeOfHeapReserve;
      public ulong SizeOfHeapCommit;
      public uint LoaderFlags;
      public uint NumberOfRvaAndSizes;
      public FLARE09.IMAGE_DATA_DIRECTORY ExportTable;
      public FLARE09.IMAGE_DATA_DIRECTORY ImportTable;
      public FLARE09.IMAGE_DATA_DIRECTORY ResourceTable;
      public FLARE09.IMAGE_DATA_DIRECTORY ExceptionTable;
      public FLARE09.IMAGE_DATA_DIRECTORY CertificateTable;
      public FLARE09.IMAGE_DATA_DIRECTORY BaseRelocationTable;
      public FLARE09.IMAGE_DATA_DIRECTORY Debug;
      public FLARE09.IMAGE_DATA_DIRECTORY Architecture;
      public FLARE09.IMAGE_DATA_DIRECTORY GlobalPtr;
      public FLARE09.IMAGE_DATA_DIRECTORY TLSTable;
      public FLARE09.IMAGE_DATA_DIRECTORY LoadConfigTable;
      public FLARE09.IMAGE_DATA_DIRECTORY BoundImport;
      public FLARE09.IMAGE_DATA_DIRECTORY IAT;
      public FLARE09.IMAGE_DATA_DIRECTORY DelayImportDescriptor;
      public FLARE09.IMAGE_DATA_DIRECTORY CLRRuntimeHeader;
      public FLARE09.IMAGE_DATA_DIRECTORY Reserved;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct IMAGE_FILE_HEADER
    {
      public ushort Machine;
      public ushort NumberOfSections;
      public uint TimeDateStamp;
      public uint PointerToSymbolTable;
      public uint NumberOfSymbols;
      public ushort SizeOfOptionalHeader;
      public ushort Characteristics;
    }

    [StructLayout(LayoutKind.Explicit)]
    public struct IMAGE_SECTION_HEADER
    {
      [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
      [FieldOffset(0)]
      public char[] Name;
      [FieldOffset(8)]
      public uint VirtualSize;
      [FieldOffset(12)]
      public uint VirtualAddress;
      [FieldOffset(16)]
      public uint SizeOfRawData;
      [FieldOffset(20)]
      public uint PointerToRawData;
      [FieldOffset(24)]
      public uint PointerToRelocations;
      [FieldOffset(28)]
      public uint PointerToLinenumbers;
      [FieldOffset(32)]
      public ushort NumberOfRelocations;
      [FieldOffset(34)]
      public ushort NumberOfLinenumbers;
      [FieldOffset(36)]
      public FLARE09.DataSectionFlags Characteristics;

      public string Section => new string(this.Name);
    }

    [Flags]
    public enum DataSectionFlags : uint
    {
      TypeReg = 0,
      TypeDsect = 1,
      TypeNoLoad = 2,
      TypeGroup = 4,
      TypeNoPadded = 8,
      TypeCopy = 16, // 0x00000010
      ContentCode = 32, // 0x00000020
      ContentInitializedData = 64, // 0x00000040
      ContentUninitializedData = 128, // 0x00000080
      LinkOther = 256, // 0x00000100
      LinkInfo = 512, // 0x00000200
      TypeOver = 1024, // 0x00000400
      LinkRemove = 2048, // 0x00000800
      LinkComDat = 4096, // 0x00001000
      NoDeferSpecExceptions = 16384, // 0x00004000
      RelativeGP = 32768, // 0x00008000
      MemPurgeable = 131072, // 0x00020000
      Memory16Bit = MemPurgeable, // 0x00020000
      MemoryLocked = 262144, // 0x00040000
      MemoryPreload = 524288, // 0x00080000
      Align1Bytes = 1048576, // 0x00100000
      Align2Bytes = 2097152, // 0x00200000
      Align4Bytes = Align2Bytes | Align1Bytes, // 0x00300000
      Align8Bytes = 4194304, // 0x00400000
      Align16Bytes = Align8Bytes | Align1Bytes, // 0x00500000
      Align32Bytes = Align8Bytes | Align2Bytes, // 0x00600000
      Align64Bytes = Align32Bytes | Align1Bytes, // 0x00700000
      Align128Bytes = 8388608, // 0x00800000
      Align256Bytes = Align128Bytes | Align1Bytes, // 0x00900000
      Align512Bytes = Align128Bytes | Align2Bytes, // 0x00A00000
      Align1024Bytes = Align512Bytes | Align1Bytes, // 0x00B00000
      Align2048Bytes = Align128Bytes | Align8Bytes, // 0x00C00000
      Align4096Bytes = Align2048Bytes | Align1Bytes, // 0x00D00000
      Align8192Bytes = Align2048Bytes | Align2Bytes, // 0x00E00000
      LinkExtendedRelocationOverflow = 16777216, // 0x01000000
      MemoryDiscardable = 33554432, // 0x02000000
      MemoryNotCached = 67108864, // 0x04000000
      MemoryNotPaged = 134217728, // 0x08000000
      MemoryShared = 268435456, // 0x10000000
      MemoryExecute = 536870912, // 0x20000000
      MemoryRead = 1073741824, // 0x40000000
      MemoryWrite = 2147483648, // 0x80000000
    }
  }
}
