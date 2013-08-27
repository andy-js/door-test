#include <door.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>

static void
server(void *cookie, char *argp, size_t arg_size,
       door_desc_t *desc, uint_t ndesc)
{
	int data = 123456789;

	door_return((char *)&data, sizeof(int), NULL, 0);
}

int
main(int argc, const char **argv)
{
	int fd;
	struct stat statbuf;
	sigset_t sigset;

	if (stat(DOOR_FILE, &statbuf) == -1) {
		fd = creat(DOOR_FILE, 0444);
		if (fd == -1) {
			perror("creat");
			return EXIT_FAILURE;
		}
	} else {
		(void) fdetach(DOOR_FILE);
	}

	fd = door_create(server, NULL, 0);
	if (fd == -1) {
		perror("door_create");
		return EXIT_FAILURE;
	}

	if (fattach(fd, DOOR_FILE) == -1) {
		perror("fattach");
		return EXIT_FAILURE;
	}

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGTERM);
	sigwait(&sigset);

	return EXIT_SUCCESS;
}
