#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <time.h>

using namespace std;

float height = 0; // Esto funciona para Conseguir los calculos de la figura
float width = 0; // 

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
	Vector3 zero = { 0, 0, 0 };

	int userInput = 0;
	srand(time(NULL));
	int vectorLength = rand() % 50 + 10; //Largo de A y B
	srand(time(NULL));
	int aAxis = rand() % 3 + 1; //Si es X, Y o Z

	cout << "Por cuanto quieres que se divida el vector random? (El resultado de este numero es la altura de los escalones)" << endl;
	cin >> userInput;

	float segmentSize = 1.0f / userInput; // es el tama�o que va a tener cada piso de la piramide

	float cLength = segmentSize * vectorLength; // esta variable es la altura

	const int screenWidth = 1366;
	const int screenHeight = 768;
	InitWindow(screenWidth, screenHeight, "TP2 Algebra");

	values(firstLineA, firstLineB, firstLineC, vectorLength, aAxis, cLength); // Es una funcion que le da valores a los Vectores3 (a los principales)

	float totalArea = 0;
	totalArea += (width * width) * 2; // esto saca el area de la parte superior e inferior de la piramide, esta solo se hace una vez, por eso esta afuera de el loop
	float totalPerimeter = 0;
	float totalVolume = 0;

	bool calculationStop = false; // booleano que hace que los calculos se generen una sola vez (HardCodeado)

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

		ClearBackground(DARKGRAY);

		BeginMode3D(camera);

		//Basic lines, A, B and C
		DrawLine3D(zero, firstLineA, RED);
		DrawLine3D(zero, firstLineB, GREEN);
		DrawLine3D(zero, firstLineC, BLUE);

		Vector3 displacementX = { firstLineA.x * segmentSize, firstLineA.y * segmentSize, firstLineA.z * segmentSize };// Reduce el largo de la base para el siguiente piso de la piramide A,B
		Vector3 displacementY = { firstLineB.x * segmentSize, firstLineB.y * segmentSize, firstLineB.z * segmentSize };//

		Vector3 upRight = Vector3Add(displacementX, displacementY);//Colocan el punto de partida donde lo necesites, en este caso estaria arriba a la derecha
		Vector3 upLeft = Vector3Add(Vector3Scale(displacementX, -1.0f), displacementY);// en este arriba a la izquierda
		Vector3 downRight = Vector3Subtract(displacementX, displacementY);// aca abajo a la derecha
		Vector3 downLeft = Vector3Subtract(Vector3Scale(displacementX, -1.0f), displacementY);// aca abajo a la izquierda

		Vector3 zeroToLine = zero; // Punto de Comienzo para el dibujado
		
		Vector3 auxA = firstLineA; // Auxiliares para cambiar valores de lineas sin cambiar las originales
		Vector3 auxB = firstLineB; // 
		
		Vector3 floatPoint = Vector3Add(firstLineA, firstLineB); // Altura del siguiente piso

		for (int i = 0; i < (1 / segmentSize) / 2; i++)// es un for que se repite hasta que el segment size sea menor a la altura
		{
			DrawLine3D(Vector3Add(zeroToLine, (Vector3Scale(upRight, i))), Vector3Add(Vector3Add(zeroToLine, (Vector3Scale(upRight, i))), firstLineC), BLACK);// Dibujado de Pilar
			DrawLine3D(Vector3Add(auxA, (Vector3Scale(upLeft, i))), Vector3Add(Vector3Add(auxA, (Vector3Scale(upLeft, i))), firstLineC), BLACK);// Dibujado de Pilar
			DrawLine3D(Vector3Add(auxB, (Vector3Scale(downRight, i))), Vector3Add(Vector3Add(auxB, (Vector3Scale(downRight, i))), firstLineC), BLACK);// Dibujado de Pilar
			DrawLine3D(Vector3Add(floatPoint, (Vector3Scale(downLeft, i))), Vector3Add(Vector3Add(floatPoint, (Vector3Scale(downLeft, i))), firstLineC), BLACK);// Dibujado de Pilar

			DrawLine3D(Vector3Add(zeroToLine, Vector3Scale(upRight, i)), Vector3Add(auxA, Vector3Scale(upLeft, i)), GREEN);// Dibujado de Piso de abajo
			DrawLine3D(Vector3Add(zeroToLine, Vector3Scale(upRight, i)), Vector3Add(auxB, Vector3Scale(downRight, i)), GREEN);// Dibujado de Piso de abajo
			DrawLine3D(Vector3Add(floatPoint, Vector3Scale(downLeft, i)), Vector3Add(auxA, Vector3Scale(upLeft, i)), GREEN);// Dibujado de Piso de abajo
			DrawLine3D(Vector3Add(floatPoint, Vector3Scale(downLeft, i)), Vector3Add(auxB, Vector3Scale(downRight, i)), GREEN);// Dibujado de Piso de abajo

			if (!calculationStop)
			{
				totalPerimeter += (width * 8) + height * 4;
				totalArea += (height * width) * 4;
				totalVolume += (width * width) * height;
				width -= height * 2;	
			}

			zeroToLine = Vector3Add(zeroToLine, firstLineC);//Aumenta un piso mas alto a los auxiliares de la piramide
			auxA = Vector3Add(auxA, firstLineC);//
			auxB = Vector3Add(auxB, firstLineC);//
			floatPoint = Vector3Add(floatPoint, firstLineC);//

			DrawLine3D(Vector3Add(zeroToLine, Vector3Scale(upRight, i)), Vector3Add(auxA, Vector3Scale(upLeft, i)), GREEN);// Dibujado de Piso de arriba
			DrawLine3D(Vector3Add(zeroToLine, Vector3Scale(upRight, i)), Vector3Add(auxB, Vector3Scale(downRight, i)), GREEN);// Dibujado de Piso de arriba
			DrawLine3D(Vector3Add(floatPoint, Vector3Scale(downLeft, i)), Vector3Add(auxA, Vector3Scale(upLeft, i)), GREEN);// Dibujado de Piso de arriba
			DrawLine3D(Vector3Add(floatPoint, Vector3Scale(downLeft, i)), Vector3Add(auxB, Vector3Scale(downRight, i)), GREEN);// Dibujado de Piso de arriba
		}

		calculationStop = true;

		EndMode3D();
		DrawText(TextFormat("ALTO: %.4f", cLength), 10, 40, 20, WHITE);
		DrawText(TextFormat("LARGO: %.01i", vectorLength), 10, 70, 20, WHITE);
		DrawText(TextFormat("AREA: %.1f", totalArea), 10, 100, 20, WHITE);
		DrawText(TextFormat("PERIMETRO: %.1f", totalPerimeter), 10, 130, 20, WHITE);
		DrawText(TextFormat("VOLUMEN: %.1f", totalVolume), 10, 160, 20, WHITE);
		

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

		width = firstLineA.x;
		height = firstLineC.z;
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

		width = firstLineA.y;
		height = firstLineC.z;
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

		width = firstLineA.z;
		height = firstLineC.x;
		break;
	default:

		break;
	}
}