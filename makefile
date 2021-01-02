compile:
	clang++ ./src/clairvic.cpp -o ./out/clv

install: compile
	sudo mv ./out/clv /usr/bin/

run_example: compile 
	./out/clv/ 