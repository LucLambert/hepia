#include <cr_section_macros.h>
#include <stdint.h>
__DATA(RAM2) uint16_t sig_ref[]={32784,32768,32736,32880,32960,32832,32704,32800,32944,
32912,32752,32736,32880,32944,32832,32720,32800,32944,32912,
32768,32736,32880,32944,32832,32720,32800,32944,32912,32768,
32752,32896,32960,32832,32736,32800,32944,32912,32752,32752,
32896,32944,32832,32736,32816,32944,32896,32736,32736,32896,
32944,32816,32720,32800,32944,32896,32752,32752,32896,32944,
32816,32720,32832,32944,32896,32752,32752,32896,32944,32816,
32720,32816,32944,32896,32736,32736,32896,32944,32816,32720,
32816,32944,32880,32736,32752,32912,32944,32800,32720,32816,
32944,32880,32736,32752,32912,32944,32800,32720,32832,32944,
32896,32736,32752,32912,32944,32800,32720,32832,32944,32880,
32736,32768,32912,32944,32816,32720,32832,32960,32880,32752,
32768,32912,32944,32800,32720,32832,32960,32880,32736,32752,
32912,32928,32800,32720,32832,32960,32864,32720,32768,32912,
32944,32800,32720,32848,32960,32880,32720,32768,32912,32944,
32800,32720,32848,32944,32880,32736,32768,32912,32928,32784,
32720,32848,32944,32880,32736,32768,32928,32928,32784,32720,
32848,32960,32864,32720,32784,32928,32944,32784,32720,32848,
32960,32864,32720,32784,32912,32928,32784,32736,32848,32960,
32864,32736,32768,32928,32928,32784,32736,32864,32960,32880,
32736,32784,32928,32928,32784,32736,32864,32960,32864,32736,
32784,32944,32928,32768,32720,32864,32960,32848,32720,32784,
32928,32928,32768,32736,32864,32960,32848,32736,32784,32928,
32912,32768,32720,32864,32960,32848,32720,32784,32928,32912,
32752,32736,32864,32960,32848,32720,32784,32928,32912,32768,
32736,32880,32960,32832,32720,32800,32928,32912,32752,32720,
32880,32944,32832,32720,32800,32944,32912,32752,32736,32880,
32960,32832,32720,32800,32944,32912,32752,32736,32880,32976,
32832,32736,32800,32960,32912,32768,32736,32896,32944,32848,
32720,32816,32944,32912,32752,32752,32896,32960,32816,32720,
32816,32944,32896,32752,32736,32880,32960,32816,32720,32800,
32944,32896,32752,32736,32896,32944,32832,32720,32816,32944,
32896,32752,32736,32896,32944,32816,32720,32832,32944,32896,
32736,32736,32896,32944,32816,32720,32832,32960,32896,32736,
32752,32896,32944,32816,32720,32832,32944,32880,32736,32752,
32896,32944,32816,32720,32816,32960,32880,32752,32752,32912,
32944,32816,32720,32832,32960,32896,32752,32752,32912,32944,
32816,32720,32848,32960,32880,32736,32752,32912,32944,32816,
32720,32832,32944,32880,32736,32752,32912,32928,32784,32720,
32832,32960,32864,32736,32752,32912,32944,32800,32704,32832,
32960,32880,32736,32768,32912,32944,32784,32720,32848,32944,
32864,32736,32768,32912,32944,32784,32720,32848,32960,32864,
32736,32768,32928,32944,32784,32720,32848,32944,32864,32720,
32768,32928,32928,32784,32720,32864,32960,32880,32720,32784,
32928,32944,32784,32736,32848,32960,32864,32720,32784,32928,
32944,32784,32736,32864,32960,32864,32736,32784,32928,32928,
32784,32736,32864,32960,32864,32720,32784,32928,32912,32768,
32720,32864,32960,32848,32720,32784,32928,32912,32768,32736,
32864,32960,32848,32720,32784,32928,32912,32784,32720,32864,
32944,32848,32720,32784,32944,32912,32768,32720,32880,32960,
32848,32720,32784,32928,32912,32768,32720,32864,32944,32848,
32720,32800,32944,32912,32768,32736,32880,32960,32832,32720,
32800,32944,32912,32768,32736,32864,32960,32832,32720,32800,
32944,32912,32752,32736,32880,32960,32848,32736,32816,32944,
32912,32768,32736,32896,32960,32832,32720,32816,32944,32912,
32752,32736,32880,32944,32832,32720,32800,32944,32912,32752,
32736,32880,32944,32816,32720,32800,32944,32896,32752,32752,
32896,32944,32816,32720,32816,32944,32896,32736,32736,32896,
32944,32816,32704,32816,32944,32896,32752,32752,32896,32944,
32816,32704,32816,32944,32896,32736,32736,32896,32944,32816,
32720,32816,32944,32896,32736,32752,32896,32944,32816,32720,
32816,32960,32896,32752,32752,32912,32944,32816,32736,32832,
32960,32896,32752,32752,32912,32960,32816,32720,32848,32960,
32880,32752,32752,32912,32944,32816,32720,32832,32960,32880,
32720,32752,32912,32944,32800,32720,32832,32960,32880,32736,
32768,32912,32928,32800,32720,32848,32960,32880,32720,32752,
32912,32928,32784,32704,32832,32944,32880,32736,32768,32912,
32928,32784,32720,32832,32960,32864,32720,32768,32928,32928,
32784,32720,32848,32960,32864,32720,32768,32912,32928,32784,
32720,32848,32960,32864,32736,32768,32928,32928,32784,32720,
32848,32960,32864,32736,32784,32928,32928,32784,32720,32864,
32960,32864,32736,32784,32928,32944,32784,32720,32848,32960,
32864,32720,32768,32928,32928,32784,32720,32864,32944,32864,
32720,32784,32944,32928,32784,32720,32864,32960,32848,32720,
32784,32944,32912,32768,32720,32864,32944,32848,32720,32784,
32944,32912,32768,32720,32864,32944,32848,32720,32784,32928,
32928,32768,32720,32864,32944,32848,32720,32784,32928,32912,
32768,32736,32864,32944,32848,32720,32800,32944,32912,32768,
32736,32880,32960,32832,32720,32816,32944,32928,32768,32752,
32880,32960,32848,32736,32816,32944,32912,32768,32736,32880,
32960,32848,32720,32800,32944,32912,32768,32736,32880,32944,
32832,32720,32800,32944,32912,32752,32736,32896,32960,32816,
32720,32800,32944,32912,32752,32736,32896,32944,32816,32720,
32816,32944,32896,32752,32736,32880,32944,32816,32720,32816,
32944,32896,32752,32736,32896,32944,32816,32720,32816,32960,
32896,32752,32736,32896,32944,32816,32720,32816,32944,32896,
32752,32736,32896,32960,32816,32736,32816,32960,32896,32736,
32752,32896,32960,32816,32720,32832,32960,32896,32752,32752,
32912,32944,32816,32720,32832,32960,32896,32736,32752,32912,
32944,32800,32720,32832,32960,32880,32736,32768,32896,32944,
32800,32720,32832,32944,32880,32720,32752,32912,32928,32800,
32720,32832,32944,32880,32736,32768,32912,32944,32800,32720,
32832,32944,32880,32736,32768,32912,32944,32784,32720,32848,
32960,32864,32736,32768,32912,32944,32784,32704,32832,32944,
32864,32720,32768,32912,32944,32784,32720,32848,32960,32864,
32720,32768,32912,32944,32784,32736,32848,32976,32880,32736,
32768,32928,32928,32800,32720,32864,32960,32880,32736,32784,
32928,32928,32784,32720,32848,32960,32848,32720,32768,32928,
32928,32768,32720,32848,32960,32864,32736,32784,32928,32928,
32784,32720,32864,32944,32848,32720,32784,32928,32912,32768,
32736,32864,32960,32848,32720,32784,32928,32912,32768,32720,
32864,32944,32848,32720,32784,32928,32928,32768,32720,32864,
32944,32848,32720,32784,32928,32912,32768,32736,32880,32960,
32848,32720,32784,32944,32912,32768,32720,32880,32960,32832,
32720,32816,32944,32928,32768,32736,32880,32960,32848,32720,
32800,32944,32912,32768,32736,32880,32960,32832,32720,32800,
32944,32896,32752,32736,32880,32944,32832,32720,32800,32944,
32912,32752,32736,32880,32944,32816,32720,32800,32944,32912,
32752,32736,32880,32960,32816,32720,32816,32944,32896,32752,
32736,32880,32944,32816,32720,32816,32944,32896,32752,32736,
32896,32944,32816,32720,32816,32944,32896,32736,32752,32896,
32944,32816,32720,32816,32944,32912,32752,32752,32896,32944,
32816,32720,32832,32960,32912,32752,32768,32896,32960,32816,
32736,32832,32960,32896,32736,32752,32912,32944,32816,32720,
32832,32944,32896,32736,32752,32912,32944,32800,32720,32832,
32944,32880,32736,32752,32896,32944,32800,32720,32832,32944,
32880,32736,32768,32912,32944,32800,32720,32832,32944,32880,
32736,32752,32912,32944,32800,32720,32832,32960,32880,32736,
32768,32912,32944,32784,32720,32832,32944,32880,32736,32768,
32912,32928,32800,32720,32832,32944,32880,32720,32768,32912,
32944,32800,32720,32848,32960,32864,32736,32768,32928,32928,
32800,32736,32848,32960,32880,32736,32768,32928,32928,32800,
32736,32864,32960,32864,32736,32784,32928,32944,32784,32720,
32864,32960,32864,32720,32784,32928,32928,32784,32720,32848,
32960,32864,32720,32784,32928,32912,32784,32720,32864,32944,
32864,32720,32784,32928,32928,32768,32720,32848,32960,32848,
32720,32784,32928,32928,32768,32720,32864,32944,32848,32720,
32784,32928,32928,32784,32736,32880,32960,32848,32720,32784,
32928,32912,32768,32736,32864,32960,32848,32736,32784,32944,
32912,32784,32736,32864,32960,32848,32736,32800,32944,32912,
32784,32736,32880,32960,32848,32720,32800,32944,32912,32768,
32736,32880,32960,32832,32720,32800,32944,32912,32752,32720,
32880,32960,32832,32720,32800,32944,32912,32752,32736,32880,
32944,32848,32720,32800,32928,32912,32752,32736,32880,32944,
32832,32720,32800,32944,32896,32768,32736,32896,32944,32816,
32720,32800,32944,32896,32752,32736,32896,32944,32816,32720,
32816,32944,32896,32752,32752,32896,32944,32816,32720,32816,
32960,32896,32752,32752,32896,32944,32816,32720,32816,32960,
32896,32752,32736,32896,32960,32816,32736,32832,32960,32896,
32752,32752,32912,32944,32816,32720,32832,32960,32896,32752,
32752,32896,32944,32800,32720,32832,32960,32880,32736,32752,
32912,32944,32800,32720,32832,32960,32880,32736,32752,32912,
32944,32800,32720,32832,32944,32880,32736,32752,32912,32928,
32800,32720,32832,32960,32880,32736,32768,32912,32944,32800,
32720,32832,32944,32864,32736,32768,32912,32928,32800,32720,
32832,32960,32864,32720,32768,32912,32928,32784,32720,32848,
32960,32864,32736,32768,32928,32944,32800,32720,32848,32960,
32864,32736,32784,32912,32944,32800,32720,32848,32960,32880,
32736,32768,32928,32944,32800,32736,32848,32960,32864,32736,
32768,32928,32928,32784,32720,32864,32960,32864,32736,32768,
32912,32928,32784,32720,32864,32944,32864,32720,32784,32928,
32928,32784,32720,32864,32960,32848,32720,32784,32928,32912,
32768,32720,32864,32944,32848,32720,32784,32928,32928,32768,
32720,32864,32960,32848,32736,32784,32928,32912,32768,32736,
32864,32944,32848,32720,32784,32944,32912,32768,32736,32880,
32960,32848,32720,32800,32928,32912,32784,32736,32880,32960,
32848,32720,32800,32944,32928,32768,32736,32880,32960,32832,
32720,32800,32944,32912,32768,32736,32880,32960,32832,32720,
32800,32944,32912,32752,32720,32880,32960,32832,32720,32800,
32944,32896,32752,32736,32880,32960,32832,32720,32800,32944,
32896,32768,32736,32880,32960,32832,32720,32816,32944,32896,
32752,32736,32880,32944,32832,32720,32816,32944,32896,32736,
32736,32880,32944,32816,32720,32816,32944,32896,32736,32736,
32896,32944,32832,32720,32816,32944,32896,32752,32752,32896,
32960,32816,32720,32832,32960,32912,32752,32752,32896,32960,
32816,32720,32816,32960,32896,32752,32752,32912,32944,32816,
32720,32816,32944,32880,32736,32752,32896,32944,32800,32720,
32816,32944,32896,32736,32752,32912,32944,32800,32720,32816,
32944,32880,32736,32752,32912,32944,32800,32720,32832,32944,
32880,32736,32752,32912,32944,32800,32720,32832,32944,32880,
32736,32768,32912,32944,32784,32720,32832,32960,32880,32736,
32768,32912,32944,32784,32720,32832,32944,32864,32736,32752,
32912,32944,32800,32720,32848,32960,32880,32736,32768,32912,
32944,32800,32720,32864,32960,32880,32736,32784,32928,32944,
32784,32736,32864,32960,32864,32736,32768,32928,32928,32784,
32720,32864,32960,32864,32720,32768,32928,32928,32784,32720,
32864,32960,32864,32720,32768,32928,32928,32784,32720,32864,
32960,32864,32720,32784,32928,32928,32768,32720,32864,32960,
32848,32720,32768,32928,32912,32768,32720,32864,32960,32848,
32720,32784,32928,32912,32768,32736,32864,32960,32848,32720,
32784,32928,32912,32768,32720,32864,32944,32848,32720,32784,
32928,32928,32768,32736,32880,32960,32848,32720,32800,32944,
32928,32768,32752,32880,32960,32848,32736,32800,32944,32912,
32768,32720,32880,32960,32848,32720,32800,32944,32912,32752,
32736,32880,32944,32832,32720,32800,32928,32912,32752,32736,
32880,32960,32832,32720,32800,32944,32912,32752,32736,32880,
32944,32816,32720,32800,32944,32912,32752,32736,32880,32944,
32832,32720,32800,32944,32912,32752,32736,32896,32960,32832,
32720,32816,32944,32896,32752,32736,32896,32944,32816,32720,
32816,32944,32896,32736,32752,32896,32960,32816,32720,32816,
32960,32896,32752,32752,32896,32960,32816,32720,32816,32960,
32896,32752,32752,32896,32944,32816,32720,32832,32944,32896,
32752,32752,32896,32944,32816,32720,32816,32944,32880,32736,
32752,32896,32944,32816,32720,32832,32944,32880,32736,32752,
32912,32944,32800,32720,32832,32960,32880,32736,32752,32896,
32944,32800,32720,32832,32944,32880,32736,32752,32912,32944,
32800,32720,32832,32960,32880,32736,32752,32912,32944,32800,
32720,32848,32960,32880,32736,32768,32912,32928,32784,32720,
32848,32960,32864,32736,32768,32928,32944,32800,32720,32848,
32960,32864,32736,32768,32928,32944,32800,32720,32848,32944,
32864,32752,32768,32928,32944,32800,32720,32864,32960,32864,
32736,32768,32928,32928,32784,32720,32848,32944,32864,32720,
32784,32928,32928,32768,32736,32848,32960,32864,32720,32784,
32928,32928,32784,32720,32864,32960,32848,32720,32784,32928,
32912,32784,32720,32864,32960,32864,32720,32784,32928,32928,
32768,32736,32864,32960,32848,32720,32784,32928,32912,32768,
32720,32864,32944,32848,32720,32800,32944,32928,32768,32736,
32880,32960,32848,32720,32784,32928,32928,32768,32752,32880,
32976,32848,32736,32800,32960,32912,32768,32736,32880,32960,
32848,32720,32800,32944,32912,32752,32736,32880,32944,32832,
32720,32800,32944,32912,32768,32720,32880,32944,32832,32720,
32800,32944,32912,32752,32736,32880,32944,32832,32720,32800,
32944,32896,32752,32736,32880,32944,32832,32704,32800,32944,
32896,32752,32736,32880,32960,32816,32720,32800,32944,32896,
32752,32736,32896,32944,32816,32720,32800,32944,32896,32736,
32752,32896,32960,32816,32736,32800,32960,32896,32752,32752,
32896,32960,32816,32736,32816,32960,32896,32752,32752,32912,
32960,32832,32720,32816,32944,32896,32752,32752,32896,32960,
32816,32704,32832,32944,32880,32736,32736,32896,32944,32800,
32720,32816,32944,32880,32736,32752,32896,32944,32800,32720,
32832,32944,32896,32736,32752,32912,32944,32800,32720,32832,
32944,32880,32736,32752,32912,32944,32800,32720,32832,32960,
32880,32736,32752,32912,32944,32800,32720,32832,32944,32880,
32720,32768,32912,32944,32800,32720,32832,32960,32880,32752,
32752,32928,32944,32800,32720,32848,32960,32864,32736,32784,
32928,32944,32800,32720,32864,32960,32880,32736,32768,32912,
32944,32784,32720,32848,32960,32864,32736,32768,32912,32928,
32784,32720,32864,32960,32864,32736,32768,32928,32928,32784,
32720,32848,32944,32864,32736,32784,32928,32928,32784,32720,
32864,32960,32864,32720,32784,32912,32928,32768,32736,32848,
32944,32848,32720,32784,32928,32928,32784,32720,32864,32960,
32848,32720,32784,32928,32912,32768,32720,32864,32944,32848,
32720,32784,32928,32928,32768,32736,32864,32960,32848,32720,
32800,32944,32928,32768,32736,32880,32960,32848,32736,32800,
32944,32912,32768,32736,32880,32960,32848,32720,32800,32944,
32912,32752,32736,32880,32944,32832,32720,32784,32944,32912,
32752,32736,32880,32960,32832,32720,32800,32944,32912,32768,
32736,32880,32960,32832,32720,32800,32928,32896,32752,32736,
32880,32960,32832,32720,32800,32928,32912,32752,32736,32880,
32944,32832,32720,32800,32944,32912,32752,32736,32896,32944,
32832,32720,32816,32944,32912,32752,32752,32896,32944,32816,
32720,32816,32944,32896,32752,32752,32896,32960,32816,32736,
32816,32960,32896,32752,32752,32896,32944,32816,32720,32816,
32960,32896,32752,32752,32896,32960,32816,32720,32816,32944,
32880,32736,32752,32896,32960,32816,32720,32816,32960,32896,
32736,32752,32896,32944,32816,32720,32832,32944,32880,32736,
32752,32912,32944,32800,32720,32832,32944,32880,32720,32752,
32912,32944,32800,32720,32832,32960,32880,32736,32752,32912,
32944,32800,32720,32832,32944,32880,32736,32768,32912,32944,
32800,32736,32832,32960,32880,32736,32752,32912,32944,32800,
32736,32848,32960,32880,32752,32768,32928,32944,32800,32720,
32848,32944,32880,32736,32784,32912,32944,32784,32720,32848,
32944,32880,32720,32768,32912,32928,32784,32720,32848,32944,
32864,32736,32768,32912,32928,32784,32720,32848,32944,32864,
32720,32768,32928,32928,32768,32720,32848,32944,32848,32720,
32784,32928,32928,32784,32720,32848,32960,32864,32720,32784,
32928,32928,32784,32720,32864,32960,32864,32720,32784,32928,
32928,32768,32720,32864,32944,32848,32736,32784,32928,32912,
32768,32736,32864,32960,32848,32720,32784,32944,32912,32784,
32736,32880,32960,32848,32720,32784,32944,32912,32768,32736,
32880,32960,32848,32720,32784,32928,32912,32768,32720,32864,
32960,32832,32720,32784,32928,32912,32768,32736,32880,32944,
32832,32720,32800,32944,32912,32768,32736,32880,32960,32832,
32720,32784,32928,32912,32752,32736,32880,32944,32816,32720,
32800,32944,32912,32752,32736,32880,32944,32816,32720,32816,
32944,32896,32752,32736,32880,32960,32832,32720,32800,32944,
32912,32752,32752,32896,32960,32832,32720,32816,32944,32896,
32752,32752,32896,32960,32816,32720,32832,32960,32896,32768,
32752,32896,32960,32816,32720,32816,32960,32912,32752,32752,
32896,32944,32816,32720,32816,32944,32896,32752,32752,32896,
32944,32816,32720,32816,32960,32896,32752,32752,32896,32944,
32816,32720,32832,32944,32896,32736,32752,32896,32928,32800,
32720,32832,32960,32880,32736,32752,32896,32944,32800,32720,
32832,32960,32880,32736,32752,32912,32944,32800,32720,32832,
32944,32880,32736,32752,32912,32944,32800,32720,32832,32960,
32880,32736,32752,32912,32944,32784,32720,32848,32976,32880,
32752,32768,32928,32944,32800,32720,32848,32960,32880,32736,
32768,32928,32944,32800,32720,32848,32960,32864,32720,32768,
32912,32928,32784,32720,32848,32960,32848,32736,32768,32912,
32928,32784,32720,32848,32960,32864,32720,32768,32928,32928,
32784,32720,32848,32960,32864,32720,32768,32928,32928,32784,
32720,32848,32960,32864,32720,32768,32912,32928,32768,32720,
32864,32960,32864,32720,32784,32928,32912,32768,32720,32864,
32960,32848,32720,32784,32944,32928,32784,32720,32864,32960,
32864,32720,32784,32928,32912,32784,32720,32864,32960,32864,
32720,32800,32928,32928,32768,32736,32864,32960,32848,32720,
32800,32960,32912,32768,32736,32880,32960,32832,32720,32784,
32944,32912,32768,32720,32880,32960,32832,32720,32800,32944,
32912,32752,32736,32864,32960,32848,32720,32800,32944,32912,
32752,32736,32880,32944,32832,32704,32800,32944,32912,32752,
32736,32880,32960,32832,32720,32800,32944,32896,32752,32736,
32880,32960,32832,32720,32816,32928,32896,32752,32736,32896,
32944,32832,32704,32816,32944,32896,32752,32752,32896,32944,
32832,32720,32816,32944,32912,32752,32752,32896,32960,32832,
32720,32816,32944,32896,32752,32752,32896,32960,32816,32720,
32816,32960,32896,32736,32752,32896,32944,32816,32704,32816,
32944,32896,32752,32752,32912,32944,32816,32720,32816,32944,
32896,32736,32752,32896,32944,32800,32720,32816,32944,32880,
32752,32752,32896,32944,32800,32720,32832,32960,32880,32736,
32752,32912,32944,32800,32720,32832,32944,32880,32736,32752,
32912,32944,32800,32720,32832,32960,32880,32736,32752,32912,
32944,32800,32720,32832,32960,32880,32752,32752,32912,32944,
32816,32720,32848,32960,32880,32736,32768,32912,32944,32800,
32736,32848,32960,32864,32736,32768,32912,32944,32784,32720,
32848,32960,32864,32736,32768,32912,32928,32784,32720,32848,
32960,32864,32720,32768,32912,32928,32784,32720,32848,32960,
32864,32720,32768,32912,32928,32784,32720,32848,32960,32864,
32720,32768,32928,32928,32784,32720,32848,32944,32848,32720,
32784,32928,32928,32768,32720,32848,32960,32848,32736,32784,
32944,32928,32784,32720,32864,32960,32848,32736,32784,32944,
32928,32784,32736,32880,32960,32848,32720,32800,32944,32928,
32768,32736,32864,32960,32848,32720,32784,32928,32912,32768,
32720,32864,32944,32848,32720,32784,32928,32912,32768,32720,
32864,32944,32832,32720,32800,32944,32912,32768,32736,32880,
32944,32832,32720,32800,32944,32912,32768,32736,32880,32960,
32832,32720,32800,32944,32912,32768,32736,32880,32960,32832,
32720,32800,32944,32912,32752,32736,32880,32944,32816,32720,
32800,32944,32912,32752,32736,32896,32960,32832,32720,32816,
32944,32896,32768,32736,32896,32960,32832,32720,32816,32944,
32912,32752,32752,32896,32960,32816,32720,32816,32944,32896,
32752,32752,32896,32944,32816,32720,32816,32944,32896,32752,
32736,32896,32944,32816,32720,32816,32944,32896,32736,32752,
32896,32944,32816,32720,32816,32944,32896,32736,32736,32896,
32944,32816,32720,32832,32944,32896,32736,32752,32896,32944,
32800,32704,32832,32944,32880,32736,32752,32896,32944,32800,
32720,32816,32944,32880,32736,32752,32912,32944,32816,32720,
32832,32960,32880,32736,32752,32912,32944,32816,32720,32848,
32960,32880,32736,32768,32912,32944,32800,32720,32832,32944,
32880,32736,32768,32912,32944,32800,32720,32848,32944,32880,
32736,32768,32912,32944,32784,32720,32848,32960,32864,32736,
32752,32912,32944,32800,32720,32848,32960,32864,32720,32768,
32912,32928,32784,32720,32848,32944,32864,32720,32768,32912,
32944,32784,32720,32848,32944,32864,32720,32768,32912,32928,
32784,32720,32864,32944,32864,32720,32784,32928,32928,32784,
32736,32864,32960,32848,32736,32784,32928,32928,32784,32736,
32864,32960,32864,32736,32784,32944,32928,32784,32720,32864,
32960,32864,32720,32784,32944,32928,32768,32720,32864,32944,
32848,32720,32784,32928,32928,32768,32720,32864,32960,32848,
32720,32784,32944,32912,32768,32720,32880,32960,32848,32720,
32800,32928,32912,32768,32720,32864,32960,32832,32704,32800,
32944,32912,32752,32736,32880,32944,32832,32720,32800,32928,
32912,32752,32720,32864,32944,32832,32720,32800,32944,32912,
32752,32736,32880,32960,32832,32720,32800,32928,32912,32768,
32752,32896,32960,32832,32720,32800,32944,32912,32768,32736,
32896,32944,32832,32720,32816,32944,32896,32752,32736,32880,
32944,32816,32720,32800,32944,32896,32752,32752,32880,32960,
32832,32720,32800,32944,32896,32752,32736,32896,32944,32816,
32720,32816,32944,32896,32752,32736,32896,32944,32816,32720,
32816,32944,32896,32736,32752,32896,32944,32816,32720,32816,
32944,32896,32736,32736,32896,32944,32800,32720,32832,32944,
32896,32736,32752,32896,32944,32800,32720,32832,32960,32896,
32736,32768,32912,32944,32800,32736,32832,32960,32880,32752,
32768,32912,32944,32816,32720,32832,32960,32880,32736,32752,
32912,32944,32800,32720,32832,32944,32880,32736,32752,32912,
32944,32784,32720,32832,32960,32880,32720,32768,32912,32928,
32784,32720,32832,32944,32880,32720,32752,32912,32928,32784,
32720,32848,32944,32864,32736,32768,32912,32928,32784,32720,
32848,32960,32864,32720,32768,32928,32928,32784,32720,32848,
32960,32864,32720,32784,32912,32944,32784,32736,32848,32960,
32880,32720,32784,32928,32928,32784,32736,32864,32944,32848,
32720,32784,32928,32928,32784,32736,32864,32960,32864,32720,
32784,32928,32912,32768,32720,32848,32960,32848,32720,32784,
32944,32912,32784,32720,32864,32960,32848,32720,32784,32928,
32928,32768,32736,32864,32960,32848,32720,32784,32944,32928,
32768,32736,32864,32960,32848,32720,32784,32928,32912,32768,
32736,32864,32960,32832,32720,32784,32944,32912,32752,32736,
32880,32960,32848,32720,32800,32944,32912,32768,32736,32880,
32960,32832,32736,32800,32944,32912,32768,32736,32880,32944,
32848,32720,32800,32944,32912,32768,32736,32896,32960,32832,
32720,32800,32944,32896,32752,32736,32880,32960,32832,32720,
32800,32944,32896,32752,32736,32896,32944,32832,32720,32816,
32944,32912,32752,32736,32880,32944,32816,32720,32800,32944,
32896,32752,32736,32896,32944,32816,32704,32816,32944,32896,
32752,32736,32896,32944,32816,32720,32816,32944,32896,32736,
32736,32896,32944,32816,32720,32816,32960,32896,32752,32752,
32912,32944,32816,32720,32816,32960,32896,32752,32752,32912,
32944,32816,32720,32848,32944,32896,32736,32752,32896,32960,
32816,32720,32832,32944,32896,32752,32752,32912,32944,32800,
32720,32832,32960,32880,32736,32752,32912,32944,32800,32720,
32832,32960,32896,32736,32752,32912,32944,32800,32720,32832,
32960,32864,32736,32752,32912,32928,32784,32720,32832,32960,
32880,32720,32768,32912,32928,32800,32720,32848,32944,32864,
32736,32752,32912,32928,32784,32720,32848,32960,32864,32736,
32768,32912,32928,32800,32720,32848,32960,32864,32752,32784,
32928,32944,32800,32720,32864,32960,32880,32720,32784,32928,
32944,32784,32720,32848,32960,32864,32720,32768,32928,32928,
32784,32736,32848,32960,32864,32736,32768,32928,32928,32784,
32720,32864,32960,32864,32720,32784,32928,32912,32784,32720,
32864,32960,32848,32720,32784,32928,32912,32768,32720,32864,
32960,32848,32720,32784,32944,32912,32768,32720,32864,32960,
32848,32720,32784,32928,32928,32768,32736,32864,32960,32848,
32720,32784,32944,32912,32784,32736,32880,32960,32848,32720,
32784,32944,32912,32768,32736,32880,32960,32848,32720,32800,
32944,32912,32768,32736,32880,32960,32832,32720,32800,32944,
32912,32752,32736,32880,32944,32832,32720,32800,32944,32912,
32752,32736,32880,32944,32832,32720,32800,32944,32912,32752,
32736,32880,32944,32832,32720,32800,32944,32912,32752,32736,
32880,32960,32816,32720,32816,32944,32896,32736,32736,32896,
32944,32816,32720,32816,32944,32896,32752,32736,32896,32944,
32816,32720,32816,32944,32912,32752,32752,32896,32960,32816,
32720,32832,32944,32912,32752,32768,32912,32944,32816,32736,
32816,32944,32880,32752,32736,32896,32944,32816,32720,32816,
32960,32880,32736,32752,32896,32944,32816,32704,32832,32960,
32880,32736,32752,32896,32960,32800,32720,32832,32960,32880,
32736,32752,32912,32944,32800,32704,32832,32944,32880,32720,
32752,32912,32944,32800,32720,32832,32944,32880,32736,32752,
32912,32944,32800,32720,32832,32960,32880,32720,32752,32912,
32928,32784,32720,32848,32960,32880,32736,32784,32912,32944,
32800,32720,32848,32960,32880,32736,32784,32912,32944,32784,
32736,32848,32960,32864,32720,32768};
