#include "rawimage.h"
#include <SDL/SDL_image.h>

//TODO: THROW EXCEPTIONS ON LOAD METHOD

using namespace std;

// -------------------------------------------------------------  
// Function: RawImage()  
// Description: Image class builder where the initialization of the class variable happen.
// Return: void  
// -------------------------------------------------------------
RawImage::RawImage() {
    _pixels = NULL;
}

// -------------------------------------------------------------  
// Function: ~RawImage()  
// Description: Image class destructor where the image files free themselves.
// Return: void  
// -------------------------------------------------------------
RawImage::~RawImage() {
    if (_pixels != NULL) {
        SDL_FreeSurface(_pixels);
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------  
// Function: load()  
// Description: Load the images on surface if its not empty.
// Parameters:
// 		const string &name;			File name.
// Return: void  
// -------------------------------------------------------------
void RawImage::load(const string& name) {
    SDL_Surface * image = IMG_Load(name.c_str());

    if (image != NULL) {
        _pixels = SDL_DisplayFormatAlpha(image);
        SDL_FreeSurface(image);
    } else {
        // Nothing to do
    }
}

// -------------------------------------------------------------  
// Function: width()  
// Description: Keep image width.
// Return: int
// -------------------------------------------------------------
int RawImage::width() const {
    if (_pixels != NULL) {
        return _pixels->w;
    } else {
        return 0;
    }
}

// -------------------------------------------------------------  
// Function: height()  
// Description: Keep image height.
// Return: int
// -------------------------------------------------------------
int RawImage::height() const {
    if (_pixels != NULL) {
        return _pixels->h;
    } else {
        return 0;
    }
}

// -------------------------------------------------------------  
// Function: pixels()  
// Description: Return surface.
// Return: SDL_Surface *	
// -------------------------------------------------------------
SDL_Surface * RawImage::pixels() const {
    return _pixels;
}
