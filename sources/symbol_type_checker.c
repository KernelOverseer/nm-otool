#include "ft_nm.h"

struct s_symbol_type_checker symbol_type_checker[] = {
	{.name=".bss", .type=TYPE_ANY, .bind=BIND_ANY, .letter='b'},
	{.name=".data", .type=TYPE_ANY, .bind=BIND_ANY, .letter='d'},
	{.name=".data1", .type=TYPE_ANY, .bind=BIND_ANY, .letter='d'},
	{.name=".dynamic", .type=TYPE_ANY, .bind=BIND_ANY, .letter='d'},
	{.name=NULL, .type=TYPE_ANY, .bind=BIND_ANY, .letter='\0'},
};
