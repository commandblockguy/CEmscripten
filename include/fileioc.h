#include <stdio.h>

typedef FILE* ti_var_t;

void ti_CloseAll(void);
void ti_Close(ti_var_t var);

ti_var_t ti_Open(const char *name, const char *mode);
char *ti_Detect(void **curr_search_posistion, const char *detection_string);
int ti_Delete(const char *name);
#define ti_Write fwrite
#define ti_Read fread
#define ti_Rewind rewind
#define ti_PutC fputc
#define ti_GetC fgetc
#define ti_Seek(offset, origin, slot) fseek(slot, offset, origin)


void *ti_GetDataPtr(const ti_var_t slot);

#define ti_SetArchiveStatus(ignore, ignore_f)
