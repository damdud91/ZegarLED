#ifndef ANIMACJE_H_
#define ANIMACJE_H_

////////////////////////////////////////////////////////////////////////////////////
const uint8_t tiktik[60][12] PROGMEM = {
	{ 31,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6},  //0
	{ 27, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4},  //1
	{ 22, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1},  //2
	{ 16, 22,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //3
	{ 10, 27,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //4
	{  6, 31,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //5
	{  4, 27, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //6
	{  1, 22, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //7
	{  0, 16, 22,  1,  0,  0,  0,  0,  0,  0,  0,  0},  //8
	{  0, 10, 27,  4,  0,  0,  0,  0,  0,  0,  0,  0},  //9
	{  0,  6, 31,  6,  0,  0,  0,  0,  0,  0,  0,  0},  //10
	{  0,  4, 27, 10,  0,  0,  0,  0,  0,  0,  0,  0},  //11
	{  0,  1, 22, 16,  0,  0,  0,  0,  0,  0,  0,  0},  //12
	{  0,  0, 16, 22,  1,  0,  0,  0,  0,  0,  0,  0},  //13
	{  0,  0, 10, 27,  4,  0,  0,  0,  0,  0,  0,  0},  //14
	{  0,  0,  6, 31,  6,  0,  0,  0,  0,  0,  0,  0},  //15
	{  0,  0,  4, 27, 10,  0,  0,  0,  0,  0,  0,  0},  //16
	{  0,  0,  1, 22, 16,  0,  0,  0,  0,  0,  0,  0},  //17
	{  0,  0,  0, 16, 22,  1,  0,  0,  0,  0,  0,  0},  //18
	{  0,  0,  0, 10, 27,  4,  0,  0,  0,  0,  0,  0},  //19
	{  0,  0,  0,  6, 31,  6,  0,  0,  0,  0,  0,  0},  //20
	{  0,  0,  0,  4, 27, 10,  0,  0,  0,  0,  0,  0},  //21
	{  0,  0,  0,  1, 22, 16,  0,  0,  0,  0,  0,  0},  //22
	{  0,  0,  0,  0, 16, 22,  1,  0,  0,  0,  0,  0},  //23
	{  0,  0,  0,  0, 10, 27,  4,  0,  0,  0,  0,  0},  //24
	{  0,  0,  0,  0,  6, 31,  6,  0,  0,  0,  0,  0},  //25
	{  0,  0,  0,  0,  4, 27, 10,  0,  0,  0,  0,  0},  //26
	{  0,  0,  0,  0,  1, 22, 16,  0,  0,  0,  0,  0},  //27
	{  0,  0,  0,  0,  0, 16, 22,  1,  0,  0,  0,  0},  //28
	{  0,  0,  0,  0,  0, 10, 27,  4,  0,  0,  0,  0},  //29
	{  0,  0,  0,  0,  0,  6, 31,  6,  0,  0,  0,  0},  //30
	{  0,  0,  0,  0,  0,  4, 27, 10,  0,  0,  0,  0},  //31
	{  0,  0,  0,  0,  0,  1, 22, 16,  0,  0,  0,  0},  //32
	{  0,  0,  0,  0,  0,  0, 16, 22,  1,  0,  0,  0},  //33
	{  0,  0,  0,  0,  0,  0, 10, 27,  4,  0,  0,  0},  //34
	{  0,  0,  0,  0,  0,  0,  6, 31,  6,  0,  0,  0},  //35
	{  0,  0,  0,  0,  0,  0,  4, 27, 10,  0,  0,  0},  //36
	{  0,  0,  0,  0,  0,  0,  1, 22, 16,  0,  0,  0},  //37
	{  0,  0,  0,  0,  0,  0,  0, 16, 22,  1,  0,  0},  //38
	{  0,  0,  0,  0,  0,  0,  0, 10, 27,  4,  0,  0},  //39
	{  0,  0,  0,  0,  0,  0,  0,  6, 31,  6,  0,  0},  //40
	{  0,  0,  0,  0,  0,  0,  0,  4, 27, 10,  0,  0},  //41
	{  0,  0,  0,  0,  0,  0,  0,  1, 22, 16,  0,  0},  //42
	{  0,  0,  0,  0,  0,  0,  0,  0, 16, 22,  1,  0},  //43
	{  0,  0,  0,  0,  0,  0,  0,  0, 10, 27,  4,  0},  //44
	{  0,  0,  0,  0,  0,  0,  0,  0,  6, 31,  6,  0},  //45
	{  0,  0,  0,  0,  0,  0,  0,  0,  4, 27, 10,  0},  //46
	{  0,  0,  0,  0,  0,  0,  0,  0,  1, 22, 16,  0},  //47
	{  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 22,  1},  //48
	{  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 27,  4},  //49
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 31,  6},  //50
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 27, 10},  //51
	{  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 22, 16},  //52
	{  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 22},  //53
	{  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10, 27},  //54
	{  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6, 31},  //55
	{ 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 27},  //56
	{ 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 22},  //57
	{ 22,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16},  //58
	{ 27,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10}}; //59
		
////////////////////////////////////////////////////////////////////////////////////
const uint8_t duszki[60][12] PROGMEM = {
	{ 31,  0,  0,  0,  0,  0,  0,  0,  3, 13, 23, 31},  //0
	{ 31,  0,  0,  0,  0,  0,  0,  0,  1, 11, 21, 31},  //1
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  9, 19, 29},  //2
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  7, 17, 27},  //3
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  5, 15, 25},  //4
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  3, 13, 23},  //5
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  1, 11, 21},  //1
	{ 29, 31,  0,  0,  0,  0,  0,  0,  0,  0,  9, 19},  //2
	{ 27, 31,  0,  0,  0,  0,  0,  0,  0,  0,  7, 17},  //3
	{ 25, 31,  0,  0,  0,  0,  0,  0,  0,  0,  5, 15},  //4
	{ 23, 31, 31,  0,  0,  0,  0,  0,  0,  0,  3, 13},  //5
	{ 21, 31, 31,  0,  0,  0,  0,  0,  0,  0,  1, 11},  //1
	{ 19, 29, 31,  0,  0,  0,  0,  0,  0,  0,  0,  9},  //2
	{ 17, 27, 31,  0,  0,  0,  0,  0,  0,  0,  0,  7},  //3
	{ 15, 25, 31,  0,  0,  0,  0,  0,  0,  0,  0,  5},  //4
	{ 13, 19, 31, 31,  0,  0,  0,  0,  0,  0,  0,  3},  //5
	{ 11, 17, 31, 31,  0,  0,  0,  0,  0,  0,  0,  1},  //1
	{  9, 15, 29, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //2
	{  7, 13, 27, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //3
	{  5, 11, 25, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //4
	{  3,  9, 23, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //5
	{  1,  7, 21, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //1
	{  0,  5, 19, 29, 31,  0,  0,  0,  0,  0,  0,  0},  //2
	{  0,  3, 17, 27, 31,  0,  0,  0,  0,  0,  0,  0},  //3
	{  0,  1, 15, 25, 31,  0,  0,  0,  0,  0,  0,  0},  //4
	{  0,  0, 13, 23, 31, 31,  0,  0,  0,  0,  0,  0},  //5
	{  0,  0, 11, 21, 31, 31,  0,  0,  0,  0,  0,  0},  //1
	{  0,  0,  9, 19, 29, 31,  0,  0,  0,  0,  0,  0},  //2
	{  0,  0,  7, 17, 27, 31,  0,  0,  0,  0,  0,  0},  //3
	{  0,  0,  5, 15, 25, 31,  0,  0,  0,  0,  0,  0},  //4
	{  0,  0,  3, 13, 23, 31, 31,  0,  0,  0,  0,  0},  //5
	{  0,  0,  1, 11, 21, 31, 31,  0,  0,  0,  0,  0},  //1
	{  0,  0,  0,  9, 19, 29, 31,  0,  0,  0,  0,  0},  //2
	{  0,  0,  0,  7, 17, 27, 31,  0,  0,  0,  0,  0},  //3
	{  0,  0,  0,  5, 15, 25, 31,  0,  0,  0,  0,  0},  //4
	{  0,  0,  0,  3, 13, 23, 31, 31,  0,  0,  0,  0},  //5
	{  0,  0,  0,  1, 11, 21, 31, 31,  0,  0,  0,  0},  //1
	{  0,  0,  0,  0,  9, 19, 29, 31,  0,  0,  0,  0},  //2
	{  0,  0,  0,  0,  7, 17, 27, 31,  0,  0,  0,  0},  //3
	{  0,  0,  0,  0,  5, 15, 25, 31,  0,  0,  0,  0},  //4
	{  0,  0,  0,  0,  3, 13, 23, 31, 31,  0,  0,  0},  //5
	{  0,  0,  0,  0,  1, 11, 21, 31, 31,  0,  0,  0},  //1
	{  0,  0,  0,  0,  0,  9, 19, 29, 31,  0,  0,  0},  //2
	{  0,  0,  0,  0,  0,  7, 17, 27, 31,  0,  0,  0},  //3
	{  0,  0,  0,  0,  0,  5, 15, 25, 31,  0,  0,  0},  //4
	{  0,  0,  0,  0,  0,  3, 13, 23, 31, 31,  0,  0},  //5
	{  0,  0,  0,  0,  0,  1, 11, 21, 31, 31,  0,  0},  //1
	{  0,  0,  0,  0,  0,  0,  9, 19, 29, 31,  0,  0},  //2
	{  0,  0,  0,  0,  0,  0,  7, 17, 27, 31,  0,  0},  //3
	{  0,  0,  0,  0,  0,  0,  5, 15, 25, 31,  0,  0},  //4
	{  0,  0,  0,  0,  0,  0,  3, 13, 23, 31, 31,  0},  //5
	{  0,  0,  0,  0,  0,  0,  1, 11, 21, 31, 31,  0},  //1
	{  0,  0,  0,  0,  0,  0,  0,  9, 19, 29, 31,  0},  //2
	{  0,  0,  0,  0,  0,  0,  0,  7, 17, 27, 31,  0},  //3
	{  0,  0,  0,  0,  0,  0,  0,  5, 15, 25, 31,  0},  //4
	{  0,  0,  0,  0,  0,  0,  0,  3, 13, 23, 31, 31},  //5
	{  0,  0,  0,  0,  0,  0,  0,  1, 11, 21, 31, 31},  //1
	{  0,  0,  0,  0,  0,  0,  0,  0,  9, 19, 29, 31},  //2
	{  0,  0,  0,  0,  0,  0,  0,  0,  7, 17, 27, 31},  //3
	{  0,  0,  0,  0,  0,  0,  0,  0,  5, 15, 25, 31}}; //4

////////////////////////////////////////////////////////////////////////////////////
const uint8_t waz[60][12] PROGMEM = {
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //0
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //1
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //2
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //3
	{ 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //4
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //5
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //6
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //7
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //8
	{ 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //9
	{ 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //10
	{ 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //11
	{ 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //12
	{ 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //13
	{ 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //14
	{ 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //15
	{ 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //16
	{ 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //17
	{ 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //18
	{ 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0},  //19
	{ 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //20
	{ 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //21
	{ 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //22
	{ 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //23
	{ 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0,  0},  //24
	{ 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0},  //25
	{ 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0},  //26
	{ 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0},  //27
	{ 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0},  //28
	{ 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0,  0},  //29
	{ 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0},  //30
	{ 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0},  //31
	{ 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0},  //32
	{ 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0},  //33
	{ 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0,  0},  //34
	{ 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0},  //35
	{ 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0},  //36
	{ 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0},  //37
	{ 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0},  //38
	{ 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0,  0},  //39
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0},  //40
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0},  //41
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0},  //42
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0},  //43
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0,  0},  //44
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0},  //45
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0},  //46
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0},  //47
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0},  //48
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0,  0},  //49
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0},  //50
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0},  //51
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0},  //52
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0},  //53
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,  0},  //54
	{ 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},  //55
	{ 25, 31, 31, 25, 31, 31, 25, 31, 31, 25, 31, 31},  //56
	{ 15, 25, 31, 15, 25, 31, 15, 25, 31, 15, 25, 31},  //57
	{  1, 15, 25,  1, 15, 25,  1, 15, 25,  1, 15, 25},  //58
	{  0,  1, 15,  0,  1, 15,  0,  1, 15,  0,  1, 15}}; //59
#endif /* ANIMACJE_H_ */