// LearningOutOfContextHooks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

#define CASE_LITERAL_RETURN_STRING(x) case x: return move(string(#x));

bool EventInRange(string& inRangeStr, DWORD eventID, DWORD start, DWORD end, const char* str)
{
    if (eventID >= start && eventID <= end)
    {
        stringstream output;
        output << str << "+0x" << uppercase << hex << (eventID - start);
        inRangeStr = move(output.str());
        return true;
    }

    return false;
}

#define EVENT_IN_RANGE_STRING(e, start, end, out) EventInRange(out, e, start, end, #start)

string EventToString(DWORD eventID)
{
    string inRangeStr;
    if (EVENT_IN_RANGE_STRING(eventID, EVENT_AIA_START, EVENT_AIA_END, inRangeStr))
        return move(inRangeStr);
    if (EVENT_IN_RANGE_STRING(eventID, EVENT_OEM_DEFINED_START, EVENT_OEM_DEFINED_END, inRangeStr))
        return move(inRangeStr);
    if (EVENT_IN_RANGE_STRING(eventID, EVENT_UIA_EVENTID_START, EVENT_UIA_EVENTID_END, inRangeStr))
        return move(inRangeStr);
    if (EVENT_IN_RANGE_STRING(eventID, EVENT_UIA_PROPID_START, EVENT_UIA_PROPID_END, inRangeStr))
        return move(inRangeStr);

    switch (eventID)
    {
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_ACCELERATORCHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_CONTENTSCROLLED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_CREATE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DEFACTIONCHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DESCRIPTIONCHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DESTROY);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DRAGSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DRAGCANCEL);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DRAGCOMPLETE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DRAGENTER);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DRAGLEAVE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_DRAGDROPPED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_END);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_FOCUS);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_HELPCHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_HIDE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_HOSTEDOBJECTSINVALIDATED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_IME_HIDE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_IME_SHOW);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_IME_CHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_INVOKED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_LIVEREGIONCHANGED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_LOCATIONCHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_NAMECHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_PARENTCHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_REORDER);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_SELECTION);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_SELECTIONADD);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_SELECTIONREMOVE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_SELECTIONWITHIN);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_SHOW);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_STATECHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_TEXTEDIT_CONVERSIONTARGETCHANGED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_TEXTSELECTIONCHANGED);
    CASE_LITERAL_RETURN_STRING(EVENT_OBJECT_VALUECHANGE);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_ALERT);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_ARRANGMENTPREVIEW);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_CAPTUREEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_CAPTURESTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_CONTEXTHELPEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_CONTEXTHELPSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_DESKTOPSWITCH);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_DIALOGEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_DIALOGSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_DRAGDROPEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_DRAGDROPSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_END);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_FOREGROUND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MENUPOPUPEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MENUPOPUPSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MENUEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MENUSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MINIMIZEEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MINIMIZESTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MOVESIZEEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_MOVESIZESTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_SCROLLINGEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_SCROLLINGSTART);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_SOUND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_SWITCHEND);
    CASE_LITERAL_RETURN_STRING(EVENT_SYSTEM_SWITCHSTART);
    default: 
        {
            stringstream output;
            output << "0x" << uppercase << setfill('0') << setw(8) << hex << eventID;
            return move(output.str());
        }
    }
}


void CALLBACK WinEventProc(
    HWINEVENTHOOK hHook,
    DWORD eventID,
    HWND hWnd,
    LONG idObject,
    LONG idChild,
    DWORD dwEventThread,
    DWORD dwmsEventTime)
{
    // Get the window title
    int windowTextLength = GetWindowTextLengthA(hWnd);
    string windowText;
    windowText.resize(windowTextLength);
    GetWindowTextA(hWnd, (LPSTR) windowText.data(), windowTextLength+1);

    // Get the process and thread that created the window
    DWORD windowProcessId = 0;
    DWORD windowThreadId = GetWindowThreadProcessId(hWnd, &windowProcessId);
    
    if (GetCurrentProcessId() == windowProcessId)
        return;

    // Get the process handle from the process Id
    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        windowProcessId);

    // Some system processes cannot be inspected.
    if (hProcess == nullptr)
        return;

    // Get the name of the process
    char exePath[MAX_PATH];
    DWORD exePathLength = _countof(exePath);
    if (!QueryFullProcessImageNameA(hProcess, 0, exePath, &exePathLength))
        return;
    
    for (char* c = exePath; c < exePath + exePathLength; ++c)
        *c = tolower(*c);

    if (strstr(exePath, "notepad") == nullptr)
        return;

    cout << EventToString(eventID) << endl;
}


int main()
{
    HWINEVENTHOOK hook = SetWinEventHook(
        EVENT_MIN,
        EVENT_MAX,
        nullptr,
        WinEventProc,
        0, // all processes
        0, // all threads
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

    if (hook == 0)
    {
        cout << "Couldn't hook events." << endl;
        return 1;
    }

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWinEvent(hook);

    return 0;
}

