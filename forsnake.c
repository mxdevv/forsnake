#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

struct termios termd, termc;
int s, c, v, t, map[8*8];

int
main(void)
{
  for( 
      tcgetattr(STDIN_FILENO, &termd),
      termc = termd, 
      termc.c_lflag &= ~(ICANON | ECHO),
      tcsetattr(STDIN_FILENO, TCSANOW, &termc),
      srand(time(0)),
      printf("\e[%d;%dH", 1, 1),
      c = 0
    ;
      ++t
      | (putchar(map[t] + 48) | (((t % 8) == 7) && putchar('\n')))
      | (((t % 64) == 63) &&
          (t = -1 | printf("\e[%d;%dH", 1, 1)
              | sleep(1))
          )
    ;

  );

  /*sleep(1);*/

  tcsetattr(STDIN_FILENO, TCSANOW, &termd);
}
