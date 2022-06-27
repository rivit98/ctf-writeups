package biz.securing.wandofchaos.databinding;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.viewbinding.ViewBinding;
import biz.securing.wandofchaos.C1111R;

public final class ActivitySpellCasterBinding implements ViewBinding {
    public final Button help;
    private final ConstraintLayout rootView;
    public final ImageView witchcraft;

    private ActivitySpellCasterBinding(ConstraintLayout constraintLayout, Button button, ImageView imageView) {
        this.rootView = constraintLayout;
        this.help = button;
        this.witchcraft = imageView;
    }

    public ConstraintLayout getRoot() {
        return this.rootView;
    }

    public static ActivitySpellCasterBinding inflate(LayoutInflater layoutInflater) {
        return inflate(layoutInflater, (ViewGroup) null, false);
    }

    public static ActivitySpellCasterBinding inflate(LayoutInflater layoutInflater, ViewGroup viewGroup, boolean z) {
        View inflate = layoutInflater.inflate(C1111R.layout.activity_spell_caster, viewGroup, false);
        if (z) {
            viewGroup.addView(inflate);
        }
        return bind(inflate);
    }

    public static ActivitySpellCasterBinding bind(View view) {
        int i = C1111R.C1114id.help;
        Button button = (Button) view.findViewById(C1111R.C1114id.help);
        if (button != null) {
            i = C1111R.C1114id.witchcraft;
            ImageView imageView = (ImageView) view.findViewById(C1111R.C1114id.witchcraft);
            if (imageView != null) {
                return new ActivitySpellCasterBinding((ConstraintLayout) view, button, imageView);
            }
        }
        throw new NullPointerException("Missing required view with ID: ".concat(view.getResources().getResourceName(i)));
    }
}
