#ifndef MANAGERS_FONT_MANAGER_H_
#define MANAGERS_FONT_MANAGER_H_

#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <utility>

class FontManager
{
  private:
	std::unordered_map<const char *, TTF_Font *> fonts;

  public:
	FontManager ();
	~FontManager ();

	TTF_Font *GetFont (const char *filePath, int fontSize);
};

#endif // MANAGERS_FONT_MANAGER_H_