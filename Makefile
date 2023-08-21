run: a.out
	./a.out < in.in

a.out: sudoku.cpp
	@g++ sudoku.cpp -Wall -Wpedantic
	@echo "Compiled"


clean:
	@rm -rf a.out
	@echo "Cleaned"
