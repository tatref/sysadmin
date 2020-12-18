// Create zombie processes
// gcc zombies.c -o zombies

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid;
  int i; 

  for (i = 0; i < 2000; i++)  {  
    pid = fork();

    if (pid == -1) {
      printf("fork failed (check ulimit?)\n");
      exit(1);
    }

    if (pid > 0) {
      // parent process
      printf("Zombie #%d born\n", i + 1);

      //int child_status;
      //waitpid(pid, &child_status, 0);
      // oops we forgot to wait for the pid, so child is now a zombie!
    } else {
      // child process
      exit(0);
    }  
  }  
  // parent will wait
  printf("Done\n");
  sleep(100);

  return 0; 
}
