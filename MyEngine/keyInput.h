#pragma once
#include <map>
#include <windows.h>
#include "D3DUtil.h"
class keyInput {
public:
	keyInput();
	~keyInput() = default; 
	void Polling();
	const keyState iskeyDown(const char key) const;
private:
	
	inline void pollingKey(const char keyName);
	std::map<char, keyState> keymap;
	static const std::map<char, int> keycode;
};