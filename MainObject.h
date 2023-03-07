#pragma once
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 20
#define PLAYER_JUMP_VAL 13
#define MAX_NUM_FRAME 4

class MainObject : public BaseObject {
public:
	MainObject();
	~MainObject();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoPlayer();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool HandleBirdCollision(RowsPipes& map_data);

private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;
	int jump_;

	SDL_Rect frame_clip_[4];

	int frame_;
	float speed_change_;
};

#endif // !MAIN_OBJECT_H_
