#include "ft_nm.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("Usage: ./ft_nm <filename>\n");
		return (1);
	}
	printf("%s %s\n", argv[0], argv[1]);
	struct nm_file	myfile;
	if (get_file_info(argv[1], &myfile) == NO_ERROR)
	{
		elf_parse_header(&myfile);
	}
	return (0);
}
