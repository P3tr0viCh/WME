// ---------------------------------------------------------------------------

#ifndef WMEOptionsH
#define WMEOptionsH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>

#include "WMEOptionsUser.h"

#include "WMETSettings.h"

// ---------------------------------------------------------------------------
class TfrmOptions : public TForm {
__published:

	TPanel *PanelMain;
	TPageControl *PageControl;
	TTabSheet *tsDatabase;
	TLabel *lblDBConnection;
	TBevel *bvlDB;
	TLabeledEdit *eDBUser;
	TLabeledEdit *eDBPass;
	TButton *btnDBConnectionCheck;
	TLabeledEdit *eDBHost;
	TLabeledEdit *eDBPort;
	TButton *btnDBConnectionDefault;
	TButton *btnDBCreate;
	TButton *btnDBDelete;
	TTabSheet *tsUsers;
	TStringGrid *sgUsers;
	TButton *btnUsersAdd;
	TButton *btnUsersChange;
	TButton *btnUsersDelete;
	TPanel *PanelButtons;
	TButton *btnOk;
	TButton *btnCancel;
	TTabSheet *tsVanTypes;
	TTabSheet *tsCargoTypes;
	TTabSheet *tsDepartStations;
	TTabSheet *tsPurposeStations;
	TTabSheet *tsInvoiceSuppliers;
	TTabSheet *tsInvoiceRecipients;
	TStringGrid *sgVanTypes;
	TButton *btnVanTypesAdd;
	TButton *btnVanTypesChange;
	TButton *btnVanTypesDelete;
	TStringGrid *sgCargoTypes;
	TButton *btnCargoTypesAdd;
	TButton *btnCargoTypesChange;
	TButton *btnCargoTypesDelete;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnDBConnectionCheckClick(TObject *Sender);
	void __fastcall btnDBConnectionDefaultClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnUsersAddClick(TObject *Sender);
	void __fastcall btnUsersChangeClick(TObject *Sender);
	void __fastcall btnUsersDeleteClick(TObject *Sender);
	void __fastcall sgUsersDblClick(TObject *Sender);
	void __fastcall sgUsersFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall btnDBCreateClick(TObject *Sender);
	void __fastcall btnDBDeleteClick(TObject *Sender);

private:
	TSettings * Settings;

	bool IsReadOnly;

	bool PerformSave;

	void CreateUsersColumns();
	void CreateVanTypesColumns();
	void CreateVanCatalogColumns(TStringGrid * Grid);

	void SetReadOnly(TComponent * Parent, bool ReadOnly);

	void UpdateForm();
	void UpdateSettingsVanCatalog(TStringGrid * Grid,
		TVanCatalogList * VanCatalogList);
	void UpdateSettings();

	TUser * GetUser(int Index);
	int SetUser(int Index, TUser * User);

	TVanType * GetVanType(int Index);
	int SetVanType(int Index, TVanType * VanType);

	TVanCatalog * GetVanCatalog(TStringGrid * Grid, int Index);
	int SetVanCatalog(TStringGrid * Grid, int Index, TVanCatalog * VanCatalog);

	bool IsUserAdmin(int Index);

	TConnectionInfo * GetConnection();

	static const int DB_ACTION_CHECK = 0;
	static const int DB_ACTION_CREATE = 1;
	static const int DB_ACTION_DROP = 2;

	void DatabaseAction(int Action);

	TStringGrid * GetStringGrid(TObject * Sender);

public:
	__fastcall TfrmOptions(TComponent* Owner);

	static bool Show(TSettings *Settings, bool ReadOnly);

	int AdminCount();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
// ---------------------------------------------------------------------------
#endif
