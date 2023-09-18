#include <iostream>
#include "raylib.h"
#include "raymath.h"

using namespace std;

//Switch value random starter
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

	cout << "Por cuanto quieres que se divida el vector random? (El resultado de este numero es la distancia del eje z)" << endl;
	cin >> userInput;

	float cLength = 1.0f / userInput * vectorLength;


	const int screenWidth = 1366;
	const int screenHeight = 768;
	InitWindow(screenWidth, screenHeight, "TP2 Algebra");

	values(firstLineA, firstLineB, firstLineC, vectorLength, aAxis, cLength);


	SetTargetFPS(144);

	//----------------------------------------------------------------------------------------------
	//Camera in 3D
	Camera3D camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                       // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;    // Camera mode type

	DisableCursor();

	while (!WindowShouldClose())
	{
		//------------------------------------------------------------------------------------------
		//UPDATE


		UpdateCamera(&camera, CAMERA_FREE); // camera movement

		if (IsKeyDown('Z')) camera.target = { 0.0f, 0.0f, 0.0f };

		//------------------------------------------------------------------------------------------
		//DRAWING
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);



		//Basic lines, A, B and C
		DrawLine3D(Zero, firstLineA, RED);
		DrawLine3D(Zero, firstLineB, GREEN);
		DrawLine3D(Zero, firstLineC, BLUE);

		Vector3 prueba = Vector3Add(firstLineA, firstLineB);

		// Pyramid base lines
		DrawLine3D(firstLineA, Vector3Add(firstLineA, firstLineB), BLACK);
		DrawLine3D(firstLineB, Vector3Add(firstLineA, firstLineB), BLACK);

		DrawLine3D(firstLineC, Vector3Add(firstLineA, firstLineC), BLACK);
		DrawLine3D(firstLineC, Vector3Add(firstLineB, firstLineC), BLACK);
		DrawLine3D(Vector3Add(firstLineC, prueba), Vector3Add(firstLineA, firstLineC), BLACK);
		DrawLine3D(Vector3Add(firstLineC, prueba), Vector3Add(firstLineB, firstLineC), BLACK);

		DrawLine3D(firstLineA, Vector3Add(firstLineA, firstLineC), BLACK);
		DrawLine3D(firstLineB, Vector3Add(firstLineB, firstLineC), BLACK);
		DrawLine3D(Vector3Add(firstLineA, firstLineB), Vector3Add(firstLineC, prueba), BLACK);

		EndMode3D();

		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
}

void values(Vector3& firstLineA, Vector3& firstLineB, Vector3& firstLineC, int vectorLength, int aAxis, float cLength)
{
	// Based on what the value of A is, the program gives B and C a value on x,y,z
	switch (aAxis)
	{
	case (int)axis::AxisX:
		firstLineA.x = vectorLength;
		firstLineA.y = 0;
		firstLineA.z = 0;

		firstLineB.x = 0;
		firstLineB.y = vectorLength;
		firstLineB.z = 0;

		firstLineC.x = 0;
		firstLineC.y = 0;
		firstLineC.z = cLength;
		break;

	case (int)axis::AxisY:
		firstLineA.x = 0;
		firstLineA.y = vectorLength;
		firstLineA.z = 0;

		firstLineB.x = vectorLength;
		firstLineB.y = 0;
		firstLineB.z = 0;

		firstLineC.x = 0;
		firstLineC.y = 0;
		firstLineC.z = cLength;
		break;

	case (int)axis::AxisZ:
		firstLineA.x = 0;
		firstLineA.y = 0;
		firstLineA.z = vectorLength;

		firstLineB.x = 0;
		firstLineB.y = vectorLength;
		firstLineB.z = 0;

		firstLineC.x = cLength;
		firstLineC.y = 0;
		firstLineC.z = 0;
		break;

	default:

		break;
	}
}