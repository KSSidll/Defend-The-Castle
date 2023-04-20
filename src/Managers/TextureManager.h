#ifndef MANAGERS_TEXTURE_MANAGER_H_
#define MANAGERS_TEXTURE_MANAGER_H_

#include <SDL2/SDL.h>
#include <rapidjson/document.h>
#include <string>
#include <unordered_map>

struct ButtonTextures
{
	SDL_Texture *none;
	SDL_Texture *over;
	SDL_Texture *down;
};

class TextureManager
{
  private:
	SDL_Renderer *renderer;

	std::unordered_map<std::string, SDL_Texture *> textureArray;
	std::unordered_map<std::string, ButtonTextures *> buttonTextureArray;

  public:
	TextureManager ();
	~TextureManager ();

	TextureManager (SDL_Renderer *renderer);

	void LoadTexture (const rapidjson::Value &texturePath);
	void LoadTexture (const char *key, const char *filePath);
	void LoadButtonTexture (const char *key, const char *none,
	                        const char *over, const char *down);

	SDL_Texture *GetTexture (const rapidjson::Value &texturePath) const;
	SDL_Texture *GetTexture (const char *key) const;
	ButtonTextures *GetButtonTexture (const char *key) const;
};

#endif // MANAGERS_TEXTURE_MANAGER_H_