#ifndef USER_INTERFACE_COMPONENTS_LABELED_BUTTON_H_
#define USER_INTERFACE_COMPONENTS_LABELED_BUTTON_H_

#include "Button.h"
#include "UILabel.h"
#include <unordered_map>

struct LabeledButton
{
	Button button;
	std::unordered_map<std::string, UILabel> labels;

	LabeledButton (Button button,
	               std::unordered_map<std::string, UILabel> labels);

	void Render () const;
	bool HandleEvents (SDL_Event *event, bool callback_on_click = false);
	void ChangeText (std::string labelKey, const char *text);
	void Callback () const;
};

#endif // USER_INTERFACE_COMPONENTS_LABELED_BUTTON_H_