#ifndef MANAGERS_FONT_MANAGER_H_
#define MANAGERS_FONT_MANAGER_H_

#include <SDL2/SDL_ttf.h>
#include <unordered_map>

class FontManager
{
  private:
	std::unordered_map<size_t, TTF_Font *> fonts;

  public:
	FontManager ();
	~FontManager ();

	TTF_Font *GetFont (const char *filePath, size_t fontSize);
};

#endif // MANAGERS_FONT_MANAGER_H_