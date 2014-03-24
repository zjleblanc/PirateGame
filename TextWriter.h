#include "SDL_ttf.h"
#include <string>
using namespace std;

#ifndef TEXTWRITER_H
#define TEXTWRITER_H

class TextWriter {
public:
	TextWriter(int);
	~TextWriter();
	void write(char*, int, int, SDL_Surface*);
private:
	TTF_Font* font;
	SDL_Surface* text;
};

#endif
