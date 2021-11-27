#include "ft_nm.h"
/*
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

static void elf_debug_section_32(Elf32_Shdr *header, struct nm_file *file)
{
	Elf32_Sym	*symbol;

	printf("================== SYMBOL TABLE ====================\n");
	symbol = file->mem + header->sh_offset;
	printf("%-10.10s : %u\n", "shndx", symbol->st_shndx);
//	printf("%-10.10s : %u\n", "name", symbol->st_name);
//	if (symbol->st_name != 0)
//		debug_print_section_name(file, symbol->st_name);
}

static void elf_debug_section_headers_32(Elf32_Shdr *header, struct nm_file *file)
{
	printf("==================    section   ====================\n");
	printf("%-10.10s : %u\n", "type", header->sh_type);
	print_section_type(header->sh_type);
	if (header->sh_type == SHT_REL || header->sh_type == SHT_RELA)
	{
		elf_debug_section_32(header, file);
	}
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
		elf_debug_section_headers_32(header, file);
		offset += file->header.elf32.e_shentsize;
		debug_print_section_name(file, header->sh_name);
	}	
}

static int	elf_verify_header_32(struct nm_file *file)
{
//	int	res;
	elf_debug_header_32(&file->header.elf32);

//	debug_print_section_name(file, 0);
//	elf_debug_all_section_headers(file);
//	elf_debug_section_headers_32(&header);
	return (NO_ERROR);
}


static int	elf_verify_header_64(struct nm_file *file)
{
	(void)file;
	return (NO_ERROR);
}
*/

static char	*elf32_get_symbol_section_name(struct nm_file *file,
	Elf32_Sym *symbol)
{
	Elf32_Shdr	*section;
	Elf32_Shdr	*strtab_section;
	char		*name;
	off_t		offset;

	if (symbol->st_shndx == SHN_UNDEF ||
		symbol->st_shndx >= file->header.elf32.e_shnum)
		return (NULL);
	offset = file->header.elf32.e_shoff + symbol->st_shndx *
		file->header.elf32.e_shentsize;
	section = file->mem + offset;
	offset = file->header.elf32.e_shoff + file->header.elf32.e_shstrndx *
		file->header.elf32.e_shentsize;
	strtab_section = file->mem + offset;
	name = file->mem + strtab_section->sh_offset + section->sh_name;
	return (name);
}

static char	*elf32_get_symbol_name(struct nm_file *file,
	Elf32_Sym *symbol, Elf32_Shdr *sym_header)
{
	Elf32_Shdr	*table_header;
	char		*string_table;
	off_t		offset;

	offset = file->header.elf32.e_shoff + file->header.elf32.e_shentsize *
		sym_header->sh_link;
	table_header = file->mem + offset;
	string_table = file->mem + table_header->sh_offset;
	return (string_table + symbol->st_name);
}

static char	elf_get_symbol_letter(struct nm_sym *result)
{
	struct s_symbol_type_checker	*check;
	int				i;

	i = 0;
	while (symbol_type_checker[i].name)
	{
		check = &(symbol_type_checker[i]);
		if (ft_strequ(check->name, result->section)
&& (check->type == TYPE_ANY || result->type & check->type)
&& (check->bind == BIND_ANY || result->bind & check->bind))
		{
			result->letter = check->letter;
			if (check->bind == BIND_ANY &&
				result->bind == STB_GLOBAL)
				result->letter = ft_toupper(result->letter);
			return (result->letter);
		}
		i++;
	}
	return ('?');
}

static void	elf32_convert_to_nm_sym(struct nm_file *file,
	Elf32_Sym *symbol, Elf32_Shdr *sym_header, struct nm_symbol *result)
{
	result->symbol.name = elf32_get_symbol_name(file, symbol, sym_header);
	result->symbol.section = elf32_get_symbol_section_name(file, symbol);
	result->symbol.type = ELF32_ST_TYPE(symbol->st_info);
	result->symbol.bind = ELF32_ST_BIND(symbol->st_info);
	result->symbol.value = symbol->st_value;
	result->symbol.letter = elf_get_symbol_letter(&result->symbol);
}

static struct nm_symbol	*elf32_process_symbol(struct nm_file *file,
	Elf32_Sym *symbol, Elf32_Shdr *sym_header)
{
	struct nm_symbol	*result;

	result = ft_memalloc(sizeof(struct nm_symbol));
	if (!result)
	{
		set_error("Symbol allocation failed",
			WARNING_ALLOCATION_FAILED);
		return (NULL);
	}
	result->sym_ref = (union u_elf_sym *)symbol;
	elf32_convert_to_nm_sym(file, symbol, sym_header, result);
	return (result);
}

static int	elf32_load_symbols(struct nm_file *file, Elf32_Shdr *s_header)
{
	Elf32_Sym	*symbol;
	int		index;
	off_t		offset;

	index = s_header->sh_size / s_header->sh_entsize;
	offset = s_header->sh_offset;
//	printf("Found symbol table\n");
	while (index--)
	{
		symbol = (Elf32_Sym *)(file->mem + offset);
		ttslist_push_new(&file->symbols, elf32_process_symbol(file,
			symbol, s_header));
		offset += s_header->sh_entsize;
	}
	return (NO_ERROR);
}

static int	elf32_load_symbol_table(struct nm_file *file)
{
	Elf32_Shdr	*s_header;
	int		index;
	off_t		offset;

	index = 0;
	offset = file->header.elf32.e_shoff;
//	printf("we have %d sections\n", file->header.elf32.e_shnum);
	while (index < file->header.elf32.e_shnum)
	{
		s_header = (Elf32_Shdr *)(file->mem + offset);
		if (s_header->sh_type == SHT_SYMTAB)
			elf32_load_symbols(file, s_header);
		offset += file->header.elf32.e_shentsize;
		index++;
	}
	return (NO_ERROR);
}

int		elf_print_symbols(t_list_head *symbols)
{
	struct nm_symbol	*symbol;
	struct nm_sym		*sym;
	
	symbols->iterator = symbols->first;
	while ((symbol = ttslist_iter_content(symbols)))
	{
		sym = &symbol->symbol;
		if (sym->type == STT_FILE || !sym->name || !sym->name[0])
			continue;
		else
			printf("%8.8x %c %20.20s", sym->value, sym->letter, sym->name);
		printf(" section: %10.10s type: %2.2d bind: %2.2d\n", sym->section, sym->type, sym->bind);
	}
	return (0);
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
	if (file->arch == ELFCLASS32)
		err = elf32_load_symbol_table(file);
//	else
//		err = elf_verify_header_64(file);
	elf_print_symbols(&file->symbols);
	return (err);
}
