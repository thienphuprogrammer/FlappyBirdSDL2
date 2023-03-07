#include "MainObject.h"

MainObject::MainObject()
{
	speed_change_ = 0;
	frame_ = 0;
	x_pos_ = SCREEN_WIDTH / 4;
	y_pos_ = BACKGROUND_HEIGHT / 2;
	x_val_ = 0;
	y_val_ = 0;
	jump_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
}

MainObject::~MainObject() {
	;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true) {
		width_frame_ = rect_.w / MAX_NUM_FRAME;
		height_frame_ = rect_.h;
	}
	return ret;
}

void MainObject::set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < MAX_NUM_FRAME; i++) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void MainObject::Show(SDL_Renderer* des) {
	LoadImg("image/bird/clipartbird.png", des);
	if (speed_change_ < 1)
	{
		speed_change_ += 0.3;
	}
	else {
		speed_change_ = 0;
	}
	frame_ += int(speed_change_);
	if (frame_ >= MAX_NUM_FRAME) {
		frame_ = 0;
	}

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = &frame_clip_[frame_];

	SDL_Rect renderQuad = { rect_.x, rect_.y , width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen) {

	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_RIGHT) {
			jump_ = 1;
		}
	}
}

void MainObject::DoPlayer() {
	x_val_ = 0;
	y_val_ += float(GRAVITY_SPEED);

	if (y_val_ >= MAX_FALL_SPEED) {
		y_val_ = MAX_FALL_SPEED;
	}

	if (jump_ == 1) {
		y_val_ = -PLAYER_JUMP_VAL;
		jump_ = 0;
	}
}

bool MainObject::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

bool MainObject::HandleBirdCollision(RowsPipes& map_data)
{
	int y1 = 0;
	int y2 = 0;

	y1 = y_pos_ + y_val_;
	y2 = y_pos_ + y_val_ + height_frame_;

	//Check Collision with Pipes
	bool collision = false;
	bool ret = false;
	for (int i = 0; i < MAX_PIPES; i++)
	{
		SDL_Rect Object1 = { x_pos_ + x_val_, y_pos_ + y_val_, width_frame_, height_frame_ };
		SDL_Rect Object2 = map_data.pipe[0][i];

		collision = CheckCollision(Object1, Object2);
		if (collision)
		{
			ret = true;
		}
		Object2 = map_data.pipe[1][i];
		collision = CheckCollision(Object1, Object2);
		if (collision)
		{
			ret = true;
		}
	}

	//Check Collision width ground 
	if (y_val_ < 0)
	{
		if (y1 < 0)
		{
			y_pos_ += 1;
			y_val_ = 0;
		}
	}
	else if (y_val_ > 0)
	{
		if (y2 > BACKGROUND_HEIGHT)
		{
			y_val_ = 0;
			ret = true;
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	return ret;
}