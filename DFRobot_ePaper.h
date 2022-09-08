/*!
 * @file DFRobot_ePaper.h
 * @brief Define the infrastructure of the DFRobot_ePaper class
 * @details 该库为IL3895和IL0376F两款墨水屏提供了通信接口和基本的图形显示接口
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-09-7
 * @url https://github.com/DFRobot/DFRobot_ePaper
 */
 
#ifndef DFROBOT_EPAPER_H_
#define DFROBOT_EPAPER_H_
 
#include <Arduino.h>
#include <String.h>
#include <math.h>
#include <Wire.h>
#include "DFRobot_Display.h"
#include "DFRobot_GT30L.h"

#ifndef __DFRobot_ePaper_H
#define __DFRobot_ePaper_H

//Pin definition
#ifdef __AVR__
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#endif

//scan_direction
#define EINK_SCAN_DIR1        ((uint8_t)2<<2)///< From left to right, top to bottom

#define EINK_SCAN_DIR2        ((uint8_t)0<<2)///< From left to right, down to the top

#define EINK_SCAN_DIR3        ((uint8_t)3<<2)///< From right to left, top to bottom

#define EINK_SCAN_DIR4        ((uint8_t)1<<2)///< From right to left, down to top 

/*! color */
#define LUCENCY  0
#define WHITE    1
#define BLACK    2
#define RED      3

/*! Instruction set */
#define  DFR_IL3895_FLUSH                      1
#define  DFR_IL3895_CLEAR                      2
#define  DFR_IL3895_DRAWPICTURE                3
#define  DFR_IL3895_DISSTRING                  4
#define  DFR_IL3895_DRAWPOINT                  5
#define  DFR_IL3895_DRAWLINE                   6
#define  DFR_IL3895_DEAWRECTANGLE              7
#define  DFR_IL3895_DRAWCIRCLE                 8
#define  DFR_IL3895_DRAWFILLRECT               9
#define  DFR_IL3895_STANDBY                   10
#define  DFR_IL3895_DISSTRING_START          111
#define  DFR_IL3895_DISSTRING_END            112
#define  DFR_IL3895_DRAWVLINE                 13
#define  DFR_IL3895_DRAWHLINE                 14

/*! Instruction set */
#define  DFR_IL0376F_FLUSH                    15
#define  DFR_IL0376F_CLEAR                    16
#define  DFR_IL0376F_DRAWPICTURE              17
#define  DFR_IL0376F_DISSTRING                18
#define  DFR_IL0376F_DRAWPOINT                19
#define  DFR_IL0376F_DRAWLINE                 20
#define  DFR_IL0376F_DEAWRECTANGLE            21
#define  DFR_IL0376F_DRAWCIRCLE               22
#define  DFR_IL0376F_DRAWFILLRECT             23
#define  DFR_IL0376F_STANDBY                  24
#define  DFR_IL0376F_DISSTRING_START         111
#define  DFR_IL0376F_DISSTRING_END           113
#define  DFR_IL0376F_DRAWVLINE                27
#define  DFR_IL0376F_DRAWHLINE                28

/*! ePaper id */
#define IL0376F_SPI  0
#define IL3895_I2C   1
#define IL0376F_I2C  2
#define IL3895_SPI   3

/*! Black and white epaper screen size */
#define xDot 128
#define yDot 250

/*! refresh mode */
#define FULL     0
#define PART     1

const unsigned char LUTDefault_part[]={
0x32,  // command
0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0F,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
const unsigned char LUTDefault_full[]={
0x32,  // command
0x22,0x55,0xAA,0x55,0xAA,0x55,0xAA,
0x11,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x1E,0x1E,0x1E,0x1E,0x1E,
0x1E,0x1E,0x1E,0x01,0x00,0x00,0x00,0x00,
};
 

/**
 * @struct eInk_dev
 * @brief eINK important parameters 
 */
typedef struct{
    uint16_t highly;
    uint16_t width;
    uint8_t scandir;
}eInk_dev;

typedef bool InkScreen_Error;

class DFRobot_ePaper : public DFRobot_Display
{
public:
  /**
   * @fn DFRobot_ePaper
   * @brief 构造函数
   * @param width 墨水瓶宽度
   * @param height 墨水瓶高度
   * @param scandir 显示方向
   * @param ADDRESS 墨水瓶地址
   * @param id 墨水屏幕id，用来分通信方式
   * @return None
   */
  DFRobot_ePaper(uint16_t width, uint16_t height, uint8_t scandir, uint8_t ADDRESS, uint8_t id);
  ~DFRobot_ePaper();

  /**
   * @fn flush
   * @brief Refresh screen 
   * @return None
   */
  void flush();

  /**
   * @fn flush
   * @brief Refresh screen 
   * @param mode PART：局部刷新模式,FULL全屏刷新模式
   * @return None
   */
  void flush(uint8_t mode);

  /**
   * @fn drawPicture
   * @brief 显示图片（212*104），可以是红色、黑白、红白黑三色图片。
   * @param pic_bw 黑白图片。
   * @param pic_red 红色图片。
   */
  void drawPicture(const unsigned char *pic_bw, const unsigned char *pic_red);

  /**
   * @fn drawPicture
   * @brief 显示图片（212*104），可以是红色、黑白、红白黑三色图片。
   * @param pic_bw_3895 黑白图片
   */
  void drawPicture(const unsigned char *pic_bw_3895);

  /**
   * @fn fillScreen
   * @brief 填充屏幕
   * @param color WHITE RED BLACK
   */
  void fillScreen(uint16_t color);

  /**
   * @fn drawPixel
   * @brief 在屏幕上画点
   * @param x 点的x坐标
   * @param y 点的y坐标
   * @param color WHITE RED BLACK
   */
  void drawPixel(int16_t x, int16_t y, uint16_t color);

  /**
   * @fn disString
   * @brief Displays a string
   * @param x 字符串起始x坐标
   * @param y 字符串起始y坐标
   * @param size 字符串的大小
   * @param ch 字符串内容
   * @param color WHITE RED BLACK
   */
  void disString(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color);

private:

/********************IL0376F*********************/

    void             setWindow(uint16_t x, uint16_t y);
    void             powerOn(void);
    void             powerOff(void);
    void             clear(uint8_t color);

    virtual void     stateScan(void) {}
    virtual void     spiRead(uint32_t addr, uint8_t len, char *ch) {}
    virtual void     spiWriteByte(unsigned char value) {}
    virtual void     spiWirteCmd(unsigned char command) {}
    virtual void     spiWirteData(unsigned char data) {}
    virtual void     spiDelay(unsigned char xsp) {}
    virtual void     disStringIL0376FSPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color) {}

    virtual void     i2cWrite(unsigned char addr, unsigned char Reg, unsigned char *buf, unsigned char Num) {}
    virtual void     i2cWriteByte(unsigned char addr, unsigned char Cmd) {}
    virtual void     i2cWriteBuffer(unsigned char addr,  unsigned char *buf, unsigned char Num) {}


/********************IL3895*********************/

    void             SetRamArea(unsigned char Xstart,unsigned char Xend,unsigned char Ystart,unsigned char Ystart1,unsigned char Yend,unsigned char Yend1);
    void             SetRamPointer(unsigned char addrX,unsigned char addrY,unsigned char addrY1);
    void             W21Init();
    void             UpdatePart();
    void             UpdateFull();
    void             disPart(unsigned char xStart,unsigned char xEnd,unsigned long yStart,unsigned long yEnd,unsigned char *DisBuffer);
    void             disFull(unsigned char *DisBuffer);
    void             WirteLUT(unsigned char *LUTvalue,unsigned char Size);
    void             powerOnIL3895();
    void             initPart();
    void             initFull();

    virtual void     spiReadIL3895(uint32_t addr, uint8_t len, char *ch) {}
    virtual void     spiWriteByteIL3895(unsigned char value) {}
    virtual void     spiWirteCmdIL3895(unsigned char command) {}
    virtual void     spiDelayIL3895(unsigned char xsp) {}
    virtual void     spiWirteCmdDataIL3895(unsigned char command,unsigned char data) {}
    virtual void     SetCmdDataIL3895(unsigned char *value, unsigned char datalen) {}
    virtual void     WriteDispRamIL3895(unsigned char XSize,unsigned int YSize,unsigned char *Dispbuff) {}
    virtual void     disStringIL3895SPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color) {}
    virtual void     stateScanIL3895(void) {}


    uint8_t           Address;
    uint8_t           epaPerID;
};

#endif
