#include "ft_nm.h"

int main(int argc, char **argv)
{
	struct nm_file	myfile;

	if (argc != 2)
	{
		ft_putstr("Usage: ./ft_nm <filename>\n");
		return (1);
	}
	ft_bzero(&myfile, sizeof(myfile));
	ttslist_init(&myfile.symbols);
	if (get_file_info(argv[1], &myfile) == NO_ERROR)
	{
		elf_parse_header(&myfile);
	}
	return (0);
}
