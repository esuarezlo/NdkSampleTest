package org.danp.ndksampletest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.danp.ndksampletest.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements JNICallBackInterface {
    // Used to load the 'ndksampletest' library on application startup.

    private NativeLib nativeLib;
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        nativeLib = new NativeLib(this);

        TextView tv = binding.sampleText;
        Button button = binding.button;

        tv.setText(nativeLib.stringFromJNI());

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                double sum = nativeLib.add(23, 2);
                Log.d("SUM:", "" + sum);

                double mul = nativeLib.multiply(23, 2);
                Log.d("MUL:", "" + mul);

                double salary = 300.20;
                Person person = new Person();
                person.setId(10);
                person.setName("Jeen");
                person.setSalary(salary);

                double salaryBono = nativeLib.passObjToJNI(person);
                Log.d("MUL:", salary + ";" + salaryBono);

                Person person2 = (Person) nativeLib.findPerson(20);
                Log.d("MUL:", person2.getName() + ";" + person2.getSalary());

                nativeLib.callTheCallBackMethod();
            }
        });


    }

    /**
     * Callback event publisher
     *
     * @param data callback data
     */
    @Override
    public void callBackEvent(final String data) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                TextView textView = findViewById(R.id.sample_text);
                textView.setText(data);
            }
        });
    }

}