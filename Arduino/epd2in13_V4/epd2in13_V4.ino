#include <SPI.h>
#include <math.h>
#include "epd2in13_V4.h"
#include "epdpaint.h"
#include "star.h"

#define COLORED     0
#define UNCOLORED   1

/**
  * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  * In this case, a smaller image buffer is allocated and you have to 
  * update a partial display several times.
  * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  */
unsigned char image[1050];
Paint paint(image, 0, 0);
Epd epd;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("epd FAST");
  epd.Init(FAST);
  // epd.Init(FULL);
  epd.Display_Fast(star);
  // epd.Display1(star);
  delay(2000);

#if 1
  Serial.println("epd FULL");
  epd.Init(FULL);
  Paint paint(image, epd.bufwidth*8, epd.bufheight);    //width should be the multiple of 8

  // 第一屏：显示标题和图标
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(20, 15, "Smart Display", &Font12, COLORED);
  // 添加一个简单的边框
  paint.DrawRectangle(5, 5, 115, 35, COLORED);
  epd.Display1(image);
  delay(1500);
  
  // 第二屏：绘制天气信息
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(10, 5, "Weather:", &Font12, COLORED);
  paint.DrawStringAt(10, 25, "Sun 26C", &Font12, COLORED);
  
  // 绘制优化的太阳图标
  int centerX = 90;
  int centerY = 20;
  int radius = 8;
  
  // 绘制太阳中心
  paint.DrawFilledCircle(centerX, centerY, radius, COLORED);
  
  // 绘制太阳光芒 - 更长的光线
  for(int i = 0; i < 8; i++) {
    float angle = i * PI / 4;
    int x1 = centerX + cos(angle) * (radius + 2);
    int y1 = centerY + sin(angle) * (radius + 2);
    int x2 = centerX + cos(angle) * (radius + 10);
    int y2 = centerY + sin(angle) * (radius + 10);
    paint.DrawLine(x1, y1, x2, y2, COLORED);
  }
  
  // 绘制额外的较短光线，使太阳看起来更生动
  for(int i = 0; i < 8; i++) {
    float angle = i * PI / 4 + PI / 8;
    int x1 = centerX + cos(angle) * (radius + 2);
    int y1 = centerY + sin(angle) * (radius + 2);
    int x2 = centerX + cos(angle) * (radius + 6);
    int y2 = centerY + sin(angle) * (radius + 6);
    paint.DrawLine(x1, y1, x2, y2, COLORED);
  }
  
  epd.Display1(image);
  delay(1500);

  // 第三屏：绘制一个简单的进度条动画
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(15, 5, "System Init...", &Font12, COLORED);
  paint.DrawRectangle(10, 25, 110, 35, COLORED);
  for(int i = 0; i < 100; i += 20) {
    paint.DrawFilledRectangle(11, 26, 11 + i, 34, COLORED);
    epd.Display1(image);
    delay(300);
  }
  
  // 第四屏：显示完成信息和装饰图案
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(20, 15, "Ready to use", &Font12, COLORED);
  epd.Display1(image);

  delay(2000);

#else

  Serial.println("epd PART");
  epd.DisplayPartBaseImage(star);
  char i = 0;
  for (i = 0; i < 10; i++) {
    Serial.println("e-Paper PART IMAGE_DATA");
    epd.Init(PART);
    epd.DisplayPart(star);
    Serial.println("e-Paper PART Clear");
	  epd.Init(PART);
    epd.ClearPart();
    delay(2000);
  }

#endif

  epd.Init(FULL);
  Serial.println("e-Paper clear and sleep");
  epd.Clear();
  epd.Sleep();

}

void loop()
{

}