package biz.securing.wandofchaos;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.hardware.SensorManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;
import androidx.security.crypto.EncryptedSharedPreferences;
import androidx.security.crypto.MasterKey;
import com.bumptech.glide.Glide;
import com.squareup.seismic.ShakeDetector;
import java.io.File;
import java.io.IOException;
import java.security.GeneralSecurityException;

public class SpellCaster<isSecretStored> extends Activity implements ShakeDetector.Listener, View.OnClickListener {
    private static MediaPlayer player;
    Button btnClickEvent;
    SpellCaster<isSecretStored>.Spellbook chaos = null;
    /* access modifiers changed from: private */
    public final String chaosSpell = BuildConfig.BABAJAGA_FLAG_2;
    private final String encryptedPreferencesName = "spellbook_level_2";
    private final String preferencesName = "spellbook_level_1";
    /* access modifiers changed from: private */
    public final String simpleSpell = BuildConfig.BABAJAGA_FLAG_1;

    /* access modifiers changed from: protected */
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(C1111R.layout.activity_spell_caster);
        getWindow().setFlags(1024, 1024);
        Button button = (Button) findViewById(C1111R.C1114id.help);
        this.btnClickEvent = button;
        button.setOnClickListener(this);
        try {
            this.chaos = new Spellbook();
        } catch (IOException | GeneralSecurityException e) {
            e.printStackTrace();
        }
        boolean checkSecret = checkSecret();
        ShakeDetector shakeDetector = new ShakeDetector(this);
        shakeDetector.start((SensorManager) getSystemService("sensor"));
        shakeDetector.setSensitivity(11);
        if (!checkSecret) {
            this.chaos.writeSpells();
        }
    }

    public boolean checkSecret() {
        File file = new File(getApplicationContext().getApplicationInfo().dataDir + "/shared_prefs/" + "spellbook_level_1" + ".xml");
        Log.d("secret", getApplicationContext().getApplicationInfo().dataDir + "/shared_prefs/" + "spellbook_level_1" + ".xml");
        return file.exists();
    }

    public void hearShake() {
        this.chaos.getChaosSpell();
        ImageView imageView = (ImageView) findViewById(C1111R.C1114id.witchcraft);
        Glide.with(getApplicationContext()).load(Integer.valueOf(C1111R.C1113drawable.witchcraft)).into(imageView);
        new Handler(Looper.getMainLooper()).post(new Runnable() {
            public final void run() {
                SpellCaster.this.lambda$hearShake$0$SpellCaster();
            }
        });
        MediaPlayer create = MediaPlayer.create(this, C1111R.raw.witch);
        player = create;
        create.start();
        if (!player.isPlaying()) {
            new Handler().postDelayed($$Lambda$SpellCaster$_Xucr9WkUKBeNl8W5M9hucsnvs.INSTANCE, (long) player.getDuration());
        }
        new Handler().postDelayed(new Runnable(imageView) {
            public final /* synthetic */ ImageView f$1;

            {
                this.f$1 = r2;
            }

            public final void run() {
                SpellCaster.this.lambda$hearShake$2$SpellCaster(this.f$1);
            }
        }, 3000);
    }

    public /* synthetic */ void lambda$hearShake$0$SpellCaster() {
        Toast.makeText(getApplicationContext(), "Spell was casted!", 0).show();
    }

    public /* synthetic */ void lambda$hearShake$2$SpellCaster(ImageView imageView) {
        Glide.with(getApplicationContext()).load(Integer.valueOf(C1111R.C1113drawable.forest)).into(imageView);
    }

    public void onClick(View view) {
        new Handler(Looper.getMainLooper()).post(new Runnable() {
            public final void run() {
                SpellCaster.this.lambda$onClick$3$SpellCaster();
            }
        });
    }

    public /* synthetic */ void lambda$onClick$3$SpellCaster() {
        Toast.makeText(getApplicationContext(), "Shake the wand to cast a spell", 0).show();
    }

    private class Spellbook {
        SharedPreferences SpellsLevel2;
        Context context;
        MasterKey secretKey;

        private Spellbook() throws GeneralSecurityException, IOException {
            Context applicationContext = SpellCaster.this.getApplicationContext();
            this.context = applicationContext;
            MasterKey build = new MasterKey.Builder(applicationContext).setKeyScheme(MasterKey.KeyScheme.AES256_GCM).build();
            this.secretKey = build;
            this.SpellsLevel2 = EncryptedSharedPreferences.create(this.context, "spellbook_level_2", build, EncryptedSharedPreferences.PrefKeyEncryptionScheme.AES256_SIV, EncryptedSharedPreferences.PrefValueEncryptionScheme.AES256_GCM);
        }

        /* access modifiers changed from: package-private */
        public String getChaosSpell() {
            return this.SpellsLevel2.getString("chaos_spell", "ups, something went wrong");
        }

        /* access modifiers changed from: private */
        public void writeSpells() {
            this.SpellsLevel2.edit().putString("chaos_spell", SpellCaster.this.chaosSpell).apply();
            SharedPreferences.Editor edit = this.context.getSharedPreferences("spellbook_level_1", 0).edit();
            edit.putString("simple_spell", SpellCaster.this.simpleSpell);
            edit.apply();
        }
    }
}
