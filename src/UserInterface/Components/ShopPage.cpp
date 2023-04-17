#include "ShopPage.h"

int
itemColumn::Pages () const
{
	return items.size () / 3;
}
void
itemColumn::Render (size_t begin_column) const
{
	label.Render ();

	size_t offset = 0;
	if (begin_column + 3 > items.size ())
	{
		offset = begin_column + 3 - items.size ();
	}

	for (auto itr = begin_column; itr < begin_column + 3 - offset; ++itr)
	{
		items[itr].button.Render ();
	}
}

void
itemColumn::HandleEvents (size_t begin_column, SDL_Event *event, bool *bUpdate)
{
	size_t offset = 0;
	if (begin_column + 3 > items.size ())
	{
		offset = begin_column + 3 - items.size ();
	}

	for (auto itr = begin_column; itr < begin_column + 3 - offset; ++itr)
	{
		if (items[itr].button.HandleEvents (event))
		{
			items[itr].button.Callback ();
			*bUpdate = true;
		}
	}
}

void
columnLine::Render (size_t begin_column, size_t begin_line) const
{
	size_t offset = 0;
	if (begin_line + 3 > columns.size ())
	{
		offset = begin_line + 3 - columns.size ();
	}

	for (auto itr = begin_line; itr < begin_line + 3 - offset; ++itr)
	{
		columns[itr].Render (begin_column);
	}
}

void
columnLine::HandleEvents (size_t begin_column, size_t begin_line,
                          SDL_Event *event, bool *bUpdate)
{
	size_t offset = 0;
	if (begin_line + 3 > columns.size ())
	{
		offset = begin_line + 3 - columns.size ();
	}

	for (size_t itr = begin_line; itr < begin_line + 3 - offset; ++itr)
	{
		columns[itr].HandleEvents (begin_column, event, bUpdate);
	}
}

void
ShopPage::Render (size_t begin_column, size_t begin_line) const
{
	fullPage.Render (begin_column, begin_line);
}

void
ShopPage::HandleEvents (size_t begin_column, size_t begin_line,
                        SDL_Event *event, bool *bUpdate)
{
	fullPage.HandleEvents (begin_column, begin_line, event, bUpdate);
}