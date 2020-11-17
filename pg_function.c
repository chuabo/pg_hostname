#include "postgres.h"
#include "fmgr.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PGDLLEXPORT Datum hostname(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(hostname);
#define MAX_HOST_SIZE 999999

Datum hostname(PG_FUNCTION_ARGS) {
	text *result;
	size_t len;
	char buf[MAX_HOST_SIZE + sizeof(char)];

	gethostname(buf, MAX_HOST_SIZE);
	len = strlen(buf);
	elog(NOTICE, "hostname=%s\n", buf);
	result = (text *)palloc(len + VARHDRSZ);
	SET_VARSIZE(result, len + VARHDRSZ);
	memcpy(VARDATA(result), buf, len);
	PG_RETURN_TEXT_P(PointerGetDatum(result));
}