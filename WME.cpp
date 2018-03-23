// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("WMEMain.cpp", Main);

// ---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	HANDLE hMutex;

	try {
		hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"ru.p3tr0vich.WME");

		if (hMutex) {
			HWND hWnd = FindWindow(TEXT("TApplication"),
				TEXT("��� \"������ ����\""));

			SwitchToThisWindow(hWnd, true);

			return 0;
		}

		hMutex = CreateMutex(0, 0, L"ru.p3tr0vich.WME");

		Application->Initialize();
		Application->MainFormOnTaskBar = false;
		Application->Title = "��� \"������ ����\"";
		Application->CreateForm(__classid(TMain), &Main);
		Application->Run();
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}

	ReleaseMutex(hMutex);

	return 0;
}
// ---------------------------------------------------------------------------
