#include "Active_Brick.h"

// AGraphics_Object.
//------------------------------------------------------------------------------------------------------------------------
AGraphics_Object::~AGraphics_Object ()
{
}
//------------------------------------------------------------------------------------------------------------------------




// AActive_Brick.
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick::~AActive_Brick ()
{
}
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick::AActive_Brick (EBrick_Type brick_type, int level_x, int level_y)
: Brick_Type (brick_type), Brick_Rect {}
{
    Brick_Rect.left = (AsConfig::Level_X_Offset + level_x * AsConfig::Cell_Width) * AsConfig::Global_Scale;
    Brick_Rect.top = (AsConfig::Level_Y_Offset + level_y * AsConfig::Cell_Height) * AsConfig::Global_Scale;
    Brick_Rect.right = Brick_Rect.left + AsConfig::Brick_Width * AsConfig::Global_Scale;
    Brick_Rect.bottom = Brick_Rect.top + AsConfig::Brick_Height * AsConfig::Global_Scale;
}
//------------------------------------------------------------------------------------------------------------------------




// AActive_Brick_Purpule_Whiteblue
AColor AActive_Brick_Purpule_Whiteblue::Fading_Purpule_Brick_Colors [Max_Fade_Step];
AColor AActive_Brick_Purpule_Whiteblue::Fading_Whiteblue_Brick_Colors [Max_Fade_Step];
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick_Purpule_Whiteblue::~AActive_Brick_Purpule_Whiteblue ()
{
}
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick_Purpule_Whiteblue::AActive_Brick_Purpule_Whiteblue (EBrick_Type brick_type, int level_x, int level_y)
: AActive_Brick (brick_type, level_x, level_y), Fade_Step (0)
{
    if (! (brick_type == EBT_Purpule || brick_type == EBT_Whiteblue))
        AsConfig::Throw ();
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Purpule_Whiteblue::Act ()
{
    if (Fade_Step < Max_Fade_Step - 1)
    {
        ++Fade_Step;
        InvalidateRect (AsConfig::hwnd, &Brick_Rect, FALSE);
    }
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Purpule_Whiteblue::Draw (HDC hdc, RECT &paint_area)
{
    AColor *color = 0;

    switch (Brick_Type)
    {
    case EBT_Purpule:
        color = &Fading_Purpule_Brick_Colors [Fade_Step];
        break;

    case EBT_Whiteblue:
        color = &Fading_Whiteblue_Brick_Colors [Fade_Step];
        break;
    }

    if (color != 0)
        color-> Select (hdc);
    AsConfig::Round_Rect (hdc, Brick_Rect);
}
//------------------------------------------------------------------------------------------------------------------------
bool AActive_Brick_Purpule_Whiteblue::Is_Finished ()
{
    if (Fade_Step >= Max_Fade_Step - 1)
        return true;
    else
        return false;
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Purpule_Whiteblue::Setup_Colors ()
{
    int i;

    for (i = 0; i < Max_Fade_Step; i++)
    {
        Get_Fading_Color (AsConfig::Purpule_Color, i, Fading_Purpule_Brick_Colors [i]);
        Get_Fading_Color (AsConfig::Whiteblue_Color, i, Fading_Whiteblue_Brick_Colors [i]);
    }
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Purpule_Whiteblue::Draw_In_Level (HDC hdc, RECT &brick_rect, EBrick_Type brick_type)
{// ����� ����������� ������� �� ������.
    const AColor *color = 0;

    switch (brick_type)
    {
    case EBT_None:
        color = &AsConfig::BG_Color;
        break;

    case EBT_Purpule:
        color = &AsConfig::Purpule_Color;
        break;

    case EBT_Whiteblue:
        color = &AsConfig::Whiteblue_Color;
        break;

    default:
        AsConfig::Throw ();
    }

    if (color != 0)
        color-> Select (hdc);
    AsConfig::Round_Rect (hdc, brick_rect);
}
//------------------------------------------------------------------------------------------------------------------------
unsigned char AActive_Brick_Purpule_Whiteblue::Get_Fading_Channel (unsigned char color, unsigned char bg_color, int step)
{
    return color - step * (color - bg_color) / (Max_Fade_Step - 1);
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Purpule_Whiteblue::Get_Fading_Color (const AColor &origin_color, int step, AColor &result_color)
{
    unsigned char r, g, b;

    r = Get_Fading_Channel (origin_color.R, AsConfig::BG_Color.R, step);
    g = Get_Fading_Channel (origin_color.G, AsConfig::BG_Color.G, step);
    b = Get_Fading_Channel (origin_color.B, AsConfig::BG_Color.B, step);

    result_color = AColor (r, g, b);
}
//------------------------------------------------------------------------------------------------------------------------




// AActive_Brick_Unbreakable
AColor AActive_Brick_Unbreakable::Purpule_Highlight (AsConfig::Purpule_Color, 3 * AsConfig::Global_Scale);
AColor AActive_Brick_Unbreakable::Whiteblue_Highlight (AsConfig::Whiteblue_Color, AsConfig::Global_Scale);
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick_Unbreakable::~AActive_Brick_Unbreakable ()
{
    DeleteObject (Region);
}
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick_Unbreakable::AActive_Brick_Unbreakable (int level_x, int level_y)
: AActive_Brick (EBT_Unbreakable, level_x, level_y), Animation_Step (0), Region (0)
{
    Region = CreateRoundRectRgn (Brick_Rect.left, Brick_Rect.top, Brick_Rect.right + 1, Brick_Rect.bottom + 1, 2 * AsConfig::Global_Scale - 1, 2 * AsConfig::Global_Scale - 1);
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Unbreakable::Act ()
{
    if (Animation_Step <= Max_Animation_Step)
    {
        ++Animation_Step;
        InvalidateRect (AsConfig::hwnd, &Brick_Rect, FALSE);
    }
}   
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Unbreakable::Draw (HDC hdc, RECT &paint_area)
{
    int offset;
    const int scale = AsConfig::Global_Scale;

    Draw_In_Level (hdc, Brick_Rect);

    SelectClipRgn (hdc, Region);

    offset = 2 * Animation_Step * scale - AsConfig::Brick_Width * scale;

    Whiteblue_Highlight.Select_Pen (hdc);
    MoveToEx (hdc, Brick_Rect.left + 4 * scale + offset, Brick_Rect.bottom + scale, 0);
    LineTo (hdc, Brick_Rect.left + 13 * scale - 1+ offset, Brick_Rect.top - 1 * scale);

    Purpule_Highlight.Select_Pen (hdc);
    MoveToEx (hdc, Brick_Rect.left + 6 * scale + offset, Brick_Rect.bottom + scale, 0);
    LineTo (hdc, Brick_Rect.left + 15 * scale - 1+ offset, Brick_Rect.top - 1 * scale);

    SelectClipRgn (hdc, 0);
}
//------------------------------------------------------------------------------------------------------------------------
bool AActive_Brick_Unbreakable::Is_Finished ()
{
    if (Animation_Step >= Max_Animation_Step)
        return true;
    else
        return false;
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Unbreakable::Draw_In_Level (HDC hdc, RECT &brick_rect)
{// ����� ����������� ������� �� ������.
    AsConfig::White_Color.Select (hdc);
    AsConfig::Round_Rect (hdc, brick_rect);
}
//------------------------------------------------------------------------------------------------------------------------




// AActive_Brick_Multihit
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick_Multihit::~AActive_Brick_Multihit ()
{
}
//------------------------------------------------------------------------------------------------------------------------
AActive_Brick_Multihit::AActive_Brick_Multihit (int level_x, int level_y)
: AActive_Brick (EBT_Multihit_1, level_x, level_y), Rotation_Step (0)
{
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Multihit::Act ()
{
    if (Rotation_Step <= Max_Rotation_Step)
    {
        ++Rotation_Step;
        InvalidateRect (AsConfig::hwnd, &Brick_Rect, FALSE);
    }
}   
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Multihit::Draw (HDC hdc, RECT &paint_area)
{
    int step;
    double rotation_angle, x_ratio;
    XFORM xform, old_xform;

    // 1. ������� ���.
    AsConfig::BG_Color.Select (hdc);
    AsConfig::Round_Rect (hdc, Brick_Rect);

    // 2. ��������� ������� �������� ������.
    step = Rotation_Step % Steps_Per_Turn;
    rotation_angle = M_PI_2 / 2.0 * (double) step;
    x_ratio = cos (rotation_angle);

    xform.eM11 = (float) x_ratio;
    xform.eM12 = 0.0f;
    xform.eM21 = 0.0f;
    xform.eM22 = 1.0f;
    xform.eDx = (float) Brick_Rect.left + (float) (1.0 - x_ratio) * (AsConfig::Brick_Width * AsConfig::Global_Scale) / 2.0f;
    xform.eDy = (float) Brick_Rect.top;
    GetWorldTransform (hdc, &old_xform);
    SetWorldTransform (hdc, &xform);

    const int scale = AsConfig::Global_Scale;
    RECT zero_rect;

    // 3. ��������� ������.
    AsConfig::Letter_Color.Select_Pen (hdc);
    MoveToEx (hdc, 0 + 1 * scale + 1, 0 + 3 * scale, 0);
    LineTo (hdc, 0 + 3 * scale + 1, 0 + 1 * scale);
    LineTo (hdc, 0 + 3 * scale + 1, 0 + 6 * scale - 1);

    zero_rect.left = 0 + 5 * scale + 1;
    zero_rect.top = 0 + 1 * scale;
    zero_rect.right = zero_rect.left + 3 * scale + 1;
    zero_rect.bottom = zero_rect.top + 5 * scale;
    AsConfig::Round_Rect (hdc, zero_rect);

    zero_rect.left += 5 * scale;
    zero_rect.right += 5 * scale;
    AsConfig::Round_Rect (hdc, zero_rect);

    SetWorldTransform (hdc, &old_xform);

}
//------------------------------------------------------------------------------------------------------------------------
bool AActive_Brick_Multihit::Is_Finished ()
{
    if (Rotation_Step >= Max_Rotation_Step)
        return true;
    else
        return false;
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Multihit::Draw_In_Level (HDC hdc, RECT &brick_rect, EBrick_Type brick_type)
{// ����� ����������� ������� �� ������.

    const int scale = AsConfig::Global_Scale;

    // 1. ������ ���.
    AsConfig::White_Color.Select (hdc);
    AsConfig::Round_Rect (hdc, brick_rect);

    AsConfig::Purpule_Color.Select (hdc);
    Rectangle (hdc, brick_rect.left + scale, brick_rect.top + scale, brick_rect.right - scale - 1, brick_rect.bottom -  scale - 1);

    // 2. ������ ���������� ��������������.
    switch (brick_type)
    {
    case EBT_Multihit_1:
        Draw_Stage (hdc, brick_rect, 2, 10);
        break;

    case EBT_Multihit_2:
        Draw_Stage (hdc, brick_rect, 2, 4);
        Draw_Stage (hdc, brick_rect, 8, 4);
        break;

    case EBT_Multihit_3:
        Draw_Stage (hdc, brick_rect, 2, 2);
        Draw_Stage (hdc, brick_rect, 6, 2);
        Draw_Stage (hdc, brick_rect, 10, 2);
        break;

    case EBT_Multihit_4:
        Draw_Stage (hdc, brick_rect, 2, 2);
        Draw_Stage (hdc, brick_rect, 5, 2);
        Draw_Stage (hdc, brick_rect, 8, 2);
        Draw_Stage (hdc, brick_rect, 11, 2);
        break;

    default:
        AsConfig::Throw ();
    }
}
//------------------------------------------------------------------------------------------------------------------------
void AActive_Brick_Multihit::Draw_Stage (HDC hdc, RECT &brick_rect, int x, int width)
{// ��������� ����������� ��������������.

    const int scale = AsConfig::Global_Scale;
    RECT stage_rect;

    stage_rect.left = brick_rect.left + x * scale;
    stage_rect.top = brick_rect.top + 2 * scale;
    stage_rect.right = stage_rect.left + width * scale;
    stage_rect.bottom = stage_rect.top + 3 * scale;

    AsConfig::BG_Color.Select (hdc);
    Rectangle (hdc, stage_rect.left + scale, stage_rect.top + scale, stage_rect.right + scale - 1, stage_rect.bottom + scale - 1);

    AsConfig::Whiteblue_Color.Select (hdc);
    Rectangle (hdc, stage_rect.left, stage_rect.top, stage_rect.right - 1, stage_rect.bottom - 1);
}
 //------------------------------------------------------------------------------------------------------------------------