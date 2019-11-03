/**
 * @file main.c
 *
 * @brief Main function
 */

#include <stdio.h>
#include <stdbool.h>

#include "mcu.h"
#include "fsm.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/

/*****************************************
 * Main Function
 *****************************************/

fsm_t main_fsm;

int main(void) {
    fsm_init(&main_fsm);

    for (;;) {
        fsm_cycle(&main_fsm);
    }
}
