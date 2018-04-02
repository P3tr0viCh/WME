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
#ifdef _DEBUG
	randomize();
#endif

	Settings = new TSettings();

	User = new TUser();

	Caption = Application->Title + " " + GetFileVer(Application->ExeName);
	StatusBar->Panels->Items[0]->Text = LoadStr(IDS_COPYRIGHT_STATUS);

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
	if (Settings->UserList->Count == 0) {
		User->Free();
		User = new TUser();

		ChangeUser();

		MsgBoxErr(LoadStr(IDS_ERROR_USERS_EMPTY));

		return;
	}

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
	if (IsEmpty(User->Name)) {
		User->Name = "Оператор";
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
void TMain::SetQuerySQL(String Text) {
	ADOQuery->SQL->Text = Text;
}

// ---------------------------------------------------------------------------
void TMain::SetQuerySQL(NativeUInt Ident) {
	TResourceStream *Stream = new TResourceStream((int)HInstance,
		LoadStr(Ident), RT_RCDATA);

	try {
		ADOQuery->SQL->LoadFromStream(Stream);
	}
	__finally {
		Stream->Free();
	}
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

			SetQuerySQL(LoadStr(IDS_MYSQL_VERSION));

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
			StringReplace(MySqlVersion, sLineBreak, " ",
			TReplaceFlags() << rfReplaceAll)));
	}

	return Result;
}

// ---------------------------------------------------------------------------
bool TMain::DatabaseDrop(TConnection *Connection) {
	bool Result = false;
	String Error;

	ShowWaitCursor();
	try {
		ADOConnection->ConnectionString =
			Connection->GetConnectionString(false);

		try {
			ADOConnection->Open();

			SetQuerySQL(LoadStr(IDS_MYSQL_DATABASE_DROP));

			ADOQuery->ExecSQL();

			Result = true;
		}
		catch (Exception *E) {
			Error = E->Message;
		}
	}
	__finally {
		RestoreCursor();
	}

	if (ADOConnection->Connected) {
		ADOConnection->Close();
	}

	if (Result) {
		WriteToLog("DROP OK");
	}
	else {
		if (IsEmpty(Error)) {
			Error = LoadStr(IDS_ERROR_UNKNOWN);
		}

		WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_FAIL, StringReplace(Error,
			sLineBreak, " ", TReplaceFlags() << rfReplaceAll)));
	}

	return Result;
}

// ---------------------------------------------------------------------------
bool TMain::DatabaseCreate(TConnection *Connection) {
	bool Result = false;
	String Error;

	ShowWaitCursor();
	try {
		ADOConnection->ConnectionString =
			Connection->GetConnectionString(false);

		try {
			ADOConnection->Open();

			SetQuerySQL(LoadStr(IDS_MYSQL_DATABASE_DROP));

			ADOQuery->ExecSQL();

			SetQuerySQL(LoadStr(IDS_MYSQL_DATABASE_CREATE));

			ADOQuery->ExecSQL();

			ADOConnection->Close();

			ADOConnection->ConnectionString =
				Connection->GetConnectionString(true);

			ADOConnection->Open();

			SetQuerySQL(IDS_MYSQL_TEMP_CREATE);

			ADOQuery->ExecSQL();

			SetQuerySQL(IDS_MYSQL_TEMP2_CREATE);

			ADOQuery->ExecSQL();

			Result = true;
		}
		catch (Exception *E) {
			Error = E->Message;
		}
	}
	__finally {
		RestoreCursor();
	}

	if (ADOConnection->Connected) {
		ADOConnection->Close();
	}

	if (Result) {
		WriteToLog("CREATE OK");
	}
	else {
		if (IsEmpty(Error)) {
			Error = LoadStr(IDS_ERROR_UNKNOWN);
		}

		WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_FAIL, StringReplace(Error,
			sLineBreak, " ", TReplaceFlags() << rfReplaceAll)));
	}

	return Result;
}

// ---------------------------------------------------------------------------
