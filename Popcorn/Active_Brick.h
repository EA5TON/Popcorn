#pragma once
#include "Config.h"

//------------------------------------------------------------------------------------------------------------------------
enum EBrick_Type
{
    EBT_None,

    EBT_Purpule,
    EBT_Whiteblue,
    EBT_Unbreakable,
    EBT_Multihit_1,
    EBT_Multihit_2,
    EBT_Multihit_3,
    EBT_Multihit_4,
    EBT_Parachute,
    EBT_Teleport,
    EBT_Ad
};
//------------------------------------------------------------------------------------------------------------------------
class AGraphics_Object
{
public:
    virtual ~AGraphics_Object ();

    virtual void Act () = 0;
    virtual void Draw (HDC hdc, RECT &paint_area) = 0;
    virtual bool Is_Finished () = 0;
};
//------------------------------------------------------------------------------------------------------------------------
class AActive_Brick: public AGraphics_Object
{
protected:
    virtual ~AActive_Brick();
    AActive_Brick (EBrick_Type brick_type, int level_x, int level_y);

    EBrick_Type Brick_Type;
    RECT Brick_Rect;
};
//------------------------------------------------------------------------------------------------------------------------
class AActive_Brick_Purpule_Whiteblue: public AActive_Brick
{
public:
    ~AActive_Brick_Purpule_Whiteblue ();
    AActive_Brick_Purpule_Whiteblue (EBrick_Type brick_type, int level_x, int level_y);
    
    virtual void Act ();
    virtual void Draw (HDC hdc, RECT &paint_area);
    virtual bool Is_Finished ();

    static void Setup_Colors ();
    static void Draw_In_Level (HDC hdc, RECT &brick_rect, EBrick_Type brick_type);
    
private:
    int Fade_Step;

    static unsigned char Get_Fading_Channel (unsigned char color, unsigned char bg_color, int step);
    static void Get_Fading_Color (const AColor &origin_color, int step, AColor &result_color);

    static const int Max_Fade_Step = AsConfig::FPS;

    static AColor Fading_Purpule_Brick_Colors [Max_Fade_Step];
    static AColor Fading_Whiteblue_Brick_Colors [Max_Fade_Step];
};
//------------------------------------------------------------------------------------------------------------------------
class AActive_Brick_Unbreakable: public AActive_Brick
{
public:
    ~AActive_Brick_Unbreakable ();
    AActive_Brick_Unbreakable (int level_x, int level_y);

    virtual void Act ();
    virtual void Draw (HDC hdc, RECT &paint_area);
    virtual bool Is_Finished ();

    static void Draw_In_Level (HDC hdc, RECT &brick_rect);

private:
    int Animation_Step;
    HRGN Region;

    static const int Max_Animation_Step = 12;
    static AColor Purpule_Highlight, Whiteblue_Highlight;
};
//------------------------------------------------------------------------------------------------------------------------
class AActive_Brick_Multihit: public AActive_Brick
{
public:
    ~AActive_Brick_Multihit ();
    AActive_Brick_Multihit (int level_x, int level_y);

    virtual void Act ();
    virtual void Draw (HDC hdc, RECT &paint_area);
    virtual bool Is_Finished ();

    static void Draw_In_Level (HDC hdc, RECT &brick_rect, EBrick_Type brick_type);

private:
    static void Draw_Stage (HDC hdc, RECT &brick_rect, int x, int width);
    
    int Rotation_Step;

    static const int Steps_Per_Turn = 16;
    static const int Max_Rotation_Step = Steps_Per_Turn * 4;
};
//------------------------------------------------------------------------------------------------------------------------