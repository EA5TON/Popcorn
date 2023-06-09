﻿#include "Config.h"

// AColor.
//------------------------------------------------------------------------------------------------------------------------
AColor::AColor()
: R (0), G (0), B (0), Pen (0), Brush (0)
{
}
//------------------------------------------------------------------------------------------------------------------------
AColor::AColor(unsigned char r, unsigned char g, unsigned char b)
: R (r), G (g), B (b), Pen (0), Brush (0)
{
    Pen = CreatePen (PS_SOLID, 0, RGB (r, g, b));
    Brush = CreateSolidBrush (RGB (r, g, b));
}
//------------------------------------------------------------------------------------------------------------------------
AColor::AColor(const AColor &pen_color, const AColor &brush_color, int pen_size)
: R (0), G (0), B (0), Pen (0), Brush (0)
{
    Pen = CreatePen (PS_SOLID, pen_size, pen_color.Get_RGB ());
    Brush = CreateSolidBrush (brush_color.Get_RGB ());
}
//------------------------------------------------------------------------------------------------------------------------
AColor::AColor (const AColor& color, int pen_size)
: R (color.R), G (color.G), B (color.B), Pen (0), Brush (0)
{
    Pen = CreatePen (PS_SOLID, pen_size, Get_RGB ());
}
//------------------------------------------------------------------------------------------------------------------------
int AColor::Get_RGB () const
{
    return RGB (R, G, B);
}
//------------------------------------------------------------------------------------------------------------------------
void AColor::Select (HDC hdc) const
{
    SelectObject (hdc, Pen);
    SelectObject (hdc, Brush);
}
//------------------------------------------------------------------------------------------------------------------------
void AColor::Select_Pen (HDC hdc) const
//------------------------------------------------------------------------------------------------------------------------
{
    SelectObject(hdc, Pen);
}
//------------------------------------------------------------------------------------------------------------------------
HBRUSH AColor::Get_Brush () const
{
    return Brush;
}
//------------------------------------------------------------------------------------------------------------------------




// AsConfig.
//------------------------------------------------------------------------------------------------------------------------
bool AsConfig::Level_Has_Floor = false;
int AsConfig::Current_Timer_Tick = 0;

const AColor AsConfig::BG_Color (1, 15, 63);
const AColor AsConfig::Purpule_Color (255, 1, 255);
const AColor AsConfig::Whiteblue_Color (1, 255, 255);
const AColor AsConfig::White_Color (255, 255, 255);
const AColor AsConfig::Letter_Color (AsConfig::White_Color, AsConfig::Global_Scale);

HWND AsConfig::hwnd;

const double AsConfig::Moving_Step_Size = 1.0 / AsConfig::Global_Scale;
const double AsConfig::PI_2 = 2.0 * M_PI;
//------------------------------------------------------------------------------------------------------------------------
int AsConfig::Rand (int range)
{// Вычисляет псевдослучайное число в диапазоне [0, ... range - 1]
    return rand () * range / RAND_MAX;
}
//------------------------------------------------------------------------------------------------------------------------
void AsConfig::Round_Rect (HDC hdc, RECT &rect, int corner_radius)
{
    int radius = corner_radius * AsConfig::Global_Scale;

    RoundRect (hdc, rect.left, rect.top, rect.right - 1, rect.bottom - 1, radius, radius);
}
//------------------------------------------------------------------------------------------------------------------------
void AsConfig::Throw ()
{
    throw 13;
}
//------------------------------------------------------------------------------------------------------------------------
