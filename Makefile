all:
	gcc ./src/*.c -I include -o penalti

run:
	./penalti

clean:
	rm penalti

