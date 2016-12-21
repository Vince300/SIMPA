#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


pid_t pid;

void kill_it();

int main(int argc, char **argv)
{
  int delay;
  int status;

  delay = atoi(argv[1]);
/*  printf("1: %s, 2: %s delay: %d\n", argv[1], argv[2], delay); */
  fflush(stdout);
  if ((pid=fork()) == 0)
    /* child fork:  execute and terminate */
    execvp(argv[2], argv + 2);
/*  printf("pid: %d\n", pid); */
  signal(SIGALRM, kill_it);
  alarm(delay);
  wait(&status);
  exit(0);
}

void kill_it()
{
  kill(pid, SIGKILL);
  exit(30);
}
