# Rutvik Patel
# 1530012
# CMPUT 379: Assignment 1
# mini shell

#  This makefile allows the user to link, compile and clean the files
#  necessary to run the package
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
CC = gcc # compiler of choice
CFLAGS = -g -Wall # compile flags
OBJS = main.o util.o # object files generated
EXC = shell379 # executable name

# builds the project
$(EXC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXC) $(OBJS)

main.o: main.c util.h
	$(CC) -c main.c

util.o: util.c util.h
	$(CC) -c util.c


# removes the .o and executable files from the directory
clean:
	@rm -f $(OBJS) $(EXC)

# printing out the makefile target objectives
help:
	@echo 'make (shell379) : builds the project and generates the shell379 executable'
	@echo 'make main.o     : compiles main.cpp into its respective object (.o) file'
	@echo 'make clean      : removes the .o and executable files from the directory'
	@echo 'make help       : prints out information about the targets of the make file'


