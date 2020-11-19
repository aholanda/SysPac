CFLAGS := -Wall -g

syspac.exe: main.c login.c paciente.c io.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) *.o *.exe