#include "FontManager.h"

FontManager::FontManager () {}

FontManager::~FontManager ()
{
	for (const auto &font : fonts)
	{
		TTF_CloseFont (font.second);
	}
}

TTF_Font *
FontManager::GetFont (const char *filePath, size_t fontSize)
{
	size_t h1 = std::hash<const char *> () (filePath);

	auto res = fonts.emplace (h1 ^ (fontSize << 1),
	                          TTF_OpenFont (filePath, fontSize));

	return res.first->second;
}