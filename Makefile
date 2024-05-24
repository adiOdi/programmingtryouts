CXX           := clang++
CXXFLAGS      := -Wall -Wextra -pedantic -gdwarf-4 -std=c++17 -g -fstandalone-debug -c -o

.DEFAULT_GOAL := default
.PHONY: default clean bin all run

default: bin

bin:	## compiles project to executable binary
	@printf "[\e[0;36mINFO\e[0m] Compiling binary...\n"
	clang++ -Wall -Wextra -o crypto main.cpp 
	chmod +x crypto

encrypt: bin						## runs the project with default configs
	@printf "[\e[0;36mINFO\e[0m] encrypting...\n"
	./crypto -e ZZZZZZZZZZZZZZZZZZZZZZZZZZ message1 AaZz09 runs the Project with default Z configs
	
decrypt: bin						## runs the project with default configs
	@printf "[\e[0;36mINFO\e[0m] decrypting...\n"
	./crypto -d ZZZZZZZZZZZZZZZZZZZZZZZZZZ

-include $(wildcard *.d)