// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEMain.h"
#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMEOptions.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptions::Show() {
	bool Result = false;

	TfrmOptions *frmOptions = new TfrmOptions(Application);
	try {
		Result = frmOptions->ShowModal() == mrOk;
	}
	__finally {
		delete frmOptions;
	}

	WriteToLog(Result ? IDS_LOG_OPTIONS_SAVE : IDS_LOG_OPTIONS_CANCEL);

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	btnDatabase->Tag = 0;
	btnUsers->Tag = 1;

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLogForm(false, ClassName());

	Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnPageSelectClick(TObject *Sender) {
	PageControl->ActivePageIndex = ((TButton*)Sender)->Tag;
    ActiveControl = PageControl;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBConnectionCheckClick(TObject *Sender) {
	if (IsEmpty(eDBServer->Text)) {
		eDBServer->Text = sDefaultMySqlHost;
	}
	if (IsEmpty(eDBPort->Text)) {
		eDBPort->Text = sDefaultMySqlPort;
	}
	if (IsEmpty(eDBUser->Text)) {
		eDBUser->Text = sDefaultMySqlUser;
	}

	String Server = eDBServer->Text;
	String Port = eDBPort->Text;
	String Database;
	String User = eDBUser->Text;
	String Password = eDBPass->Text;

	bool Result = false;
	String Error;
	String MySqlVersion;

	ShowWaitCursor();
	try {
		Main->Connection->ConnectionString =
			GetMySqlConnectionString(Server, Port, Database, User, Password);

		try {
			WriteToLog(Format(IDS_LOG_MYSQL_CONNECT,
				ARRAYOFCONST((User, Server, Port))));

			Main->Connection->Open();

			Main->Query->SQL->Strings[0] = LoadStr(IDS_MYSQL_VERSION);

			Main->Query->Open();

			MySqlVersion = Main->Query->Fields->Fields[0]->AsString;

			Result = true;
		}
		catch (Exception *E) {
			Error = E->Message;
		}
	}
	__finally {
		RestoreCursor();
	}

	if (Main->Connection->Connected) {
		Main->Connection->Close();
	}

	if (Result) {
		WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_OK, MySqlVersion));

		MsgBox(Format(IDS_MSG_MYSQL_CONNECTION_OK, MySqlVersion));
	}
	else {
		if (IsEmpty(Error)) {
			Error = LoadStr(IDS_ERROR_UNKNOWN);
		}

		WriteToLog(Format(IDS_LOG_MYSQL_CONNECT_FAIL, StringReplace(Error, "\n",
			" ", TReplaceFlags() << rfReplaceAll)));

		MsgBoxErr(Format(IDS_ERROR_MYSQL_CONNECTION, Error));
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBConnectionDefaultClick(TObject * Sender) {
	eDBServer->Text = sDefaultMySqlHost;
	eDBPort->Text = sDefaultMySqlPort;
	eDBUser->Text = sDefaultMySqlUser;
	eDBPass->Text = "";
}
// ---------------------------------------------------------------------------
