#ifndef _toFile_h_
#define _toFile_h_

int OpenWrite(char *, FILE **);
int OpenRead(char *, FILE **);
int Write (FILE *, char );
int Read(FILE *, int *, char **);

#endif
