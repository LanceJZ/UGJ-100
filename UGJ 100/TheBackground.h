#pragma once
#include "Globals.h"
#include "Model3D.h"
#include <cstdlib>

enum TileType
{
	Wall,
	Floor
};

class TheBackground : public Common
{
public:
	TheBackground();
	virtual ~TheBackground();

	int MAP_WIDTH = 0;
	int MAP_HEIGHT = 0;

	std::vector<Entity*> Walls = {};

	void SetFloorModel(Model model);
	void SetWallModel(Model model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void FixedUpdate();

private:
	Model WallModel = {};
	Model FloorModel = {};

	std::vector<std::vector<TileType>> Map = {};
	std::vector<Model3D*> FloorSquares = {};

	std::vector<std::vector<TileType>> GenerateMap();
	void BuildMap();
	void MakeWall(int index);
	void MakeFloor(int index);
};

