# Rutvik Patel
# 1530012
# CMPUT 379: Assignment 1
# mini shell

#  This makefile allows the user to link, compile and clean the files
#  necessary to run the package
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
CC = gcc # compiler of choice
CFLAGS = -g -Wall # compile flags
OBJS = main.o # object files generated
EXC = shell379 # executable name

# builds the project
$(EXC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXC) $(OBJS)

main.o: main.c
	$(CC) -c main.c

# removes the .o and executable files from the directory
clean:
	@rm -f $(OBJS) $(EXC)

# printing out the makefile target objectives
help:
	@echo 'make        : '
	@echo 'make .o : '
	@echo 'make      : '
	@echo 'make clean        : removes the .o and executable files from the directory'
	@echo 'make help         : prints out information about the targets of the make file'


