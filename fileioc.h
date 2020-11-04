#include <stdio.h>

typedef FILE* ti_var_t;

void ti_CloseAll(void);
void ti_Close(ti_var_t var);

ti_var_t ti_Open(const char *name, const char *mode);
#define ti_Write fwrite
#define ti_Read fread

#define ti_SetArchiveStatus(ignore, ignore_f)
