// ---------------------------------------------------------------------------

#ifndef WMEAddH
#define WMEAddH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Grids.hpp>

// ---------------------------------------------------------------------------
bool StringGridIsEmpty(TStringGrid *Grid);
void StringGridSelectCell(TStringGrid *Grid, int ACol, int ARow);
void StringGridUpdateOrderNum(TStringGrid *Grid);
void StringGridDeleteRow(TStringGrid *Grid, int ARow, int AColCount = -1);
void StringGridSetHeader(TStringGrid *Grid, int Col, String ColName,
	int ColWidth);
void StringGridDrawCell(TStringGrid *Grid, int ACol, int ARow, TRect Rect,
	TGridDrawState State, TIntegerSet ColsReadOnly, TIntegerSet ColsLeftAlign,
	TIntegerSet ColsCustomColor, TColor ReadOnlyColor, TColor CustomColor,
	bool DrawFocusedOnInactive);

// ---------------------------------------------------------------------------
String LoadSQL(NativeUInt Ident);

// ---------------------------------------------------------------------------
String DateTimeToSQLStr(TDateTime ADateTime);
int DateTimeToWTime(TDateTime ADateTime);

// ---------------------------------------------------------------------------
#endif
