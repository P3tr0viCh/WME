// ---------------------------------------------------------------------------

#ifndef WMETVanCatalogH
#define WMETVanCatalogH

#include <System.Classes.hpp>

#include <ObjList.h>

const VAN_CATALOG_CODE_NONE = 0;

// ---------------------------------------------------------------------------
class TVanCatalog : public TObject {
private:
	int FCode;
	String FName;

public:
	__fastcall TVanCatalog();
	__fastcall TVanCatalog(int Code, String Name);

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TVanCatalog* Source);

	__property int Code = {read = FCode, write = FCode};
	__property String Name = {read = FName, write = FName};
};

// ---------------------------------------------------------------------------
typedef TObjList<TVanCatalog>TVanCatalogList;

// ---------------------------------------------------------------------------
#endif
