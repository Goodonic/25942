#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
#ifdef _WIN32
  if (_putenv_s("TZ", "PST8") != 0) {
#else
    if (setenv("TZ", "PST8", 1) != 0) {
#endif
    perror("TZ");
    return EXIT_FAILURE;
  }

#ifdef _WIN32
  _tzset();
#else
  tzset();
#endif

  time_t now = time(NULL);
  if (now == (time_t) -1) {
    perror("time");
    return EXIT_FAILURE;
  }

  struct tm *california_time = localtime(&now);
  if (california_time == NULL) {
    perror("localtime");
    return EXIT_FAILURE;
  }

  char buffer[64];
  if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S PST",
               california_time) == 0) {
    fputs("Could not format time\n", stderr);
    return EXIT_FAILURE;
  }

  puts(buffer);
  return EXIT_SUCCESS;
}
//TODO Переделать вручную