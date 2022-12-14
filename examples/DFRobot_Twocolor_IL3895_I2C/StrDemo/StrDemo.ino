/**！
 * @file StrDemo.ino
 * @brief example Font Display
 * @details The FireBeetle -ePaper Display Module has a built-in font chip that can display 
 * both Chinese and English.
 * Once the program downloaded, ePaper will display two lines of strings that 
 * shows ePaper basic string display. Users just need to call function: 
 * disString and random strings display are available. String colors, 
 * size and coordinate are adjustable.
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
    //Refresh screen display
    epaper.flush(PART);

    //Displays a string, black font
    epaper.disString(41,12,1,"DFRobot黑白电子墨水屏",BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Displays a string, black font
    epaper.disString(57,40,1,"《+-*/=!@#$%&*(》",BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Display large font
    epaper.disString(61,65,2,"大号字体",BLACK);
    //Refresh screen display
    epaper.flush(PART);
}

void loop(void)
{
    delay(8000);
}
