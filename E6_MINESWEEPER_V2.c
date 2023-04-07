#include <stdio.h>

int d_read(char);
int bombs(int,int);
int creation_of_tab(int,int);
int bomb_placement(int,int,int,int**);
int numbers_placement(int,int,int **);
void level_printer(int,int,int **,int **);
int search(int,int,int,int,int **);
void game(int,int,int,int **);

int main(int argc,char **argv){
	
	int m,n,b;
	int **game_table;
	int i,j;
	int ans;

	do{
		system("cls");
		m=d_read('y');
		n=d_read('x');
		b=bombs(m,n);
		game_table=creation_of_tab(m,n);
		game_table=bomb_placement(m,n,b,game_table);
		game_table=numbers_placement(m,n,game_table);
		game(m,n,b,game_table);
	    printf("Do you want to play again(1==Yes/0==No): ");
	    scanf("%d",&ans);
	}while(ans==1);
	

	system("pause");
	return 0;
}

int d_read(char y){
	int x;
	
	printf("give dimension %c : ",y);
	scanf("%d",&x);
	
	return(x);
}


int bombs(int m,int n){
	
	int b,s;
	
	s=m*n;
	do{
		system("cls");
		printf("Give the number of the bombs you want to have in your game: ");
		scanf("%d",&b);
		if(b>=s){
			printf("The number of bombs can't be the same or bigger than the size of your table,give again\n");
			system("pause");
		}
		else if(b<0){
			printf("The number of bombs can't be a negative number!Give again\n");
			system("pause");
		}
	}while(b>=s||b<0);
	
	system("cls");
	return(b);	
}


int creation_of_tab(int m,int n){
	
	int **p;
	int i,j;
	
	p=malloc(sizeof(int*)*m);
	for(i=0;i<m;i++){
		p[i]=malloc(sizeof(int)*n);
	}
	
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			p[i][j]=0;

	return p;
}


int bomb_placement(int m,int n,int k,int **tab){
	int i,j,flag;
	int x,y;
	
	srand(time(NULL));
	for(i=0;i<k;i++){
		do{
			flag=0;
			x=rand()%(m);
			y=rand()%(n);
			if(tab[x][y]==0)
				tab[x][y]=9;
			else
				flag=1;
		}while(flag==1);
	}
	return tab;
}


int numbers_placement(int m,int n,int **tab){
	int i,j;
	int k,l;	
	
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(tab[i][j]!=9){
				if(i!=0 && j!=0 && i!=m-1 && j!=n-1){
					for(k=i-1;k<=i+1;k++){
						for(l=j-1;l<=j+1;l++){
							if(tab[k][l]==9)
								tab[i][j]++;
						}
					}
				}
				else if(i==0 && j!=0 && j!=n-1){
					for(k=i;k<=i+1;k++){
						for(l=j-1;l<=j+1;l++){
							if(tab[k][l]==9)
								tab[i][j]++;
						}
					}
				}
				else if(i==0 && j==0){
					for(k=i;k<=i+1;k++){
						for(l=j;l<=j+1;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}
				}
				else if(i==0 && j==n-1){
					for(k=i;k<=i+1;k++){
						for(l=j-1;l<=j;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}
				}
				else if(j==0 && i!=0 && i!=m-1){
					for(k=i-1;k<=i+1;k++){
						for(l=j;l<=j+1;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}
				}
				else if(j==n-1 && i!=0 && i!=m-1){
					for(k=i-1;k<=i+1;k++){
						for(l=j-1;l<=j;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}
				}
				else if(i==m-1 && j==0){
					for(k=i-1;k<=i;k++){
						for(l=j;l<=j+1;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}
				}
				else if(i==m-1 && j!=0 && j!=n-1){
					for(k=i-1;k<=i;k++){
						for(l=j-1;l<=j+1;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}	
				}
				else if(i==m-1 && j==n-1){
					for(k=i-1;k<=i;k++){
						for(l=j-1;l<=j;l++){
							if(tab[k][l]==9)
								tab[i][j]++;		
						}
					}		
				}
			}
		}
	}
	
	
	return tab;
}


void level_printer(int m,int n,int **tab,int **temp){
	int i,j;

		for(i=0;i<m;i++){
			if(i==0){
				printf("  ");
				for(j=0;j<n;j++)
					printf(" %d ",j);
				printf("\n");
			}
			for(j=0;j<n;j++){
				 if(j==0)
					printf("%d ",i);
			
				if(temp[i][j]==0)
					printf("[ ]");
				else if(temp[i][j]==1)
					printf("[%d]",tab[i][j]);
				else if(temp[i][j]==-1)
					printf("[%c]",'B');				
			}
			printf("\n");
		}
}

void game(int m,int n,int b,int **tab){
	
	int **temp;
	int i,j,x,y;
	int flag=0;
	int k=0;
	
	
	temp=malloc(sizeof(int*)*m);
	for(i=0;i<m;i++){
		temp[i]=malloc(sizeof(int)*n);
	}
	
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			temp[i][j]=0;
			
	level_printer(m,n,tab,temp);
	
	do{
		do{
			printf("Give Y: ");
			scanf("%d",&y);
		}while(y>m-1);
		
		do{
			printf("Give X: ");
			scanf("%d",&x);
		}while(x>n-1);
		
		if(tab[y][x]==9){
			flag=1;
			temp[y][x]=-1;
		}
		else{
			temp[y][x]=1;
			k++;	
		}
				
		system("Cls");	
		level_printer(m,n,tab,temp);
	}while(flag==0 && k<(m*n-b));
	if(flag==1)
		printf("GAME OVER\n");
	else
		printf("YOU WON!!\n");
}

