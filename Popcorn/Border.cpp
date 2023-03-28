﻿#include "Border.h"

// AsBorder.
//------------------------------------------------------------------------------------------------------------------------
AsBorder::AsBorder ()
{
}
//------------------------------------------------------------------------------------------------------------------------
void AsBorder::Draw (HDC hdc, RECT &paint_area)
{// Отрисовка рамки.

    int i;

    // 1. Линия слева.
    for (i = 0; i < 50; i++)
        Draw_Element (hdc, 2, 1 + i * 4, false);

    // 2. Линия справа.
    for (i = 0; i < 50; i++)
        Draw_Element (hdc, 201, 1 + i * 4, false);

    // 3. Линия сверху.
    for (i = 0; i < 50; i++)
        Draw_Element (hdc, 3 + i * 4, 0, true);
}
//------------------------------------------------------------------------------------------------------------------------
bool AsBorder::Check_Hit (double next_x_pos, double next_y_pos, ABall *ball)
{
    bool got_hit = false;

    // Корректируем позицию при отражении от рамки.
    if (next_x_pos - ball-> Radius < AsConfig::Border_X_Offset)
    {
        got_hit = true;
        ball-> Reflect (false);
    }

    if (next_y_pos - ball-> Radius < AsConfig::Border_Y_Offset)
    {
        got_hit = true;
        ball-> Reflect (true);
    }

    if (next_x_pos + ball-> Radius > AsConfig::Max_X_Pos)
    {
        got_hit = true;
        ball-> Reflect (false);
    }

    if (next_y_pos + ball-> Radius > AsConfig::Max_Y_Pos)
    {
        if (AsConfig::Level_Has_Floor)
        {
            got_hit = true;
            ball-> Reflect (true);
        }
        else
        {
            if (next_y_pos + ball-> Radius > AsConfig::Max_Y_Pos + ball-> Radius * 4.0) // Проверяем max_x_pos мяча для того, чтобы он мог улететь ниже пола. 
                ball-> Set_State (EBS_Lost, next_x_pos);
        }
    }
    return got_hit;
}
//------------------------------------------------------------------------------------------------------------------------
void AsBorder::Draw_Element (HDC hdc, int x, int y, bool top_border)
{// Отрисвока элемента рамки.

    // Основная линия.
    AsConfig::Whiteblue_Color.Select (hdc);

    if (top_border)
        Rectangle (hdc, x * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale - 1, (y + 4) * AsConfig::Global_Scale - 1);
    else
        Rectangle (hdc, (x + 1) * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale - 1, (y + 4) * AsConfig::Global_Scale - 1);

    // Белая кайма.
    AsConfig::White_Color.Select (hdc);


    if (top_border)
        Rectangle (hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 4) * AsConfig::Global_Scale - 1, (y + 1) * AsConfig::Global_Scale);
    else
        Rectangle (hdc, x * AsConfig::Global_Scale, y * AsConfig::Global_Scale, (x + 1) * AsConfig::Global_Scale - 1, (y + 4) * AsConfig::Global_Scale);

    // Перфорация.
    AsConfig::BG_Color.Select (hdc);

    if (top_border)
        Rectangle (hdc, (x + 2) * AsConfig::Global_Scale, (y + 2) * AsConfig::Global_Scale, (x + 3) * AsConfig::Global_Scale - 1, (y + 3) * AsConfig::Global_Scale - 1);
    else
        Rectangle (hdc, (x + 2) * AsConfig::Global_Scale, (y + 1) * AsConfig::Global_Scale, (x + 3) * AsConfig::Global_Scale - 1, (y + 2) * AsConfig::Global_Scale - 1);
}
//------------------------------------------------------------------------------------------------------------------------