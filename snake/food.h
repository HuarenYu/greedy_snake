typedef struct food
{
	int l_x;
	int l_y;
	int r_x;
	int r_y;
	int size;
}food;
//��ʼ��ʳ��
food *init_food(int size);
//�ı�ʳ��λ��
void change_food_position(food *f);

