// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"
#include "WMEStringsGridHeader.h"

#include "WMETrainList.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
class TTrainsColumns {
public:
	static const NUM = 0;
	static const DATETIME = 1;
	static const CARRYING = 2;
	static const BRUTTO = 3;
	static const TARE = 4;
	static const NETTO = 5;
	static const OVERLOAD = 6;
	static const VANCOUNT = 7;

	static const VISIBLE_COUNT = 8;

	static const COUNT = 8;

	TTrainsColumns() {
		LeftAlign = TIntegerSet() << DATETIME;
	}

	TIntegerSet LeftAlign;
};

static TTrainsColumns TrainsColumns;

// ---------------------------------------------------------------------------
class TVansColumns {
public:
	static const NUM = 0;
	static const DATETIME = 1;
	static const VANNUM = 2;
	static const VANTYPE = 3;
	static const CARRYING = 4;
	static const BRUTTO = 5;
	static const TARE = 6;
	static const TARE_T = 7;
	static const TARE_D = 8;
	static const TARE_S = 9;
	static const TARE_INDEX = 10;
	static const NETTO = 11;
	static const OVERLOAD = 12;
	static const CARGOTYPE = 13;
	static const DEPART_STATION = 14;
	static const PURPOSE_STATION = 15;
	static const INVOICE_NUM = 16;
	static const INVOICE_SUPPLIER = 17;
	static const INVOICE_RECIPIENT = 18;

	static const VISIBLE_COUNT = 19;

	static const COUNT = 19;

	TVansColumns() {
		LeftAlign = TIntegerSet() << NUM << DATETIME << VANNUM << VANTYPE <<
			CARGOTYPE << DEPART_STATION << PURPOSE_STATION << INVOICE_NUM <<
			INVOICE_SUPPLIER << INVOICE_RECIPIENT;
	}

	TIntegerSet ReadOnly;

	TIntegerSet LeftAlign;
};

static TVansColumns VansColumns;

// ---------------------------------------------------------------------------
__fastcall TfrmTrainList::TfrmTrainList(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void TfrmTrainList::Show() {
	TfrmTrainList *frmTrainList = new TfrmTrainList(Application);
	try {
		frmTrainList->ShowModal();
	}
	__finally {
		delete frmTrainList;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	CreateTrainsColumns();
	CreateVansColumns();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void TfrmTrainList::CreateTrainsColumns() {
	sgTrains->ColCount = TrainsColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgTrains, TrainsColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgTrains, TrainsColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);
	StringGridSetHeader(sgTrains, TrainsColumns.CARRYING,
		IDS_GRID_HEADER_CARRYING, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.BRUTTO,
		IDS_GRID_HEADER_BRUTTO, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.TARE, IDS_GRID_HEADER_TARE, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.NETTO,
		IDS_GRID_HEADER_NETTO, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.OVERLOAD,
		IDS_GRID_HEADER_OVERLOAD, 90);
	StringGridSetHeader(sgTrains, TrainsColumns.VANCOUNT,
		IDS_GRID_HEADER_VANCOUNT, 120);
}

// ---------------------------------------------------------------------------
void TfrmTrainList::CreateVansColumns() {
	sgVans->ColCount = VansColumns.VISIBLE_COUNT;

	StringGridSetHeader(sgVans, VansColumns.NUM, IDS_GRID_HEADER_NUM, 50);
	StringGridSetHeader(sgVans, VansColumns.DATETIME,
		IDS_GRID_HEADER_DATETIME, 160);
	StringGridSetHeader(sgVans, VansColumns.VANNUM, IDS_GRID_HEADER_VANNUM, 80);
	StringGridSetHeader(sgVans, VansColumns.VANTYPE,
		IDS_GRID_HEADER_VANTYPE, 120);
	StringGridSetHeader(sgVans, VansColumns.CARRYING,
		IDS_GRID_HEADER_CARRYING, 50);
	StringGridSetHeader(sgVans, VansColumns.BRUTTO, IDS_GRID_HEADER_BRUTTO, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE, IDS_GRID_HEADER_TARE, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_T, IDS_GRID_HEADER_TARE_T, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_D, IDS_GRID_HEADER_TARE_D, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_S, IDS_GRID_HEADER_TARE_S, 60);
	StringGridSetHeader(sgVans, VansColumns.TARE_INDEX,
		IDS_GRID_HEADER_TARE_INDEX, 60);
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
void __fastcall TfrmTrainList::tbtnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::sgTrainsDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgTrains, ACol, ARow, Rect, State, NUSet,
		TrainsColumns.LeftAlign, NUSet, NUColor, NUColor, false);
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::sgVansDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgVans, ACol, ARow, Rect, State, NUSet,
		VansColumns.LeftAlign, NUSet, NUColor, NUColor, true);
}

// ---------------------------------------------------------------------------
