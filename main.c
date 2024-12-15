#include <stdio.h>
#include <SDL2/SDL.h>
#include "spritesheet.h"

#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480

int main(/*int argc, char* argv[]*/) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Project",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a spritesheet (example path "critters.bmp", 5 rows, 3 columns)
    Spritesheet *spritesheet = spritesheet_create(renderer, "critters.bmp", 5, 3);
    if (!spritesheet) {
        fprintf(stderr, "Failed to load spritesheet.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Select the sprite at row 1, column 2 (0-based)
    spritesheet_select_sprite(spritesheet, 2, 1);

    // Define where to draw the sprite on the screen
    SDL_Rect dest_rect = {100, 100, spritesheet->m_clip.w, spritesheet->m_clip.h};

    // Main loop flag
    int quit = 0;
    SDL_Event e;

    // Event loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear screen with black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the selected sprite
        spritesheet_draw_selected_sprite(spritesheet, renderer, &dest_rect);

        // Present the renderer (display the drawn frame)
        SDL_RenderPresent(renderer);

        // Wait a few seconds before quitting
        SDL_Delay(3000);
    }

    // Clean up
    spritesheet_destroy(spritesheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
