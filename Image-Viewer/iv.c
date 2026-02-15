#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main() {
    // تأكد من عمل Init لـ SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    FILE *in = stdin;
    char pthroway[1000];

    fgets(pthroway, 1000, in); // P3 or P6
    fgets(pthroway, 1000, in); // Comment

    int width = -1, height = -1;
    fscanf(in, "%d %d\n", &width, &height); // أسهل من sscanf
    fgets(pthroway, 1000, in); // Max color value

    printf("width= %d, height= %d\n", width, height);

    SDL_Window *pwindow = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    SDL_Rect pixel = {0, 0, 1, 1};
    
    // الترتيب الصحيح: y ثم x
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint8 r = fgetc(in);
            Uint8 g = fgetc(in);
            Uint8 b = fgetc(in);

            // التصحيح الأهم: تخزين قيمة اللون
            Uint32 color = SDL_MapRGB(psurface->format, r, g, b);
            
            pixel.x = x;
            pixel.y = y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(pwindow);

    int app_running = 1;
    while (app_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app_running = 0;
            }
        }
        SDL_Delay(16); // 16ms تعطي تقريباً 60 فريم في الثانية
    }

    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}