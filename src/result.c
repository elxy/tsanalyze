#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "result.h"

static uint8_t outtype;

struct res_ops rops[RES_NUM];

int res_settype(int t)
{
	outtype = t;
	return 0;
}

int res_open(const char *filename)
{
	char outfile[1024];
	if(outtype == RES_STD)
		rops[outtype].f = stdout;
	else if (outtype == RES_TXT)
	{
		snprintf(outfile, 1024, "%s.txt", filename);
		rops[outtype].f = fopen(outfile, "w");
	}
	else if (outtype == RES_JSON)
	{
		snprintf(outfile, 1024, "%s.json", filename);
		rops[outtype].f = fopen(outfile, "w");
	}
	return 0;
}

int res_put(const char *fmt, ...)
{
	va_list args;
	char buf[1024];
	int ret;
	va_start(args, fmt);
	vsnprintf(buf, 1024, fmt, args);
	ret = fprintf(rops[outtype].f, "%s", buf);
	va_end(args);
	return ret;    
}

int res_close(void)
{
	if(outtype != RES_STD)
		fclose(rops[outtype].f);
	return 0;
}