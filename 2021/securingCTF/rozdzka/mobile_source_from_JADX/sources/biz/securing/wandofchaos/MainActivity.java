package biz.securing.wandofchaos;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Debug;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import com.scottyab.rootbeer.RootBeer;
import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import javax.net.ssl.HttpsURLConnection;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends Activity implements View.OnClickListener {
    Button btnClickEvent;

    /* access modifiers changed from: protected */
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(C1111R.layout.activity_main);
        getWindow().setFlags(1024, 1024);
        Button button = (Button) findViewById(C1111R.C1114id.unlock);
        this.btnClickEvent = button;
        button.setOnClickListener(this);
        antiRe();
    }

    public void antiRe() {
        boolean checkRoot = checkRoot();
        if (checkRoot) {
            Log.d("antiRE", "Application runs on rooted device!");
        }
        boolean checkDebugger = checkDebugger();
        boolean checkDebuggerAttached = checkDebuggerAttached();
        if (checkRoot || checkDebugger || checkDebuggerAttached) {
            Log.d("Root", String.valueOf(checkRoot));
            Log.d("Debugger", String.valueOf(checkDebugger));
            Log.d("DebuggerAttached", String.valueOf(checkDebuggerAttached));
            Log.d("antiRE", "Device is not secure");
            exitApp();
        }
    }

    private boolean checkDebuggerAttached() {
        return Debug.isDebuggerConnected();
    }

    private boolean checkDebugger() {
        return (getApplicationInfo().flags & 2) != 0;
    }

    private boolean checkRoot() {
        return new RootBeer(this).isRooted();
    }

    public void exitApp() {
        finishAffinity();
        System.exit(0);
    }

    public void authorize() throws IOException, JSONException {
        JSONObject jSONObject = new JSONObject();
        jSONObject.put("password", ((EditText) findViewById(C1111R.C1114id.password)).getText().toString());
        HttpsURLConnection httpsURLConnection = (HttpsURLConnection) new URL("https://rozdzka.securing.pl/login").openConnection();
        httpsURLConnection.setRequestMethod("POST");
        httpsURLConnection.setRequestProperty("Content-Type", "application/json; charset=utf-8");
        httpsURLConnection.setRequestProperty("Accept", "application/json");
        httpsURLConnection.setDoInput(true);
        httpsURLConnection.setDoOutput(true);
        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(new BufferedOutputStream(httpsURLConnection.getOutputStream()), StandardCharsets.UTF_8));
        bufferedWriter.write(jSONObject.toString());
        bufferedWriter.flush();
        int responseCode = httpsURLConnection.getResponseCode();
        Log.d("response", "Response code is " + responseCode);
        if (responseCode == 200) {
            startActivity(new Intent(this, SpellCaster.class));
        } else {
            new Handler(Looper.getMainLooper()).post(new Runnable() {
                public final void run() {
                    MainActivity.this.lambda$authorize$0$MainActivity();
                }
            });
        }
    }

    public /* synthetic */ void lambda$authorize$0$MainActivity() {
        Toast.makeText(getApplicationContext(), "Wrong password", 0).show();
    }

    public void onClick(View view) {
        new Thread(new Runnable() {
            public final void run() {
                MainActivity.this.lambda$onClick$1$MainActivity();
            }
        }).start();
    }

    public /* synthetic */ void lambda$onClick$1$MainActivity() {
        try {
            authorize();
        } catch (IOException | JSONException e) {
            e.printStackTrace();
            Toast.makeText(getApplicationContext(), "Ooops, something went wrong", 0).show();
        }
    }
}
