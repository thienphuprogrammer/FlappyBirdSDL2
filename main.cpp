#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "ImpTimer.h"
#include "MainObject.h"

BaseObject g_background;
BaseObject g_ground;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_windows = SDL_CreateWindow("Game Cpp SDL 2.0",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (g_windows == NULL) success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_windows, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen,
                RENDERER_DRAW_COLOR,
                RENDERER_DRAW_COLOR,
                RENDERER_DRAW_COLOR,
                RENDERER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                std::cout << "Error: " << IMG_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("image/bk.png", g_screen);
    if (ret == false) return false;

    ret = g_ground.LoadImg("image/ground.png", g_screen);
    g_ground.SetRect(0, BACKGROUND_HEIGHT);
    if (ret == false) return false;
    return true;
}

void close()
{
    g_background.Free();
    g_ground.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_windows);
    g_windows = NULL;

    IMG_Quit();
    SDL_Quit();
}

#undef main
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if (!InitData()) return -1;
    if (!LoadBackground()) return -1;

    GameMap stack_pipes;
    stack_pipes.LoadPipes(g_screen, "image/pipeUp.png", "image/pipeDown.png");

    MainObject p_player;
    p_player.LoadImg("image/bird/clipartbird.png", g_screen);
    p_player.set_clips();


    bool is_quit = false;
    bool game_over = false;
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            if (!game_over)
            {
                p_player.HandleInputAction(g_event, g_screen);
            }
            else
            {
                if (g_event.type == SDL_KEYDOWN)
                {
                    SDL_RenderPresent(g_screen);
                    stack_pipes.LoadPipes(g_screen, "image/pipeUp.png", "image/pipeDown.png");
                    p_player.MainObject::MainObject();
                    game_over = false;
                    continue;
                }
            }
        }

        //SDL_SetRenderDrawColor(g_screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);
        g_ground.Render(g_screen, NULL);

        if (!game_over) stack_pipes.ResetPipes(g_screen, MAX_SPEED);
        else if (game_over)
        {
            stack_pipes.ResetPipes(g_screen, 0);
        }

        RowsPipes pipe_map = stack_pipes.GetPipe();
        p_player.DoPlayer();
        p_player.Show(g_screen);
        if (p_player.HandleBirdCollision(pipe_map))
        {
            game_over = true;
        }

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;

        if (real_imp_time < time_one_frame) {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }

    close();
    return 0;
}
