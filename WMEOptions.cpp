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
	static const USERS = 10;
	static const VANTYPES = 11;
	static const CARGOTYPES = 12;
} StringGrids;

// ---------------------------------------------------------------------------
struct {
	static const NUM = 0;
	static const USER_NAME = 1;
	static const HAS_PASS = 2;
	static const IS_ADMIN = 3;
	static const TABNUM = 4;
	static const SHIFTNUM = 5;
	static const PASS = 6;

	static const VISIBLE_COUNT = 6;

	static const COUNT = 7;
} UsersColumns;

// ---------------------------------------------------------------------------
struct {
	static const NUM = 0;
	static const CODE = 1;
	static const NAME = 2;
	static const AXIS_COUNT = 3;

	static const VISIBLE_COUNT = 4;

	static const COUNT = 4;
} VanTypesColumns;

// ---------------------------------------------------------------------------
struct {
	static const NUM = 0;
	static const CODE = 1;
	static const NAME = 2;

	static const VISIBLE_COUNT = 3;

	static const COUNT = 3;
} VanCatalogColumns;

// ---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptions::Show(TSettings *Settings, bool ReadOnly) {
	bool Result = false;

	TfrmOptions * frmOptions = new TfrmOptions(Application);
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

	sgUsers->Tag = StringGrids.USERS;
	btnUsersAdd->Tag = StringGrids.USERS;
	btnUsersChange->Tag = StringGrids.USERS;
	btnUsersDelete->Tag = StringGrids.USERS;

	sgVanTypes->Tag = StringGrids.VANTYPES;
	btnVanTypesAdd->Tag = StringGrids.VANTYPES;
	btnVanTypesChange->Tag = StringGrids.VANTYPES;
	btnVanTypesDelete->Tag = StringGrids.VANTYPES;

	sgCargoTypes->Tag = StringGrids.CARGOTYPES;
	btnCargoTypesAdd->Tag = StringGrids.CARGOTYPES;
	btnCargoTypesChange->Tag = StringGrids.CARGOTYPES;
	btnCargoTypesDelete->Tag = StringGrids.CARGOTYPES;

	CreateUsersColumns();
	CreateVanTypesColumns();
	CreateVanCatalogColumns(sgCargoTypes);

	PerformSave = false;

	Settings = new TSettings();

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
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
	StringGridSetHeader(sgUsers, UsersColumns.USER_NAME,
		IDS_GRID_HEADER_USER_NAME, 190);
	StringGridSetHeader(sgUsers, UsersColumns.HAS_PASS,
		IDS_GRID_HEADER_HAS_PASS, 70);
	StringGridSetHeader(sgUsers, UsersColumns.IS_ADMIN,
		IDS_GRID_HEADER_IS_ADMIN, 60);
	StringGridSetHeader(sgUsers, UsersColumns.TABNUM,
		IDS_GRID_HEADER_TABNUM, 100);
}

// ---------------------------------------------------------------------------
void TfrmOptions::CreateVanTypesColumns() {
	sgVanTypes->ColCount = VanTypesColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgVanTypes, VanTypesColumns.NUM,
		IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgVanTypes, VanTypesColumns.CODE,
		IDS_GRID_HEADER_CODE, 70);
	StringGridSetHeader(sgVanTypes, VanTypesColumns.NAME,
		IDS_GRID_HEADER_NAME, 190);
	StringGridSetHeader(sgVanTypes, VanTypesColumns.AXIS_COUNT,
		IDS_GRID_HEADER_AXIS_COUNT, 100);
}

// ---------------------------------------------------------------------------
void TfrmOptions::CreateVanCatalogColumns(TStringGrid * Grid) {
	Grid->ColCount = VanCatalogColumns.VISIBLE_COUNT;

	StringGridSetHeader(Grid, VanCatalogColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(Grid, VanCatalogColumns.CODE, IDS_GRID_HEADER_CODE, 70);
	StringGridSetHeader(Grid, VanCatalogColumns.NAME,
		IDS_GRID_HEADER_NAME, 190);
}

// ---------------------------------------------------------------------------
void TfrmOptions::SetReadOnly(TComponent *Parent, bool ReadOnly) {
	TWinControl * Child;

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

	// VanTypes
	for (int i = 0; i < Settings->VanTypeList->Count; i++) {
		SetVanType(-1, Settings->VanTypeList->Items[i]);
	}
	sgVanTypes->Row = 1;

	// CargoTypes
	for (int i = 0; i < Settings->CargoTypeList->Count; i++) {
		SetVanCatalog(sgCargoTypes, -1, Settings->CargoTypeList->Items[i]);
	}
	sgCargoTypes->Row = 1;
}

// ---------------------------------------------------------------------------
void TfrmOptions::UpdateSettingsVanCatalog(TStringGrid * Grid,
	TVanCatalogList * VanCatalogList) {
	VanCatalogList->Clear();

	if (!StringGridIsEmpty(Grid)) {
		TVanCatalog * VanCatalog;

		for (int i = 1; i < Grid->RowCount; i++) {
			VanCatalog = new TVanCatalog();

			VanCatalog->Code = StrToInt(Grid->Cells[VanCatalogColumns.CODE][i]);
			VanCatalog->Name = Grid->Cells[VanCatalogColumns.NAME][i];

			VanCatalogList->Add(VanCatalog);
		}
	}
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
		TUser * User;

		for (int i = 1; i < sgUsers->RowCount; i++) {
			User = new TUser();

			User->Name = sgUsers->Cells[UsersColumns.USER_NAME][i];
			User->Pass = sgUsers->Cells[UsersColumns.PASS][i];
			User->TabNum = sgUsers->Cells[UsersColumns.TABNUM][i];
			User->ShiftNum = sgUsers->Cells[UsersColumns.SHIFTNUM][i];

			User->IsAdmin = !IsEmpty(sgUsers->Cells[UsersColumns.IS_ADMIN][i]);

			Settings->UserList->Add(User);
		}
	}

	// VanTypes
	Settings->VanTypeList->Clear();

	if (!StringGridIsEmpty(sgVanTypes)) {
		TVanType * VanType;

		for (int i = 1; i < sgVanTypes->RowCount; i++) {
			VanType = new TVanType();

			VanType->Code =
				StrToInt(sgVanTypes->Cells[VanTypesColumns.CODE][i]);
			VanType->Name = sgVanTypes->Cells[VanTypesColumns.NAME][i];
			VanType->AxisCount =
				StrToInt(sgVanTypes->Cells[VanTypesColumns.AXIS_COUNT][i]);

			Settings->VanTypeList->Add(VanType);
		}
	}

	UpdateSettingsVanCatalog(sgCargoTypes, Settings->CargoTypeList);
}

// ---------------------------------------------------------------------------
TConnectionInfo * TfrmOptions::GetConnection() {
	TConnectionInfo * Connection = new TConnectionInfo();

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
		if (!MsgBoxYesNo(IDS_QUESTION_DB_CREATE)) {
			return;
		}
		break;
	case DB_ACTION_DROP:
		if (!MsgBoxYesNo(IDS_QUESTION_DB_DROP)) {
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
	TConnectionInfo * Connection = GetConnection();

	TDatabaseOperation * DatabaseOperation;

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
		MsgBox(ActionResultOK[Action]);
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

		switch (MsgBox(IDS_QUESTION_SETTINGS_CHANGED,
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

	User->Name = sgUsers->Cells[UsersColumns.USER_NAME][Index];
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
	sgUsers->Cells[UsersColumns.USER_NAME][Index] = User->Name;
	sgUsers->Cells[UsersColumns.HAS_PASS][Index] = IsEmpty(User->Pass) ?
		"" : "###";
	sgUsers->Cells[UsersColumns.IS_ADMIN][Index] = User->IsAdmin ? "��" : "";
	sgUsers->Cells[UsersColumns.TABNUM][Index] = User->TabNum;
	sgUsers->Cells[UsersColumns.SHIFTNUM][Index] = User->ShiftNum;
	sgUsers->Cells[UsersColumns.PASS][Index] = User->Pass;

	return Index;
}

// ---------------------------------------------------------------------------
TVanType * TfrmOptions::GetVanType(int Index) {
	TVanType * VanType = new TVanType();

	VanType->Code = StrToInt(sgVanTypes->Cells[VanTypesColumns.CODE][Index]);
	VanType->Name = sgVanTypes->Cells[VanTypesColumns.NAME][Index];
	VanType->AxisCount =
		StrToInt(sgVanTypes->Cells[VanTypesColumns.AXIS_COUNT][Index]);

	return VanType;
}

// ---------------------------------------------------------------------------
int TfrmOptions::SetVanType(int Index, TVanType * VanType) {
	if (Index < 0) {
		if (!StringGridIsEmpty(sgVanTypes)) {
			sgVanTypes->RowCount++;
		}
		Index = sgVanTypes->RowCount - 1;
	}

	sgVanTypes->Cells[VanTypesColumns.NUM][Index] = IntToStr(Index);
	sgVanTypes->Cells[VanTypesColumns.CODE][Index] = IntToStr(VanType->Code);
	sgVanTypes->Cells[VanTypesColumns.NAME][Index] = VanType->Name;
	sgVanTypes->Cells[VanTypesColumns.AXIS_COUNT][Index] =
		IntToStr(VanType->AxisCount);

	return Index;
}

// ---------------------------------------------------------------------------
TVanCatalog * TfrmOptions::GetVanCatalog(TStringGrid * Grid, int Index) {
	TVanCatalog * VanCatalog = new TVanCatalog();

	VanCatalog->Code = StrToInt(Grid->Cells[VanCatalogColumns.CODE][Index]);
	VanCatalog->Name = Grid->Cells[VanCatalogColumns.NAME][Index];

	return VanCatalog;
}

// ---------------------------------------------------------------------------
int TfrmOptions::SetVanCatalog(TStringGrid * Grid, int Index,
	TVanCatalog * VanCatalog) {
	if (Index < 0) {
		if (!StringGridIsEmpty(Grid)) {
			Grid->RowCount++;
		}
		Index = Grid->RowCount - 1;
	}

	Grid->Cells[VanCatalogColumns.NUM][Index] = IntToStr(Index);
	Grid->Cells[VanCatalogColumns.CODE][Index] = IntToStr(VanCatalog->Code);
	Grid->Cells[VanCatalogColumns.NAME][Index] = VanCatalog->Name;

	return Index;
}

// ---------------------------------------------------------------------------
bool TfrmOptions::IsUserAdmin(int Index) {
	return !IsEmpty(sgUsers->Cells[UsersColumns.IS_ADMIN][Index]);
}

// ---------------------------------------------------------------------------
TStringGrid* TfrmOptions::GetStringGrid(TObject *Sender) {
	switch (((TControl*)Sender)->Tag) {
	case StringGrids.USERS:
		return sgUsers;
	case StringGrids.VANTYPES:
		return sgVanTypes;
	case StringGrids.CARGOTYPES:
		return sgCargoTypes;
	default:
		throw Exception("GetStringGrid: unknown Sender (" + ((TControl*)Sender)
			->Name + ")");
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersAddClick(TObject * Sender) {
	TStringGrid *SG = GetStringGrid(Sender);

	TUser * User;
	TVanType * VanType;
	TVanCatalog * VanCatalog;

	switch (SG->Tag) {
	case StringGrids.USERS:
		User = new TUser();
		try {
#ifdef _DEBUG
			User->Name = "Name " + IntToStr(rand());
#endif

			if (TfrmOptionsUser::Show(this, User, AdminCount())) {
				sgUsers->Row = SetUser(-1, User);
			}
		}
		__finally {
			User->Free();
		}
		break;

	case StringGrids.VANTYPES:
		VanType = new TVanType();
		try {
#ifdef _DEBUG
			VanType->Code = rand();
			VanType->Name = "Name " + IntToStr(VanType->Code);
			VanType->AxisCount = random(3) + 1;
#endif
			sgVanTypes->Row = SetVanType(-1, VanType);

			// TODO
			// if (TfrmOptionsUser::Show(this, User, AdminCount())) {
			// sgVanTypes->Row = SetVanType(-1, VanCatalog);
			// }
		}
		__finally {
			VanType->Free();
		}
		break;

	case StringGrids.CARGOTYPES:
		VanCatalog = new TVanCatalog();
		try {
#ifdef _DEBUG
			VanCatalog->Code = rand();
			VanCatalog->Name = "Name " + IntToStr(VanCatalog->Code);
#endif
			SG->Row = SetVanCatalog(SG, -1, VanCatalog);
			// TODO
			// if (TfrmOptionsUser::Show(this, User, AdminCount())) {
			// sgVanTypes->Row = SetVanType(-1, VanCatalog);
			// }
		}
		__finally {
			VanCatalog->Free();
		}
		break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersChangeClick(TObject * Sender) {
	TStringGrid *SG = GetStringGrid(Sender);

	if (StringGridIsEmpty(SG)) {
		return;
	}

	TUser * User;
	TVanType * VanType;
	TVanCatalog * VanCatalog;

	switch (SG->Tag) {
	case StringGrids.USERS:
		User = GetUser(sgUsers->Row);
		try {
			if (TfrmOptionsUser::Show(this, User, AdminCount())) {
				SetUser(sgUsers->Row, User);
			}
		}
		__finally {
			User->Free();
		}
		break;

	case StringGrids.VANTYPES:
		VanType = GetVanType(sgVanTypes->Row);
		try {
			VanType->Code = VanType->Code + 1;
			SetVanType(sgVanTypes->Row, VanType);
		}
		__finally {
			VanType->Free();
		}
		break;

	case StringGrids.CARGOTYPES:
		VanCatalog = GetVanCatalog(SG, SG->Row);
		try {
			VanCatalog->Code = VanCatalog->Code + 1;
			SetVanCatalog(SG, SG->Row, VanCatalog);
		}
		__finally {
			VanCatalog->Free();
		}
		break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::btnUsersDeleteClick(TObject *Sender) {
	TStringGrid *SG = GetStringGrid(Sender);

	int ColumnCount;

	switch (SG->Tag) {
	case StringGrids.USERS:
		if (IsUserAdmin(sgUsers->Row) && (AdminCount() == 1)) {
			MsgBoxErr(IDS_ERROR_USERS_LAST_ADMIN);

			return;
		}

		ColumnCount = UsersColumns.COUNT;
		break;
	case StringGrids.VANTYPES:
		ColumnCount = VanTypesColumns.COUNT;
		break;
	case StringGrids.CARGOTYPES:
		ColumnCount = VanCatalogColumns.COUNT;
		break;
	}

	StringGridDeleteRow(SG, SG->Row, ColumnCount);

	if (!StringGridIsEmpty(SG)) {
		StringGridUpdateOrderNum(SG);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::sgUsersDblClick(TObject *Sender) {
	TStringGrid *SG = GetStringGrid(Sender);

	TButton * btnAdd;
	TButton * btnChange;

	switch (SG->Tag) {
	case StringGrids.USERS:
		btnAdd = btnUsersAdd;
		btnChange = btnUsersChange;
		break;
	case StringGrids.VANTYPES:
		btnAdd = btnVanTypesAdd;
		btnChange = btnVanTypesChange;
		break;
	case StringGrids.CARGOTYPES:
		btnAdd = btnCargoTypesAdd;
		btnChange = btnCargoTypesChange;
		break;
	}

	if (!btnAdd->Enabled) {
		return;
	}

	if (StringGridIsEmpty(SG)) {
		btnAdd->Click();
		return;
	}

	int Col, Row;

	StringGridMouseToCell(SG, Col, Row);

	if (Col < 0 || Row < 0) {
		btnAdd->Click();
	}
	else {
		btnChange->Click();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptions::sgUsersFixedCellClick(TObject *Sender, int ACol,
	int ARow) {
	if (ARow < 1) {
		return;
	}

	TStringGrid *SG = GetStringGrid(Sender);

	if (StringGridIsEmpty(SG)) {
		return;
	}

	SG->Row = ARow;
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
