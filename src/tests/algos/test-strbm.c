#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <ycc/algos/string.h>


int main()
{
	char *haystack = "I'm yanyg, i'm from china, yyg is a good boy";
	char *needle = ", yyg is a good";
	size_t table_sgs[32], table_ebc[UCHAR_MAX+1];

	//strbm_init(needle, strlen(needle), table_sgs, table_ebc);

	//char *result = strbm_find(haystack, needle,
	//			  strlen(haystack), strlen(needle),
	//			  table_sgs, table_ebc);
	strbmh_init(needle, strlen(needle), table_ebc);

	char *result = strbmh_find(haystack, needle,
				  strlen(haystack), strlen(needle),
				  table_ebc);

	if (result)
		printf("find success: %s\n", result);
	else
		printf("find failed !\n");

	return 0;
}
