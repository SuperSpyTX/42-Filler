#* ************************************************************************** */
#*                                                                            */
#*                                                        :::      ::::::::   */
#*   Makefile                                           :+:      :+:    :+:   */
#*                                                    +:+ +:+         +:+     */
#*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
#*                                                +#+#+#+#+#+   +#+           */
#*   Created: 2017/04/18 03:42:42 by jkrause           #+#    #+#             */
#*   Updated: 2017/06/11 02:45:14 by jkrause          ###   ########.fr       */
#*                                                                            */
#* ************************************************************************** */
# ----------------- Version 1.5 --------------------- #
divert(-1)

# ------------- Real Configuration ------------------ #
define(MK_NUM_OF_TARGETS, 1)
define(MK_FCLEAN_ON_RE, 0)
define(MK_DEBUG, 0)

define(MK_FILLER_NAME, filler)
define(MK_FILLER_ISLIB, 0)
define(MK_FILLER_INCLUDE_DIRS, includes)
define(MK_FILLER_SRC_DIRS, src libft)
define(MK_FILLER_DEBUG, 0)
define(MK_FILLER_LITE, 0)

# ------------ Automated Variables ------------------ #
define(MK_AUTO_ISLINUX, ifelse(esyscmd(uname -s | tr -d '\n'), `Darwin', 0, 1))
define(MK_AUTO_COMPILER,ifelse(MK_AUTO_ISLINUX, 1, clang, gcc))

define(MK_FILLER_AUTO_SRC_DIR, patsubst(MK_FILLER_SRC_DIRS,` ',`````,'''''))
pushdef(`MK_FILLER_AUTO_SRC_DIR', ifelse(MK_FILLER_SRC_DIRS,.,.,{MK_FILLER_AUTO_SRC_DIR}))
define(MK_FILLER_AUTO_SRC, esyscmd(bash -c 'find MK_FILLER_AUTO_SRC_DIR -type f -name "*.c" | sed -e "s/$/ \\\/g"'))
define(MK_FILLER_AUTO_SRC_DIR, patsubst(MK_FILLER_SRC_DIRS,` ',```,'''))
define(MK_FILLER_AUTO_INCLUDE_DIR, -I patsubst(MK_FILLER_INCLUDE_DIRS,` ',``` -I '''))

divert(0)
# ------------- Automated Configuration ------------- #
CFLAGS = ifelse(MK_DEBUG, 1,-g) ifelse(MK_AUTO_ISLINUX,1,-fPIC) -Wall -Werror -Wextra
FILLER_NAME = ifelse(MK_FILLER_ISLIB, 1, MK_FILLER_NAME.a, MK_FILLER_NAME)
CFLAGS += MK_FILLER_AUTO_INCLUDE_DIR
FILLER_SRC = MK_FILLER_AUTO_SRC
FILLER_OBJ = $(subst .c,.o, $(FILLER_SRC))

# ------------------- Targets ----------------------- #

all: $(FILLER_NAME)

%.o: %.c
	MK_AUTO_COMPILER $(CFLAGS) -c $? -o $@

$(FILLER_NAME): $(FILLER_OBJ)
	ifelse(MK_FILLER_ISLIB, 0,MK_AUTO_COMPILER $(FILLER_OBJ) -lncurses -o $(FILLER_NAME),
	/bin/rm -f $(FILLER_NAME)
	ar rcs $(FILLER_NAME) $(FILLER_OBJ))dnl


re: ifelse(MK_FCLEAN_ON_RE, 1,f)clean all dnl


clean:
	/bin/rm -f $(FILLER_OBJ)

fclean: clean
	/bin/rm -f $(FILLER_NAME)
