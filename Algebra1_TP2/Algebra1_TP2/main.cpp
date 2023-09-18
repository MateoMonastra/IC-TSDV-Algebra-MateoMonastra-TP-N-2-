#include <iostream>
#include "raylib.h"
#include "raymath.h"
using namespace std;

enum class axis
{
	AxisX = 1,
	AxisY,
	AxisZ
};

void values(Vector3& A, Vector3& B, Vector3& C, int vectorLenght, int aAxis, float cLength);

int main()
{
	Vector3 firstLineA;
	Vector3 firstLineB;
	Vector3 firstLineC;
	Vector3 Zero = { 0, 0, 0 };

	int userInput = 0;
	int vectorLength = GetRandomValue(10, 10); //Largo de A y B
	int aAxis = 1/*GetRandomValue(1, 3)*/; //Si es X, Y o Z

	cin >> userInput;

	float cLength = 1.0f / userInput * vectorLength;

	values(firstLineA, firstLineB, firstLineC, vectorLength, aAxis, cLength);

	const int screenWidth = 1366;
	const int screenHeight = 768;

	SetTargetFPS(144);

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

	Camera3D camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                       // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

	DisableCursor();

	cout << vectorLength;

	while (!WindowShouldClose())
	{
		UpdateCamera(&camera, CAMERA_FREE);

		if (IsKeyDown('Z')) camera.target = { 0.0f, 0.0f, 0.0f };

		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawLine3D(Zero, firstLineA, RED);
		DrawLine3D(Zero, firstLineB, GREEN);
		DrawLine3D(Zero, firstLineC, BLUE);

		for (int i = 0; i < 5; i++)
		{
			DrawLine3D(Zero, firstLineA, BROWN);
			DrawLine3D(Zero, firstLineB, BROWN);
			DrawLine3D(firstLineA, Vector3Add(firstLineA, firstLineB), BROWN);
			DrawLine3D(firstLineB, Vector3Add(firstLineA, firstLineB), BROWN);


		}

		/*DrawLine3D(Vector3AddValue(ABC, cLength), firstLineA, BROWN);
		DrawLine3D(Vector3AddValue(ABC, cLength), firstLineB, BROWN);
		DrawLine3D(Vector3AddValue(firstLineA, cLength), Vector3Add(firstLineA, firstLineB), BROWN);
		DrawLine3D(Vector3AddValue(firstLineB, cLength), Vector3Add(firstLineA, firstLineB), BROWN);*/

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
	case (int)axis::AxisX:

		A.x = vectorLength;
		A.y = 0;
		A.z = 0;

		B.x = 0;
		B.y = vectorLength;
		B.z = 0;

		C.x = 0;
		C.y = 0;
		C.z = cLength;


		break;

	case (int)axis::AxisY:

		A.x = 0;
		A.y = vectorLength;
		A.z = 0;

		B.x = vectorLength;
		B.y = 0;
		B.z = 0;

		C.x = 0;
		C.y = 0;
		C.z = cLength;

		break;

	case (int)axis::AxisZ:

		A.x = 0;
		A.y = 0;
		A.z = vectorLength;

		B.x = 0;
		B.y = vectorLength;
		B.z = 0;

		C.x = cLength;
		C.y = 0;
		C.z = 0;

		break;
	default:
		break;
	}



}