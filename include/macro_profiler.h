/**
 * \file macro_profiler.h
 * \brief Déclaration des macros PROFILE et return.
 * \author KUOCH Maxime et LAMBERT-DELAVAQUERIE Fabien
 */
#ifndef __MACRO_PROFILER__
#define __MACRO_PROFILER__


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BILLION (double)1000000000L

/**
 * \def PROFILE
 * \brief Macro PROFILE
 */
#define PROFILE struct timespec __time__; \
                FILE *filelog; \
                if(strcmp(__FUNCTION__, "main") == 0) \
                    filelog = fopen("KUOCH_LAMBERT.log", "w+"); \
                else \
                if ( (filelog = fopen("KUOCH_LAMBERT.log", "a")) == NULL ) { \
                    fprintf(stderr, "File could not be open\n"); \
                    exit(EXIT_FAILURE); \
                } \
                clock_gettime(CLOCK_REALTIME, &__time__); \
                fprintf(filelog, "%s -- time : %.6lfs\n", __FUNCTION__, (__time__.tv_sec + (__time__.tv_nsec / BILLION))); \
                fclose(filelog);

/**
 * \def return 
 * \brief Macro return
 */
#define return  struct timespec __end__; \
                FILE* fileend; \
                if ( (fileend = fopen("KUOCH_LAMBERT.log", "a")) == NULL ) { \
                    fprintf(stderr, "File could not be open\n"); \
                    exit(EXIT_FAILURE); \
                } \
                clock_gettime(CLOCK_REALTIME, &__end__); \
                fprintf(fileend, "END -- time : %.6lfs\n", (__end__.tv_sec + (__end__.tv_nsec / BILLION))); \
                fclose(fileend); \
                return


#endif
