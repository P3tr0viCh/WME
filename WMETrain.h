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
	TToolButton *ToolButton3;
	TPanel *PanelBottom;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tbtnCloseClick(TObject *Sender);
	void __fastcall tbtnAddClick(TObject *Sender);
	void __fastcall tbtnDeleteClick(TObject *Sender);
	void __fastcall sgVansSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall sgVansSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);





private:
	void CreateVansColumns();
	void CreateTrainColumns();

	void UpdateTrain();

public:
	__fastcall TfrmTrain(TComponent* Owner);

	static bool Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrain *frmTrain;
// ---------------------------------------------------------------------------
#endif
