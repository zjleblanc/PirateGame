#include "TextWriter.h"
#include <string>
using namespace std;

TextWriter::TextWriter(int fontSize) {
	TTF_Init();
	font = TTF_OpenFont("ARIALN.ttf", fontSize);
}

TextWriter::~TextWriter() {
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
}

void TextWriter::write(char* message, int x, int y, SDL_Surface* screen) {
	SDL_Color textColor = {0,0,0};
	text = TTF_RenderText_Solid(font, message, textColor);

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(text, NULL, screen, &offset);
}
