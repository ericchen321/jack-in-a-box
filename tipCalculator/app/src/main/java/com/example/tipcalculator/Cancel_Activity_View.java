package com.example.tipcalculator;

import android.view.View;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.graphics.Rect;
import android.view.View;


public class Cancel_Activity_View extends View {
    public Cancel_Activity_View(Context context) {
        super(context);
    }

    @Override
    public void onDraw (Canvas canvas) {
        canvas.drawColor(Color.BLACK);

        Paint paint = new Paint();        // create a new “paint brush” to draw on canvas
        int max_x = getWidth() - 1;        // get width and height of the view in pixel
        int max_y = getHeight() - 1;

        paint.setColor(Color.RED);    // Draw some green lines of various transparencies
        paint.setStrokeWidth(10);        // Set paintbrush thickness to 5 pixels
        int alpha = 255;

        for (int j = 10; j <=max_y; j += 120 ) {
            for (int i = 10; i <= max_x-100 ; i += 120 ) {
                //for(int j = 120; j<= ma)
                cross(i, j, canvas, paint);
            }
        }

        paint.setColor(Color.GRAY);
        canvas.drawRect(500, 350, 950, 500, paint);

        paint.setColor(Color.YELLOW);
        canvas.drawCircle(250, 250, 175, paint);

        paint.setColor(Color.BLUE);
        paint.setStrokeWidth(50);
        canvas.drawLine(437, 400, 437-200, 400+200, paint);
        canvas.drawLine(400, 400, 400+200, 400+200, paint);
        paint.setStrokeWidth(30);
        canvas.drawLine(437-220, 400+200, 400+220, 400+200, paint);
        canvas.drawLine(437-150, 400+170, 400+150, 400+170, paint);
        canvas.drawLine(437-120, 400+140, 400+120, 400+140, paint);
        canvas.drawLine(437-90, 400+110, 400+90, 400+110, paint);
        canvas.drawLine(437-60, 400+70, 400+60, 400+70, paint);
        canvas.drawLine(437-60, 400+80, 400+60, 400+80, paint);

        paint.setColor(Color.GREEN);
        canvas.drawRect(205, 350, 350, 500, paint);

        paint.setColor(Color.MAGENTA);
        paint.setStrokeWidth(50);
        canvas.drawLine(700+ 100, 200, 550, 450, paint);
        canvas.drawCircle(625, 255, 40, paint);
        canvas.drawCircle(755, 375, 40, paint);

        paint.setColor(Color.RED);
        canvas.drawRect(100, 800, 1000, 1300, paint);
        paint.setColor(Color.BLACK);
        canvas.drawRect(120, 820, 980, 1280, paint);
        paint.setColor(Color.WHITE);
        paint.setTextSize(110);
        canvas.drawText ("Thankyou for", 140, 920, paint );
        canvas.drawText ("using our ", 140, 1020, paint );
        paint.setColor(Color.RED);
        canvas.drawText ("TipCalculator", 140, 1140, paint );


        canvas.drawRect(100, 1400, 1000, 1500, paint);
        paint.setColor(Color.WHITE);
        canvas.drawText ("EXIT", 450, 1490, paint );

        paint.setColor(Color.GREEN);
        canvas.drawRect(100, 1600, 1000, 1700, paint);
        paint.setColor(Color.WHITE);
        canvas.drawText ("BACK", 425, 1690, paint );



    }



    public void cross (int x, int y, Canvas canvas, Paint paint){
        canvas.drawLine(x, y, x + 100, y + 100, paint);
        canvas.drawLine(x + 100, y, x, y + 100, paint);
    }



        /*for ( int y = 0; y <= 9 * max_y / 10; y += max_y / 10) {
            int max = y+200;
            //for(int i=y; i<max; i++){
                /*paint.setColor(y*2);
                paint.setAlpha(alpha);
                canvas.drawLine(0, i, max_x,i, paint);
                i = i+5;
                alpha -= 25;

            //}
            canvas.drawCircle(max_x/2, max_y/2, max, paint);
            paint.setColor(Color.GREEN);
            //canvas.drawLine(0, y, max_x,y, paint);
            alpha = 255;
        }*/
        /*paint.setAlpha(alpha);
        for (int i = 100; i>=0; i--){
            canvas.drawCircle(max_x/2, max_y/2, i, paint);
            paint.setAlpha(alpha);
            alpha -=25;
        }
        paint.setAlpha(255);
        paint.setAlpha(255); 		// Draw some text at X,Y co-ord [50,50]
        //paint.setTextSize(100);
        //canvas.drawText ("Thank you, come again.", (max_x/4), max_y/2, paint );



    }
/*
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int Action = event.getAction();
        //if (Action == MotionEvent.ACTION_DOWN) {
            int XCoord = (int) event.getX();    // x coord of touch
            int YCoord = (int) event.getY();      // y coord of touch

            Canvas canvas = new Canvas();
            Paint paint = new Paint();
            paint.setColor(Color.RED);
            paint.setStrokeWidth(5);
            canvas.drawCircle(XCoord, YCoord, 10, paint);
        //}
        invalidate();
        return true;
    }*/

}


