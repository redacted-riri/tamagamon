#include "spritesheet.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

// Helper function to load an image as a texture (using SDL_LoadBMP)
SDL_Texture* load_texture(SDL_Renderer* renderer, const char *path) {
    SDL_Surface *loaded_surface = SDL_LoadBMP(path);
    if (!loaded_surface) {
        fprintf(stderr, "Error loading BMP: %s\n", SDL_GetError());
        return NULL;
    }

    // Create a texture from the loaded surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    SDL_FreeSurface(loaded_surface);  // Free the surface after creating texture

    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
    }
    return texture;
}

Spritesheet* spritesheet_create(SDL_Renderer* renderer, const char *path, int row_count, int column_count) {
    // Allocate memory for the Spritesheet struct
    Spritesheet *spritesheet = (Spritesheet *)malloc(sizeof(Spritesheet));
    if (!spritesheet) {
        return NULL;  // Memory allocation failed
    }

    // Load the spritesheet texture
    spritesheet->m_spritesheet_texture = load_texture(renderer, path);
    if (!spritesheet->m_spritesheet_texture) {
        free(spritesheet);  // Free the struct if image loading failed
        return NULL;
    }

    // Set the number of rows and columns
    spritesheet->m_row_count = row_count;
    spritesheet->m_column_count = column_count;

    // Calculate the width and height of each sprite (based on the image size)
    SDL_QueryTexture(spritesheet->m_spritesheet_texture, NULL, NULL, &spritesheet->m_clip.w, &spritesheet->m_clip.h);
    spritesheet->m_clip.w /= column_count;
    spritesheet->m_clip.h /= row_count;

    return spritesheet;
}

void spritesheet_destroy(Spritesheet *spritesheet) {
    if (spritesheet) {
        if (spritesheet->m_spritesheet_texture) {
            SDL_DestroyTexture(spritesheet->m_spritesheet_texture);  // Free the texture
        }
        free(spritesheet);  // Free the struct itself
    }
}

void spritesheet_select_sprite(Spritesheet *spritesheet, int x, int y) {
    // Calculate the position of the sprite in the spritesheet
    spritesheet->m_clip.x = x * spritesheet->m_clip.w;
    spritesheet->m_clip.y = y * spritesheet->m_clip.h;
}

void spritesheet_draw_selected_sprite(Spritesheet *spritesheet, SDL_Renderer *renderer, SDL_Rect *position) {
    // Render the selected sprite onto the renderer (using SDL_RenderCopy)
    SDL_RenderCopy(renderer, spritesheet->m_spritesheet_texture, &spritesheet->m_clip, position);
}
