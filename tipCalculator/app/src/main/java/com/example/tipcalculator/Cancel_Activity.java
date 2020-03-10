package com.example.tipcalculator;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Rect;
import android.os.Bundle;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.View;

public class Cancel_Activity extends AppCompatActivity {

    Cancel_Activity_View myNewGraphicsView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_cancel_);
        myNewGraphicsView = new Cancel_Activity_View(this);
        setContentView(myNewGraphicsView);

        myNewGraphicsView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                float x = motionEvent.getX();
                float y = motionEvent.getY();
                if(x>=100 && x<=1000 && y>=1400 && y<=1500){
                    finishAffinity();
                }
                else if(x>=100 && x<=1000 && y>=1600 && y<=1700){
                    finish();
                }
                return false;
            }
        });
    }


}
