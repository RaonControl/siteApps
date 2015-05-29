#include <my_global.h>
#include <mysql.h>

int version()
{
	printf("MySQL client version: %s\n", mysql_get_client_info());
	return 0;
}
