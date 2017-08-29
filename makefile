default:
	gcc -o server *.c -pthread
gdb:
	gcc -o -g server *.c -pthread
