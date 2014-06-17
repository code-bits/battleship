#pragma once

#include <map>
#include <string>
#include <windows.h>



void CreateDeveloperConsole();
void SetFontForChildren(HWND parent, HFONT font);
BOOL CALLBACK SetFontProc(HWND child, LPARAM lParam);
