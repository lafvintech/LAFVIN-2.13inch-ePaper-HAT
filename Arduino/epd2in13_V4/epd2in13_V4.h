#ifndef epd2in13_V4
#define epd2in13_V4

#include "epdif.h"

// Display resolution
#define EPD_WIDTH       122
#define EPD_HEIGHT      250

#define FULL			0
#define FAST			1
#define PART			2

class Epd : EpdIf {
public:
    unsigned long width;
    unsigned long height;
    int bufwidth;
    int bufheight;
    int count;

    Epd();
    ~Epd();
    int  Init(char Mode);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle(void);
	void SetWindows(unsigned char Xstart, unsigned char Ystart, unsigned char Xend, unsigned char Yend);
	void SetCursor(unsigned char Xstart, unsigned char Ystart);
	void Lut(unsigned char *lut);
    void Reset(void);
    void Clear(void);
    void Display(const unsigned char* frame_buffer);
    void Display1(const unsigned char* frame_buffer);
    void Display_Fast(const unsigned char* frame_buffer);
    void DisplayPartBaseImage(const unsigned char* frame_buffer);
    void DisplayPart(const unsigned char* frame_buffer);
    void ClearPart(void);
    
    void Sleep(void);
private:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
};

#endif /* EPD2IN13_V4_H */

/* END OF FILE */