#include "raylib.h"
#include "raymath.h"
int main()
{

    InitWindow(800, 450, "Algebra1_TP2");

    float tamanioW = GetRandomValue(400, 700);
    float tamanioH = GetRandomValue(100, 400);

    Vector2 start = { GetScreenWidth() / 6, GetScreenHeight() - 100 };
    Vector2 linea = { 400, 350 };
    Vector2 linea2 = { GetScreenHeight() - 400, (GetScreenWidth()/6 - 400 ) *-1};

    /*Vector2 linea2 = Vector2Invert(linea);*/

    while (!WindowShouldClose())    
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawLineV(start, linea, RED);
        DrawLineV(start, linea2, BLUE);

        EndDrawing();
    }
    return 0;
}
