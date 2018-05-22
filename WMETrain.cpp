// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"
#include "WMEStringsGridHeader.h"

#include "WMETDBSaveTrain.h"

#include "WMEMain.h"
#include "WMEService.h"

#include "WMETrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
class TVansColumns {
public:
	static const NUM = 0;
	static const DATETIME = 1;
	static const WEIGHTTYPE = 2;
	static const VANNUM = 3;
	static const VANTYPE = 4;
	static const CARRYING = 5;
	static const BRUTTO = 6;
	static const TARE = 7;
	static const TARE_T = 8;
	static const TARE_D = 9;
	static const TARE_S = 10;
	static const TARE_INDEX = 11;
	static const NETTO = 12;
	static const OVERLOAD = 13;
	static const CARGOTYPE = 14;
	static const DEPART_STATION = 15;
	static const PURPOSE_STATION = 16;
	static const INVOICE_NUM = 17;
	static const INVOICE_SUPPLIER = 18;
	static const INVOICE_RECIPIENT = 19;

	static const WEIGHTTYPE_AS_INT = 20;
	static const TARE_INDEX_AS_INT = 21;

	static const VISIBLE_COUNT = 21;

	static const COUNT = 22;

	TVansColumns() {
		ReadOnly = TIntegerSet() << NUM << TARE << TARE_D << TARE_S << NETTO <<
			OVERLOAD;
		ComboBox = TIntegerSet() << WEIGHTTYPE << VANTYPE << TARE_INDEX <<
			CARGOTYPE << DEPART_STATION << PURPOSE_STATION <<
			INVOICE_SUPPLIER << INVOICE_RECIPIENT;
		LeftAlign =
			TIntegerSet() << DATETIME << WEIGHTTYPE << VANNUM << VANTYPE <<
			TARE_INDEX << CARGOTYPE << DEPART_STATION << PURPOSE_STATION <<
			INVOICE_NUM << INVOICE_SUPPLIER << INVOICE_RECIPIENT;
	}

	TIntegerSet ReadOnly;

	TIntegerSet ComboBox;

	TIntegerSet LeftAlign;
};

static TVansColumns VansColumns;

// ---------------------------------------------------------------------------
class TTrainColumns {
public:
	static const VANCOUNT = 0;
	static const DATETIME = 1;
	static const CARRYING = 2;
	static const BRUTTO = 3;
	static const TARE = 4;
	static const NETTO = 5;
	static const OVERLOAD = 6;

	static const VISIBLE_COUNT = 7;

	static const COUNT = 7;

	TTrainColumns() {
		LeftAlign = TIntegerSet() << DATETIME;
	}

	TIntegerSet LeftAlign;
};

static TTrainColumns TrainColumns;

// ---------------------------------------------------------------------------
__fastcall TfrmTrain::TfrmTrain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmTrain::Show(TTrain *Train) {
	bool Result = false;

	TfrmTrain * frmTrain = new TfrmTrain(Application);
	try {
		frmTrain->Train = Train;

		frmTrain->UpdateVans(Train);

		frmTrain->Changed = false;

		Result = frmTrain->ShowModal() == mrOk;
	}
	__finally {
		delete frmTrain;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	CreateVansColumns();
	CreateTrainColumns();

	WeightTypeList = new TVanCatalogList();
	WeightTypeList->Add(new TVanCatalog(wtBrutto, IDS_TXT_WEIGHT_TYPE_BRUTTO));
	WeightTypeList->Add(new TVanCatalog(wtTare, IDS_TXT_WEIGHT_TYPE_TARE));

	TareIndexList = new TVanCatalogList();
	TareIndexList->Add(new TVanCatalog(tiTrafaret, IDS_TXT_TARE_TRAFARET));
	TareIndexList->Add(new TVanCatalog(tiDynamic, IDS_TXT_TARE_DYNAMIC));
	TareIndexList->Add(new TVanCatalog(tiStatic, IDS_TXT_TARE_STATIC));

	sgVans->DefaultRowHeight = Main->DefaultRowHeight; // >> ComboBox->Height;
	sgTrain->DefaultRowHeight = Main->DefaultRowHeight;
	sgTrain->Height = (sgTrain->GridHeight + 2);

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	if (Main->User->IsAdmin) {
		sgVans->Options = sgVans->Options << goColSizing;
		sgTrain->Options = sgTrain->Options << goColSizing;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	TareIndexList->Free();

	WeightTypeList->Free();

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateVansColumns() {
	sgVans->ColCount = VansColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgVans, VansColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgVans, VansColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);

	StringGridSetHeader(sgVans, VansColumns.WEIGHTTYPE,
		IDS_GRID_HEADER_WEIGHTTYPE, 110);

	StringGridSetHeader(sgVans, VansColumns.VANNUM, IDS_GRID_HEADER_VANNUM, 80);
	StringGridSetHeader(sgVans, VansColumns.VANTYPE,
		IDS_GRID_HEADER_VANTYPE, 120);

	StringGridSetHeader(sgVans, VansColumns.CARRYING,
		IDS_GRID_HEADER_CARRYING, 50);
	StringGridSetHeader(sgVans, VansColumns.BRUTTO, IDS_GRID_HEADER_BRUTTO, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE, IDS_GRID_HEADER_TARE, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_T,
		IDS_GRID_HEADER_TARE_TRAFARET, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_D,
		IDS_GRID_HEADER_TARE_DYNAMIC, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_S,
		IDS_GRID_HEADER_TARE_STATIC, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_INDEX,
		IDS_GRID_HEADER_TARE_INDEX, 80);
	StringGridSetHeader(sgVans, VansColumns.NETTO, IDS_GRID_HEADER_NETTO, 60);
	StringGridSetHeader(sgVans, VansColumns.OVERLOAD,
		IDS_GRID_HEADER_OVERLOAD, 80);

	StringGridSetHeader(sgVans, VansColumns.CARGOTYPE,
		IDS_GRID_HEADER_CARGOTYPE, 120);
	StringGridSetHeader(sgVans, VansColumns.DEPART_STATION,
		IDS_GRID_HEADER_DEPART_STATION, 180);
	StringGridSetHeader(sgVans, VansColumns.PURPOSE_STATION,
		IDS_GRID_HEADER_PURPOSE_STATION, 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_NUM,
		IDS_GRID_HEADER_INVOICE_NUM, 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_SUPPLIER,
		IDS_GRID_HEADER_INVOICE_SUPPLIER, 180);
	StringGridSetHeader(sgVans, VansColumns.INVOICE_RECIPIENT,
		IDS_GRID_HEADER_INVOICE_RECIPIENT, 180);
}

// ---------------------------------------------------------------------------
void TfrmTrain::CreateTrainColumns() {
	sgTrain->ColCount = TrainColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgTrain, TrainColumns.VANCOUNT,
		IDS_GRID_HEADER_VANCOUNT, 120);
	StringGridSetHeader(sgTrain, TrainColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);
	StringGridSetHeader(sgTrain, TrainColumns.CARRYING,
		IDS_GRID_HEADER_CARRYING, 90);
	StringGridSetHeader(sgTrain, TrainColumns.BRUTTO,
		IDS_GRID_HEADER_BRUTTO, 90);
	StringGridSetHeader(sgTrain, TrainColumns.TARE, IDS_GRID_HEADER_TARE, 90);
	StringGridSetHeader(sgTrain, TrainColumns.NETTO, IDS_GRID_HEADER_NETTO, 90);
	StringGridSetHeader(sgTrain, TrainColumns.OVERLOAD,
		IDS_GRID_HEADER_OVERLOAD, 90);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void TfrmTrain::CalcFields(int ARow) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	if (ARow == -1) {
		for (int i = 1; i < sgVans->RowCount; i++) {
			CalcFields(i);
		}
		return;
	}

	float Carrying =
		StrToFloatDef(sgVans->Cells[VansColumns.CARRYING][ARow], 0);
	float Brutto = StrToFloatDef(sgVans->Cells[VansColumns.BRUTTO][ARow], 0);

	int TareIndex =
		StrToInt(sgVans->Cells[VansColumns.TARE_INDEX_AS_INT][ARow]);
	int TareCol;

	switch (TareIndex) {
	case tiDynamic:
		TareCol = VansColumns.TARE_D;
		break;
	case tiStatic:
		TareCol = VansColumns.TARE_S;
		break;
	case tiTrafaret:
	default:
		TareCol = VansColumns.TARE_T;
	}

	float Tare = StrToFloatDef(sgVans->Cells[TareCol][ARow], 0);

	sgVans->Cells[VansColumns.TARE][ARow] = FloatToStr(Tare);

	float Netto = 0;
	float Overload = 0;

	if (Brutto > 0 && Tare > 0) {
		Netto = Brutto - Tare;
	}
	if (Carrying > 0 && Netto > 0) {
		Overload = Netto - Carrying;
	}

	sgVans->Cells[VansColumns.NETTO][ARow] = FloatToStr(Netto);
	sgVans->Cells[VansColumns.OVERLOAD][ARow] = FloatToStr(Overload);
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateTrainCell(int ACol, float Value) {
	sgTrain->Cells[ACol][1] = FloatToStr(Value);
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateTrain() {
	if (StringGridIsEmpty(sgVans)) {
		sgTrain->Rows[1]->Clear();

		return;
	}

	sgTrain->Cells[TrainColumns.VANCOUNT][1] = IntToStr(sgVans->RowCount - 1);

	if (IsEmpty(sgTrain->Cells[TrainColumns.DATETIME][1])) {
		sgTrain->Cells[TrainColumns.DATETIME][1] = DateTimeToStr(Now());
	}

	float Carrying = 0;
	float Brutto = 0;
	float Tare = 0;
	float Netto = 0;
	float Overload = 0;

	for (int i = 1; i < sgVans->RowCount; i++) {
		Carrying += StrToFloatDef(sgVans->Cells[VansColumns.CARRYING][i], 0);
		Brutto += StrToFloatDef(sgVans->Cells[VansColumns.BRUTTO][i], 0);
		Tare += StrToFloatDef(sgVans->Cells[VansColumns.TARE][i], 0);
		Netto += StrToFloatDef(sgVans->Cells[VansColumns.NETTO][i], 0);
		Overload += StrToFloatDef(sgVans->Cells[VansColumns.OVERLOAD][i], 0);
	}

	UpdateTrainCell(TrainColumns.CARRYING, Carrying);
	UpdateTrainCell(TrainColumns.BRUTTO, Brutto);
	UpdateTrainCell(TrainColumns.TARE, Tare);
	UpdateTrainCell(TrainColumns.NETTO, Netto);
	UpdateTrainCell(TrainColumns.OVERLOAD, Overload);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnAddClick(TObject *Sender) {
	if (!StringGridIsEmpty(sgVans)) {
		sgVans->RowCount++;
	}

	int Row = sgVans->RowCount - 1;

	sgVans->Cells[VansColumns.DATETIME][Row] = DateTimeToStr(Now());

	// TODO: enum mb != 0,1...
	int WeightType = DEFAULT_WEIGHTTYPE;
	sgVans->Cells[VansColumns.WEIGHTTYPE_AS_INT][Row] = IntToStr(WeightType);
	sgVans->Cells[VansColumns.WEIGHTTYPE][Row] =
		WeightTypeList->Items[WeightType]->Name;

	int TareIndex = DEFAULT_TARE_INDEX;
	sgVans->Cells[VansColumns.TARE_INDEX_AS_INT][Row] = IntToStr(TareIndex);
	sgVans->Cells[VansColumns.TARE_INDEX][Row] =
		TareIndexList->Items[TareIndex]->Name;

	sgVans->Row = Row;

	StringGridUpdateOrderNum(sgVans);

	CalcFields();
	UpdateTrain();

	Changed = true;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnDeleteClick(TObject *Sender) {
	StringGridDeleteRow(sgVans, sgVans->Row, VansColumns.COUNT);

	if (!StringGridIsEmpty(sgVans)) {
		StringGridUpdateOrderNum(sgVans);
	}

	UpdateTrain();

	Changed = true;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansSelectCell(TObject *Sender, int ACol, int ARow,
	bool &CanSelect) {
	if (StringGridIsEmpty(sgVans)) {
		sgVans->Options = sgVans->Options >> goEditing;
		return;
	}

	if (VansColumns.ReadOnly.Contains(ACol) || VansColumns.ComboBox.Contains
		(ACol)) {
		sgVans->Options = sgVans->Options >> goEditing;
	}
	else {
		sgVans->Options = sgVans->Options << goEditing;
	}

	CalcFields();
	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansGetEditText(TObject *Sender, int ACol,
	int ARow, UnicodeString & Value) {
	CellValue = Value;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansSetEditText(TObject *Sender, int ACol,
	int ARow, const UnicodeString Value) {
	if (AnsiSameStr(CellValue, Value)) {
		return;
	}

	Changed = true;
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateVanComboBox(TVanCatalogList *VanCatalogList) {
	ComboBox->Items->Clear();

	for (int i = 0; i < VanCatalogList->Count; i++) {
		ComboBox->Items->Add(VanCatalogList->Items[i]->Name);
	}
}

// ---------------------------------------------------------------------------
bool TfrmTrain::ShowVanComboBox(int Col) {
	switch (Col) {
	case VansColumns.WEIGHTTYPE:
		UpdateVanComboBox(WeightTypeList);
		break;
	case VansColumns.VANTYPE:
		UpdateVanComboBox((TVanCatalogList *)Main->Settings->VanTypeList);
		break;
	case VansColumns.TARE_INDEX:
		UpdateVanComboBox(TareIndexList);
		break;
	case VansColumns.CARGOTYPE:
		UpdateVanComboBox(Main->Settings->CargoTypeList);
		break;
	case VansColumns.DEPART_STATION:
		UpdateVanComboBox(Main->Settings->DepartStationList);
		break;
	case VansColumns.PURPOSE_STATION:
		UpdateVanComboBox(Main->Settings->PurposeStationList);
		break;
	case VansColumns.INVOICE_RECIPIENT:
		UpdateVanComboBox(Main->Settings->InvoiceRecipientList);
		break;
	case VansColumns.INVOICE_SUPPLIER:
		UpdateVanComboBox(Main->Settings->InvoiceSupplierList);
		break;
	default:
		return false;
	}

	TRect Rect = sgVans->CellRect(sgVans->Col, sgVans->Row);

	ComboBox->SetBounds(sgVans->Left + Rect.Left + sgVans->GridLineWidth + 1,
		sgVans->Top + Rect.Top + sgVans->GridLineWidth + 1,
		sgVans->ColWidths[sgVans->Col], sgVans->DefaultRowHeight);

	switch (Col) {
	case VansColumns.WEIGHTTYPE:
	case VansColumns.TARE_INDEX:
		ComboBox->Style = csDropDownList;
		break;
	default:
		ComboBox->Style = csDropDown;
	}

	ComboBox->Visible = true;
	ComboBox->SetFocus();

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	if (Shift.Empty() && (Key == VK_RETURN || Key == VK_F2)) {
		if (ShowVanComboBox(sgVans->Col)) {
			return;
		}
	}

	if (Shift.Empty() && Key == VK_ESCAPE) {
		if (sgVans->EditorMode) {
			sgVans->EditorMode = false;

			sgVans->Cells[sgVans->Col][sgVans->Row] = CellValue;

			return;
		}
	}

	if (Shift == (TShiftState() << ssAlt)) {
		switch (Key) {
		case VK_UP:
		case VK_DOWN:
			bool Cond;
			int Inc;

			if (Key == VK_UP) {
				Cond = sgVans->Row > 1;
				Inc = -1;
			}
			else {
				Cond = sgVans->Row < sgVans->RowCount - 1;
				Inc = +1;
			}

			if (Cond) {
				sgVans->Cells[sgVans->Col][sgVans->Row + Inc] =
					sgVans->Cells[sgVans->Col][sgVans->Row];

				int HiddenColumn = -1;
				switch (sgVans->Col) {
				case VansColumns.WEIGHTTYPE:
					HiddenColumn = VansColumns.WEIGHTTYPE_AS_INT;
					break;
				case VansColumns.TARE_INDEX:
					HiddenColumn = VansColumns.TARE_INDEX_AS_INT;
					break;
				}

				if (HiddenColumn > 0) {
					sgVans->Cells[HiddenColumn][sgVans->Row + Inc] =
						sgVans->Cells[HiddenColumn][sgVans->Row];
				}

				Changed = true;
			}
			break;
		}

		return;
	}

	if (Key == VK_RETURN) {
		CalcFields();
		UpdateTrain();
	}
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateValue(int ACol, int ARow) {
	if (IsEmpty(sgVans->Cells[ACol][ARow])) {
		sgVans->Cells[ACol][ARow] = "0";
	}
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateValues(int ARow) {
	if (ARow == -1) {
		for (int i = 1; i < sgVans->RowCount; i++) {
			UpdateValues(i);
		}
		return;
	}

	UpdateValue(VansColumns.CARRYING, ARow);
	UpdateValue(VansColumns.BRUTTO, ARow);
	UpdateValue(VansColumns.TARE_T, ARow);
	UpdateValue(VansColumns.TARE_D, ARow);
	UpdateValue(VansColumns.TARE_S, ARow);

	CalcFields(ARow);
}

// ---------------------------------------------------------------------------
void TfrmTrain::SetChanged(bool Value) {
	FChanged = Value;

	ComboBox->Visible = false;

	UpdateButtons();
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateButtons() {
	tbtnDelete->Enabled = !StringGridIsEmpty(sgVans);

	tbtnService->Enabled = tbtnDelete->Enabled;

	if (!tbtnDelete->Enabled) {
		sgVans->Options = sgVans->Options >> goEditing;
	}

	tbtnSave->Enabled = tbtnDelete->Enabled && Changed;
}

// ---------------------------------------------------------------------------
void TfrmTrain::CheckValue(int ACol, int ARow, int MaxLength) {
	sgVans->Cells[ACol][ARow] = CheckStrValue(sgVans->Cells[ACol][ARow],
		MaxLength);
}

// ---------------------------------------------------------------------------
bool TfrmTrain::CheckValues(int ARow) {
	if (ARow == -1) {
		bool Result = true;

		for (int i = 1; i < sgVans->RowCount; i++) {
			if (!CheckValues(i)) {
				Result = false;
			}
		}

		return Result;
	}

	CheckValue(VansColumns.VANNUM, ARow, 8);
	CheckValue(VansColumns.VANTYPE, ARow, 32);
	CheckValue(VansColumns.CARGOTYPE, ARow, 32);
	CheckValue(VansColumns.DEPART_STATION, ARow, 32);
	CheckValue(VansColumns.PURPOSE_STATION, ARow, 32);
	CheckValue(VansColumns.INVOICE_NUM, ARow, 16);
	CheckValue(VansColumns.INVOICE_SUPPLIER, ARow, 32);
	CheckValue(VansColumns.INVOICE_RECIPIENT, ARow, 32);

	if (!CheckDateTimeValue(sgVans->Cells[VansColumns.DATETIME][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.DATETIME, ARow);
		return false;
	}

	if (!CheckIntValue(sgVans->Cells[VansColumns.CARRYING][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.CARRYING, ARow);
		return false;
	}
	if (!CheckIntValue(sgVans->Cells[VansColumns.BRUTTO][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.BRUTTO, ARow);
		return false;
	}
	if (!CheckIntValue(sgVans->Cells[VansColumns.TARE_T][ARow])) {
		StringGridSelectCell(sgVans, VansColumns.TARE_T, ARow);
		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
bool TfrmTrain::CheckVanNums() {
	String VanNum1;
	String VanNum2;

	for (int i = 1; i < sgVans->RowCount; i++) {
		VanNum1 = sgVans->Cells[VansColumns.VANNUM][i];

		if (IsEmpty(VanNum1)) {
			continue;
		}

		for (int j = i + 1; j < sgVans->RowCount; j++) {
			VanNum2 = sgVans->Cells[VansColumns.VANNUM][j];

			if (IsEmpty(VanNum2)) {
				continue;
			}

			if (AnsiSameStr(VanNum1, VanNum2)) {
				StringGridSelectCell(sgVans, VansColumns.VANNUM, j);

				return false;
			}
		}
	}

	return true;
}

// ---------------------------------------------------------------------------
bool TfrmTrain::CheckVanList() {
	if (StringGridIsEmpty(sgVans)) {
		MsgBoxErr(IDS_ERROR_NOTHING_SAVE);
		WriteToLog(IDS_LOG_NOTHING_SAVE);
		return false;
	}

	UpdateValues();

	if (!CheckValues()) {
		MsgBoxErr(IDS_ERROR_BAD_VALUES);
		WriteToLog(IDS_LOG_BAD_VALUES);
		return false;
	}

	if (!CheckVanNums()) {
		MsgBoxErr(IDS_ERROR_BAD_VANNUMS);
		WriteToLog(IDS_LOG_BAD_VANNUMS);
		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
int TfrmTrain::GetVanCatalogCode(int CatalogIdent, String Name) {
	TVanCatalogList * VanCatalogList;

	switch (CatalogIdent) {
	case VansColumns.WEIGHTTYPE:
		VanCatalogList = WeightTypeList;
		break;
	case VansColumns.VANTYPE:
		VanCatalogList = (TVanCatalogList*)Main->Settings->VanTypeList;
		break;
	case VansColumns.TARE_INDEX:
		VanCatalogList = TareIndexList;
		break;
	case VansColumns.CARGOTYPE:
		VanCatalogList = Main->Settings->CargoTypeList;
		break;
	case VansColumns.DEPART_STATION:
		VanCatalogList = Main->Settings->DepartStationList;
		break;
	case VansColumns.PURPOSE_STATION:
		VanCatalogList = Main->Settings->PurposeStationList;
		break;
	case VansColumns.INVOICE_RECIPIENT:
		VanCatalogList = Main->Settings->InvoiceRecipientList;
		break;
	case VansColumns.INVOICE_SUPPLIER:
		VanCatalogList = Main->Settings->InvoiceSupplierList;
		break;
	default:
		return VAN_CATALOG_CODE_NONE;
	}

	for (int i = 0; i < VanCatalogList->Count; i++) {
		if (AnsiSameStr(VanCatalogList->Items[i]->Name, Name)) {
			return VanCatalogList->Items[i]->Code;
		}
	}

	return VAN_CATALOG_CODE_NONE;
}

// ---------------------------------------------------------------------------
TVanType * TfrmTrain::GetVanType(String Name) {
	for (int i = 0; i < Main->Settings->VanTypeList->Count; i++) {
		if (AnsiSameStr(Main->Settings->VanTypeList->Items[i]->Name, Name)) {
			return Main->Settings->VanTypeList->Items[i];
		}
	}

	TVanType * VanType = new TVanType();
	VanType->Name = Name;

	return VanType;
}

// ---------------------------------------------------------------------------
TVanList * TfrmTrain::GetVanList() {
	TVanList * VanList = new TVanList();

	if (StringGridIsEmpty(sgVans)) {
		return VanList;
	}

	TVan * Van;

	for (int i = 1; i < sgVans->RowCount; i++) {
		Van = new TVan();

		Van->Num = i;

		Van->DateTime = StrToDateTime(sgVans->Cells[VansColumns.DATETIME][i]);

		Van->WeightType =
			(TWeightType)StrToInt
			(sgVans->Cells[VansColumns.WEIGHTTYPE_AS_INT][i]);

		Van->VanNum = sgVans->Cells[VansColumns.VANNUM][i];

		Van->VanType->Assign(GetVanType(sgVans->Cells[VansColumns.VANTYPE][i]));

		Van->Carrying = StrToInt(sgVans->Cells[VansColumns.CARRYING][i]);
		Van->Brutto = StrToInt(sgVans->Cells[VansColumns.BRUTTO][i]);

		Van->TareTrft = StrToInt(sgVans->Cells[VansColumns.TARE_T][i]);
		Van->TareDyn = StrToInt(sgVans->Cells[VansColumns.TARE_D][i]);
		Van->TareSta = StrToInt(sgVans->Cells[VansColumns.TARE_S][i]);

		Van->TareIndex =
			(TTareIndex) StrToInt
			(sgVans->Cells[VansColumns.TARE_INDEX_AS_INT][i]);

		Van->CargoType->Name = sgVans->Cells[VansColumns.CARGOTYPE][i];
		Van->CargoType->Code = GetVanCatalogCode(VansColumns.CARGOTYPE,
			Van->CargoType->Name);

		Van->User = Main->User;

		Van->DepartStation->Name = sgVans->Cells[VansColumns.DEPART_STATION][i];
		Van->DepartStation->Code = GetVanCatalogCode(VansColumns.DEPART_STATION,
			Van->DepartStation->Name);

		Van->PurposeStation->Name =
			sgVans->Cells[VansColumns.PURPOSE_STATION][i];
		Van->PurposeStation->Code =
			GetVanCatalogCode(VansColumns.PURPOSE_STATION,
			Van->PurposeStation->Name);

		Van->InvoiceNum = sgVans->Cells[VansColumns.INVOICE_NUM][i];

		Van->InvoiceSupplier->Name =
			sgVans->Cells[VansColumns.INVOICE_SUPPLIER][i];
		Van->InvoiceSupplier->Code =
			GetVanCatalogCode(VansColumns.INVOICE_SUPPLIER,
			Van->InvoiceSupplier->Name);

		Van->InvoiceRecipient->Name =
			sgVans->Cells[VansColumns.INVOICE_RECIPIENT][i];
		Van->InvoiceRecipient->Code =
			GetVanCatalogCode(VansColumns.INVOICE_RECIPIENT,
			Van->InvoiceRecipient->Name);

		VanList->Add(Van);
	}

	return VanList;
}

// ---------------------------------------------------------------------------
TTrain * TfrmTrain::GetTrain(int TrainNum) {
	TTrain * Train = new TTrain(GetVanList());

	Train->TrainNum = TrainNum;

	Train->DateTime = Train->VanList->Items[0]->DateTime;
	Train->UnixTime = DateTimeToWTime(Train->DateTime);

	int WeightTypeBrutto = 0;
	int WeightTypeTare = 0;

	int Carrying = 0;
	int Brutto = 0;
	int Tare = 0;

	for (int i = 0; i < Train->VanList->Count; i++) {
		switch (Train->VanList->Items[i]->WeightType) {
		case wtBrutto:
			WeightTypeBrutto++;
			break;
		case wtTare:
			WeightTypeTare++;
			break;
		}

		Carrying += Train->VanList->Items[i]->Carrying;
		Brutto += Train->VanList->Items[i]->Brutto;
		Tare += Train->VanList->Items[i]->Tare;
	}

	if (WeightTypeBrutto > 0 && WeightTypeTare > 0) {
		Train->WeightType = wtMixed;
	}
	else {
		if (WeightTypeBrutto > 0) {
			Train->WeightType = wtBrutto;
		}
		else {
			Train->WeightType = wtTare;
		}
	}

	Train->Carrying = Carrying;
	Train->Brutto = Brutto;
	Train->Tare = Tare;

	if (Train->Brutto > 0 && Train->Tare > 0) {
		Train->Netto = Train->Brutto - Train->Tare;
	}
	else {
		Train->Netto = 0;
	}

	if (Train->Carrying > 0 && Train->Netto > 0) {
		Train->Overload = Train->Netto - Train->Carrying;
	}
	else {
		Train->Overload = 0;
	}

	Train->VanCount = Train->VanList->Count;

	Train->User = Main->User;

	return Train;
}

// ---------------------------------------------------------------------------
bool TfrmTrain::SaveVans() {
	bool Result = false;

	TTrain * TempTrain = GetTrain(Train->TrainNum);

	ShowWaitCursor();

	TDBSaveTrain * DBSaveTrain =
		new TDBSaveTrain(Main->Settings->LocalConnection, TempTrain);
	try {
		Result = DBSaveTrain->Execute();

		Train->Assign(TempTrain);
	}
	__finally {
		DBSaveTrain->Free();
		TempTrain->Free();

		RestoreCursor();
	}

	if (!Result) {
		MsgBoxErr(IDS_ERROR_TRAIN_SAVE);
	}

	return Result;
}

// ---------------------------------------------------------------------------
int TfrmTrain::SetVan(int Index, TVan * Van) {
	if (Index < 0) {
		if (!StringGridIsEmpty(sgVans)) {
			sgVans->RowCount++;
		}
		Index = sgVans->RowCount - 1;
	}

	sgVans->Cells[VansColumns.NUM][Index] = IntToStr(Van->Num);
	sgVans->Cells[VansColumns.DATETIME][Index] = DateTimeToStr(Van->DateTime);

	sgVans->Cells[VansColumns.WEIGHTTYPE_AS_INT][Index] =
		IntToStr(Van->WeightType);
	sgVans->Cells[VansColumns.WEIGHTTYPE][Index] =
		Main->GetWeightTypeAsText(Van->WeightType);

	sgVans->Cells[VansColumns.VANNUM][Index] = Van->VanNum;

	sgVans->Cells[VansColumns.VANTYPE][Index] = Van->VanType->Name;

	sgVans->Cells[VansColumns.CARRYING][Index] = IntToStr(Van->Carrying);
	sgVans->Cells[VansColumns.BRUTTO][Index] = IntToStr(Van->Brutto);
	sgVans->Cells[VansColumns.TARE][Index] = IntToStr(Van->Tare);
	sgVans->Cells[VansColumns.TARE_T][Index] = IntToStr(Van->TareTrft);
	sgVans->Cells[VansColumns.TARE_S][Index] = IntToStr(Van->TareSta);
	sgVans->Cells[VansColumns.TARE_D][Index] = IntToStr(Van->TareDyn);

	sgVans->Cells[VansColumns.TARE_INDEX_AS_INT][Index] =
		IntToStr(Van->TareIndex);
	sgVans->Cells[VansColumns.TARE_INDEX][Index] =
		Main->GetTareIndexAsText(Van->TareIndex);

	sgVans->Cells[VansColumns.NETTO][Index] = IntToStr(Van->Netto);
	sgVans->Cells[VansColumns.OVERLOAD][Index] = IntToStr(Van->Overload);

	sgVans->Cells[VansColumns.CARGOTYPE][Index] = Van->CargoType->Name;

	sgVans->Cells[VansColumns.DEPART_STATION][Index] = Van->DepartStation->Name;
	sgVans->Cells[VansColumns.PURPOSE_STATION][Index] =
		Van->PurposeStation->Name;

	sgVans->Cells[VansColumns.INVOICE_NUM][Index] = Van->InvoiceNum;

	sgVans->Cells[VansColumns.INVOICE_SUPPLIER][Index] =
		Van->InvoiceSupplier->Name;
	sgVans->Cells[VansColumns.INVOICE_RECIPIENT][Index] =
		Van->InvoiceRecipient->Name;

	return Index;
}

// ---------------------------------------------------------------------------
void TfrmTrain::UpdateVans(TTrain * Train) {
	for (int i = 0; i < Train->VanList->Count; i++) {
		SetVan(-1, Train->VanList->Items[i]);
	}
	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnSaveClick(TObject *Sender) {
	if (!CheckVanList()) {
		return;
	}

	if (SaveVans()) {
		Changed = false;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansGetEditMask(TObject *Sender, int ACol,
	int ARow, UnicodeString & Value) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	switch (ACol) {
	case VansColumns.DATETIME:
		Value = "00/00/0000 00:00:00";
		break;
	case VansColumns.VANNUM:
		Value = "00000000";
		break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansExit(TObject *Sender) {
	CalcFields();
	UpdateTrain();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansDrawCell(TObject *Sender, int ACol, int ARow,
	TRect & Rect, TGridDrawState State) {
	StringGridDrawCell(sgVans, ACol, ARow, Rect, State, VansColumns.ReadOnly,
		VansColumns.LeftAlign, NUSet, Main->Settings->ColorReadOnly,
		NUColor, true);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgTrainDrawCell(TObject *Sender, int ACol, int ARow,
	TRect & Rect, TGridDrawState State) {
	StringGridDrawCell(sgTrain, ACol, ARow, Rect, State, NUSet,
		TrainColumns.LeftAlign, NUSet, NUColor, NUColor, false);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::FormCloseQuery(TObject *Sender, bool &CanClose) {
	ModalResult = mrOk;

	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	if (!Changed) {
		return;
	}

	switch (MsgBox(IDS_QUESTION_TRAIN_CHANGED,
		MB_ICONQUESTION | MB_YESNOCANCEL)) {
	case ID_YES:
		CanClose = SaveVans();
		break;
	case ID_CANCEL:
		CanClose = false;
		break;
	default:
		CanClose = true;
		ModalResult = mrCancel;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::sgVansDblClick(TObject *Sender) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	int Col, Row;

	StringGridMouseToCell(sgVans, Col, Row);

	if (Row < 1) {
		return;
	}

	if (ShowVanComboBox(Col)) {
		return;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::ComboBoxExit(TObject *Sender) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	if (sgVans->Cells[sgVans->Col][sgVans->Row] != ComboBox->Text) {
		sgVans->Cells[sgVans->Col][sgVans->Row] = ComboBox->Text;

		switch (sgVans->Col) {
			// TODO: enums
		case VansColumns.WEIGHTTYPE:
			sgVans->Cells[VansColumns.WEIGHTTYPE_AS_INT][sgVans->Row] =
				IntToStr(ComboBox->ItemIndex);
			break;
		case VansColumns.TARE_INDEX:
			sgVans->Cells[VansColumns.TARE_INDEX_AS_INT][sgVans->Row] =
				IntToStr(ComboBox->ItemIndex);

			CalcFields(sgVans->Row);
			UpdateTrain();

			break;
		}

		Changed = true;
	}

	ComboBox->Visible = false;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::ComboBoxEnter(TObject *Sender) {
	if (StringGridIsEmpty(sgVans)) {
		return;
	}

	switch (sgVans->Col) {
		// TODO : enums
	case VansColumns.WEIGHTTYPE:
		ComboBox->ItemIndex =
			StrToInt(sgVans->Cells[VansColumns.WEIGHTTYPE_AS_INT][sgVans->Row]);
		break;
	case VansColumns.TARE_INDEX:
		ComboBox->ItemIndex =
			StrToInt(sgVans->Cells[VansColumns.TARE_INDEX_AS_INT][sgVans->Row]);
		break;
	default:
		ComboBox->Text = sgVans->Cells[sgVans->Col][sgVans->Row];
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::ComboBoxKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	if (Key == VK_ESCAPE) {
		switch (sgVans->Col) {
		case VansColumns.WEIGHTTYPE:
			ComboBox->ItemIndex =
				StrToInt(sgVans->Cells[VansColumns.WEIGHTTYPE_AS_INT]
				[sgVans->Row]);
			break;
		case VansColumns.TARE_INDEX:
			ComboBox->ItemIndex =
				StrToInt(sgVans->Cells[VansColumns.TARE_INDEX_AS_INT]
				[sgVans->Row]);
			break;
		default:
			ComboBox->Text = sgVans->Cells[sgVans->Col][sgVans->Row];
		}

		sgVans->SetFocus();

		return;
	}

	if (Key == VK_RETURN) {
		sgVans->SetFocus();
		return;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::ComboBoxKeyPress(TObject *Sender,
	System::WideChar &Key) {
	if (Key == '\x1B' || Key == '\r' || Key == '\n') {
		Key = 0;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::ToolBarMouseActivate(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest,
	TMouseActivate &MouseActivate) {
	ComboBox->Visible = false;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrain::tbtnServiceClick(TObject *Sender) {
	if (!CheckVanList()) {
		return;
	}

	TfrmService::Show(GetVanList());
}

// ---------------------------------------------------------------------------
