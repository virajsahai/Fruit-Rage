//Quick Sort Code From - http://www.geeksforgeeks.org/quick-sort/


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <limits.h>
#include <math.h>
#include <time.h>
using namespace std;
struct heap_node
{
 	int x;
 	int y;
 	int count;
};
class result
{
public:
 	int x;
 	int y;
 	int score;
};
class node
{
public:
	int* num_of_fruits;
	int* grid_size;
	int* time_to_run;
	int** grid;
	int* heuristic_vals; //??
	int* fruit_count;
	int depth;
	int best_x,best_y;
	int score;
	node()
	{

	}

	node(int *g_size, int *n_o_f,int* t_t_r)
	{
		grid_size=g_size;
		num_of_fruits=n_o_f;
		time_to_run=t_t_r;
		grid=new int*[*grid_size];
		for(int i=0;i<*grid_size;i++)
		{
			grid[i]=new int[*grid_size];
		}
		fruit_count=new int[*num_of_fruits];
		depth=0;
		best_x=-1;
		best_y=-1;
		score=0;
	}

	void init_grid(int** g)
	{
		for(int i=0;i<*grid_size;i++)
		{
			for(int j=0;j<*grid_size;j++)
			{
				grid[i][j]=g[i][j];
				fruit_count[g[i][j]]++;
			}
		}
	}

	void apply_gravity()
	{
		for(int j=*grid_size-1;j>=0;j--)
		{
			int first_star_index=-1;
			for(int i=*grid_size-1;i>=0;i--)
			{
				if (first_star_index==-1 && grid[i][j]==-1) first_star_index=i;
				if (first_star_index!=-1 && grid[i][j]!=-1)
				{
					grid[first_star_index][j]=grid[i][j];
					grid[i][j]=-1;
					first_star_index--;
				}
			}
		}
	}

	int end_of_game()
	{
		for(int i=0;i<*num_of_fruits;i++)
		{
			if (fruit_count[i]!=0) return 0;
		}	
		return 1;
	}
	~node()
	{
		
	}
};

int min_move(node*,int,int,result*);
int max_move(node*,int,int,result*);

void update_neighbor(node* child_board,int x,int y,int compare)
{
	child_board->grid[x][y]=-1;
	child_board->fruit_count[compare]--;
 	if(x>0 && compare == child_board->grid[x-1][y]) update_neighbor(child_board,x-1,y,compare);
 	if(x<*child_board->grid_size-1 && compare == child_board->grid[x+1][y]) update_neighbor(child_board,x+1,y,compare); 
 	if(y>0 && compare == child_board->grid[x][y-1]) update_neighbor(child_board,x,y-1,compare);
 	if(y<*child_board->grid_size-1 && compare == child_board->grid[x][y+1]) update_neighbor(child_board,x,y+1,compare);	
}
void visited_fruit(node* child_board,int** visited,int x, int y,int compare,int* count)
{
 	visited[x][y]=1;
 	*count+=1;
 	if(x>0 && compare == child_board->grid[x-1][y] && visited[x-1][y] != 1) visited_fruit(child_board,visited,x-1, y,compare,count);
 	if(x<*child_board->grid_size-1 && compare == child_board->grid[x+1][y]&& visited[x+1][y] != 1) visited_fruit(child_board,visited,x+1, y,compare,count); 
 	if(y>0 && compare == child_board->grid[x][y-1]&& visited[x][y-1] != 1) visited_fruit(child_board,visited,x, y-1,compare,count);
 	if(y<*child_board->grid_size-1 && compare == child_board->grid[x][y+1]&& visited[x][y+1] != 1) visited_fruit(child_board,visited,x, y+1,compare,count);
}

int cutoff_test(node* child_board)
{
 	clock_t t;
 	t=clock();
 	float ti=((float)t)/CLOCKS_PER_SEC;
	if (child_board->depth==7 || child_board->end_of_game() || (*child_board->time_to_run>=250 && (ti)>=6) || (*child_board->time_to_run>=200 && *child_board->time_to_run<250 && (ti)>=4) || (*child_board->time_to_run>=150 && *child_board->time_to_run<200 && (ti)>=3) || (*child_board->time_to_run>=100 && *child_board->time_to_run<150 && (ti)>=3) || (*child_board->time_to_run>=50 && *child_board->time_to_run<100 && (ti)>=2) || (*child_board->time_to_run>=25 && *child_board->time_to_run<50 && (ti)>=2) || (*child_board->time_to_run>=10 && *child_board->time_to_run<25 && (ti)>=1) || (*child_board->time_to_run>=5 && *child_board->time_to_run<10 && (ti)>=.5) || (*child_board->time_to_run<5 && (*child_board->grid_size)<=12 && child_board->depth==4) || (*child_board->time_to_run<5 && (*child_board->grid_size)>12 && (*child_board->grid_size)<=18 && child_board->depth==3) || (*child_board->time_to_run<5 && (*child_board->grid_size)>18 && *child_board->grid_size<=26 && child_board->depth==3)) return 1;
	return 0;
}

int eval(node* child_board)
{
	return child_board->score;
}
int partition (heap_node arr[], int low, int high)
{
    int pivot = arr[high].count;    // pivot
    int i = (low - 1);  // Index of greater element
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].count >= pivot)
        {
            i++;    // increment index of greater element
         	int temp;
         	temp=arr[i].x;
         	arr[i].x=arr[j].x;
         	arr[j].x=temp;
         	temp=arr[i].y;
         	arr[i].y=arr[j].y;
         	arr[j].y=temp;
         	temp=arr[i].count;
         	arr[i].count=arr[j].count;
         	arr[j].count=temp;
        }
    }
 	int temp;
 	temp=arr[i + 1].x;
 	arr[i + 1].x=arr[high].x;
 	arr[high].x=temp;
 	temp=arr[i + 1].y;
 	arr[i + 1].y=arr[high].y;
 	arr[high].y=temp;
 	temp=arr[i + 1].count;
 	arr[i + 1].count=arr[high].count;
 	arr[high].count=temp;
    return (i + 1);
}

void quickSort(heap_node arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int max_move(node* child_board, int alpha, int beta,result* res)
{
	if (cutoff_test(child_board)) return eval(child_board);
	node copyNode(child_board->grid_size,child_board->num_of_fruits,child_board->time_to_run);
	copyNode.init_grid(child_board->grid);
	copyNode.depth=child_board->depth;
	copyNode.score=child_board->score;
	int** visited=new int*[*child_board->grid_size];
 	for(int i=0;i<*child_board->grid_size;i++)
    {
     	visited[i]=new int[*child_board->grid_size];
    }
 	int* count=new int;
 	int size_heap=*child_board->grid_size<=20?(*child_board->grid_size) * (*child_board->grid_size):400;
 	heap_node ins[size_heap];
 	int h=0;
 	for(int i=0;i<*child_board->grid_size;i++)
    {
     	for(int j=0;j<*child_board->grid_size;j++)
        {
         	if(visited[i][j]==1 || child_board->grid[i][j]==-1)continue;
         	else
            {
             	*count=0;
             	visited_fruit(child_board,visited,i, j,child_board->grid[i][j],count);
             	ins[h].x=i;
             	ins[h].y=j;
             	ins[h].count=*count;
             	h++;
             	if (h==size_heap) break;
            }
         	
        }
     	if (h==size_heap) break;
    }
    quickSort(ins,0,h-1);
	int x=0;
 	while(x<h)
    {
     	heap_node temp=ins[x];
		child_board->depth=copyNode.depth+1;
		int ini_fruit=child_board->fruit_count[child_board->grid[temp.x][temp.y]];
		update_neighbor(child_board,temp.x,temp.y,child_board->grid[temp.x][temp.y]);
		child_board->score+=(ini_fruit-child_board->fruit_count[child_board->grid[temp.x][temp.y]])*(ini_fruit-child_board->fruit_count[child_board->grid[temp.x][temp.y]]);
		child_board->apply_gravity();
		int temp1=alpha;
		alpha=std::max(alpha,min_move(child_board,alpha,beta,res));
		if (alpha>temp1)
		{ 
			res->x=temp.x;
			res->y=temp.y;
			res->score=child_board->score;
		}
		if (alpha >= beta)
		{
			return beta;
		}
		child_board->init_grid(copyNode.grid);
		child_board->depth=copyNode.depth;
     	child_board->score=copyNode.score;
     	x++;
	}
	return alpha;
}

int min_move(node* child_board, int alpha, int beta,result* res)
{
	if (cutoff_test(child_board)) return eval(child_board);
	node copyNode(child_board->grid_size,child_board->num_of_fruits,child_board->time_to_run);
	copyNode.init_grid(child_board->grid);
	copyNode.depth=child_board->depth;
	copyNode.score=child_board->score;
 	int** visited=new int*[*child_board->grid_size];
 	for(int i=0;i<*child_board->grid_size;i++)
    {
     	visited[i]=new int[*child_board->grid_size];
    }
 	int* count=new int;
 	int size_heap=*child_board->grid_size<=20?(*child_board->grid_size) * (*child_board->grid_size):400;
 	heap_node ins[size_heap];
 	int h=0;
 	for(int i=0;i<*child_board->grid_size;i++)
    {
     	for(int j=0;j<*child_board->grid_size;j++)
        {
         	if(visited[i][j]==1 || child_board->grid[i][j]==-1)continue;
         	else
            {
             	*count=0;
             	visited_fruit(child_board,visited,i, j,child_board->grid[i][j],count);
             	ins[h].x=i;
             	ins[h].y=j;
             	ins[h].count=*count;
             	h++;
             	if (h==size_heap) break;
            }
         	
        }
     	if (h==size_heap) break;
    }
    quickSort(ins,0,h-1);
	int x=0;
	while(x<h)
    {
     	heap_node temp=ins[x];
		child_board->depth=copyNode.depth+1;
		int ini_fruit=child_board->fruit_count[child_board->grid[temp.x][temp.y]];
		update_neighbor(child_board,temp.x,temp.y,child_board->grid[temp.x][temp.y]);
		child_board->score-=(ini_fruit-child_board->fruit_count[child_board->grid[temp.x][temp.y]])*(ini_fruit-child_board->fruit_count[child_board->grid[temp.x][temp.y]]);
		child_board->apply_gravity();
		int temp1=beta;
		beta=std::max(beta,max_move(child_board,alpha,beta,res));
		if (beta<temp1)
		{ 
			res->x=temp.x;
			res->y=temp.y;
			res->score=child_board->score;
		}
		if (alpha >= beta)
		{
			return alpha;
		}
		child_board->init_grid(copyNode.grid);
		child_board->depth=copyNode.depth;
     	child_board->score=copyNode.score;
     	x++;
	}
	return beta;
}

int main()
{
	string line;
	ifstream input("input.txt");
	ofstream output("output.txt");
	if (input.is_open())
	{
		while(!input.eof())
		{
			int* g_size=new int;
			int* fruit_num=new int;
			int* remain_t=new int;
			getline(input,line);
			*g_size=atoi(line.c_str());
			getline(input,line);
			*fruit_num=atoi(line.c_str());
			getline(input,line);
			*remain_t=atoi(line.c_str());
			node* res_node=new node(g_size,fruit_num,remain_t);
			node* root=new node(g_size,fruit_num,remain_t);
			result* res=new result;
			for(int i=0;i<*g_size;i++)
            {
                getline(input,line);
                for(int j=0;j<*g_size;j++)
                {
                	if(line.at(j)=='*') root->grid[i][j]=-1;
                	else 
                    {
                     	root->grid[i][j]=line.at(j)-'0';
                    	root->fruit_count[line.at(j)-'0']++;
                    }
                }
            }
            res_node->init_grid(root->grid);
            max_move(root,INT_MIN,INT_MAX,res);
            output<<char('A'+res->y)<<1+res->x<<"\n";
         	update_neighbor(res_node,res->x,res->y,res_node->grid[res->x][res->y]);
         	res_node->apply_gravity();
            for(int i=0;i<*g_size;i++)
            {
            	for(int j=0;j<*g_size;j++)
            	{
            		if(res_node->grid[i][j]==-1) output<<"*";
            		else output<<res_node->grid[i][j];
            	}
            	output<<"\n";
            }
            delete g_size;
            delete fruit_num;
            delete remain_t;
            delete root;
            delete res_node;
            delete res;
            break;
		}
		input.close();
		output.close();
	}
	else cout<<"Error opening file. \n";
	return 0;
}