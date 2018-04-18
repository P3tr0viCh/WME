// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEAdd.h"
#include "WMEStrings.h"
#include "WMEStringsGridHeader.h"

#include "WMEMain.h"

#include "WMETSettings.h"

#include "WMETDBDrop.h"
#include "WMETDBCheck.h"
#include "WMETDBCreate.h"

#include "WMEOptions.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
struct {
	static const NUM = 0;
	static const NAME = 1;
	static const HAS_PASS = 2;
	static const IS_ADMIN = 3;
	static const TABNUM = 4;
	static const SHIFTNUM = 5;
	static const PASS = 6;

	static const VISIBLE_COUNT = 6;

	static const COUNT = 7;
} UsersColumns;

// ---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptions::Show(TSettings *Settings, bool ReadOnly) {
	bool Result = false;

	TfrmOptions *frmOptions = new TfrmOptions(Application);
	try {
		frmOptions->IsReadOnly = ReadOnly;
		if (ReadOnly) {
			frmOptions->SetReadOnly(frmOptions, true);
		}
		frmOptions->btnCancel->Enabled = true;

		frmOptions->Settings->Assign(Settings);

		frmOptions->UpdateForm();

		Result = frmOptions->ShowModal() == mrOk;

		if (!ReadOnly && Result) {
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

	CreateUsersColumns();
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
void TfrmOptions::CreateUsersColumns() {
	sgUsers->ColCount = UsersColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgUsers, UsersColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgUsers, UsersColumns.NAME, IDS_GRID_HEADER_NAME, 190);
	StringGridSetHeader(sgUsers, UsersColumns.HAS_PASS,
		IDS_GRID_HEADER_HAS_PASS, 70);
	StringGridSetHeader(sgUsers, UsersColumns.IS_ADMIN,
		IDS_GRID_HEADER_IS_ADMIN, 60);
	StringGridSetHeader(sgUsers, UsersColumns.TABNUM,
		IDS_GRID_HEADER_TABNUM, 100);
	StringGridSetHeader(sgUsers, UsersColumns.SHIFTNUM,
		IDS_GRID_HEADER_SHIFTNUM, 60);
}

// ---------------------------------------------------------------------------
void TfrmOptions::SetReadOnly(TComponent *Parent, bool ReadOnly) {
	TWinControl *Child;

	for (int i = 0; i < ((TWinControl*)Parent)->ControlCount; i++) {
		try {
			Child = dynamic_cast<TWinControl*>
				(((TWinControl*)Parent)->Controls[i]);

			if (Child->ClassNameIs("TButton") || Child->ClassNameIs
				("TLabeledEdit")) {
				Child->Enabled = !ReadOnly;
			}
			else {
				SetReadOnly(Child, ReadOnly);
			}
		}
		catch (...) {
		}
	}
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

			User->Name = sgUsers->Cells[UsersColumns.NAME][i];
			User->Pass = sgUsers->Cells[UsersColumns.PASS][i];
			User->TabNum = sgUsers->Cells[UsersColumns.TABNUM][i];
			User->ShiftNum = sgUsers->Cells[UsersColumns.SHIFTNUM][i];

			User->IsAdmin = !IsEmpty(sgUsers->Cells[UsersColumns.IS_ADMIN][i]);

			Settings->UserList->Add(User);
		}
	}
}

// ---------------------------------------------------------------------------
TConnectionInfo* TfrmOptions::GetConnection() {
	TConnectionInfo *Connection = new TConnectionInfo();

	Connection->Host = eDBHost->Text;
	Connection->Port = eDBPort->Text;
	Connection->User = eDBUser->Text;
	Connection->Password = eDBPass->Text;

	return Connection;
}

// ---------------------------------------------------------------------------
void TfrmOptions::DatabaseAction(int Action) {
	switch (Action) {
	case DB_ACTION_CREATE:
		if (!MsgBoxYesNo(LoadStr(IDS_QUESTION_DB_CREATE))) {
			return;
		}
		break;
	case DB_ACTION_DROP:
		if (!MsgBoxYesNo(LoadStr(IDS_QUESTION_DB_DROP))) {
			return;
		}
		break;
	}

	bool Result = false;

	String MySqlVersion;

	int ActionResultOK[3] = {
		IDS_MSG_MYSQL_CONNECTION_OK, IDS_MSG_MYSQL_DB_CREATE_OK,
		IDS_MSG_MYSQL_DB_DROP_OK};
	int ActionResultFail[3] = {
		IDS_ERROR_MYSQL_CONNECTION, IDS_ERROR_MYSQL_DB_CREATE,
		IDS_ERROR_MYSQL_DB_DROP};

	ShowWaitCursor();
	TConnectionInfo *Connection = GetConnection();

	TDatabaseOperation *DatabaseOperation;

	try {
		switch (Action) {
		case DB_ACTION_CHECK:
			DatabaseOperation = new TDBCheck(Connection);

			break;
		case DB_ACTION_CREATE:
			DatabaseOperation = new TDBCreate(Connection);

			break;
		case DB_ACTION_DROP:
			DatabaseOperation = new TDBDrop(Connection);

			break;
		default:
			throw EActionError("DatabaseAction: unknown Action");
		}

		Result = DatabaseOperation->Execute();
	}
	__finally {
		DatabaseOperation->Free();
		Connection->Free();

		RestoreCursor();
	}

	if (Result) {
		MsgBox(LoadStr(ActionResultOK[Action]));
	}
	else {
		MsgBoxErr(ActionResultFail[Action]);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBConnectionCheckClick(TObject *Sender) {
	DatabaseAction(DB_ACTION_CHECK);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBCreateClick(TObject *Sender) {
	DatabaseAction(DB_ACTION_CREATE);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnDBDeleteClick(TObject *Sender) {
	DatabaseAction(DB_ACTION_DROP);
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
	if (IsReadOnly) {
		CanClose = true;
		return;
	}

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
TUser* TfrmOptions::GetUser(int Index) {
	TUser *User = new TUser();

	User->Name = sgUsers->Cells[UsersColumns.NAME][Index];
	User->Pass = sgUsers->Cells[UsersColumns.PASS][Index];
	User->TabNum = sgUsers->Cells[UsersColumns.TABNUM][Index];
	User->ShiftNum = sgUsers->Cells[UsersColumns.SHIFTNUM][Index];

	User->IsAdmin = IsUserAdmin(Index);

	return User;
}

// ---------------------------------------------------------------------------
int TfrmOptions::SetUser(int Index, TUser *User) {
	if (Index < 0) {
		if (!StringGridIsEmpty(sgUsers)) {
			sgUsers->RowCount++;
		}
		Index = sgUsers->RowCount - 1;
	}

	sgUsers->Cells[UsersColumns.NUM][Index] = IntToStr(Index);
	sgUsers->Cells[UsersColumns.NAME][Index] = User->Name;
	sgUsers->Cells[UsersColumns.HAS_PASS][Index] = IsEmpty(User->Pass) ?
		"" : "###";
	sgUsers->Cells[UsersColumns.IS_ADMIN][Index] = User->IsAdmin ? "Да" : "";
	sgUsers->Cells[UsersColumns.TABNUM][Index] = User->TabNum;
	sgUsers->Cells[UsersColumns.SHIFTNUM][Index] = User->ShiftNum;
	sgUsers->Cells[UsersColumns.PASS][Index] = User->Pass;

	return Index;
}

// ---------------------------------------------------------------------------
bool TfrmOptions::IsUserAdmin(int Index) {
	return !IsEmpty(sgUsers->Cells[UsersColumns.IS_ADMIN][Index]);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersAddClick(TObject * Sender) {
	TUser *User = new TUser();
#ifdef _DEBUG
	User->Name = "Name " + IntToStr(rand());
#endif

	if (TfrmOptionsUser::Show(this, User, AdminCount())) {
		sgUsers->Row = SetUser(-1, User);
	}

	User->Free();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersChangeClick(TObject * Sender) {
	TUser *User = GetUser(sgUsers->Row);

	if (TfrmOptionsUser::Show(this, User, AdminCount())) {
		SetUser(sgUsers->Row, User);
	}

	User->Free();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersDeleteClick(TObject *Sender) {
	if (IsUserAdmin(sgUsers->Row) && (AdminCount() == 1)) {
		MsgBoxErr(IDS_ERROR_USERS_LAST_ADMIN);

		return;
	}

	StringGridDeleteRow(sgUsers, sgUsers->Row, UsersColumns.COUNT);

	StringGridUpdateOrderNum(sgUsers);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::sgUsersDblClick(TObject *Sender) {
	if (!btnUsersAdd->Enabled) {
		return;
	}

	if (StringGridIsEmpty(sgUsers)) {
		btnUsersAdd->Click();
		return;
	}

	int Col, Row;

	StringGridMouseToCell(sgUsers, Col, Row);

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
	if (ARow < 1) {
		return;
	}

	if (StringGridIsEmpty(sgUsers)) {
		return;
	}

	sgUsers->Row = ARow;
}

// ---------------------------------------------------------------------------
int TfrmOptions::AdminCount() {
	int Count = 0;

	for (int i = 1; i < sgUsers->RowCount; i++) {
		if (IsUserAdmin(i)) {
			Count++;
		}
	}

	return Count;
}

// ---------------------------------------------------------------------------
