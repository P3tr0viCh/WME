// ---------------------------------------------------------------------------

#ifndef WMEAddH
#define WMEAddH

#include <System.Classes.hpp>
#include <Vcl.Grids.hpp>

bool StringGridIsEmpty(TStringGrid *Grid);
void StringGridUpdateOrderNum(TStringGrid *Grid);
void StringGridDeleteRow(TStringGrid *Grid, int ARow, int AColCount = -1);
void StringGridSetHeader(TStringGrid *Grid, int Col, String ColName, int ColWidth);

// ---------------------------------------------------------------------------
#endif
