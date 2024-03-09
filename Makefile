CC = gcc
files := $(wildcard commands/*.c)

clean: run
	@rm -r output

run: compile
	@./output

compile:
	@$(CC) main.c $(files) -o output