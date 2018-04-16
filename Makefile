# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 13:08:18 by kyork             #+#    #+#              #
#    Updated: 2018/04/16 13:21:30 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract-vm

CLANGFORMAT ?= clang-format

$(NAME): Build/Makefile src/*.cpp src/*.hpp
	make -C Build $(NAME)
	cp Build/abstract-vm abstract-vm

all: $(NAME)

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

