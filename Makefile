# OS specific part
ifeq ($(OS),Windows_NT)
	RM = del /S
	RMALLO = del /S *.o
	RMDIR = -RMDIR /S /Q
	MKDIR = -mkdir
	ERRIGNORE = 2>NUL || true
	SEP=\\
else
	RM = rm -f
	RMALLO = find . -type f -name '*.o' -print -delete
	RMDIR = rm -rf 
	MKDIR = mkdir -p
	ERRIGNORE = 2>/dev/null
	SEP=/
endif
PSEP = $(strip $(SEP))


# Define project directory
PROJDIR := $(realpath $(CURDIR)$(PSEP)..)


# Define src directory to compile main file
SOURCEDIR := $(subst /, $(PSEP), $(PROJDIR)$(PSEP)src$(PSEP))

OUT	:= calculator.exe

CC	 = gcc
FLAGS	 = -c -Wall
LFLAGS	 = 
INCLUDE = -I lib


.PHONY: all rebuild clean

all: libs main.o
	$(CC) -o $(OUT) src\main.o lib\functions.o

main.o: src\main.c
	$(CC) $(FLAGS) $(INCLUDE) -o src\main.o src\main.c

libs:
	cd lib && $(MAKE)


rebuild: clean all

clean:
	$(RMALLO)
	$(RM) $(OUT)
