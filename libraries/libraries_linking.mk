# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libraries_linking.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiri <abiri@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 14:39:16 by abiri             #+#    #+#              #
#    Updated: 2021/07/05 17:44:15 by abiri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_libcplus_FILE = $(LIBS_DIR)/libCplus/libC+.a

REQUIRED_RULES += $(LIB_libcplus_FILE)

CLEAN_RULES += LIB_libcplus_CLEAN

FCLEAN_RULES += LIB_libcplus_FCLEAN

.PHONY: LIB_libcplus_CLEAN LIB_libcplus_FCLEAN

LINKS += -L $(LIBS_DIR)/libCplus -lC+
INCS += -I $(LIBS_DIR)/libCplus/includes

# MAIN RULES

$(LIB_libcplus_FILE):
	@make -C $(LIBS_DIR)/libCplus

LIB_libcplus_CLEAN:
	@make -C $(LIBS_DIR)/libCplus clean

LIB_libcplus_FCLEAN:
	@make -C $(LIBS_DIR)/libCplus fclean
