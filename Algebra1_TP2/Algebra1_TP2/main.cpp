#include "raylib.h"
#include <iostream>
#include "raymath.h"

using namespace std;

void values(Vector3& A, Vector3& B, Vector3& C, int vectorLenght, int aAxis, float cLength);

int main()
{
	Vector3 A;
	Vector3 B;
	Vector3 C;
	Vector3 ABC = { 0, 0, 0 };

	int userInput = 0;
	int vectorLength = GetRandomValue(10, 100); //Largo de A y B
	int aAxis = GetRandomValue(1, 3); //Si es X, Y o Z
	float cLength = 1.0f / userInput * vectorLength;

	cin >> userInput;

	values(A, B, C, vectorLength, aAxis, cLength);

	const int screenWidth = 1366;
	const int screenHeight = 768;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

	Camera3D camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                       // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawLine3D(ABC, A, BLACK);
		DrawLine3D(ABC, B, BLACK);
		DrawLine3D(ABC, C, BLACK);

		DrawGrid(10, 1.0f);

		EndMode3D();

		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
}

void values(Vector3& A, Vector3& B, Vector3& C, int vectorLength, int aAxis, float cLength)
{
	switch (aAxis)
	{
	case 1:
		A.x = vectorLength;
		A.y = 0;
		A.z = 0;
		break;
	case 2:
		A.x = 0;
		A.y = vectorLength;
		A.z = 0;
		break;
	case 3:
		A.x = 0;
		A.y = 0;
		A.z = vectorLength;
		break;
	}

	if (A.x == vectorLength)
	{
		B.x = 0;
		B.y = vectorLength;
		B.z = 0;

		C.x = 0;
		C.y = 0;
		C.z = cLength;
	}
	else if (A.y == vectorLength)
	{
		B.x = vectorLength;
		B.y = 0;
		B.z = 0;

		C.x = 0;
		C.y = 0;
		C.z = cLength;
	}
	else if (A.z == vectorLength)
	{
		B.x = 0;
		B.y = vectorLength;
		B.z = 0;

		C.x = cLength;
		C.y = 0;
		C.z = 0;
	}
}