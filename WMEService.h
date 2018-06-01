// ---------------------------------------------------------------------------

#ifndef WMEServiceH
#define WMEServiceH

// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "WMETVan.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ToolWin.hpp>

// ---------------------------------------------------------------------------
class TfrmService : public TForm {
__published:
	TPanel *PanelMain;
	TToolBar *ToolBar;
	TToolButton *tbtnSave;
	TToolButton *tbtnSeparator03;
	TToolButton *tbtnClose;
	TStringGrid *sgVansLocal;
	TPanel *PanelTop;
	TToolButton *tbtnLocal;
	TToolButton *tbtnServer;
	TToolButton *tbtnSeparator01;
	TToolButton *tbtnSearch;
	TStatusBar *StatusBar;
	TStringGrid *sgVansServer;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall sgVansLocalDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall tbtnLocalClick(TObject *Sender);
	void __fastcall tbtnServerClick(TObject *Sender);
	void __fastcall sgVansServerDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgVansServerFixedCellClick(TObject *Sender, int ACol,
		int ARow);
	void __fastcall tbtnSearchClick(TObject *Sender);

private:
	TVanList * VanList;

	TIntegerSet EmptyVanNums;
	TIntegerSet BruttoVans;

	enum TSearchType {
		stLocal, stServer
	};

	void SetSearchType(TSearchType Value);

	TStringGrid * GetStringGrid(TSearchType SearchType);

	void CreateVansColumns(TSearchType SearchType);

	int SetVan(TSearchType SearchType, int Index, TVan * Van);

	void UpdateReadOnlyVans();
	void UpdateVanNums(TSearchType SearchType);

	void ClearVans(TSearchType SearchType);
	void SearchVans(TSearchType SearchType);

public:
	__fastcall TfrmService(TComponent* Owner);

	static bool Show(TVanList * VanList);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmService *frmService;
// ---------------------------------------------------------------------------
#endif
