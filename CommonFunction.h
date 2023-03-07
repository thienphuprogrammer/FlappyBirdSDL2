#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

static SDL_Window* g_windows = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 770;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDERER_DRAW_COLOR = 0xff;

//IMAGAE
const int BACKGROUND_HEIGHT = 670;
const int GROUND_HEIGHT = 100;

//SET PIPES
#define MAX_SPEED 5.8
#define MAX_PIPES 3
#define DISTANCE_PIPES BACKGROUND_HEIGHT / 3

typedef struct RowsPipes {
	SDL_Rect pipe[2][MAX_PIPES];
} RowsPipes;

#endif // !COMMON_FUNCTION_H_
