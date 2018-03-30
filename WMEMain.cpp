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
	Settings = new TSettings();

	User = new TUser();

	Caption = Application->Title + " " + GetFileVer(Application->ExeName);
	StatusBar->Panels->Items[0]->Text = LoadStr(IDS_COPYRIGHT_STATUS);

	ADOQuery->SQL->Add("");
	ADOQuery->Connection = ADOConnection;

	WriteToLog(Format(IDS_LOG_START_PROGRAM,
		ARRAYOFCONST((GetFileVer(Application->ExeName, false)))));

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	Settings->Load();

#ifndef FORCELOGON
	if (Settings->UserList->Count > 0) {
		if (TfrmLogin::Show(Settings->UserList, User)) {
			ChangeUser();
		}
		else {
			Application->Terminate();
			return;
		}
	}
	else {
		ChangeUser();
	}
#endif

	// btnOptions->Click();
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

	User->Free();

	Settings->Free();

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
	bool Result = false;

	// TODO: Settings->UserList->Count == 0

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
	if (IsEmpty(User->Name)) {
		User->Name = "��������";
	}

	btnOperator->Caption = User->Name;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnOptionsClick(TObject *Sender) {
	TfrmOptions::Show(Settings);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCloseQuery(TObject *Sender, bool &CanClose) {
#ifndef FORCECLOSE
	CanClose = MsgBoxYesNo(LoadStr(IDS_QUESTION_CLOSE_PROGRAM));
#endif
}

// ---------------------------------------------------------------------------
bool TMain::CheckConnection(TConnection *Connection) {
	String MySqlVersion;
	return CheckConnection(Connection, MySqlVersion);
}

// ---------------------------------------------------------------------------
bool TMain::CheckConnection(TConnection *Connection, String &MySqlVersion) {
	bool Result = false;

	ShowWaitCursor();
	try {
		ADOConnection->ConnectionString =
			Connection->GetConnectionString(false);

		try {
			WriteToLog(Format(IDS_LOG_MYSQL_CONNECT,
				ARRAYOFCONST((Connection->User, Connection->Host,
				Connection->Port))));

			ADOConnection->Open();

			ADOQuery->SQL->Strings[0] = LoadStr(IDS_MYSQL_VERSION);

			ADOQuery->Open();

			MySqlVersion = ADOQuery->Fields->Fields[0]->AsString;

			Result = true;
		}
		catch (Exception *E) {
			MySqlVersion = E->Message;
		}
	}
	__finally {
		RestoreCursor();
	}

	if (ADOConnection->Connected) {
		ADOConnection->Close();
	}

	if (Result) {
		WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_OK, MySqlVersion));
	}
	else {
		if (IsEmpty(MySqlVersion)) {
			MySqlVersion = LoadStr(IDS_ERROR_UNKNOWN);
		}

		WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_FAIL,
			StringReplace(MySqlVersion, "\n", " ",
			TReplaceFlags() << rfReplaceAll)));
	}

	return Result;
}

// ---------------------------------------------------------------------------
