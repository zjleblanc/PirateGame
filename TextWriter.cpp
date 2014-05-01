#include "TextWriter.h"
#include <string>
using namespace std;

// CONSTRUCTOR

TextWriter::TextWriter(int fontSize) {
	TTF_Init();
	font = TTF_OpenFont("ARIALN.ttf", fontSize);		// we use an arial narrow font for all text writing
}

// DECONSTRUCTOR

TextWriter::~TextWriter() {
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
}

// PUBLIC METHODS

void TextWriter::write(const char* message, int x, int y, SDL_Surface* screen) {
	SDL_Color textColor = {0,0,0};								// default color is black
	text = TTF_RenderText_Solid(font, message, textColor);

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(text, NULL, screen, &offset);				// determines where to render text on the screen
}

