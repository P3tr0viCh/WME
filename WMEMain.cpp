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

#include "WMETDBDrop.h"
#include "WMETDBCheck.h"
#include "WMETDBCreate.h"

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
#ifdef _DEBUG
	randomize();
#endif

	FUser = new TUser();

	FSettings = new TSettings();

	InitStrings();

	DefaultRowHeight = Canvas->TextHeight("ComboBox") + 8;

	Caption = Application->Title + " " + GetFileVer(Application->ExeName);
	StatusBar->Panels->Items[0]->Text = LoadStr(IDS_COPYRIGHT_STATUS);

	WriteToLog(Format(IDS_LOG_START_PROGRAM,
		ARRAYOFCONST((GetFileVer(Application->ExeName, false)))));

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	if (!Settings->Load()) {
		MsgBoxErr(IDS_ERROR_LOAD_SETTINGS);

		Application->Terminate();
		return;
	}

#ifndef FORCELOGON
	if (TfrmLogin::Show(Settings->UserList, User)) {
		ChangeUser();
	}
	else {
		Application->Terminate();
		return;
	}
#else
	User->Assign(Settings->UserList->Items[0]);
	ChangeUser();
#endif

	// btnOptions->Click();
	// btnManual->Click();
	 btnDatabase->Click();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	FSettings->Free();

	FUser->Free();

	WriteToLog(IDS_LOG_STOP_PROGRAM);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnManualClick(TObject *Sender) {
	TfrmTrain::Show(new TTrain());

	// Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnDatabaseClick(TObject *Sender) {
	TfrmTrainList::Show();

	// Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOperatorClick(TObject *Sender) {
	bool Result = false;

	Hide();
	try {
		Result = TfrmLogin::Show(Settings->UserList, User);
	}
	__finally {
		if (Result) {
			ChangeUser();
			Show();
		}
		else {
			Application->Terminate();
		}
	}
}

// ---------------------------------------------------------------------------
void TMain::ChangeUser() {
	btnOperator->Caption = User->Name;
}

// ---------------------------------------------------------------------------
void TMain::InitStrings() {
	WeightTypeAsText[0] = LoadStr(IDS_TXT_WEIGHT_TYPE_BRUTTO);
	WeightTypeAsText[1] = LoadStr(IDS_TXT_WEIGHT_TYPE_TARE);
	WeightTypeAsText[2] = LoadStr(IDS_TXT_WEIGHT_TYPE_MIXED);

	TareIndexAsText[0] = LoadStr(IDS_TXT_TARE_DYNAMIC);
	TareIndexAsText[1] = LoadStr(IDS_TXT_TARE_STATIC);
	TareIndexAsText[2] = LoadStr(IDS_TXT_TARE_TRAFARET);
};

// ---------------------------------------------------------------------------
String TMain::GetWeightTypeAsText(TWeightType Value) {
	switch (Value) {
	case wtBrutto:
		return WeightTypeAsText[0];
	case wtTare:
		return WeightTypeAsText[1];
	case wtMixed:
	default:
		return WeightTypeAsText[2];
	}
}

// ---------------------------------------------------------------------------
String TMain::GetTareIndexAsText(TTareIndex Value) {
	switch (Value) {
	case tiDynamic:
		return TareIndexAsText[0];
	case tiStatic:
		return TareIndexAsText[1];
	case tiTrafaret:
	default:
		return TareIndexAsText[2];
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOptionsClick(TObject *Sender) {
	if (TfrmOptions::Show(Settings, !User->IsAdmin)) {
		for (int i = 0; i < Settings->UserList->Count; i++) {
			if (AnsiSameStr(User->Name, Settings->UserList->Items[i]->Name)) {
				User->Assign(Settings->UserList->Items[i]);
				return;
			}
		}

		btnOperator->Click();
	}

	// Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject * Sender, bool &CanClose) {
#ifndef FORCECLOSE
	CanClose = MsgBoxYesNo(IDS_QUESTION_CLOSE_PROGRAM);
#endif
}

// ---------------------------------------------------------------------------
void __fastcall TMain::ApplicationEventsException(TObject * Sender,
	Exception * E) {
	MsgBoxErr(Format(IDS_ERROR_UNKNOWN_EXCEPTION, E->Message));
	WriteToLog(Format(IDS_LOG_EXCEPTION, E->Message));
}

// ---------------------------------------------------------------------------
