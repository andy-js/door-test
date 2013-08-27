#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <door.h>

int
main(int argc, const char *argv)
{
	int fd;
	door_arg_t door_arg = {0};

	fd = open(DOOR_FILE, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	if (door_call(fd, &door_arg) == -1) {
		perror("door_call");
		close(fd);
		return EXIT_FAILURE;
	}

	printf("door_arg.rsize is %d\n", door_arg.rsize);

	if (door_arg.rsize != sizeof(int))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
