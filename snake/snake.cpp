#include <stdlib.h>
#include <Windows.h>
#include "snake.h"


//��ʼ��
snake_body *init_snake(int x,int y,int node_size)
{
	snake_body *snake = (snake_body*)malloc(sizeof(snake_body));
	snake->head = NULL;
	snake->tail = NULL;
	snake->node_size = node_size;
	snake->x = x;
	snake->y = y;
	snake->length = 0;
	snake->direction = DOWN;
	add_head(snake,DOWN);
	add_head(snake,DOWN);
	add_head(snake,DOWN);  
	return snake;
}
//���ͷ��
void add_head(snake_body *snake,int direction)
{
	//����һ���ڵ�
	snake_node *new_node = (snake_node*)malloc(sizeof(snake_node));
	if (snake->length == 0 )
	{
		new_node->l_x = snake->x;
		new_node->l_y = snake->y;
		new_node->r_x = snake->x+snake->node_size;
		new_node->r_y = snake->x+snake->node_size;
		new_node->next_node = NULL;
		new_node->prev_node = NULL;
		snake->head = new_node;
		snake->tail = new_node;
		++snake->length;
	}
	else 
	{
		snake_node *tmp = snake->head;
		switch(direction)
		{
		case 1://����x����y����
			new_node->l_x = tmp->l_x;
			new_node->l_y = tmp->l_y-snake->node_size;
			new_node->r_x = tmp->r_x;
			new_node->r_y = tmp->r_y-snake->node_size;
			break;
		case 2://����y����x����
			new_node->l_x = tmp->l_x+snake->node_size;
			new_node->l_y = tmp->l_y;
			new_node->r_x = tmp->r_x+snake->node_size;
			new_node->r_y = tmp->r_y;
			break;
		case 3://����x����y����
			new_node->l_x = tmp->l_x;
			new_node->l_y = tmp->l_y+snake->node_size;
			new_node->r_x = tmp->r_x;
			new_node->r_y = tmp->r_y+snake->node_size;
			break;
		case 4://����y����x����
			new_node->l_x = tmp->l_x-snake->node_size;
			new_node->l_y = tmp->l_y;
			new_node->r_x = tmp->r_x-snake->node_size;
			new_node->r_y = tmp->r_y;
			break;
		}
		tmp->prev_node = new_node;
		new_node->next_node = tmp;
		snake->head = new_node;
		++snake->length;
	} 
	
}
//ɾ��β��
void delete_tail(snake_body *snake)
{
	snake_node *tmp = snake->tail;
	snake->tail = tmp->prev_node;
	tmp->prev_node->next_node = NULL;
	free(tmp);
	--snake->length;
}
//�ƶ�
void move(snake_body *snake)
{
	//��ͷ
	add_head(snake,snake->direction);
	//ȥβ
	delete_tail(snake);
}
//����
void destroy(snake_body *snake)
{
	snake_node *tmp1=snake->head;
	while(tmp1->next_node!=NULL) 
	{
		snake_node *tmp2 = tmp1;
		tmp1 = tmp1->next_node;
		free(tmp2);
	}
	free(snake);
}