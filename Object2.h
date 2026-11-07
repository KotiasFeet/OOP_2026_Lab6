#pragma once

#include "resource2.h"

#include <windows.h>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <functional>

using SortClipboardNumbersCallback = std::function<void(HWND)>;

class Object2 {
private:
	std::vector<int> _random_numbers;
	SortClipboardNumbersCallback sortClipboardNumbersCallback;

	std::wstring FormatNumbers() const;
	void SaveToClipboard(HWND hwnd, const std::wstring& text);
public: 
	Object2() {}
	~Object2() {}
	
	void GenerateRandomNumbers(std::vector<int> numbers);
	void DisplayRandomNumbers(HWND hwnd);

	void SetSortClipboardNumbersCallback(SortClipboardNumbersCallback callback);
};