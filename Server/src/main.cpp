#include "lib/socket.h"
#include "lib/showmsg.h"
#include "lib/taskmgr.h"
#include "lib/timer.h"

#include "server.h"
#include "test/test.h"

#include <string.h>

int main(int argc, char **argv)
{
	if (argc > 1)
		for (int i = 0; i < argc; i++)
			if (strncmp(argv[i], "test", 4)==0){
				Test *test = new Test();
				test->run();
			}
				
	ShowInfo(CL_MAGENTA"WarGames Server"CL_RESET"\n");
	//init sockets
	socket_init();
	server_init();
	timer_init();
	fd_set readfd;
	{
		int next;

		while (true)
		{
			next = CTaskMgr::getInstance()->DoTimer(gettick_nocache());
			process_sockets(&readfd, next);
		}
	}
}
