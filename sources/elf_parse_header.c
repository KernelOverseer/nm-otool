#include "ft_nm.h"

static void elf_debug_section_headers_32(Elf32_Shdr *header)
{
	printf("==================    section   ====================\n");
	printf("%-10.10s : %u\n", "type", header->e_type);
}

static void elf_debug_header_32(Elf32_Ehdr *header)
{
	printf("================== 32bit Header ====================\n");
	printf("%-10.10s : %u\n", "type", header->e_type);
	printf("%-10.10s : %u\n", "machine", header->e_machine);
	printf("%-10.10s : %u\n", "version", header->e_version);
	printf("%-10.10s : %#x\n", "entry", header->e_entry);
	printf("%-10.10s : %u\n", "phoff", header->e_phoff);
	printf("%-10.10s : %u\n", "shoff", header->e_shoff);
	printf("%-10.10s : %u\n", "flags", header->e_flags);
	printf("%-10.10s : %u\n", "ehsize", header->e_ehsize);
	printf("%-10.10s : %u\n", "phentsize", header->e_phentsize);
	printf("%-10.10s : %u\n", "phnum", header->e_phnum);
	printf("%-10.10s : %u\n", "shentsize", header->e_shentsize);
	printf("%-10.10s : %u\n", "shnum", header->e_shnum);
	printf("%-10.10s : %u\n", "shstrndx", header->e_shstrndx);	
}

static int	elf_verify_header_32(struct nm_file *file)
{
	int	res;
	elf_debug_header_32(&file->header.elf32);

	Elf32_Shdr	header;
	res = elf_copy_from_offset(&header, file->header.elf32.e_shoff, sizeof(Elf32_Shdr), file);
	if (res == ERROR_INCOMPLETE_COPY)
		printf("INCOMPLETE COPY\n");
	elf_debug_section_headers_32(&header);
	return (NO_ERROR);
}


static int	elf_verify_header_64(struct nm_file *file)
{
	(void)file;
	return (NO_ERROR);
}

int		elf_parse_header_after_id(struct nm_file *file)
{
	int	err;
	size_t	size;

	size = sizeof(Elf32_Ehdr);
	if (file->arch == ELFCLASS64)
		size = sizeof(Elf64_Ehdr);
	if ((err = elf_move_from_mem(&file->header, size, file)))
		return (err);
	if (file->arch == ELFCLASS64)
		err = elf_verify_header_64(file);
	else
		err = elf_verify_header_32(file);
	return (err);
}
