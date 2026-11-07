#include "Object1.h"

#include <iostream>

Object1::Object1(HINSTANCE hInstance) 
	: m_hInstance(hInstance)
	, _n(993)
	, _min(0)
	, _max(100) {}

void Object1::SetSendNumbersCallback(SendNumbersCallback callback) {
    sendNumbers = callback;
}

INT_PTR Object1::ShowDialog(HWND hParent) {
	return DialogBoxParam(m_hInstance, MAKEINTRESOURCE(IDD_OBJECT1), hParent, StaticDlgProc, (LPARAM)(this));
}

INT_PTR CALLBACK Object1::StaticDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Object1* pThis = nullptr;

    if (uMsg == WM_INITDIALOG) {
        pThis = reinterpret_cast<Object1*>(lParam);
        SetWindowLongPtr(hwndDlg, DWLP_USER, (LONG_PTR)pThis);
    }
    else {
        pThis = reinterpret_cast<Object1*>(GetWindowLongPtr(hwndDlg, DWLP_USER));
    }

    if (pThis) {
        return pThis->DlgProc(hwndDlg, uMsg, wParam, lParam);
    }

    return FALSE;
}

INT_PTR Object1::DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG: 
        SendMessage(GetDlgItem(hwndDlg, IDC_SPIN_N), UDM_SETRANGE32, 0, INT_MAX);
        SendMessage(GetDlgItem(hwndDlg, IDC_SPIN_MIN), UDM_SETRANGE32, INT_MIN, INT_MAX);
        SendMessage(GetDlgItem(hwndDlg, IDC_SPIN_MAX), UDM_SETRANGE32, INT_MIN, INT_MAX);

        SetDlgItemInt(hwndDlg, IDC_EDIT_N, _n, FALSE);
        SetDlgItemInt(hwndDlg, IDC_EDIT_MIN, _min, FALSE);
        SetDlgItemInt(hwndDlg, IDC_EDIT_MAX, _max, FALSE);
        return TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            BOOL bSuccess;

            // save user 
            _n = GetDlgItemInt(hwndDlg, IDC_EDIT_N, &bSuccess, TRUE);
            _min = GetDlgItemInt(hwndDlg, IDC_EDIT_MIN, &bSuccess, TRUE);
            _max = GetDlgItemInt(hwndDlg, IDC_EDIT_MAX, &bSuccess, TRUE);

			std::cout << "User input: n = " << _n << ", min = " << _min << ", max = " << _max << std::endl;

            if (!bSuccess) {
                MessageBox(hwndDlg, L"Please enter valid integers.", L"Input Error", MB_OK | MB_ICONERROR);
                return TRUE;
            }

            if (_min > _max) {
                std::swap(_min, _max);
            }

            if (_n <= 0) {
                _n = 1;
            }

			std::vector<int> numbers = { _n, _min, _max };
			sendNumbers(numbers);

            EndDialog(hwndDlg, IDOK);
            return TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hwndDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
