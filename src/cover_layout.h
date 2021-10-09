#include <Arduino.h>
#include <hash_map>
#ifndef COVER_LAYOUT_H
#define COVER_LAYOUT_H

#define UE 154
#define OE 153
#define AE 142
#define NUMBER_OF_LETTERS 110

typedef struct
{
    char c;
    unsigned short x;
    unsigned short y;
    bool on;
} s_letter;

s_letter letter_arr[110];

typedef struct
{
    const String word;
    unsigned short position;
    unsigned short length;
} s_word;

#define WORD_2 3
#define WORD_3 4
#define WORD_4 6
#define WORD_5 8
#define WORD_6 9
#define WORD_7 11
#define WORD_11 18

s_word words[24] = {
    {"ES", 0, WORD_2},                  //0
    {"IST", 5, WORD_3},                 //1
    {"FÜNF_M", 11, WORD_4},             //2
    {"ZEHN_M", 18, WORD_4},             //3
    {"ZWANZIG", 25, WORD_7},            //4
    {"DREIVIERTEL", 36, WORD_11},       //5
    {"VOR", 54, WORD_3},                //6
    {"NACH", 66, WORD_4},               //7
    {"HALB", 72, WORD_4},               //8
    {"ELF", 80, WORD_3},                //9
    {"FÜNF", 83, WORD_4},               //10
    {"EINS", 90, WORD_4},               //11
    {"ZWEI", 102, WORD_4},              //12
    {"DREI", 106, WORD_4},              //13
    {"VIER", 117, WORD_4},              //14
    {"SECHS", 126, WORD_5},             //15
    {"ACHT", 138, WORD_4},              //16
    {"SIEBEN", 144, WORD_6},            //17
    {"ZWÖLF", 154, WORD_5},             //18
    {"ZEHN", 163, WORD_4},              //19
    {"NEUN", 168, WORD_4},              //20
    {"UHR", 177, WORD_3},               //21
    {"VIERTEL", 42, WORD_7},            //22
    {"EIN", 90, WORD_3},               //23
    };              

//                                                     //0_ 1_ 2_ 3_ 4_ 5_ 6_ 7_ 8_ 9_ 10 11 12 13 14 15 16 17
//                                                     //17 16 15 14 13 12 11 10 9_ 8_ 7_ 6_ 5_ 4_ 3_ 2_ 1_ 0_
// unsigned short init_letter_arr[NUMBER_OF_LETTERS] = {'E', 'S', 'K', 'I', 'S', 'T', 'A', 'F', 'Ü', 'N', 'F',  //0-17
//                                                      'G', 'I', 'Z', 'N', 'A', 'W', 'Z', 'N', 'H', 'E', 'Z',  //18-35
//                                                      'D', 'R', 'E', 'I', 'V', 'I', 'E', 'R', 'T', 'E', 'L',  //36-53
//                                                      'H', 'C', 'A', 'N', 'K', 'N', 'U', 'F', 'R', 'O', 'V',  //54-71
//                                                      'H', 'A', 'L', 'B', 'A', 'E', 'L', 'F', 'Ü', 'N', 'F',  //72-89
//                                                      'I', 'E', 'W', 'Z', 'M', 'A', 'X', 'S', 'N', 'I', 'E',  //90-105
//                                                      'D', 'R', 'E', 'I', 'P', 'M', 'J', 'V', 'I', 'E', 'R',  //106-125
//                                                      'T', 'H', 'C', 'A', 'L', 'N', 'S', 'H', 'C', 'E', 'S',  //126-143
//                                                      'S', 'I', 'E', 'B', 'E', 'N', 'Z', 'W', 'Ö', 'L', 'F',  //144-162
//                                                      'R', 'H', 'U', 'K', 'N', 'U', 'E', 'N', 'H', 'E', 'Z'}; //163-180

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