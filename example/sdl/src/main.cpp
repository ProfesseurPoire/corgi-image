#include <SDL2/SDL.h>
#include <corgi/image/raster_image.h>
#include <corgi/test/test.h>
#include <windows.h>

#include <vector>

using namespace corgi::image;

raster_image img  = raster_image("resources/corgi.png");
raster_image img2 = raster_image(100, 100, corgi::image::color_format::rgba);

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return 0;
    }
    auto window =
        SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, img.width(), img.height(), 0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return 0;
    }

    auto renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_GetWindowSurface(window);

    auto pitch = img.width() * img.color_channel_count();

    // Ok so I'm not too sure about this. Like in opengl it's RGBA and sdl
    // it seems it's ABGR?
    // Looks like its something related to little/big endians but I
    // don't really get it yet. At least it kinda works.

    auto surface = SDL_CreateRGBSurfaceWithFormatFrom(
        img.data(), img.width(), img.height(), img.bits_per_pixel(), pitch,
        SDL_PIXELFORMAT_ABGR8888);

    // I'll keep this here, it helps knowing which texture format
    // are supported by SDL. surface needs to match one of this
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    std::cout << "Renderer name: " << info.name << std::endl;
    std::cout << "Texture formats: " << std::endl;
    for(Uint32 i = 0; i < info.num_texture_formats; i++)
    {
        std::cout << SDL_GetPixelFormatName(info.texture_formats[i])
                  << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // So the texture generated is using SDL_PIXELFORMAT_ARGB8888

    Uint32 fo;
    int    w;
    int    h;
    int    a;

    SDL_QueryTexture(texture, &fo, &a, &w, &h);
    SDL_Rect source;
    source.h = img.height();
    source.w = img.width();
    source.x = 0;
    source.y = 0;

    bool keep_window_open = true;

    while(keep_window_open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 110, 110, 130, 230);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, &source, &source);

        SDL_RenderPresent(renderer);
    }
}