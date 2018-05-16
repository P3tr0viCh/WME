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
#include "WMEOptionsVanType.h"
#include "WMEOptionsVanCatalog.h"

#include "WMETSettings.h"

// ---------------------------------------------------------------------------
class TfrmOptions : public TForm {
__published:
	TPanel *PanelMain;
	TPageControl *PageControl;
	TTabSheet *tsLocalDatabase;
	TLabel *lblLocalConnection;
	TBevel *bvlLocalDB;
	TLabeledEdit *eLocalDBUser;
	TLabeledEdit *eLocalDBPass;
	TButton *btnLocalDBConnectionCheck;
	TLabeledEdit *eLocalDBHost;
	TLabeledEdit *eLocalDBPort;
	TButton *btnLocalDBConnectionDefault;
	TButton *btnLocalDBCreate;
	TButton *btnLocalDBDelete;
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
	TStringGrid *sgDepartStations;
	TButton *btnDepartStationsAdd;
	TButton *btnDepartStationsChange;
	TButton *btnDepartStationsDelete;
	TStringGrid *sgInvoiceRecipients;
	TButton *btnInvoiceRecipientsAdd;
	TButton *btnInvoiceRecipientsChange;
	TButton *btnInvoiceRecipientsDelete;
	TStringGrid *sgPurposeStations;
	TButton *btnPurposeStationsAdd;
	TButton *btnPurposeStationsChange;
	TButton *btnPurposeStationsDelete;
	TStringGrid *sgInvoiceSuppliers;
	TButton *btnInvoiceSuppliersAdd;
	TButton *btnInvoiceSuppliersChange;
	TButton *btnInvoiceSuppliersDelete;
	TTabSheet *tsServerDatabase;
	TLabeledEdit *eServerDBHost;
	TLabeledEdit *eServerDBPort;
	TLabeledEdit *eServerDBUser;
	TLabeledEdit *eServerDBPass;
	TButton *btnServerDBConnectionCheck;
	TCheckBox *cboxServerDBConnection;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnLocalDBConnectionCheckClick(TObject *Sender);
	void __fastcall btnLocalDBConnectionDefaultClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnUsersAddClick(TObject *Sender);
	void __fastcall btnUsersChangeClick(TObject *Sender);
	void __fastcall btnUsersDeleteClick(TObject *Sender);
	void __fastcall sgUsersDblClick(TObject *Sender);
	void __fastcall sgUsersFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall btnLocalDBCreateClick(TObject *Sender);
	void __fastcall btnLocalDBDeleteClick(TObject *Sender);
	void __fastcall sgVanCatalogDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgVanTypesDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall sgUsersDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall btnServerDBConnectionCheckClick(TObject *Sender);

private:
	TIntegerSet NUSet;
	TColor NUColor;

	TSettings * Settings;

	bool IsReadOnly;

	bool PerformSave;

	void CreateUsersColumns();
	void CreateVanTypesColumns();
	void CreateVanCatalogColumns(TStringGrid * Grid);

	void SetReadOnly(TComponent * Parent, bool ReadOnly);

	void UpdateFormVanCatalog(TStringGrid * Grid,
		TVanCatalogList * VanCatalogList);
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

	enum TConnectionType {
		ctLocal, ctServer
	};

	TConnectionInfo * GetConnection(TConnectionType Type);

	enum TDBAction {
		dbaLocalCheck, dbaLocalCreate, dbaLocalDrop, dbaServerCheck
	};

	void DatabaseAction(TDBAction Action);

	TStringGrid * GetStringGrid(TObject * Sender);

	void SetStringGridValues(bool Add, TObject * Sender);

public:
	__fastcall TfrmOptions(TComponent * Owner);

	static bool Show(TSettings * Settings, bool ReadOnly);

	int AdminCount();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
// ---------------------------------------------------------------------------
#endif
