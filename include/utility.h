/*
 * @author Feng Li, IUPUI
 * @date   2017
 */

#ifndef UTILITY_H
#define UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <errno.h>

#include "logging.h"

//#define SIZE_ONE (2)

// signed to unsigned, could also be implemented with bit operations
#define EVAL(a)  ((uint64_t)(a))

// status
typedef int status_t;
#define S_OK (0)
#define S_FAIL (-1)


#ifndef STRING_LENGTH
#define STRING_LENGTH (160)
#endif


#define RANK_SEQUENTIAL (-1)

static double get_cur_time() {
  struct timeval   tv;
  struct timezone  tz;
  double cur_time;

  gettimeofday(&tv, &tz);
  cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;
  //printf("%f\n",cur_time);

  return cur_time;
}

static void check_malloc(void * pointer){
  if (pointer == NULL) {
    perror("Malloc error!\n");
    fprintf (stderr, "at %s, line %d.\n", __FILE__, __LINE__);
    exit(1);
  }
}

#ifdef __cplusplus
}
#endif

#endif
