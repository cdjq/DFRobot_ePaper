/*!
 * @file DFRobot_IL3895_I2C.h
 * @brief Define the infrastructure of the DFRobot_IL3895_I2C class
 * @details 该库通过I2C协议与IL3895墨水屏幕控制芯片通信
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2022-09-7
 * @url https://github.com/DFRobot/DFRobot_ePaper
 */

#include <Arduino.h>
#include <Wire.h>
#include <String.h>
#include <math.h>
#include "DFRobot_ePaper.h"

#ifndef __DFRobot_IL3895_I2C_H
#define __DFRobot_IL3895_I2C_H

/*! Instruction set */
#define  DFR_IL3895_FLUSH                    1
#define  DFR_IL3895_CLEAR                    2
#define  DFR_IL3895_DRAWPICTURE              3
#define  DFR_IL3895_DISSTRING                4
#define  DFR_IL3895_DRAWPOINT                5
#define  DFR_IL3895_DRAWLINE                 6
#define  DFR_IL3895_DEAWRECTANGLE            7
#define  DFR_IL3895_DRAWCIRCLE               8
#define  DFR_IL3895_DRAWFILLRECT             9
#define  DFR_IL3895_STANDBY                 10
#define  DFR_IL3895_DISSTRING_START         111
#define  DFR_IL3895_DISSTRING_END           112
#define  DFR_IL3895_DRAWVLINE               13
#define  DFR_IL3895_DRAWHLINE               14
//Address selection
#define A0   0x30>>1
#define A1   0x38>>1
#define A2   0x3C>>1
#define A3   0x3E>>1
//Instruction set
#define  DFR_IL3895_STANDBY         10
//Screen parameters
#define WIDTH                       (uint16_t)250
#define HIGHLY                      (uint16_t)122
#define ID                          (uint8_t)1

class DFRobot_IL3895_I2C : public DFRobot_ePaper
{
public:
  /**
   * @fn DFRobot_IL3895_I2C
   * @brief 构造函数
   * @return None
   */
  DFRobot_IL3895_I2C();
  /**
   * @fn ~DFRobot_IL3895_I2C
   * @brief 析构函数
   * @return None
   */
  ~DFRobot_IL3895_I2C();

  /**
   * @fn begin
   * @brief 初始化屏幕
   * @param busy Select I2C busy pin
   */
  void        begin(const char busy);
  /**
   * @fn standby
   * @brief 是屏幕进入standby模式
   */
  void        standby();

  /**
   * @fn wakeUp
   * @brief 唤醒屏幕
   */
  void        wakeUp();

  /**
   * @fn fillRect
   * @brief Fill the rectangle
   * @param x 矩形起点x坐标
   * @param y 矩形起点y坐标
   * @param width 矩形的宽度
   * @param height 矩形的高度
   * @param color WHITE RED BLACK
   */
  void        fillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);

  /**
   * @fn fillCircle
   * @brief Fill the circle 
   * @param x0 圆心的x坐标
   * @param y0 圆心的y坐标
   * @param r 圆的半径
   * @param color WHITE RED BLACK
   */
  void        fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
private:
    void        stateScan();
    void        i2cWrite(unsigned char addr, unsigned char Reg, unsigned char *buf, unsigned char Num);
    void        i2cWriteByte(unsigned char addr, unsigned char Cmd);
    void        i2cWriteBuffer(unsigned char addr,  unsigned char *buf, unsigned char Num);

    uint8_t     Address;
    uint8_t     DFR_W21_BUSY;
};

#endif
