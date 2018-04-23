// ---------------------------------------------------------------------------

#ifndef WMETVanTypeH
#define WMETVanTypeH

#include <System.Classes.hpp>

#include <ObjList.h>

#include "WMETVanCatalog.h"

const VAN_TYPE_AXIS_NONE = 0;

// ---------------------------------------------------------------------------
class TVanType : public TVanCatalog {
private:
	int FAxisCount;

public:
	__fastcall TVanType();
	__fastcall TVanType(int Code, String Name, int AxisCount);

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TVanType * Source);
	String __fastcall ToString();

	__property int AxisCount = {read = FAxisCount, write = FAxisCount};
};

// ---------------------------------------------------------------------------
typedef TObjList<TVanType>TVanTypeList;

// ---------------------------------------------------------------------------
#endif
