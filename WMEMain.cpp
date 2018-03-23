// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <AboutFrm.h>

#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFiles.h>
#include <UtilsFileIni.h>
#include <UtilsLog.h>
#include <UtilsKAndM.h>

#include "WMEAdd.h"
#include "WMEStrings.h"

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
	MsgBox("TODO: " + ((TButton*)Sender)->Caption);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnDatabaseClick(TObject *Sender) {
	MsgBox("TODO: " + ((TButton*)Sender)->Caption);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOperatorClick(TObject *Sender) {
	MsgBox("TODO: " + ((TButton*)Sender)->Caption);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOptionsClick(TObject *Sender) {
	MsgBox("TODO: " + ((TButton*)Sender)->Caption);
}
// ---------------------------------------------------------------------------
