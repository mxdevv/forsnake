#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
      c = 1,
      s = 36
    ;
      ++t
      | (putchar(map[t % 64] + 48) | (((t % 8) == 7) && putchar('\n')))
      | (((t % 64) == 63) &&
          (printf("\e[%d;%dH", 1, 1)
              | (map[s] == -1 && c++)
              | (map[s] = c)
              | (v == 'a' && (s -= 1))
              | (v == 'w' && (s -= 8))
              | (v == 'd' && (s += 1))
              | (v == 's' && (s += 8))
              | (scanf("%lc", &v))
          )
        )
      | ((t % 640) == 639 &&
          (map[rand() % 64] = -1)
        )
    ;
      (map[t % 64] > 0 && map[t % 64]--)
  );
}
