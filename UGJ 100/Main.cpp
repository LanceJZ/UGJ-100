#pragma warning ( push )
#pragma warning ( disable : 26495 )

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "raylib.h"
#include "Game.h"
#include "glfw/glfw3.h"

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define DBG_NEW new
#endif

TheManagers Managers = {};
Camera TheCamera = {};
Vector2 FieldSize = {};

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
	static Game game;

	int windowHeight = 960; //height
	int windowWidth = 1280; //width

	InitWindow(windowWidth, windowHeight, "UGJ 100 Pre Alpha");
	InitAudioDevice();

	Image icon = LoadImage("icon.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);

	if (IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
	glfwSwapInterval(0);
	SetTargetFPS(0);

	static Utilities TheUtilities = {};

	Managers.EM.SetUtilities(&TheUtilities);

	// Define the camera to look into our 3D world.
	// Camera position
	TheCamera.position = { 0.0f, 0.0f, -500.0f };
	// Camera looking at point
	TheCamera.target = { 0.0f, 0.0f, 0.0f };
	// Camera up vector (rotation towards target)
	TheCamera.up = { 0.0f, -1.0f, 0.0f };
	//Camera/World space is 1:1 screen space.
	TheCamera.fovy = (float)GetScreenHeight();
	// Camera mode type
	TheCamera.projection = CAMERA_ORTHOGRAPHIC;
	// The Managers needs a reference to The Camera
	Managers.SetCamera(TheCamera);

	game.Initialize(&TheUtilities);
	Managers.Initialize();
	game.Load();
	game.BeginRun();
	Managers.BeginRun();

#ifdef _DEBUG
	unsigned int frames = 0;
	unsigned int updateFrames = 0;
	float frameRate = 0;
	float framerate = 30.0f;
	float updateFrameRate = 0;
	long millisecondsCount = 0;
	int fps = 0;
#endif

	bool fixedUpdate = true;
	bool update = true;
	bool render = true;
	float fixedDeltaTime = 1.0f / 30.0f;
	double fixedAccumulator = 0.0f;
	float updateDeltaTime = 1.0f / 200.0f;
	double updateAccumulator = 0.0f;
	float renderDeltaTime = 1.0f / 60.0f; //Change to get the vsync rate.
	double renderAccumulator = 0.0f;
	double deltaTime = 0.0f;

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		fixedAccumulator += deltaTime;
		updateAccumulator += deltaTime;
		renderAccumulator += deltaTime;

		if (fixedAccumulator >= fixedDeltaTime)
		{
			fixedAccumulator = 0.0f;
			fixedUpdate = true;
		}

		if (updateAccumulator >= updateDeltaTime)
		{
			updateAccumulator = 0.0f;
			update = true;
		}

		if (renderAccumulator >= renderDeltaTime)
		{
			renderAccumulator = 0.0f;
			render = true;
		}

		if (game.Logic->State != GameState::Pause)
		{
#ifdef _DEBUG
			//updateFrameRate += (float)deltaTime;
			//int updateFPS = (int)(updateFrames / updateFrameRate);
#endif // _DEBUG

			if (true)
			{
				Managers.EM.Update((float)deltaTime);
				game.Update((float)deltaTime);

#ifdef _DEBUG
				//Color color = LIME;                            // Good FPS
				//updateFrames++;
				//DrawText(TextFormat("%2i Update FPS:", updateFPS), 5, 22, 20, color);
#endif //_DEBUG
			}

			if (fixedUpdate)
			{
				fixedUpdate = false;
				Managers.EM.FixedUpdate((float)deltaTime);
				game.FixedUpdate((float)deltaTime);
			}
		}

		if (true)
		{
			update = false;
			Managers.EM.Input();
			game.ProcessInput();
			//PollInputEvents();
		}

		if (true)
		{
			render = false;
			BeginDrawing();
			ClearBackground({ 8, 2, 16, 100 });
			BeginMode3D(TheCamera);
			Managers.EM.Draw3D();
			game.Draw3D();
			EndMode3D();
			Managers.EM.Draw2D();
			game.Draw2D();

#ifdef _DEBUG
			Color color = LIME;                               // Good FPS

			//frameRate += (float)(deltaTime);
			//int fps = (int)(frames / frameRate);
			//frames++;

			//auto frame = std::chrono::steady_clock::now();
			//std::chrono::duration<double> frameTime = frame - start;
			//auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(frameTime);

			//millisecondsCount += (long)milliseconds.count();

			//if (millisecondsCount >= 1000.0)
			//{
			//	millisecondsCount = 0;
			//	framerate = (float)(frames * 0.5f) + framerate * 0.5f;
			//	frames = 0;
			//	fps = 1000 / int(framerate == 0 ? 0.001 : framerate);
			//	if ((fps < 30) && (fps >= 15)) color = ORANGE; // Warning FPS
			//	else if (fps < 15) color = RED;                // Low FPS
			//}

			//DrawText(TextFormat("%2i FPS", fps), 5, 5, 20, color);
#endif

			EndDrawing();
			//SwapScreenBuffer();
		}
	}

	UnloadImage(icon);

	CloseWindow();
	CloseAudioDevice();
}