#pragma once

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <io.h>
#include <cstdio>
#include <fcntl.h>


#include "window.h"
#include "viewport_window.h"
#include "frame_window.h"
#include "backbuffer.h"
#include "mouse.h"
#include "application.h"
#include "timer.h"
#include "error.h"
#include "tools.h"
#include "field.h"
#include "message.h"
#include "cell.h"
#include "player.h"
#include "dialogboxes.h"

#include "resource.h"
