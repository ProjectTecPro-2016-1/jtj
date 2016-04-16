#include "sdlutil.h"
#include <string>
#include <SDL/SDL_image.h>
#include <cassert>

using namespace std;

// -------------------------------------------------------------
// Function: loadImage()
// Description: Load image of some element to draw on screen.
// Parameters:
//		string filename;			Name of image file that will be drwan in element.
// Return: SDL_Surface *
// -------------------------------------------------------------
SDL_Surface * SDLUtil::loadImage(string filename) {
    SDL_Surface * loadedImage = NULL;
    SDL_Surface * optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());
    if (loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);

        SDL_FreeSurface(loadedImage);

        if (optimizedImage != NULL) {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 255, 0, 255);

            int result_SDL_SetColorKey = SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
            assert(result_SDL_SetColorKey >= 0 && "Error setting colors");

        } else {
            // Nothing to do
        }
    } else {
        // Nothing to do
    }

    return optimizedImage;
}

// -------------------------------------------------------------
// Function: applySurface()
// Description: Applies the surface according to graphic components.
// Parameters:
//		int x;								X axis position where the element will be drawn.
//		int y;								Y axis position where the element will be drawn.
//		SDL_Surface * source;				Pointer to the element that will contain the draw.
//		SDL_Surface * destination;			Pointer to the location where the element is arranged.
//		SDL_Rect * clip;					Null pointer passed as parameter to a graphical function.
// Return: void
// -------------------------------------------------------------
void SDLUtil::applySurface(int x, int y, SDL_Surface * source, SDL_Surface * destination,
                           SDL_Rect * clip) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    int result_SDL_BlitSurface = SDL_BlitSurface(source, clip, destination, &offset);
    assert(result_SDL_BlitSurface >= 0 && "Error performing the blit");

    return;
}
