public string GetFlag(string password)
{
	Decoder decoder = Encoding.UTF8.GetDecoder();
	UTF8Encoding uTF8Encoding = new UTF8Encoding();
	string text = "";
	byte[] array = new byte[64];
	char[] array2 = new char[64];
	byte[] bytes = uTF8Encoding.GetBytes(password + "\0");
	using (NamedPipeClientStream namedPipeClientStream = new NamedPipeClientStream(".", "FlareOn", PipeDirection.InOut))
	{
		namedPipeClientStream.Connect();
		namedPipeClientStream.ReadMode = PipeTransmissionMode.Message;
		namedPipeClientStream.Write(bytes, 0, Math.Min(bytes.Length, 64));
		int byteCount = namedPipeClientStream.Read(array, 0, array.Length);
		int chars = decoder.GetChars(array, 0, byteCount, array2, 0);
		text += new string(array2, 0, chars);
	}
	return text;
}
