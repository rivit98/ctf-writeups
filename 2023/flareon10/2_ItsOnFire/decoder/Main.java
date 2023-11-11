import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.zip.CRC32;

import static java.nio.charset.StandardCharsets.UTF_8;

public class Main {
    public static void main(String[] args) {
        try {
            var dec = c("./iv.png");
            Files.write(Path.of("./iv.dec.png"), dec);

            dec = c("./ps.png");
            Files.write(Path.of("./ps.dec.png"), dec);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static long a(byte[] bArr) {
        CRC32 crc32 = new CRC32();
        crc32.update(bArr);
        return crc32.getValue();
    }

    private static byte[] b(String str, byte[] bArr, SecretKeySpec secretKeySpec, IvParameterSpec ivParameterSpec) throws InvalidAlgorithmParameterException, InvalidKeyException, NoSuchPaddingException, NoSuchAlgorithmException, IllegalBlockSizeException, BadPaddingException {
        Cipher instance = Cipher.getInstance(str);
        instance.init(Cipher.DECRYPT_MODE, secretKeySpec, ivParameterSpec);
        byte[] doFinal = instance.doFinal(bArr);
//        Intrinsics.checkNotNullExpressionValue(doFinal, "cipher.doFinal(input)");
        return doFinal;
    }

    private static byte[] c(String fname) throws InvalidAlgorithmParameterException, NoSuchPaddingException, IllegalBlockSizeException, NoSuchAlgorithmException, BadPaddingException, InvalidKeyException {
        byte[] e2 = e(fname);
        String d2 = d();
        Charset charset = UTF_8;
        byte[] bytes = d2.getBytes(charset);
//        Intrinsics.checkNotNullExpressionValue(bytes, "this as java.lang.String).getBytes(charset)");
        SecretKeySpec secretKeySpec = new SecretKeySpec(bytes, "AES");
        String string = "AES/CBC/PKCS5Padding";
        String string2 = "abcdefghijklmnop";
        byte[] bytes2 = string2.getBytes(charset);
        byte[] b2 = b(string, e2, secretKeySpec, new IvParameterSpec(bytes2));
        return b2;
    }

    private static String d() {
//        String string = context.getString(R.string.c2);
        String string = "https://flare-on.com/evilc2server/report_token/report_token.php?token=";
//        Intrinsics.checkNotNullExpressionValue(string, "context.getString(R.string.c2)");
//        String string2 = context.getString(R.string.w1);
        String string2 = "wednesday";
//        Intrinsics.checkNotNullExpressionValue(string2, "context.getString(R.string.w1)");
        StringBuilder sb = new StringBuilder();
        sb.append(string.subSequence(4, 10));
        sb.append(string2.subSequence(2, 5));
        String sb2 = sb.toString();
//        Intrinsics.checkNotNullExpressionValue(sb2, "StringBuilder().apply(builderAction).toString()");
        byte[] bytes = sb2.getBytes(UTF_8);
//        Intrinsics.checkNotNullExpressionValue(bytes, "this as java.lang.String).getBytes(charset)");
        long a2 = a(bytes);
        StringBuilder sb3 = new StringBuilder();
        sb3.append(a2);
        sb3.append(a2);
        String sb4 = sb3.toString();
//        Intrinsics.checkNotNullExpressionValue(sb4, "StringBuilder().apply(builderAction).toString()");
//        return StringsKt___StringsKt.slice(sb4, new IntRange(0, 15));
        return sb4.substring(0, 16);
    }

    private static byte[] e(String fname) {
        // load file
        try {
            return Files.readAllBytes(Path.of(fname));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
