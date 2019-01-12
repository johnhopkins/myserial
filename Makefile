myserial: myserial.c
	gcc -std=c17 -Wall -Wextra myserial.c -lserialport -o myserial

launch: myserial
	./myserial

clean:
	rm -f *.so myserial 
