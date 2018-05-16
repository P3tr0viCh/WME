// ---------------------------------------------------------------------------

#ifndef WMETSettingsH
#define WMETSettingsH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "WMETUser.h"
#include "WMETConnectionInfo.h"
#include "WMETVanCatalog.h"
#include "WMETVanType.h"

#define CFG_DIR_NAME "cfg"
#define CFG_EXT ".cfg"

// ---------------------------------------------------------------------------
class TSettings : public TObject {
private:
	String FConfigDir;

	TColor FColorReadOnly;

	bool FUseServer;

	TConnectionInfo * FLocalConnection;
	TConnectionInfo * FServerConnection;

	TUserList * FUserList;

	TVanTypeList * FVanTypeList;

	TVanCatalogList * FCargoTypeList;
	TVanCatalogList * FDepartStationList;
	TVanCatalogList * FPurposeStationList;
	TVanCatalogList * FInvoiceRecipientList;
	TVanCatalogList * FInvoiceSupplierList;

	int FLoadTrainCount;

	String GetConfigDir();
	bool CheckConfigDir();
	String GetConfigFileName(NativeUInt ConfigName);

	String Encrypt(String Text);
	String Decrypt(String Text);

	void DeleteConfigFile(String ConfigFileName);

	void LoadVanCatalog(String ConfigFileName, String Name,
		TVanCatalogList * VanCatalogList);
	void SaveVanCatalog(String ConfigFileName, String Name,
		TVanCatalogList * VanCatalogList);

	void LoadUsers(String ConfigFileName);
	void LoadSettings(String ConfigFileName);
	void LoadDatabases(String ConfigFileName);
	void LoadVanTypes(String ConfigFileName);
	void LoadCargoTypes(String ConfigFileName);
	void LoadDepartStations(String ConfigFileName);
	void LoadPurposeStations(String ConfigFileName);
	void LoadInvoiceRecipients(String ConfigFileName);
	void LoadInvoiceSuppliers(String ConfigFileName);

	void SaveUsers(String ConfigFileName);
	void SaveSettings(String ConfigFileName);
	void SaveDatabases(String ConfigFileName);
	void SaveVanTypes(String ConfigFileName);
	void SaveCargoTypes(String ConfigFileName);
	void SaveDepartStations(String ConfigFileName);
	void SavePurposeStations(String ConfigFileName);
	void SaveInvoiceRecipients(String ConfigFileName);
	void SaveInvoiceSuppliers(String ConfigFileName);

public:
	__fastcall TSettings();
	__fastcall ~TSettings();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TSettings * Source);
	String __fastcall ToString();

	bool Load();
	bool Save();

	__property TColor ColorReadOnly = {read = FColorReadOnly};

	__property bool UseServer = {read = FUseServer, write = FUseServer};

	__property TConnectionInfo * LocalConnection = {read = FLocalConnection};
	__property TConnectionInfo * ServerConnection = {read = FServerConnection};

	__property TUserList * UserList = {read = FUserList};

	__property TVanTypeList * VanTypeList = {read = FVanTypeList};

	__property TVanCatalogList * CargoTypeList = {read = FCargoTypeList};
	__property TVanCatalogList * DepartStationList = {read = FDepartStationList
	};
	__property TVanCatalogList * PurposeStationList = {
		read = FPurposeStationList};
	__property TVanCatalogList * InvoiceRecipientList = {
		read = FInvoiceRecipientList};
	__property TVanCatalogList * InvoiceSupplierList = {
		read = FInvoiceSupplierList};

	__property int LoadTrainCount = {
		read = FLoadTrainCount, write = FLoadTrainCount};
};

// ---------------------------------------------------------------------------
#endif
