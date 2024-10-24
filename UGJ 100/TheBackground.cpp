#include "TheBackground.h"

TheBackground::TheBackground()
{
	int columns = 40;
	int rows = 40;

	for (int i = 0; i < columns * rows; i++)
	{
		FloorSquares.push_back(DBG_NEW Model3D());
		Managers.EM.AddModel3D(FloorSquares.back());
	}

	MAP_WIDTH = columns;
	MAP_HEIGHT = rows;
}

TheBackground::~TheBackground()
{
}

void TheBackground::SetFloorModel(Model model)
{
	FloorModel = model;
}

void TheBackground::SetWallModel(Model model)
{
	WallModel = model;
}

bool TheBackground::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	return false;
}

bool TheBackground::BeginRun()
{
	BuildMap();

	return false;
}

void TheBackground::FixedUpdate()
{
	Common::FixedUpdate();

}

std::vector<std::vector<TileType>> TheBackground::GenerateMap()
{
	std::vector<std::vector<TileType>> map(MAP_HEIGHT,
		std::vector<TileType>(MAP_WIDTH, Wall));

	// Step 1: Fill the map randomly with walls and floors
	for (int y = 1; y < MAP_HEIGHT - 1; ++y)
	{
		for (int x = 1; x < MAP_WIDTH - 1; ++x)
		{
			if (GetRandomValue(0, 100) < 70)
			{
				map[y][x] = Floor;
			}
		}
	}

	// Step 2: Apply Cellular Automatic rules to smooth the map
	for (int i = 0; i < 5; ++i)
	{
		std::vector<std::vector<TileType>> newMap = map;

		for (int y = 1; y < MAP_HEIGHT - 1; ++y)
		{
			for (int x = 1; x < MAP_WIDTH - 1; ++x)
			{
				int wallCount = 0;

				for (int dy = -1; dy <= 1; ++dy)
				{
					for (int dx = -1; dx <= 1; ++dx)
					{
						if (map[y + dy][x + dx] == Wall)
						{
							wallCount++;
						}
					}
				}

				if (wallCount >= 5 || (wallCount == 4 && map[y][x] == Wall))
				{
					newMap[y][x] = Wall;
				}
				else
				{
					newMap[y][x] = Floor;
				}

				if (y > MAP_HEIGHT - 10) newMap[x][y] = Floor;
			}
		}

		map = newMap;
	}

	map.at((MAP_WIDTH / 2) - 1).at((MAP_HEIGHT / 2) - 5) = Floor;
	map.at((MAP_WIDTH / 2)).at((MAP_HEIGHT / 2) - 5) = Floor;
	map.at((MAP_WIDTH / 2) - 1).at((MAP_HEIGHT / 2) - 6) = Floor;
	map.at((MAP_WIDTH / 2)).at((MAP_HEIGHT / 2) - 6) = Floor;



	return map;
}

void TheBackground::BuildMap()
{
	int t = 0;
	float tileSize = 64.0f;
	float width = FieldSize.x / 2.0f;
	float height = FieldSize.y / 2.0f;

	Map = GenerateMap();

	for (const auto& row : Map)
	{
		int r = 0;

		for (const auto& tile : row)
		{
			int index = (t * MAP_HEIGHT) + r;

			FloorSquares[index]->Position =
			{ -width + (t * tileSize) + (tileSize / 2.0f),
				-height + (r * tileSize) + (tileSize / 2.0f), 10.0f };

			//tile == Wall ? MakeWall(index) : MakeFloor(index);

			if (tile == Wall) MakeWall(index);
			else MakeFloor(index);

			r++;
		}

		t++;
	}
}

void TheBackground::MakeWall(int index)
{
	FloorSquares[index]->SetModel(WallModel);

	Walls.push_back(DBG_NEW Entity);
	Walls.back()->Position = FloorSquares[index]->Position;
	Walls.back()->Radius = FloorSquares[index]->Radius;
	Walls.back()->ShowCollision = true;
	Walls.back()->EntityOnly = true;
}

void TheBackground::MakeFloor(int index)
{
	FloorSquares[index]->SetModel(FloorModel);
}
