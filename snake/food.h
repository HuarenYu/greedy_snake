typedef struct food
{
	int l_x;
	int l_y;
	int r_x;
	int r_y;
	int size;
}food;
//初始化食物
food *init_food(int size);
//改变食物位置
void change_food_position(food *f);

