#include <windows.h>
#include <stdio.h>
#include "definition.h"

#define BUTTON_CALL 400

HWND hwnd, hComboBox, hCallButton;

extern bool IsLogin;
extern char MyEmail[GENERAL_BUFSIZE];
char ContactList[5][GENERAL_BUFSIZE]{};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case BUTTON_CALL:
   	    {
            int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
            if (selectedIndex != CB_ERR)
            {
                // ���õ� �׸��� ���� ��������
                int textLength = SendMessage(hComboBox, CB_GETLBTEXTLEN, selectedIndex, 0);
                if (textLength != CB_ERR)
                {
                    // ���õ� �׸��� �ؽ�Ʈ ��������
                    wchar_t* selectedText = new wchar_t[textLength + 1];
                    SendMessage(hComboBox, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

                    // ���õ� �׸� ���
                    MessageBox(hwnd, selectedText, L"Selected Item", MB_OK);
                }
            }
        }
        }
    }
    break;
    case WM_CREATE:
    {
        // ComboBox ����
        hComboBox = CreateWindowEx(0, L"ComboBox", NULL, WS_CHILD | WS_VISIBLE | CBS_SIMPLE,
            10, 10, 200, 200, hwnd, NULL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);


        TCHAR Contact[5][GENERAL_BUFSIZE]{};

        for (int i = 0; i < 5; i++)
        {
            if (strlen((const char*)ContactList[i]) > 0) { // need to exclue myself?
                MultiByteToWideChar(CP_ACP, 0, ContactList[i], -1, Contact[i], GENERAL_BUFSIZE);
                SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)Contact[i]);
            }
        }
    }
    break;

    case WM_DESTROY:
    {
        DestroyWindow(hCallButton);
        DestroyWindow(hComboBox);
        DestroyWindow(hwnd);
        return 0;
    }
    case WM_CLOSE:
    {
        DestroyWindow(hCallButton);
        DestroyWindow(hComboBox);
        DestroyWindow(hwnd);
        return 0;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI CreateContactList(HWND Phwnd)
{
    if (!IsLogin)
    {
        MessageBox(NULL, L"Please Login First", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    // ������ Ŭ���� ���
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"MainWindowClass";
    RegisterClass(&wc);
    

    // ������ ����
    hwnd = CreateWindowEx(0, L"MainWindowClass", L"Contact List", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, wc.hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Failed to create the window.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    hCallButton = CreateWindowEx(
        0,
        L"BUTTON",
        L"Call",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        250, 10, 100, 30,
        hwnd, (HMENU)BUTTON_CALL, NULL, NULL
    );

    // ������ ǥ��
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // �޽��� ����
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}