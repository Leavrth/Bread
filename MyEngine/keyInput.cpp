#include "keyInput.h"

const std::map<char, int> keyInput::keycode = {
	std::map<char, int>::value_type('W', 87)
};

keyInput::keyInput(){
	for (auto it = keycode.cbegin(); it != keycode.cend(); it++)
		keymap[it->first] = UNDOWN;
}

inline void keyInput::pollingKey(const char keyName) {
	if (GetAsyncKeyState(keycode.at(keyName)) & 0x8000) { //W
		if (keymap[keyName] == 0)
			keymap[keyName] = DOWN_FIRST;
		else keymap[keyName] = DOWN_CONTINUE;
	}
	else {
		keymap[keyName] = UNDOWN;
	}
}

void keyInput::Polling() {
	for (auto it = keycode.cbegin(); it != keycode.cend(); it++)
		pollingKey(it->first);
}

const keyState keyInput::iskeyDown(const char key) const {
	return keymap.at[key];
}