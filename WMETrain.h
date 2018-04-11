// ---------------------------------------------------------------------------

#ifndef WMETrainH
#define WMETrainH

// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "WMETVan.h"

// ---------------------------------------------------------------------------
class TfrmTrain : public TForm {
__published:
	TStatusBar *StatusBar;
	TPanel *PanelMain;
	TToolBar *ToolBar;
	TToolButton *tbtnClose;
	TStringGrid *sgVans;
	TPanel *PanelTop;
	TStringGrid *sgTrain;
	TToolButton *tbtnDelete;
	TToolButton *tbtnAdd;
	TToolButton *tbtnSeparator01;
	TPanel *PanelBottom;
	TToolButton *tbtnSave;
	TToolButton *tbtnSeparator02;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall tbtnAddClick(TObject *Sender);
	void __fastcall tbtnDeleteClick(TObject *Sender);
	void __fastcall sgVansSelectCell(TObject *Sender, int ACol, int ARow,
		bool &CanSelect);
	void __fastcall sgVansSetEditText(TObject *Sender, int ACol, int ARow,
		const UnicodeString Value);
	void __fastcall sgVansKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift);
	void __fastcall tbtnSaveClick(TObject *Sender);
	void __fastcall sgVansGetEditMask(TObject *Sender, int ACol, int ARow,
		UnicodeString &Value);
	void __fastcall sgVansGetEditText(TObject *Sender, int ACol, int ARow,
		UnicodeString &Value);
	void __fastcall sgVansExit(TObject *Sender);
	void __fastcall sgVansDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgTrainDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:
	bool Changed;

	TIntegerSet NUSet;
	TColor NUColor;

	String CellValue;

	void CreateVansColumns();
	void CreateTrainColumns();

	void UpdateTrainCell(int ACol, float Value);

	void CalcFields(int ARow = -1);
	void UpdateTrain();

	void UpdateValue(int ACol, int ARow);
	void UpdateValues(int ARow = -1);

	String CheckStrValue(String Value);
	void CheckStrValue(int ACol, int ARow);
	bool CheckDateTimeValue(String Value);
	bool CheckIntValue(String Value);
	bool CheckValues(int ARow = -1);

	TVanList *GetVanList();

	bool SaveVans();

public:
	__fastcall TfrmTrain(TComponent* Owner);

	static bool Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrain *frmTrain;
// ---------------------------------------------------------------------------
#endif
