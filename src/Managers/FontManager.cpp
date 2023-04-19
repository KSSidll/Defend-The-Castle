#include "FontManager.h"
#include <utility>

FontManager::FontManager () {}

FontManager::~FontManager ()
{
	for (const auto &font : fonts)
	{
		TTF_CloseFont (font.second);
	}
}

TTF_Font *
FontManager::GetFont (const char *filePath, int fontSize)
{
	auto res = fonts.emplace (filePath + fontSize,
	                          TTF_OpenFont (filePath, fontSize));

	return res.first->second;
}