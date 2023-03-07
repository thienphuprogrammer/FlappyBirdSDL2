#include "game_map.h"

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::LoadPipes(SDL_Renderer* scr, const char* filename1, const char* filename2)
{
	pipelines_[0].LoadImg(filename1, scr);
	pipelines_[1].LoadImg(filename2, scr);
	float x_val;
	float y_val;

	srand(time(NULL));
	for (int i = 0; i < MAX_PIPES; i++)
	{

		x_val = (SCREEN_WIDTH / MAX_PIPES) * i + SCREEN_WIDTH;
		y_val = rand() % (BACKGROUND_HEIGHT / 4) + (BACKGROUND_HEIGHT / 1.5 - BACKGROUND_HEIGHT / 4 + 1);

		map_pipe_.pipe[0][i] = { int(x_val), int(y_val), int(pipelines_[0].GetRect().w)
			, int(pipelines_[0].GetRect().h) };

		map_pipe_.pipe[1][i] = { int(x_val), int(y_val - pipelines_[1].GetRect().h - DISTANCE_PIPES)
			, int(pipelines_[1].GetRect().w), int(pipelines_[1].GetRect().h) };
	}
}

void GameMap::ResetPipes(SDL_Renderer* scr, const int move_speed = MAX_SPEED)
{
	for (int i = 0; i < MAX_PIPES; i++)
	{
		float x_val1 = map_pipe_.pipe[0][i].x;
		float x_val2 = map_pipe_.pipe[1][i].x;

		float y_val1 = map_pipe_.pipe[0][i].y;
		float y_val2 = map_pipe_.pipe[1][i].y;

		float width = map_pipe_.pipe[0][i].w;
		float height = map_pipe_.pipe[0][i].h;

		if (x_val1 + width >= 0
			&& x_val2 + width >= 0)
		{
			x_val1 -= move_speed;
			x_val2 -= move_speed;
		}
		else
		{
			x_val1 = SCREEN_WIDTH;
			x_val2 = SCREEN_WIDTH;

			y_val1 = rand() % (BACKGROUND_HEIGHT / 4) + (BACKGROUND_HEIGHT / 1.5 - BACKGROUND_HEIGHT / 4 + 1);
			y_val2 = y_val1 - height - DISTANCE_PIPES;
		}

		pipelines_[0].SetRect(x_val1, y_val1);
		pipelines_[1].SetRect(x_val2, y_val2);

		map_pipe_.pipe[0][i].x = x_val1;
		map_pipe_.pipe[1][i].x = x_val2;
		map_pipe_.pipe[0][i].y = y_val1;
		map_pipe_.pipe[1][i].y = y_val2;

		pipelines_[0].Render(scr);
		pipelines_[1].Render(scr);
	}
}