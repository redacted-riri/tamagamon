#pragma once

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect m_clip;                // Stores the current sprite's rectangle (position and size)
    SDL_Texture *m_spritesheet_texture; // Pointer to the spritesheet texture
    int m_row_count;                // Number of rows in the spritesheet
    int m_column_count;             // Number of columns in the spritesheet
} Spritesheet;

Spritesheet* spritesheet_create(SDL_Renderer* renderer, const char *path, int row_count, int column_count);
void spritesheet_destroy(Spritesheet *spritesheet);
void spritesheet_select_sprite(Spritesheet *spritesheet, int x, int y);
void spritesheet_draw_selected_sprite(Spritesheet *spritesheet, SDL_Renderer *renderer, SDL_Rect *position);
