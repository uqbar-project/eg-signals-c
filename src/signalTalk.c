/*
 * signalTalk.c
 *
 *  Created on: 09/07/2013
 *      Author: Fernando
 */
/*
 * sig_talk.c
 *
 *  Created on: 09/07/2013
 *      Author: Internet
 */
/* sig_talk.c --- Example of how 2 processes can talk */
/* to each other using kill() and signal() */
/* We will fork() 2 process and let the parent send a few */
/* signals to it`s child  */

/* cc sig_talk.c -o sig_talk  */

//para Linux
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Para Windows
//#include <sys/types.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <process.h>
//#include <signal.h>
//#include <windows.h>

void sighup(); /* routines child will call upon sigtrap */
void sigint();
void sigquit();

int main(void) {
	/* Creamos un proceso hijo */
	int pid = fork(); // TODO: ojo que puede devolver -1
	int procesoHijo = pid == 0;

	if (procesoHijo) {
		/* Proceso hijo */
		/* Asociamos funciones para responder a cada signal */
		signal(SIGHUP, sighup);
		signal(SIGINT, sigint);
		signal(SIGBUS, sigquit);
		for (;;)
			; /* loop infinito */
	} else {
		/* Proceso padre */
		/* pid mantiene el identificador del proceso hijo */
		printf("PROCESS ID DEL HIJO: %d\n", pid);
		sleep(10);
		printf("\nPARENT: sending SIGHUP\n\n");
		kill(pid, SIGHUP);
		sleep(10);
		printf("\nPARENT: sending SIGINT\n\n");
		kill(pid, SIGINT);
		sleep(10);
		printf("\nPARENT: sending SIGBUS\n\n");
		sleep(10);
		kill(pid, SIGBUS);
		sleep(10);
	}
	return 0;

}

void sighup() {
	printf("CHILD: I have received a SIGHUP\n");
	signal(SIGHUP, sighup); /* reset signal */
}

void sigint() {
	printf("CHILD: I have received a SIGINT\n");
	signal(SIGINT, sigint); /* reset signal */
}

void sigquit() {
	printf("My DADDY has Killed me!!!\n");
	exit(0);
}
