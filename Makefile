all:
	@g++ main.cpp -o todo

run: all
	@./todo

clean:
	@rm -f ./todo
