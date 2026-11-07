#include "Object3.h"

#include <algorithm>
#include <sstream>

bool Object3::ReadFromClipboard(HWND hwnd) {
    _numbers.clear();

    if (!OpenClipboard(hwnd)) {
        return false;
    }

    HANDLE clipboardData = GetClipboardData(CF_UNICODETEXT);
    if (clipboardData == nullptr) {
        CloseClipboard();
		throw std::runtime_error("Failed to get clipboard data");
        return false;
    }

    LPCWSTR clipboardText = static_cast<LPCWSTR>(GlobalLock(clipboardData));
    if (clipboardText == nullptr) {
        CloseClipboard();
		throw std::runtime_error("Failed to lock clipboard data");
        return false;
    }

    std::wstring text(clipboardText);
    GlobalUnlock(clipboardData);
    CloseClipboard();

    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == L',') {
            text[i] = L' ';
        }
    }

    std::wistringstream input(text);
    int number;
    while (input >> number) {
        _numbers.push_back(number);
    }

    return !_numbers.empty();
}

std::wstring Object3::FormatNumbers() const {
    std::wstringstream wss;
    for (size_t i = 0; i < _numbers.size(); ++i) {
        wss << _numbers[i];
        if (i < _numbers.size() - 1) {
            wss << L", ";
        }
    }
    return wss.str();
}

void Object3::SortClipboardNumbers(HWND mainWindow, std::wstring& numbers) {
    if (!ReadFromClipboard(mainWindow)) {
        MessageBoxW(mainWindow, L"The clipboard does not contain numbers.",
            L"Object3", MB_OK | MB_ICONWARNING);
        return;
    }

    std::sort(_numbers.begin(), _numbers.end());
    const std::wstring sortedNumbers = FormatNumbers();

    //SetWindowTextW(mainWindow, (L"Sorted numbers: " + sortedNumbers).c_str());

	numbers = sortedNumbers;

    MessageBoxW(mainWindow, sortedNumbers.c_str(), L"Object3 - Sorted Numbers",
        MB_OK | MB_ICONINFORMATION);
}
