package com.example.tipcalculator;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.textfield.TextInputLayout;

public class MainActivity extends AppCompatActivity {
    /* user inputs */
    private double totalBill;
    private int tipPercent;
    private int numPerson;
    /*outputs */
    private double totalToPay;
    private double tipTotal;
    private double totalPerPerson;

    /* extract user inputs (total bills, tip percent, etc.) */
    private void extractAllInputs() {
        TextInputLayout textViewTotalBill = findViewById(R.id.entryTotalBill);
        this.totalBill = Double.parseDouble(textViewTotalBill.getEditText().getText().toString());
        // tipPercent should have been updated
        // numPerson should have been updated
    }

    /* calculate outputs based on user inputs */
    private void calculateAllOutputs() {
        this.tipTotal = this.totalBill * this.tipPercent / 100.0;
        this.totalToPay = this.totalBill + this.tipTotal;
        if (numPerson == 0) {
            Context context = getApplicationContext();
            CharSequence text = "Hmm.. no one is paying the damn bill?";
            int duration = Toast.LENGTH_LONG;

            Toast toast = Toast.makeText(context, text, duration);
            toast.show();

        }
        this.totalPerPerson = this.totalToPay / numPerson;
    }

    /* display outputs in corresponding places */
    private void showAllOutputs() {
        TextView textViewTotalToPay = findViewById(R.id.textView6);
        textViewTotalToPay.setText(Double.toString(this.totalToPay));
        TextView textViewTipTotal = findViewById((R.id.textView8));
        textViewTipTotal.setText(Double.toString((this.tipTotal)));
        TextView textViewTotalPerPerson = findViewById(R.id.textView10);
        textViewTotalPerPerson.setText(Double.toString(this.totalPerPerson));
    }

    private void updateTipPercent(int subOrAdd) {
        if (subOrAdd == 0) {
            this.tipPercent = this.tipPercent - 1;
        }
        else {
            this.tipPercent = this.tipPercent + 1;
        }

        if (this.tipPercent<0) {
            this.tipPercent = 0;
        }
        else if (this.tipPercent>99) {
            this.tipPercent = 99;
        }
    }

    private void updateNumPerson(int subOrAdd) {
        if (subOrAdd == 0) {
            this.numPerson = this.numPerson - 1;
        }
        else {
            this.numPerson = this.numPerson + 1;
        }

        if (this.numPerson<0) {
            this.numPerson = 0;
        }
        else if (this.numPerson>20) {
            this.numPerson = 20;
        }
    }

    private void showTipPercent() {
        TextView textViewTipPercent = findViewById(R.id.textView11);
        textViewTipPercent.setText(Integer.toString((this.tipPercent)));
    }

    private void showNumPerson() {
        TextView textViewTipPercent = findViewById(R.id.textView12);
        textViewTipPercent.setText(Integer.toString((this.numPerson)));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        /* initialize state variables */
        this.tipPercent = 0;
        this.numPerson = 0;

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar myToolbar = findViewById(R.id.tipCalcToolBar);
        setSupportActionBar(myToolbar);
        showTipPercent();
        showNumPerson();

        /* set behavior when "calculate" pressed */
        Button buttonCalculate = findViewById(R.id.buttonCalculate);
        buttonCalculate.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                extractAllInputs();
                calculateAllOutputs();
                showAllOutputs();
            }
        });

        /* set behavior when "tip -" pressed */
        Button buttonTipPercentSub = findViewById(R.id.buttonTipPercentSub);
        buttonTipPercentSub.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                updateTipPercent(0);
                showTipPercent();
            }
        });

        /* set behavior when "tip +" pressed */
        Button buttonTipPercentAdd = findViewById(R.id.buttonTipPercentAdd);
        buttonTipPercentAdd.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                updateTipPercent(1);
                showTipPercent();
            }
        });

        /* set behavior when "numPerson -" pressed */
        Button buttonNumPersonSub = findViewById(R.id.buttonNumPersonSub);
        buttonNumPersonSub.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                updateNumPerson(0);
                showNumPerson();
            }
        });

        /* set behavior when "numPerson +" pressed */
        Button buttonNumPersonAdd = findViewById(R.id.buttonNumPersonAdd);
        buttonNumPersonAdd.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                updateNumPerson(1);
                showNumPerson();
            }
        });

        Button cancelButton = findViewById((R.id.buttonCancel));
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openCancel_Activity();
            }
        });

        Button finishButton = findViewById((R.id.buttonFinish));
        finishButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openFinish_Activity();
            }
        });
    }
    public void openCancel_Activity() {
        Intent intent = new Intent(this, Cancel_Activity.class);
        startActivity(intent);
    }

    public void openFinish_Activity() {
        Intent intent = new Intent(this, Finish_Activity.class);
        startActivity(intent);
    }
}
