/**！
 * @file FigureDemo.ino
 * @brief It shows infrastructure functions of ePaper drawing.
 * @details Once the program downloaded, ePaper will display some figures 
 * such as dotted lines,oblique lines, rectangle, filling rectangle 
 * region, round, filling round range.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-09-7
 * @url https://github.com/DFRobot/DFRobot_ePaper
 */
 
#include "Arduino.h"
#include "DFRobot_IL3895_I2C.h"
DFRobot_IL3895_I2C epaper;

#define BUSY     D4

void setup(void)
{
    Serial.begin(115200);
    //Select the corresponding pins
    epaper.begin(BUSY);

    //Clear the screen and display white
    epaper.fillScreen(WHITE);
    //Refresh screen display
    epaper.flush(FULL);
    //Displays a string, black font
    epaper.disString(0,0,1,"I2C",BLACK);
    
    //Let me draw a red dot
    for(uint8_t x=12,y=12; y<110; y+=3)
    {
        epaper.drawPixel(x,y,BLACK);
    }
    //Refresh screen display
    epaper.flush(PART);

    //Draw two lines
    epaper.drawLine(24,12, 36,110,BLACK);
    epaper.drawLine(36,12, 24,110,BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Draw a red rectangle
    epaper.drawRect(48,12, 40,98,BLACK);
    //Refresh screen display
    epaper.flush(PART);
    //Fill a rectangle with black
    epaper.fillRect(55,19, 26,84,BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Draw a hollow circle
    epaper.drawCircle(122,37, 25,BLACK);
    //Refresh screen display
    epaper.flush(PART);
    //Draw a solid circle
    epaper.fillCircle(122,37, 18,BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Draw a rounded rectangle
    epaper.drawRoundRect(97,67, 50,43, 10,BLACK);
     //Refresh screen display
    epaper.flush(PART);
    //Fill in a rounded rectangle
    epaper.fillRoundRect(102,72, 40,33, 8,BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Draw a triangle
    epaper.drawTriangle(180,12, 155,110, 205,110,BLACK);
    //Refresh screen display
    epaper.flush(PART);
    //Fill in a triangle
    epaper.fillTriangle(180,23, 162,105, 198,105,BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Prompt characters
    epaper.disString(215,12, 2,"图",BLACK);
    epaper.disString(215,78, 2,"形",BLACK);
    //Refresh screen display
    epaper.flush(PART);
}

void loop(void)
{
    delay(8000);
}