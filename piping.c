#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>

double phi = 1.6180339887;

int READ = 0;
int WRIT = 1;

int main() {
  int uno[2], due[2];

  pipe(uno);
  pipe(due);

  if (fork() == 0) {
    int n;

    close(uno[READ]);
    close(due[WRIT]);

    read(due[READ], &n, sizeof(int));

    printf("[child] performing operation on %d\n", n);
    n = round((pow(phi, n) - pow(1-phi, n)) / sqrt(5));
    printf("[child] computed %d\n", n);
    write(uno[WRIT], &n, sizeof(int));
  } else {
    srand(time(NULL));

    close(uno[WRIT]);
    close(due[READ]);
    
    int n = rand() % 50;
    write(due[WRIT], &n, sizeof(int));
    printf("[parent] sending %d to child\n", n);

    read(uno[READ], &n, sizeof(int));
    printf("[parent] recieved %d from child\n", n);

    return 0;
  }
}
    
    
