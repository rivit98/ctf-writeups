Decompile apk

Find the following decompiled code:


```java

package f;

import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.net.Uri;
import androidx.compose.runtime.internal.StabilityInferred;
import androidx.core.content.FileProvider;
import com.secure.itsonfire.R;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.util.zip.CRC32;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import kotlin.Metadata;
import kotlin.jvm.internal.Intrinsics;
import kotlin.ranges.IntRange;
import kotlin.text.Charsets;
import org.jetbrains.annotations.NotNull;

@StabilityInferred(parameters = 0)
@Metadata(bv = {}, d1 = {"\u0000L\n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0002\u0010\u000e\n\u0000\n\u0002\u0010\u0012\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0003\n\u0002\u0010\t\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0002\n\u0002\u0010\b\n\u0000\n\u0002\u0018\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\b\u0002\n\u0002\u0018\u0002\n\u0002\b\u0004\bÇ\u0002\u0018\u00002\u00020\u0001B\t\b\u0002¢\u0006\u0004\b\u001a\u0010\u001bJ*\u0010\n\u001a\u00020\u00042\u0006\u0010\u0003\u001a\u00020\u00022\b\u0010\u0005\u001a\u0004\u0018\u00010\u00042\u0006\u0010\u0007\u001a\u00020\u00062\u0006\u0010\t\u001a\u00020\bH\u0002J\u0010\u0010\r\u001a\u00020\f2\u0006\u0010\u000b\u001a\u00020\u0004H\u0002J\u0010\u0010\u0010\u001a\u00020\u00022\u0006\u0010\u000f\u001a\u00020\u000eH\u0002J\u0018\u0010\u0014\u001a\u00020\u00132\u0006\u0010\u0012\u001a\u00020\u00112\u0006\u0010\u000f\u001a\u00020\u000eH\u0002J\u001a\u0010\u0017\u001a\u0004\u0018\u00010\u00042\u0006\u0010\u0016\u001a\u00020\u00152\u0006\u0010\u0012\u001a\u00020\u0011H\u0002J\u0016\u0010\u0019\u001a\u00020\u00182\u0006\u0010\u000f\u001a\u00020\u000e2\u0006\u0010\u0012\u001a\u00020\u0011¨\u0006\u001c"}, d2 = {"Lf/b;", "", "", "algorithm", "", "input", "Ljavax/crypto/spec/SecretKeySpec;", "key", "Ljavax/crypto/spec/IvParameterSpec;", "iv", "b", "value", "", "a", "Landroid/content/Context;", "context", "d", "", "resourceId", "Ljava/io/File;", "c", "Landroid/content/res/Resources;", "res", "e", "Landroid/content/Intent;", "f", "<init>", "()V", "app_release"}, k = 1, mv = {1, 6, 0})
public final class b {
    @NotNull

    /* renamed from: a  reason: collision with root package name */
    public static final b f360a = new b();

    /* renamed from: b  reason: collision with root package name */
    public static final int f361b = 0;

    private b() {
    }

    private final long a(byte[] bArr) {
        CRC32 crc32 = new CRC32();
        crc32.update(bArr);
        return crc32.getValue();
    }

    private final byte[] b(String str, byte[] bArr, SecretKeySpec secretKeySpec, IvParameterSpec ivParameterSpec) {
        Cipher instance = Cipher.getInstance(str);
        instance.init(2, secretKeySpec, ivParameterSpec);
        byte[] doFinal = instance.doFinal(bArr);
        Intrinsics.checkNotNullExpressionValue(doFinal, "cipher.doFinal(input)");
        return doFinal;
    }

    private final File c(int i2, Context context) {
        Resources resources = context.getResources();
        Intrinsics.checkNotNullExpressionValue(resources, "context.resources");
        byte[] e2 = e(resources, i2);
        String d2 = d(context);
        Charset charset = Charsets.UTF_8;
        byte[] bytes = d2.getBytes(charset);
        Intrinsics.checkNotNullExpressionValue(bytes, "this as java.lang.String).getBytes(charset)");
        SecretKeySpec secretKeySpec = new SecretKeySpec(bytes, context.getString(R.string.ag));
        String string = context.getString(R.string.alg);
        Intrinsics.checkNotNullExpressionValue(string, "context.getString(R.string.alg)");
        String string2 = context.getString(R.string.iv);
        Intrinsics.checkNotNullExpressionValue(string2, "context.getString(\n     …             R.string.iv)");
        byte[] bytes2 = string2.getBytes(charset);
        Intrinsics.checkNotNullExpressionValue(bytes2, "this as java.lang.String).getBytes(charset)");
        byte[] b2 = b(string, e2, secretKeySpec, new IvParameterSpec(bytes2));
        File file = new File(context.getCacheDir(), context.getString(R.string.playerdata));
        FilesKt__FileReadWriteKt.writeBytes(file, b2);
        return file;
    }

    private final String d(Context context) {
        String string = context.getString(R.string.c2);
        Intrinsics.checkNotNullExpressionValue(string, "context.getString(R.string.c2)");
        String string2 = context.getString(R.string.w1);
        Intrinsics.checkNotNullExpressionValue(string2, "context.getString(R.string.w1)");
        StringBuilder sb = new StringBuilder();
        sb.append(string.subSequence(4, 10));
        sb.append(string2.subSequence(2, 5));
        String sb2 = sb.toString();
        Intrinsics.checkNotNullExpressionValue(sb2, "StringBuilder().apply(builderAction).toString()");
        byte[] bytes = sb2.getBytes(Charsets.UTF_8);
        Intrinsics.checkNotNullExpressionValue(bytes, "this as java.lang.String).getBytes(charset)");
        long a2 = a(bytes);
        StringBuilder sb3 = new StringBuilder();
        sb3.append(a2);
        sb3.append(a2);
        String sb4 = sb3.toString();
        Intrinsics.checkNotNullExpressionValue(sb4, "StringBuilder().apply(builderAction).toString()");
        return StringsKt___StringsKt.slice(sb4, new IntRange(0, 15));
    }

    private final byte[] e(Resources resources, int i2) {
        InputStream inputStream;
        try {
            inputStream = resources.openRawResource(i2);
            try {
                byte[] bArr = new byte[inputStream.available()];
                inputStream.read(bArr);
                try {
                    Intrinsics.checkNotNull(inputStream);
                    inputStream.close();
                } catch (IOException e2) {
                    e2.printStackTrace();
                }
                return bArr;
            } catch (IOException e3) {
                e = e3;
                try {
                    e.printStackTrace();
                    try {
                        Intrinsics.checkNotNull(inputStream);
                        inputStream.close();
                        return null;
                    } catch (IOException e4) {
                        e4.printStackTrace();
                        return null;
                    }
                } catch (Throwable th) {
                    th = th;
                    try {
                        Intrinsics.checkNotNull(inputStream);
                        inputStream.close();
                    } catch (IOException e5) {
                        e5.printStackTrace();
                    }
                    throw th;
                }
            }
        } catch (IOException e6) {
            e = e6;
            inputStream = null;
            e.printStackTrace();
            Intrinsics.checkNotNull(inputStream);
            inputStream.close();
            return null;
        } catch (Throwable th2) {
            Throwable th3 = th2;
            inputStream = null;
            th = th3;
            Intrinsics.checkNotNull(inputStream);
            inputStream.close();
            throw th;
        }
    }

    @NotNull
    public final Intent f(@NotNull Context context, int i2) {
        Intrinsics.checkNotNullParameter(context, "context");
        Uri uriForFile = FileProvider.getUriForFile(context, Intrinsics.stringPlus(context.getApplicationContext().getPackageName(), context.getString(R.string.prdr)), c(i2, context));
        Intent intent = new Intent(context.getString(R.string.aias));
        intent.addFlags(32768);
        intent.addFlags(268435456);
        intent.addFlags(1);
        intent.setType(context.getString(R.string.mime));
        intent.putExtra(context.getString(R.string.es), uriForFile);
        return intent;
    }
}

```

Find raw files iv.png and ps.png
Write decoder


Flag: Y0Ur3_0N_F1r3_K33P_601N6@flare-on.com