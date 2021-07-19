int main(int argc, char **argv)
{
	int fd;
	int	fd2;
	int ret;
	char *line;
	int	i;

	line = 0;
	if (argc == 3)
	{
		fd = open(argv[1], O_RDONLY);
		i = 1;
		while ((line = get_next_line(fd)) != 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("ERROR\n");
		else if (ret == 0)
			printf("EOF\n");
		fd2 = open(argv[2], O_RDONLY);
		close(fd);
		fd = fd2;
		while ((line = get_next_line(fd)) > 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("ERROR\n");
		if (ret == 0)
			printf("EOF\n");
	}
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)) != 0)
		{
			printf("Line #%s\n", line);
			free(line);
		}
		printf("Line #%s\n", line);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of file\n");
		close(fd);
	}
	if (argc == 1)
	{
		while ((line = get_next_line(fd)) != 0)
		{
			line = get_next_line(fd);
			printf("Line #%s\n", line);
			free(line);
		}
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		close(fd);
	}
	return (0);
}
