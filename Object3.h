#pragma once
#pragma once

#include <windows.h>
#include <string>
#include <vector>

class Object3 {
private:
    std::vector<int> _numbers;

    bool ReadFromClipboard(HWND hwnd);
    std::wstring FormatNumbers() const;

public:
    void SortClipboardNumbers(HWND mainWindow, std::wstring& numbers);
};
