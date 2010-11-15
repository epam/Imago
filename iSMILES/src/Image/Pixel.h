#pragma once
namespace gga
{
    static const unsigned char BACKGROUND = 255;
    static const unsigned char INK        = 0;

#pragma pack(push, 1)
    struct Pixel
    {
        unsigned char Value;

        inline Pixel(unsigned char color = BACKGROUND) : Value(color) {}
		
        inline bool isBackground()const { return BACKGROUND == Value;}
        inline bool isInk()const        { return INK == Value;}
    };
#pragma pack(pop)

}
