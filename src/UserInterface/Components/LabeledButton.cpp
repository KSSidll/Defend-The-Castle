#include "LabeledButton.h"

LabeledButton::LabeledButton (Button button,
                              std::unordered_map<std::string, UILabel> labels)
{
	this->button = button;
	this->labels = labels;
}

void
LabeledButton::Render () const
{
	button.Render ();
	for (auto &label : labels)
	{
		label.second.Render ();
	}
}

bool
LabeledButton::HandleEvents (SDL_Event *event, bool callback_on_click)
{
	return button.HandleEvents (event, callback_on_click);
}

void
LabeledButton::ChangeText (std::string labelKey, const char *text)
{
	labels.at (labelKey).ChangeText (text);
}

void
LabeledButton::Callback () const
{
	button.Callback ();
}