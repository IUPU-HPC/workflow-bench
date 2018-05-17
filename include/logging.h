/*
 * Description:
 *
 * First created: 2018 Mar 30
 * Last modified: 2018 Apr 09
 *
 * Author: Feng Li
 * e-mail: fengggli@yahoo.com
 *
 * this file is derived from here: https://github.com/IBM/comanche/blob/2be084c535c86eda316f204dc2aa9a839a463aa3/src/lib/common/include/common/logging.h
 * The origin author has the copyright
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <assert.h>
#include <stdio.h>

#define NORMAL_CYAN "\033[36m"
#define NORMAL_MAGENTA "\033[35m"
#define NORMAL_BLUE "\033[34m"
#define NORMAL_YELLOW "\033[33m"
#define NORMAL_GREEN "\033[32m"
#define NORMAL_RED "\033[31m"

#define BRIGHT "\033[1m"
#define NORMAL_XDK "\033[0m"
#define RESET "\033[0m"

#define BRIGHT_CYAN "\033[1m\033[36m"
#define BRIGHT_MAGENTA "\033[1m\033[35m"
#define BRIGHT_BLUE "\033[1m\033[34m"
#define BRIGHT_YELLOW "\033[1m\033[33m"
#define BRIGHT_GREEN "\033[1m\033[32m"
#define BRIGHT_RED "\033[1m\033[31m"

#define WHITE_ON_RED "\033[41m"
#define WHITE_ON_GREEN "\033[42m"
#define WHITE_ON_YELLOW "\033[43m"
#define WHITE_ON_BLUE "\033[44m"
#define WHITE_ON_MAGENTA "\033[44m"

#define ESC_LOG NORMAL_GREEN
#define ESC_DBG NORMAL_YELLOW
#define ESC_INF NORMAL_CYAN
#define ESC_WRN NORMAL_RED
#define ESC_ERR BRIGHT_RED
#define ESC_END "\033[0m"


#define PINF(f, a...) fprintf(stderr, "%s" f "%s\n", ESC_INF, ##a, ESC_END)
#define PWRN(f, a...) fprintf(stderr, "%s[WRN]: " f "%s\n", ESC_WRN, ##a, ESC_END)
#define PERR(f, a...) fprintf(stderr, "%sERROR %s:" f "%s\n", ESC_ERR, __FUNCTION__, ##a, ESC_END);

#ifdef DEBUG
#define PDBG(f, a...) fprintf(stderr, "%sDEBUG %s:" f "%s\n", ESC_DBG, __FUNCTION__, ##a, ESC_END);
#else 
#define PDBG(f, a...) ;
#endif

#define TRACE() fprintf(stderr, "[TRACE]: %s\n", __FUNCTION__)

#endif
