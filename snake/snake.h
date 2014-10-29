/************
 *  ̰����  *
 ************/
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define START 1
#define GAME 2
#define OVER 3
//�ߵĽڵ�
typedef struct snake_node
{
	int l_x;//���ε�����x
	int l_y;//���ε�����y
	int r_x;//���ε�����x
	int r_y;//���ε�����y
	snake_node *next_node;//ָ����һ���ڵ�
	snake_node *prev_node;//ָ����һ���ڵ�
}snake_node;

//�ߵ�����
typedef struct snake_body
{
	snake_node *head;//ָ���ߵ�ͷ��
	snake_node *tail;//ָ���ߵ�β��
	int length;//�ߵĳ���
	int node_size;//�߽ڵ�Ĵ�С
	int x;//�ߵĳ�ʼ��xλ��
	int y;//�ߵĳ�ʼ��yλ��
	int direction;
}snake_body;

//��ʼ��
snake_body *init_snake(int x,int y,int node_size);
//���ͷ��
void add_head(snake_body *snake,int direction);
//ɾ��β��
void delete_tail(snake_body *snake);
//�ƶ�
void move(snake_body *snake);
//����
void destroy(snake_body *snake);
