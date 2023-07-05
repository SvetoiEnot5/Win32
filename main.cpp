#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
MSG msg{};
HWND hwnd{};
static char txt[32] = "Токарев";
static HPEN hpen;
static HBRUSH hbrush;
WNDCLASSEX wndclass{sizeof(WNDCLASSEX)};
wndclass.style = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            HWND hButton = CreateWindow(L"Button", L"Вывести флаг", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 480, 370, 300, 20, hWnd, HMENU(1), nullptr, nullptr);
            HWND hButton1 = CreateWindow(L"Button", L"Очистить поле", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 480, 400, 300, 20, hWnd, HMENU(2), nullptr, nullptr);
            HWND hButton2 = CreateWindow(L"Button", L"Вывести фамилию", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 480, 430, 300, 20, hWnd, HMENU(3), nullptr, nullptr);
        }
            return 0;

        case WM_COMMAND:
        {
            hpen = CreatePen(PS_SOLID, 10, RGB(255,0,0));
            hbrush = CreateSolidBrush(RGB(255,0,0));

            switch (LOWORD(wParam))
            {
                case 1:
                {
                    HDC hdc;
                    PAINTSTRUCT ps;
                    hdc = BeginPaint(hWnd, &ps);
                    SelectObject(hdc, hbrush);
                    SelectObject(hdc, hpen);
                    Rectangle(hdc, 0, 0, 300, 200);
                    EndPaint(hWnd, &ps);
                    return 0;

                }
                    break;
                case 2:
                {
                    InvalidateRect(hWnd, NULL, TRUE);
                    return 0;
                }
                    break;
                case 3:
                {
                    HDC hdc;
                    hdc = GetDC(hWnd);
                    LPCWSTR txt1 = L"Токарев";
                    TextOutA(hdc, 100, 300, txt1, strlen(txt));
                }
                    break;
            }
        }
            return 0;


        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
        }
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
};
wndclass.cbClsExtra = 0;
wndclass.cbWndExtra = 0;
wndclass.hInstance = hInstance;
wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
wndclass.lpszMenuName = nullptr;
wndclass.lpszClassName = L"MyAppClass";
wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
if (!RegisterClassEx(&wndclass))
return EXIT_FAILURE;

if (hwnd = CreateWindow(wndclass.lpszClassName, L"Заголовок", WS_OVERLAPPEDWINDOW, 0, 0, 800, 800, nullptr, nullptr, wndclass.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
return EXIT_FAILURE;

ShowWindow(hwnd, nCmdShow);
UpdateWindow(hwnd);

while (GetMessage(&msg,nullptr,0,0))
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}

return msg.wParam;
}