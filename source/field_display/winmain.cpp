
#include "../battleship/stdafx.h"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInstance;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
	wincl.lpszClassName = L"Class1";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = 0;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if(!RegisterClassEx(&wincl)) return 0;

    hwnd = CreateWindowEx (
        0,
        L"Class1",
		L"Lab 3 Project",
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
        CW_USEDEFAULT, CW_USEDEFAULT,
        780, 450,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL);

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
      TranslateMessage(&messages);
      DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdcMem;

	HDC hdc = GetDC(hwnd);
	PAINTSTRUCT ps;
	POINT ptMouse;
	RECT rcFieldArea;

	rcFieldArea.top = FldAreaTop;
	rcFieldArea.left = FldAreaLeft;
	rcFieldArea.bottom = FldAreaBtm;
	rcFieldArea.right = FldAreaRgt;

	int** field_array = new int*[Rows];
	for (int i = 0; i < Rows; i++)
	{
		field_array[i] = new int[Columns];
		for (int j = 0; j < Columns; j++)
		{
			
			field_array[i][j] = (i + j)%4;
		}
	}

	switch (message)
	{
		case WM_PAINT:
			{
				hdc = BeginPaint(hwnd, &ps);

				DrawField(hdc, field_array);
				//DrawCell(hdc, RGB(0, 25, 60), 2, 2);
				EndPaint(hwnd, &ps);
			}
			return 0;

		case WM_LBUTTONDOWN:
			{
				ptMouse.x       = GET_X_LPARAM(lParam);
				ptMouse.y       = GET_Y_LPARAM(lParam);

				if(IsInArea(ptMouse, rcFieldArea))
				{
					CellCoord cCoord;

					cCoord.row = (ptMouse.x - FldAreaLeft)/CellWidth;
					cCoord.col = (ptMouse.y - FldAreaTop)/CellWidth;

					CheckCell(hwnd, cCoord, field_array);
					
					hdc = GetDC(hwnd);					
					DrawCell(hdc, field_array[cCoord.row][cCoord.col], cCoord.row * CellWidth, cCoord.col * CellWidth);
					ReleaseDC(hwnd, hdc);
				}

				return 0;
			}

		case WM_DESTROY:
            PostQuitMessage (0);
            return 0;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
	}

	return 0;
}