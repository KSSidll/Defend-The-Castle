#ifndef USER_INTERFACE_COMPONENTS_UI_LABEL_H_
#define USER_INTERFACE_COMPONENTS_UI_LABEL_H_

#include <SDL2/SDL_ttf.h>
#include <string>

class UILabel
{
  private:
	SDL_Renderer *renderer;
	TTF_Font *font;
	SDL_Texture *texture;

	SDL_Rect position;
	SDL_Rect org_refPos;
	SDL_Color color;
	bool wCentered = false;
	bool hCentered = false;
	std::string text;

  public:
	UILabel ();
	~UILabel ();

	UILabel (SDL_Renderer *renderer, int xPos, int yPos, TTF_Font *font,
	         std::string text, SDL_Color color);
	UILabel (SDL_Renderer *renderer, int xPos, int yPos, TTF_Font *font,
	         std::string text, SDL_Color color, int labelWidth);
	UILabel (SDL_Renderer *renderer, int xPos, int yPos, TTF_Font *font,
	         std::string text, SDL_Color color, int labelWidth,
	         int labelHeight);

	void ChangeText (const char *text);
	void Render () const;

	SDL_Rect GetPosition () const;
};

#endif // USER_INTERFACE_COMPONENTS_UI_LABEL_H_