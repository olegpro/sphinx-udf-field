/* 
   Created by olegpro.ru
   Oleg Maksimenko <oleg.39style@gmail.com>
   10.12.2017
*/

#include "sphinxudf.h"
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/// UDF version control
/// gets called once when the library is loaded
DLLEXPORT int bk_field_ver()
{
	return SPH_UDF_VERSION;
}

DLLEXPORT int bk_field_init(SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_message)
{
	int i;

	if (args->arg_count < 2) {
		snprintf(error_message, SPH_UDF_ERROR_LEN, "bk_field() takes at least 2 arguments");
		return 1;
	}

	for (i = 0; i < args->arg_count; i++) {
		if (
			args->arg_types[i] == SPH_UDF_TYPE_STRING
			|| args->arg_types[i] == SPH_UDF_TYPE_INT64
			|| args->arg_types[i] == SPH_UDF_TYPE_UINT32
		) {

		} else {
			snprintf(error_message, SPH_UDF_ERROR_LEN, "bk_field() only supports int or string as arguments (num bad arg: %d, type: %d)", i, args->arg_types[i]);
			return 2;
		}
	}

	return 0;
}

/// UDF re-initialization func
/// gets called on sighup (workers=prefork only)
DLLEXPORT void udfexample_reinit()
{
}

/// UDF deinitialization
/// gets called on every query, when query ends
DLLEXPORT void bk_field_deinit(SPH_UDF_INIT * init)
{
}

/// UDF implementation
/// gets called for every row, unless optimized away
DLLEXPORT int bk_field(SPH_UDF_INIT * init, SPH_UDF_ARGS * args, char * error_flag) {
	int i;

	for (i = 1; i < args->arg_count; i++) {
		if (
			args->arg_types[i] == SPH_UDF_TYPE_INT64
			|| args->arg_types[i] == SPH_UDF_TYPE_UINT32
		) {
			if (*(int*)args->arg_values[0] == *(int*)args->arg_values[i]) {
				return i;
			}
		} else if (args->arg_types[i] == SPH_UDF_TYPE_STRING) {
			if (strcmp(args->arg_values[0], args->arg_values[i]) == 0) {
				return i;
			}
		}
	}

	return 0;
}

void main() {}
