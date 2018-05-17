/*
 * @brief  test functionanlity of tranport selection
 *
 * @author Feng Li, lifen@iupui.edu, IUPUI
 * @date   2017
 */
#include <stdio.h>
#include "transports.h"

int main(int argc, char *argv[]){
    transport_method_t transport;
    transport = get_current_transport();
    printf("get tranport code %x, major %x, minor %x\n", transport, get_major(transport) , get_minor(transport));
    return 1;
}

