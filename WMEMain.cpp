// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <AboutFrm.h>

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsKAndM.h>
#include <UtilsFiles.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMELogin.h"
#include "WMETrain.h"
#include "WMETrainList.h"
#include "WMEOptions.h"

#include "WMEMain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnAboutClick(TObject *Sender) {
	ShowAbout(16, MAXBYTE, MAXBYTE, MAXBYTE, NULL, NULL, NULL, NULL, NULL,
		LoadStr(IDS_COPYRIGHT));
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender) {
	Caption = Application->Title + " " + GetFileVer(Application->ExeName);
	StatusBar->Panels->Items[0]->Text = LoadStr(IDS_COPYRIGHT_STATUS);

	WriteToLog(Format(IDS_LOG_START_PROGRAM,
		ARRAYOFCONST((GetFileVer(Application->ExeName, false)))));

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	if (!TfrmLogin::Show()) {
		Application->Terminate();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLog(IDS_LOG_STOP_PROGRAM);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnManualClick(TObject *Sender) {
	TfrmTrain::Show();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnDatabaseClick(TObject *Sender) {
	TfrmTrainList::Show();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOperatorClick(TObject *Sender) {
	bool LoginResult = false;

	Hide();
	try {
		LoginResult = TfrmLogin::Show();
	}
	__finally {
		if (LoginResult) {
			// ChangeUser();
			Show();
		}
		else {
			Application->Terminate();
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOptionsClick(TObject *Sender) {
	TfrmOptions::Show();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose) {
#ifndef FORCECLOSE
	CanClose = MsgBoxYesNo(LoadStr(IDS_QUESTION_CLOSE_PROGRAM));
#endif
}
// ---------------------------------------------------------------------------
