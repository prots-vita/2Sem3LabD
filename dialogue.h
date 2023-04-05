#ifndef _dialogue_h_
#define _dialogue_h_
#include "func.h"

int dialog(const char *msgs[], int);

int Dshow(Table *);

int Dfile(Table *);

int Dadd(Table *);

int Ddelete(Table *);

int DdeleteRes(Table *);

//int Dfind(Table *);

int Dfind1(Table *);

int DfindRes(Table *);

int Dtask(Table *);

#endif
