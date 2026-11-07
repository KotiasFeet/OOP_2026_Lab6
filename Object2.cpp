#include "Object2.h"


int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distr(min, max);
    return distr(gen);
}

void Object2::GenerateRandomNumbers(std::vector<int> numbers) {
    if (numbers.size() < 3) {
        throw std::invalid_argument("Vector must contain exactly 3 elements: n, min, and max.");
    }
    
    int n = numbers[0];
    int min = numbers[1];
    int max = numbers[2];

    if (min > max) {
        std::swap(min, max);
	}

    if (n <= 0) {
        n = 1;
	}

    _random_numbers.clear();
    
    for (int i = 0; i < n; ++i) {
        _random_numbers.push_back(getRandomInt(min, max));
    }
}

std::wstring Object2::FormatNumbers() const {
    std::wstringstream wss;
    for (size_t i = 0; i < _random_numbers.size(); ++i) {
        wss << _random_numbers[i];
        if (i < _random_numbers.size() - 1) {
            wss << L", ";
        }
    }
    return wss.str();
}

void Object2::SaveToClipboard(HWND hwnd, const std::wstring& text) {
    if (!OpenClipboard(hwnd)) {
        return;
    }

    EmptyClipboard();

    size_t bufferSize = (text.length() + 1) * sizeof(wchar_t);

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, bufferSize);
    if (hMem != NULL) {
        void* pMem = GlobalLock(hMem);
        if (pMem != NULL) {
            memcpy(pMem, text.c_str(), bufferSize);
            GlobalUnlock(hMem);

            SetClipboardData(CF_UNICODETEXT, hMem);
        }
        else {
            GlobalFree(hMem);
        }
    }

    CloseClipboard();
}

void Object2::SetSortClipboardNumbersCallback(
    SortClipboardNumbersCallback callback) {
    sortClipboardNumbersCallback = callback;
}

void Object2::DisplayRandomNumbers(HWND hParent) {
    std::wstring outputText = FormatNumbers();

    SaveToClipboard(hParent, outputText);

    MessageBoxW(hParent, outputText.c_str(), L"Object2 - Generated Random Numbers", MB_OK | MB_ICONINFORMATION);

    if (sortClipboardNumbersCallback) {
        sortClipboardNumbersCallback(hParent);
    }
}