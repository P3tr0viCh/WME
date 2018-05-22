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
	TStringGrid *sgVans;
	TPanel *PanelTop;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall sgVansDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);

private:
	TVanList * VanList;

public:
	__fastcall TfrmService(TComponent* Owner);

	static bool Show(TVanList * VanList);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmService *frmService;
// ---------------------------------------------------------------------------
#endif
