// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMEMain.h"

#include "WMETSettings.h"

#include "WMEOptions.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const COLUMN_USERS_NUM = 0;
const COLUMN_USERS_NAME = 1;
const COLUMN_USERS_IS_PASS = 2;
const COLUMN_USERS_TABNUM = 3;
const COLUMN_USERS_SHIFTNUM = 4;
const COLUMN_USERS_PASS = 5;
const COLUMN_USERS_COUNT = 6;

// ---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptions::Show(TSettings *Settings) {
	bool Result = false;

	TfrmOptions *frmOptions = new TfrmOptions(Application);
	try {
		frmOptions->Settings->Assign(Settings);

		frmOptions->UpdateForm();

		Result = frmOptions->ShowModal() == mrOk;

		if (Result) {
			Settings->Assign(frmOptions->Settings);
		}
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

	PerformSave = false;

	Settings = new TSettings();

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	UpdateUsersColumns();
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

	Settings->Free();
}

// ---------------------------------------------------------------------------
void TfrmOptions::UpdateUsersColumns() {
	sgUsers->Cells[COLUMN_USERS_NUM][0] = "№";
	sgUsers->ColWidths[COLUMN_USERS_NUM] = 50;
	sgUsers->Cells[COLUMN_USERS_NAME][0] = "ФИО";
	sgUsers->ColWidths[COLUMN_USERS_NAME] = 200;
	sgUsers->Cells[COLUMN_USERS_IS_PASS][0] = "Пароль";
	sgUsers->ColWidths[COLUMN_USERS_IS_PASS] = 70;
	sgUsers->Cells[COLUMN_USERS_TABNUM][0] = "Таб. номер";
	sgUsers->ColWidths[COLUMN_USERS_TABNUM] = 120;
	sgUsers->Cells[COLUMN_USERS_SHIFTNUM][0] = "Смена";
	sgUsers->ColWidths[COLUMN_USERS_SHIFTNUM] = 60;
}

// ---------------------------------------------------------------------------
void TfrmOptions::UpdateForm() {
	// Database
	eDBHost->Text = Settings->Connection->Host;
	eDBPort->Text = Settings->Connection->Port;
	eDBUser->Text = Settings->Connection->User;
	eDBPass->Text = Settings->Connection->Password;

	// Users
	for (int i = 0; i < Settings->UserList->Count; i++) {
		SetUser(-1, Settings->UserList->Items[i]);
	}
	sgUsers->Row = 1;
}

// ---------------------------------------------------------------------------
void TfrmOptions::UpdateSettings() {
	// Database
	Settings->Connection->Host = eDBHost->Text;
	Settings->Connection->Port = eDBPort->Text;
	Settings->Connection->User = eDBUser->Text;
	Settings->Connection->Password = eDBPass->Text;

	// Users

	Settings->UserList->Clear();

	if (!StringGridIsEmpty(sgUsers)) {
		TUser *User;

		for (int i = 1; i < sgUsers->RowCount; i++) {
			User = new TUser();

			User->Name = sgUsers->Cells[COLUMN_USERS_NAME][i];
			User->Pass = sgUsers->Cells[COLUMN_USERS_PASS][i];
			User->TabNum = sgUsers->Cells[COLUMN_USERS_TABNUM][i];
			User->ShiftNum = sgUsers->Cells[COLUMN_USERS_SHIFTNUM][i];

			Settings->UserList->Add(User);
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBConnectionCheckClick(TObject *Sender) {
	bool Result = false;

	String MySqlVersion;

	TConnection *Connection = new TConnection();

	try {
		Connection->Host = eDBHost->Text;
		Connection->Port = eDBPort->Text;
		Connection->User = eDBUser->Text;
		Connection->Password = eDBPass->Text;

		Result = Main->CheckConnection(Connection, MySqlVersion);
	}
	__finally {
		Connection->Free();
	}

	if (Result) {
		MsgBox(Format(IDS_MSG_MYSQL_CONNECTION_OK, MySqlVersion));
	}
	else {
		MsgBoxErr(Format(IDS_ERROR_MYSQL_CONNECTION, MySqlVersion));
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBConnectionDefaultClick(TObject * Sender) {
	Settings->Connection->SetDefault();

	eDBHost->Text = Settings->Connection->Host;
	eDBPort->Text = Settings->Connection->Port;
	eDBUser->Text = Settings->Connection->User;
	eDBPass->Text = Settings->Connection->Password;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormCloseQuery(TObject *Sender, bool &CanClose) {
	UpdateSettings();

	if (!PerformSave) {
		if (Main->Settings->Equals(Settings)) {
			CanClose = true;
			ModalResult = mrCancel;
			return;
		}

		switch (MsgBox(LoadStr(IDS_QUESTION_SETTINGS_CHANGED),
			MB_ICONQUESTION | MB_YESNOCANCEL)) {
		case ID_YES:
			PerformSave = true;
			break;
		case ID_CANCEL:
			CanClose = false;
			break;
		default:
			CanClose = true;
			ModalResult = mrCancel;
		}
	}

	if (PerformSave) {
		PerformSave = false;

		CanClose = Settings->Save();

		if (CanClose) {
			ModalResult = mrOk;
		}
		else {
			MsgBoxErr(Format(IDS_ERROR_SETTINGS_SAVE, CFG_DIR_NAME));
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnOkClick(TObject *Sender) {
	PerformSave = true;
}

// ---------------------------------------------------------------------------
int TfrmOptions::SetUser(int Index, TUser *User) {
	if (Index < 0) {
		if (!StringGridIsEmpty(sgUsers)) {
			sgUsers->RowCount++;
		}
		Index = sgUsers->RowCount - 1;
	}

	sgUsers->Cells[COLUMN_USERS_NUM][Index] = IntToStr(Index);
	sgUsers->Cells[COLUMN_USERS_NAME][Index] = User->Name;
	sgUsers->Cells[COLUMN_USERS_IS_PASS][Index] = IsEmpty(User->Pass) ?
		"" : "###";
	sgUsers->Cells[COLUMN_USERS_TABNUM][Index] = User->TabNum;
	sgUsers->Cells[COLUMN_USERS_SHIFTNUM][Index] = User->ShiftNum;
	sgUsers->Cells[COLUMN_USERS_PASS][Index] = User->Pass;

	return Index;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersAddClick(TObject * Sender) {
	TUser *User = new TUser();
	User->Name = IntToStr(rand());

	if (TfrmOptionsUser::Show(this, User)) {
		sgUsers->Row = SetUser(-1, User);
	}

	User->Free();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersChangeClick(TObject * Sender) {
	TUser *User = new TUser();

	User->Name = sgUsers->Cells[COLUMN_USERS_NAME][sgUsers->Row];
	User->Pass = sgUsers->Cells[COLUMN_USERS_PASS][sgUsers->Row];
	User->TabNum = sgUsers->Cells[COLUMN_USERS_TABNUM][sgUsers->Row];
	User->ShiftNum = sgUsers->Cells[COLUMN_USERS_SHIFTNUM][sgUsers->Row];

	if (TfrmOptionsUser::Show(this, User)) {
		SetUser(sgUsers->Row, User);
	}

	User->Free();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersDeleteClick(TObject *Sender) {
	StringGridDeleteRow(sgUsers, sgUsers->Row, COLUMN_USERS_COUNT);

	if (!StringGridIsEmpty(sgUsers)) {
		StringGridUpdateOrderNum(sgUsers);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::sgUsersDblClick(TObject *Sender) {
	if (StringGridIsEmpty(sgUsers)) {
		btnUsersAdd->Click();
		return;
	}

	TPoint P = Mouse->CursorPos;
	P = sgUsers->ScreenToClient(P);

	int Col, Row;

	sgUsers->MouseToCell(P.X, P.Y, Col, Row);

	if (Col < 0 || Row < 0) {
		btnUsersAdd->Click();
	}
	else {
		btnUsersChange->Click();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::sgUsersFixedCellClick(TObject *Sender, int ACol,
	int ARow) {
	if (StringGridIsEmpty(sgUsers)) {
		return;
	}

	if (ARow < 1) {
		return;
	}

	sgUsers->Row = ARow;
}

// ---------------------------------------------------------------------------
