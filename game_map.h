#pragma once
#ifndef OBSTACLE_OBJECT_H_
#define OBSTACLE_OBJECT_H_

#include "BaseObject.h"

class PipeLine : public BaseObject
{
public:
	PipeLine() {};
	~PipeLine() {};

private:

};

class GameMap
{
public:
	GameMap();
	~GameMap();
	void LoadPipes(SDL_Renderer* scr, const char* filename1, const char* filename2);
	void ResetPipes(SDL_Renderer* scr, const int move_speed);

	RowsPipes GetPipe() const { return map_pipe_; }
	void SetPipe(RowsPipes map) { map_pipe_ = map; }

private:
	PipeLine pipelines_[2];
	RowsPipes map_pipe_;
};

#endif // !OBSTACLE_OBJECT_H_
