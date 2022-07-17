package com.example.validator;

import android.os.Bundle;
import android.widget.Button;
import android.widget.Toast;
import androidx.activity.ComponentActivity;
import androidx.activity.result.ActivityResultRegistry;
import androidx.activity.result.a;
import androidx.activity.result.c;
import b3.d;
import d.e;
import java.util.Locale;
import x0.b;
import z2.o;

/* loaded from: classes.dex */
public class MainActivity extends e {
    public static final /* synthetic */ int s = 0;

    /* renamed from: p */
    public final byte[] f1920p = new byte[32];

    /* renamed from: q */
    public d f1921q;

    /* renamed from: r */
    public final androidx.activity.result.d f1922r;

    public MainActivity() {
        this.f1920p = new byte[32];
        o oVar = new o();
        c cVar = new b();
        ComponentActivity.b bVar = this.f77i;
        StringBuilder g3 = a.g("activity_rq#");
        g3.append(this.f76h.getAndIncrement());
        this.f1922r = (ActivityResultRegistry.a) bVar.d(g3.toString(), this, oVar, cVar);
    }

    /*
        Code decompiled incorrectly, please refer to instructions dump.
        To view partially-correct code enable 'Show inconsistent code' option in preferences
    */
    public static void t(com.example.validator.MainActivity r6, java.lang.String r7, byte[] r8, android.widget.TextView r9) {
        java.util.Objects.requireNonNull(r6);
        android.util.Log.d("MEOW", "data:");     // Catch: java.lang.Exception -> L24
        android.util.Log.d("MEOW", r7);     // Catch: java.lang.Exception -> L24
        b3.a r2 = new b3.a(java.security.MessageDigest.getInstance("SHA-512"));     // Catch: java.lang.Exception -> L24
        r2.initVerify(r6.f1921q);     // Catch: java.lang.Exception -> L24
        r2.update(r7.getBytes());     // Catch: java.lang.Exception -> L24
        if (r2.verify(r8) == true) goto L7;
        java.lang.String r6 = "failed on local verify";
    L11:
        android.util.Log.d("MEOW", r6);     // Catch: java.lang.Exception -> L24
    L26:
        boolean r2 = false;
    L27:
        if (r2 == false) goto L29;
        java.lang.Runnable r6 = new x0.d(r9, r7, 0);
    L30:
        r9.post(r6);
        return;
    L29:
        r6 = new x0.c(r9, r7, 0);
        goto L30
    L7:
        if (r7.equals("example") == false) goto L9;
    L12:
        java.lang.StringBuilder r6 = new java.lang.StringBuilder("[");     // Catch: java.lang.Exception -> L24
        int r2 = r8.length;     // Catch: java.lang.Exception -> L24
        int r3 = 0;
    L13:
        if (r3 >= r2) goto L15;
        r6.append(r8[r3] & 255);     // Catch: java.lang.Exception -> L24
        r6.append(',');     // Catch: java.lang.Exception -> L24
        r3 = r3 + 1;     // Catch: java.lang.Exception -> L24
        goto L13
    L15:
        r2 = true;
        r6.setCharAt(r6.length() - 1, ']');     // Catch: java.lang.Exception -> L24
        java.lang.String r6 = java.lang.String.format("{\"id\":\"%s\",\"signature\":%s}", new java.lang.Object[]{r7, r6});     // Catch: java.lang.Exception -> L24
        android.util.Log.d("MEOW", r6);     // Catch: java.lang.Exception -> L24
        javax.net.ssl.HttpsURLConnection r8 = (javax.net.ssl.HttpsURLConnection) new java.net.URL("https://validator.ecsc22.hack.cert.pl/").openConnection();     // Catch: java.lang.Exception -> L24
        r8.setDoOutput(true);     // Catch: java.lang.Throwable -> L21 java.io.FileNotFoundException -> L21
        r8.setRequestProperty("Content-Type", "application/json");     // Catch: java.lang.Throwable -> L21 java.io.FileNotFoundException -> L21
        java.io.BufferedOutputStream r3 = new java.io.BufferedOutputStream(r8.getOutputStream());     // Catch: java.lang.Throwable -> L21 java.io.FileNotFoundException -> L21
        r3.write(r6.getBytes());     // Catch: java.lang.Throwable -> L21 java.io.FileNotFoundException -> L21
        r3.flush();     // Catch: java.lang.Throwable -> L21 java.io.FileNotFoundException -> L21
        if (r8.getResponseCode() == 200) goto L20;
        r2 = false;
    L20:
        r8.disconnect();     // Catch: java.lang.Exception -> L24
    L21:
        r6 = move-exception;
        r6.printStackTrace();     // Catch: java.lang.Throwable -> L21
        android.util.Log.d("error", (java.lang.String) new java.io.BufferedReader(new java.io.InputStreamReader(r8.getErrorStream(), java.nio.charset.StandardCharsets.UTF_8)).lines().collect(java.util.stream.Collectors.joining("\n")));     // Catch: java.lang.Throwable -> L21
        r8.disconnect();     // Catch: java.lang.Exception -> L24
        goto L26
    L9:
        if (r7.equals("flag") == true) goto L12;
        r6 = "failed data check";
    L24:
        r6 = move-exception;
        android.util.Log.d("MEOW", r6.getMessage());
        r6.printStackTrace();
        goto L26
    }

    @Override // androidx.fragment.app.p, androidx.activity.ComponentActivity, v.f, android.app.Activity
    public final void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(R.layout.activity_main);
        u();     // Catch: Exception -> L6
        ((Button) findViewById(R.id.scan_button)).setOnClickListener(new x0.a());
        return;
    L7:
        throw new RuntimeException("failed to init");
    }

    public final void u() {
        getResources().openRawResource(R.raw.key).read(this.f1920p);
        e3.d dVar = new e3.d(this.f1920p, e3.b.f2672b.get("Ed25519".toLowerCase(Locale.ENGLISH)));
        c3.e eVar = dVar.f2678d;
        eVar.n();
        this.f1921q = new d(new e3.e(eVar, dVar.f2679e));
    }

    public final void v(String str) {
        Toast.makeText(this, str, 1).show();
    }
}