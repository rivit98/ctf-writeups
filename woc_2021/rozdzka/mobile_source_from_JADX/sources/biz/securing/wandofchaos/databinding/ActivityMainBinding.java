package biz.securing.wandofchaos.databinding;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.viewbinding.ViewBinding;
import biz.securing.wandofchaos.C1111R;

public final class ActivityMainBinding implements ViewBinding {
    public final ImageView moon;
    public final EditText password;
    private final ConstraintLayout rootView;
    public final Button unlock;

    private ActivityMainBinding(ConstraintLayout constraintLayout, ImageView imageView, EditText editText, Button button) {
        this.rootView = constraintLayout;
        this.moon = imageView;
        this.password = editText;
        this.unlock = button;
    }

    public ConstraintLayout getRoot() {
        return this.rootView;
    }

    public static ActivityMainBinding inflate(LayoutInflater layoutInflater) {
        return inflate(layoutInflater, (ViewGroup) null, false);
    }

    public static ActivityMainBinding inflate(LayoutInflater layoutInflater, ViewGroup viewGroup, boolean z) {
        View inflate = layoutInflater.inflate(C1111R.layout.activity_main, viewGroup, false);
        if (z) {
            viewGroup.addView(inflate);
        }
        return bind(inflate);
    }

    public static ActivityMainBinding bind(View view) {
        int i = C1111R.C1114id.moon;
        ImageView imageView = (ImageView) view.findViewById(C1111R.C1114id.moon);
        if (imageView != null) {
            i = C1111R.C1114id.password;
            EditText editText = (EditText) view.findViewById(C1111R.C1114id.password);
            if (editText != null) {
                i = C1111R.C1114id.unlock;
                Button button = (Button) view.findViewById(C1111R.C1114id.unlock);
                if (button != null) {
                    return new ActivityMainBinding((ConstraintLayout) view, imageView, editText, button);
                }
            }
        }
        throw new NullPointerException("Missing required view with ID: ".concat(view.getResources().getResourceName(i)));
    }
}
