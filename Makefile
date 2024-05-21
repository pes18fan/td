all:
	@g++ main.cpp -o td

run: all
	@./td

clean:
	@rm -f ./td
