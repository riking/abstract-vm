# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 13:08:18 by kyork             #+#    #+#              #
#    Updated: 2018/04/16 12:59:07 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract-vm

CLANGFORMAT ?= clang-format

$(NAME): Build/abstract-vm
	cp $^ $@

all: $(NAME)

Build/abstract-vm: Build/Makefile
	make -C Build $(NAME)

Build/Makefile: CMakeLists.txt
	mkdir -p Build
	cd Build && sh -c 'cmake ..'

clean:
	make -C Build clean

fclean:
	rm -rf Build

re: fclean all

format:
	$(CLANGFORMAT) -style=file -i src/*.cpp src/*.hpp

