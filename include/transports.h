#ifndef TRANSPORT_H
#define TRANSPORT_H
/*
 * @brief type definition of different tranports
 *
 * @author Feng Li, IUPUI
 * @date   2017
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*
 * totally three types of transport methods are used
 *  I. adios-staging(DataSpaces/DIMES/Flexpath with ADIOS wrapper), 
 *  II.adios-mpiio(mature disk-based IO method suggested by ADIOS)
 *  III.native staging(native methods for DataSpaces and DIMES)
 *
 * To select different transport method, set environment method, such as
 *  * export Tranport=NATIVE_STAGING_DSPACES
 *
 * 0xff will returned for unsuported method
 */


/*
 * major method
 */
#define ADIOS_DISK (0)
#define ADIOS_STAGING (1)
#define NATIVE_STAGING (2)
#define MAJOR_NO_DEF (0xff)

/*
 * minor method
 */
#define DSPACES (0)
#define DIMES (1)
#define FLEXPATH (2)
#define MPIIO (3)
#define MINOR_NO_DEF (0xff)

/*
 * minor method
 */
typedef uint8_t transport_method_t;

/*
 * @brief construct method using major and minor methods
 */
#define construct_method(major, minor) \
    (major<<4 | minor)


#define get_major(method) \
    (method >> 4)

#define get_minor(method) \
    (method & 0x0f)


/*
 * @brief get current tranport method from environment variables
 *
 * @return  current tranport method
 */
//#include "utility.h"

static transport_method_t get_current_transport(){
    uint8_t major, minor; // method id
    char * transport_string; //input from user

    /*
     * must define tranport method!
     */
    minor = MAJOR_NO_DEF ;
    minor = MINOR_NO_DEF;

    /*
     * get the configuration from environment variable
     */
    if((transport_string = getenv("MyTransport")) != NULL){
        //clog_debug(CLOG(MY_LOGGER),"get string %s\n", transport_string);
        printf("get string %s\n", transport_string);

        /*
         * adios-mpiio
         */ 
        if(strcmp(transport_string, "ADIOS_DISK_MPIIO") == 0){
            major = ADIOS_DISK;
            minor = MPIIO;
        }

        /*
         * adios staging
         */
        else if (strcmp(transport_string, "ADIOS_STAGING_DSPACES") == 0){
            major = ADIOS_STAGING;
            minor = DSPACES;
        }
        else if (strcmp(transport_string, "ADIOS_STAGING_DIMES") == 0){
            major = ADIOS_STAGING;
            minor = DIMES;
        }

        else if (strcmp(transport_string, "ADIOS_STAGING_FLEXPATH") == 0){
            major = ADIOS_STAGING;
            minor = FLEXPATH;
        }

        /*
         * native staging
         */

        else if (strcmp(transport_string, "NATIVE_STAGING_DSPACES") == 0){
            major = NATIVE_STAGING;
            minor = DSPACES;
        }
        else if (strcmp(transport_string, "NATIVE_STAGING_DIMES") == 0){
            major = NATIVE_STAGING;
            minor = DIMES;
        }

        else{
            minor = MAJOR_NO_DEF ;
            minor = MINOR_NO_DEF;
        }
    }


    transport_method_t transport = construct_method(major, minor);
    printf("tranport code %x\n", transport);
    return transport;
}

#endif
