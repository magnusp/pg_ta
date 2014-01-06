// PostgreSQL includes
#include "postgres.h"
#include "fmgr.h"
#include "funcapi.h"
#include "utils/array.h"

#include "ta_libc.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

// RhodiumToad is awesome.
#define SRF_RETURN_NEXT_NULL(_funcctx) \
do { \
	ReturnSetInfo	   *rsi; \
	(_funcctx)->call_cntr++; \
	rsi = (ReturnSetInfo *) fcinfo->resultinfo; \
	rsi->isDone = ExprMultipleResult; \
	PG_RETURN_NULL(); \
} while (0)

/*
 * Taken from the intarray contrib header
 */
#define ARRPTR(x)  ( (double *) ARR_DATA_PTR(x) )
#define ARRNELEMS(x)  ArrayGetNItems( ARR_NDIM(x), ARR_DIMS(x))

Datum ta_f( PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(ta_f);
Datum ta_f( PG_FUNCTION_ARGS)
{

	// Declare for TA
	TA_RetCode retCode;
	TA_Real *closePrice = NULL;
	TA_Real *out;

	TA_Integer outBeg;
	TA_Integer outNbElement;

	// Declare for postgres
	FuncCallContext *funcctx;
	int call_cntr;
	int max_calls;
	Datum *result = NULL;
	int dim;
	int z;
	ArrayType *ur = PG_GETARG_ARRAYTYPE_P(0);

	if (array_contains_nulls(ur))
	{
		ereport(ERROR,
				( errcode(ERRCODE_ARRAY_ELEMENT_ERROR), errmsg("cannot work with arrays containing NULLs") ));
	}

	dim = ARRNELEMS(ur);
	closePrice = ARRPTR(ur);

	if (SRF_IS_FIRSTCALL())
	{
		MemoryContext oldcontext;

		funcctx = SRF_FIRSTCALL_INIT();
		oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
		/* One-time setup code appears here: */
		retCode = TA_Initialize();
		if (retCode != TA_SUCCESS)
		{
			ereport(ERROR,
					( errcode(ERRCODE_FEATURE_NOT_SUPPORTED), errmsg("Cannot initialize TA-Lib (%d)!\n", retCode) ));
		}

		out = palloc(dim * sizeof(TA_Real));

		retCode = TA_MA(0, dim - 1, &closePrice[0], 5, TA_MAType_SMA, &outBeg,
				&outNbElement, &out[0]);

		result = palloc(outNbElement * sizeof(Datum));

		// Error log for debugging
		/*
		ereport(NOTICE,
				(errmsg("dims %d,  outBeg: %d, outNbElement %d\n", dim, outBeg, outNbElement)));
		*/
		for (z = 0; z < dim; z++)
		{
			// Error log for debugging
			//ereport(NOTICE, (errmsg("z: %d, out[z]: %5.1f", z, out[z])));
			if(z > outBeg-1) {
				result[z] = Float8GetDatum(out[z-outBeg]);
				continue;
			}
			result[z] = NULL;
		}
		TA_Shutdown();

		funcctx->max_calls = dim;
		funcctx->user_fctx = result;
		MemoryContextSwitchTo(oldcontext);
	}

	/* stuff done on every call of the function */
	funcctx = SRF_PERCALL_SETUP();

	call_cntr = funcctx->call_cntr;
	max_calls = funcctx->max_calls;

	if (call_cntr < max_calls)
	{
		if(((Datum *) funcctx->user_fctx)[call_cntr]) {
			SRF_RETURN_NEXT(funcctx, ((Datum *) funcctx->user_fctx)[call_cntr]);
		}
		SRF_RETURN_NEXT_NULL(funcctx);
	}
	SRF_RETURN_DONE(funcctx);
}

