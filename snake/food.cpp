#include <stdlib.h>
#include <time.h>
#include "food.h"


food *init_food(int size)
{
	srand((unsigned)time(NULL));
	//产生随机位置
	int rand_x = ((int)(rand()%35))*20;
	int rand_y = (int)((rand()%25)*20+60);
	//创建一个食物
	food *f = (food *) malloc(sizeof(food));
	f->l_x = rand_x;
	f->l_y = rand_y;
	f->r_x = rand_x+size;
	f->r_y = rand_y+size;
	f->size = size;
	return f;
}

void change_food_position(food *f)
{
	srand((unsigned)time(NULL));
	//产生随机位置
	int rand_x = ((int)(rand()%35))*20;
	int rand_y = (int)((rand()%25)*20+60);
	f->l_x = rand_x;
	f->l_y = rand_y;
	f->r_x = rand_x + f->size;
	f->r_y = rand_y + f->size;
}