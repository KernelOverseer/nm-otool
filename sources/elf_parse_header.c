#include "ft_nm.h"

static void	print_section_type(int type)
{
	switch(type)
	{
		case SHT_NULL:
			printf("type: SHT_NULL\n");
			break;
		case SHT_PROGBITS:
			printf("type: SHT_PROGBITS\n");
			break;
		case SHT_SYMTAB:
			printf("type: SHT_SYMTAB\n");
			break;
		case SHT_STRTAB:
			printf("type: SHT_STRTAB\n");
			break;
		case SHT_RELA:
			printf("type: SHT_RELA\n");
			break;
		case SHT_HASH:
			printf("type: SHT_HASH\n");
			break;
		case SHT_DYNAMIC:
			printf("type: SHT_DYNAMIC\n");
			break;
		case SHT_NOTE:
			printf("type: SHT_NOTE\n");
			break;
		case SHT_NOBITS:
			printf("type: SHT_NOBITS\n");
			break;
		case SHT_REL:
			printf("type: SHT_REL\n");
			break;
		case SHT_SHLIB:
			printf("type: SHT_SHLIB\n");
			break;
		case SHT_DYNSYM:
			printf("type: SHT_DYNSYM\n");
			break;
		case SHT_LOPROC:
			printf("type: SHT_LOPROC\n");
			break;
		case SHT_HIPROC:
			printf("type: SHT_HIPROC\n");
			break;
		case SHT_LOUSER:
			printf("type: SHT_LOUSER\n");
			break;
		case SHT_HIUSER:
			printf("type: SHT_HIUSER\n");
			break;
		default:
			printf("type: unknown !\n");
	}
}

static void	debug_print_section_name(struct nm_file *file, int index)
{
	size_t offset = file->header.elf32.e_shoff;

	offset += (file->header.elf32.e_shstrndx * file->header.elf32.e_shentsize);
	Elf32_Shdr	*header;

	header = (Elf32_Shdr *)(file->mem + offset);
	char	*str;

	str = file->mem + header->sh_offset + index;
	printf("name : %s\n", str);
}

static void elf_debug_section_headers_32(Elf32_Shdr *header)
{
	printf("==================    section   ====================\n");
	printf("%-10.10s : %u\n", "type", header->sh_type);
	print_section_type(header->sh_type);
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

static void	elf_debug_all_section_headers(struct nm_file *file)
{
	size_t offset = file->header.elf32.e_shoff;

	for (int i = 0; i < file->header.elf32.e_shnum; i++)
	{
		Elf32_Shdr	*header;

		header = (Elf32_Shdr *)(file->mem + offset);
		elf_debug_section_headers_32(header);
		offset += file->header.elf32.e_shentsize;
		debug_print_section_name(file, header->sh_name);
	}	
}

static int	elf_verify_header_32(struct nm_file *file)
{
//	int	res;
	elf_debug_header_32(&file->header.elf32);

//	debug_print_section_name(file, 0);
	elf_debug_all_section_headers(file);
//	elf_debug_section_headers_32(&header);
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
