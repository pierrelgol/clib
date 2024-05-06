# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plgol.perso <pollivie@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 14:39:40 by plgol.perso       #+#    #+#              #
#    Updated: 2023/12/01 14:39:43 by plgol.perso      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC     =  clang
RM     =  rm -f

CFLAGS =   -Wall                                    \
           -Wextra                                  \
           -fsanitize=memory                        \
           -g3                                      \

NAME   =    libclib.a
DIRS   =    source/memory                           \
            source/allocator                        \
            source/bitset                           \
            source/string                           \
            source/misc                             \

SRCS := $(foreach dir,$(DIRS),$(wildcard ./$(dir)/*.c))
OBJS := $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(SHARED_NAME)

re: fclean all

run : $(NAME)
	$(CC) test.c libplib.a $(CFLAGS) -o test
	./test
