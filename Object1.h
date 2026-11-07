#pragma once

#include "resource1.h"
#include <windows.h>
#include <functional>
#include <vector>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

using SendNumbersCallback = std::function<void(const std::vector<int>&)>;

class Object1 {
private:
	static INT_PTR CALLBACK StaticDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	INT_PTR DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HINSTANCE m_hInstance;

	int _n;
	int _min;
	int _max;

	SendNumbersCallback sendNumbers;


public:
	Object1(HINSTANCE hInstance);
	~Object1() {}

	INT_PTR ShowDialog(HWND hParent = NULL);

	void SetSendNumbersCallback(SendNumbersCallback callback);

	int getN() const { return _n; }
	int getMin() const { return _min; }
	int getMax() const { return _max; }
};