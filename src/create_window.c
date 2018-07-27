#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 900;
const int SCREEN_BPP = 32;

const int pos_name_x = 100;
const int pos_name_y = 50;
const int font_size = 18;

SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *up = NULL;
SDL_Surface *down = NULL;
SDL_Surface *left = NULL;
SDL_Surface *right = NULL;

SDL_Event event;

TTF_Font *font;

SDL_Color textColor = { 255, 255, 255 };

SDL_Surface *load_image(char *filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = SDL_LoadBMP(filename);
    if(loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        if(optimizedImage != NULL)
        {
            //transparence
            SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
        }
    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, destination, &offset);
}

bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if(screen == NULL)
        return false;
    if(TTF_Init() == -1)
        return false;
    SDL_WM_SetCaption("TTF Test", NULL);
    return true;
}

bool load_files()
{
    background = load_image("background/wallpaperArchLinux.bmp");
    font = TTF_OpenFont( "/usr/share/fonts/TTF/Hack-Regular.ttf", font_size);
    if(background == NULL)
        return false;
    else
      ft_putendl("Background Loaded");
    if( font == NULL )
        return false;
    else
      ft_putendl("Font Loaded");
    return true;
}

void clean_up()
{
    SDL_FreeSurface(background);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void key_pressed()
{
  Uint8 *keystates;

  keystates = SDL_GetKeyState(NULL);

  if(keystates[SDLK_UP])
          apply_surface((SCREEN_WIDTH - up->w) / 2, (SCREEN_HEIGHT / 2 - up->h) / 2, up, screen, NULL); 
  if(keystates[SDLK_DOWN])
    apply_surface((SCREEN_WIDTH - down->w) / 2, (SCREEN_HEIGHT / 2 - down->h) / 2 + (SCREEN_HEIGHT / 2), down, screen, NULL); 
  if( keystates[SDLK_LEFT] )
    apply_surface((SCREEN_WIDTH / 2 - left->w) / 2, (SCREEN_HEIGHT - left->h) / 2, left, screen, NULL); 
  if( keystates[SDLK_RIGHT])
    apply_surface((SCREEN_WIDTH / 2 - right->w) / 2 + (SCREEN_WIDTH / 2), (SCREEN_HEIGHT - right->h) / 2, right, screen, NULL); 
}

int main( int argc, char** argv)
{
    bool quit = false;
    if(init() == false)
    {
      ft_putendl("Eroor init");
      return 1;
    }
    if(load_files() == false)
    {
      ft_putendl("Eroor load file");
        return 1;
    }
    message = TTF_RenderText_Blended(font, "Anubis_LAB", textColor);
    if(message == NULL)
    {
      ft_putendl("Eroor assign message");
      return 1;
    }
    apply_surface(0, 0, background, screen, NULL);
    apply_surface(pos_name_x, pos_name_y,message, screen, NULL);
    message = NULL;
    up = TTF_RenderText_Blended(font, "Up", textColor);
    down = TTF_RenderText_Blended(font, "Down", textColor);
    left = TTF_RenderText_Blended(font, "Left", textColor);
    right = TTF_RenderText_Blended(font, "Right", textColor);
    while(quit == false)
    {
        while(SDL_PollEvent(&event))
        {
	  if (event.type == SDL_KEYDOWN)
	    key_pressed();
	  else if(event.type == SDL_QUIT)
	    quit = true;
	}
	if (message != NULL)
	  {
	    apply_surface(0, 0, background, screen, NULL);
	    apply_surface((SCREEN_WIDTH - message->w) / 2, (SCREEN_HEIGHT - message->h) / 2, message, screen, NULL);
	    message = NULL;
	  }
	if(SDL_Flip(screen) == -1)
	  return 1;
    }
    clean_up();
    return 0;
}
