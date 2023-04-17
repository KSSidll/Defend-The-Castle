#ifndef USER_INTERFACE_COMPONENTS_SHOP_PAGE_H_
#define USER_INTERFACE_COMPONENTS_SHOP_PAGE_H_

#include "../Components/LabeledButton.h"
#include <deque>

// Recurrent dependency
class Shop;

struct itemButton
{
	LabeledButton button;
	std::string item_name;
};

struct itemColumn
{
	UILabel label;
	std::deque<itemButton> items;

	int Pages () const;
	void Render (size_t begin_column) const;

	void HandleEvents (size_t begin_column, SDL_Event *event, bool *bUpdate);
};

struct columnLine
{
	std::deque<itemColumn> columns;

	void Render (size_t begin_column, size_t begin_line) const;
	void HandleEvents (size_t begin_column, size_t begin_line,
	                   SDL_Event *event, bool *bUpdate);
};

struct ShopPage
{
	columnLine fullPage;

	void Render (size_t begin_column, size_t begin_line) const;
	void HandleEvents (size_t begin_column, size_t begin_line,
	                   SDL_Event *event, bool *bUpdate);
};

#endif // USER_INTERFACE_COMPONENTS_SHOP_PAGE_H_
