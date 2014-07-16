
#include "dialogboxes.h"
#include "stdafx.h"

BOOL CALLBACK NewGameDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static NewGameParams * ngp;
    switch (message)
    {
    case WM_INITDIALOG:
        ngp = (NewGameParams *) lParam;
        CheckDlgButton(hDlg, IDC_RADIO_BOT, BST_CHECKED);
        return TRUE ;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            if (IsDlgButtonChecked(hDlg, IDC_RADIO_BOT))
            {
                ngp->gameMode = OFFLINE;
            }
            else if (IsDlgButtonChecked(hDlg, IDC_RADIO_HOST))
            {
                ngp->gameMode = ONLINE_HOST;
            }
            else if (IsDlgButtonChecked(hDlg, IDC_RADIO_CONNECT))
            {
                ngp->gameMode = ONLINE_CLIENT;

                DWORD ipData;
                SendMessage(GetDlgItem(hDlg, IDC_IPADDRESS), IPM_GETADDRESS, 0, (LPARAM) & ipData);

                std::stringstream ss;
                ss << FIRST_IPADDRESS(ipData) << "."
                    << SECOND_IPADDRESS(ipData) << "."
                    << THIRD_IPADDRESS(ipData) << "."
                    << FOURTH_IPADDRESS(ipData);

                ss >> (ngp->ipAddress);
                EndDialog(hDlg, TRUE);
            }
            return TRUE;

        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            return TRUE;
        }
    }
    return FALSE;
}
