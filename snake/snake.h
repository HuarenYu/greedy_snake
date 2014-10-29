/************
 *  贪吃蛇  *
 ************/
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define START 1
#define GAME 2
#define OVER 3
//蛇的节点
typedef struct snake_node
{
	int l_x;//矩形的左上x
	int l_y;//矩形的左上y
	int r_x;//矩形的右下x
	int r_y;//矩形的右下y
	snake_node *next_node;//指向下一个节点
	snake_node *prev_node;//指向上一个节点
}snake_node;

//蛇的身体
typedef struct snake_body
{
	snake_node *head;//指向蛇的头部
	snake_node *tail;//指向蛇的尾部
	int length;//蛇的长度
	int node_size;//蛇节点的大小
	int x;//蛇的初始化x位置
	int y;//蛇的初始化y位置
	int direction;
}snake_body;

//初始化
snake_body *init_snake(int x,int y,int node_size);
//添加头部
void add_head(snake_body *snake,int direction);
//删除尾部
void delete_tail(snake_body *snake);
//移动
void move(snake_body *snake);
//析构
void destroy(snake_body *snake);
