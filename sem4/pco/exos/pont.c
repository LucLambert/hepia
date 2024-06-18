#include <stdio.h>
#include <stdlib.h>
#include "thread_wrapper.h"

// bridge = semaphore(8);

// car() {
//     while (true) {
//         drive_around(long_time)
//         wait(bridge)
//         cross_bridge(short_time)
//         post(bridge)
//     }
// }
// truck() {
//     while (true) {
//         drive_around(long_time)
//         wait(bridge)
//         wait(bridge)
//         cross_bridge(short_time)
//         post(bridge)
//         post(bridge)
//     }
// }

int main(int argc, char** argv){
    if(argc != 4){
        fprintf(stderr,"Usage : %s m_voiture m_camion charge_pont\n", argv[0]);
        return 0;
    }
    int m_car = atoi(argv[1]);
    int m_truck = atoi(argv[2]);
    int m_bridge = atoi(argv[3]);

    if (m_bridge <= m_truck) {
        fprintf(stderr,"la charge maximale du pont doit être supérieur à celle d'un camion\n");
        return 0;
    }
    if (m_car >= m_truck) {
        fprintf(stderr,"la masse d'une voiture doit être inférieur à celle d'un camion\n");
        return 0;
    }


}