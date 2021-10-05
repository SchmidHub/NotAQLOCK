#ifndef COVER_LAYOUT_H
#define COVER_LAYOUT_H

#define UE      154
#define OE      153
#define AE      142
#define NUMBER_OF_LETTERS       110

typedef struct
{
    char c;
    unsigned short x;
    unsigned short y;
    bool on;
} s_letter;

s_letter letter_arr[110];

unsigned short init_letter_arr[NUMBER_OF_LETTERS] = {'E', 'S', 'K', 'I', 'S', 'T', 'A', 'F', UE , 'N', 'F',
                                                     'G', 'I', 'Z', 'N', 'A', 'W', 'Z', 'N', 'H', 'E', 'Z',
                                                     'D', 'R', 'E', 'I', 'V', 'I', 'E', 'R', 'T', 'E', 'L',
                                                     'H', 'C', 'A', 'N', 'K', 'N', 'U', 'F', 'R', 'O', 'V',
                                                     'H', 'A', 'L', 'B', 'A', 'E', 'L', 'F', UE , 'N', 'F',
                                                     'I', 'E', 'W', 'Z', 'M', 'A', 'X', 'S', 'N', 'I', 'E',
                                                     'D', 'R', 'E', 'I', 'P', 'M', 'J', 'V', 'I', 'E', 'R',
                                                     'T', 'H', 'C', 'A', 'L', 'N', 'S', 'H', 'C', 'E', 'S',
                                                     'S', 'I', 'E', 'B', 'E', 'N', 'Z', 'W', OE , 'L', 'F',
                                                     'R', 'H', 'U', 'K', 'N', 'U', 'E', 'N', 'H', 'E', 'Z'};

/*
unsigned short init_letter_arr[NUMBER_OF_LETTERS] = {'E', 'S', 'K', 'I', 'S', 'T', 'A', 'F', UE , 'N', 'F',
                                                     'Z', 'E', 'H', 'N', 'Z', 'W', 'A', 'N', 'Z', 'I', 'G',
                                                     'D', 'R', 'E', 'I', 'V', 'I', 'E', 'R', 'T', 'E', 'L',
                                                     'V', 'O', 'R', 'F', 'U', 'N', 'K', 'N', 'A', 'C', 'H',
                                                     'H', 'A', 'L', 'B', 'A', 'E', 'L', 'F', UE , 'N', 'F',
                                                     'E', 'I', 'N', 'S', 'X', 'A', 'M', 'Z', 'W', 'E', 'I',
                                                     'D', 'R', 'E', 'I', 'P', 'M', 'J', 'V', 'I', 'E', 'R',
                                                     'S', 'E', 'C', 'H', 'S', 'N', 'L', 'A', 'C', 'H', 'T',
                                                     'S', 'I', 'E', 'B', 'E', 'N', 'Z', 'W', OE , 'L', 'F',
                                                     'Z', 'E', 'H', 'N', 'E', 'U', 'N', 'K', 'U', 'H', 'R'};
*/

#endif