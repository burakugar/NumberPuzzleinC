	/* BURAK UGAR HW6
	IMPORTANT NOTE: THIS HOMEWORK IS PREPARED IN TERMS OF PDF DOCUMENT AND SOME RESEARCH ON INTERNET.
	FOR SOLVE TO THE PUZZLE, FINAL EMPTY SPACE HAVE TO BE AT RIGHT BOTTOM CORNER OF THE PUZZLE SUCH THAT
	1 2 3
	4 5 6
	7 8   */
	#include <stdio.h>
	#include <stdlib.h> /*to use RAND_MAX */
	#include <math.h>
	#include <time.h>
	#define N 5 /*defining the matrix size */

	/*You will write a function that prints the current puzzle on the console. You are
	expected to format the puzzle properly. The printed board has to be bordered with *s
	and numbers appropriately centered.*/
enum Move{
		left=1,
		right=2,
		up=3,
		down=4
	}move;
	
void shuffle(unsigned char *array, int n)
	{ /*function that shuffles the array using Fisher's algorithm */
	    if (n > 1) 
	    {
	        int i;
	        int j;
	        int t;
	        for (i = 0; i < n - 1; i++) 
	        {
	           j = i + rand() / (RAND_MAX / (n - i) + 1);
	           t = array[j];
	          array[j] = array[i]; /*swapping the elements */
	          array[i] = t;
	        }
	    }
	}
	
void filltheMatrix(unsigned char M[N][N],unsigned char arr[N*N],unsigned char arr2[N*N-1],int* flag_x,int* flag_y){
		int i,j,t,k=0;
		char* p;
	    int count=1;
	    int numb;
	    srand(time(NULL)); /* to fill the matrix randomly */
	    for (i = 0; i<N; i++){
	    	for(j=0;j<N;j++){ /* filling the matrix with elements 1,2,3...n */
	    			M[i][j]=k;
	    			k++;
			 }
	     }
	   	
	     for(i=0;i<N*N;i++){
	     	arr[i]=i+1; /*filling an array with same elements */ 
		 }	
		shuffle(arr,N*N); /* shuffling the original the array */
		 k=0;
		for (i = 0; i < N; i++){
	    		for(j=0;j<N;j++){
	    			if(arr[k]==N*N){ /* array's last element is space such as if the matrix is 3x3 last, our array starts from 0 and goes to 8 since when
					we come across with N*N that means it's the last element and also space's itself */
						k++;
	    				*flag_x=i; /* flag_x and flag_y values are space's coordinates */
	    				*flag_y=j;
				}
				else{
	    		M[i][j]= arr[k];
	    			k++;
	    		}
	    		}
			}
		
	}
	/*You will write a function that checks if the puzzle is solved/correct. It should return a
	logical value.*/
	
int checkOk(unsigned char M[N][N],unsigned char arr2[N*N-1]){ /* function controls the puzlle is solved or not */
		int i,j,count=0,k=0;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				if(M[i][j]==arr2[k]){
					count++;
				}
				k++; /*check if the puzzle is done or not */
		}
	}
		if(count==N*N-1){
			return 1;
		}
		else{
			return 0;
		}
}
	
int checkSpace(int x,int y,int flag_x,int flag_y){
			int i,j,result;
		   
			if(flag_x==x&& flag_y!= y){ /* if x coordinates are same */
			return 1;
			}
			else if(flag_y==y&& flag_x!=x){	
			return 2;	 /* if y coordinates are same */
			}
			else
			return 0;
		}
		/* this function controls the move */
		/*You will write a function that performs the desired move on the puzzle board. The
	movement parameters are
	a. The direction of the movement: towards {left, right, up, down} enumerated
	type.
	b. Movement start location: Movement will start at this location (you will need
	two parameters for this).*/
void controlMove(unsigned char M[N][N],int x,int y,int* flag_x,int* flag_y,int direction,int* isitok){
		int i,j,value;
		int temp_x1=*flag_x; /*temp_x1: x coordinate of the space */
		int temp_y1=*flag_y; /*temp_y1: y coordinate of the space */
		int temp_x2=x; /* temp_x2: x coordinate of the given point */
		int temp_y2=y; /* temp_y2: y coordinate of the given point */
		int distance;
		
	if(checkSpace(x,y,*flag_x,* flag_y)==1){ /* if x coordinates are same */
		if(direction ==right  && (*flag_y > y)){	/*if the given direction is right and space is in the right direction of the given point */
		 *isitok=0;
		for(i=*flag_y-1;i>=y;i--){
			M[temp_x1][i+1]=M[temp_x1][i]; /*IF USER DECIDES TO GO TROUGH RIGHT */
		}
		*flag_x=temp_x2;
		*flag_y=temp_y2; /* assign the new space to the given point because it will move */	
			 *isitok=1;
		}	
		else if(direction == left && (*flag_y < y)){ /*if the given direction is left and space is in the left direction of the given point */
		
		*isitok=0;
		for(i=*flag_y+1;i<=y;i++){ 
			M[temp_x2][i-1]=M[temp_x2][i];
			}
		*flag_x=temp_x2;
		*flag_y=temp_y2; /*assign the new space to the given point because it will move */
		*isitok=1;
		}
		else{
			printf("Please choose a valid point or direction to move");
		}
	}
	else if(checkSpace(x,y,*flag_x,* flag_y)==2){ /* if y coordinates are same */
		if(direction == up && (*flag_x < temp_x2)){ /*IF USER DECIDES TO GO TROUGH UPWARD */
		*isitok=0;                                           
			for(i=temp_x1;i<temp_x2+1;i++){ 
					M[i][temp_y2]=M[i+1][temp_y2];
				}
		*flag_x=temp_x2;
		*flag_y=temp_y2; /* assign the new space to the given point because it will move */
		 *isitok=1;
		}		
		else if(direction == down && (*flag_x > temp_x2)){ /*IF USER DECIDES TO GO TROUGH DOWNWARD */
		 /* assign the new space to the given point because it will move	*/
		 *isitok=0;		
		for(i=temp_x1-1;i>temp_x2-1;i--){
			M[i+1][temp_y2]=M[i][temp_y2];
		}
		*flag_x=temp_x2;
		*flag_y=temp_y2; /* assign the new space to the given point because it will move */
			*isitok=1;
				}
		else{
			printf("Please choose a valid point or direction to move");
		}
	}
	else{
		printf("Please choose a valid point or direction to move");
	}
}
void print(unsigned char M[N][N],int flag_x,int flag_y,int isitok){	     
int i,j=0,l;
char c = '*'; 
int count = 5*N;
for (i = 0; i < count+2; i ++) { /*printing the stars */
    putchar(c);
}
printf("\n");
     for(i=0;i<N;i++){
		 for(j=0;j<N;j++){
			printf("*");
			if(i==flag_x&& j== flag_y && isitok!=0){
				printf("    "); /* when come across with space than print the space */
				continue;
			}
			else{
			 printf("%3d ",M[i][j]);
		 }
		}
		 printf(" *");
		 printf("\n"); /* printing the right star and space patterns */
		 for (l = 0; l < count+2; l ++) {
    putchar(c);
}		
	printf("\n");
		}
	}
	
int main(){
		int flag_x;
		int flag_y;
		int isitok=1; /* control flag for the puzzle that is it solved or not */
		int x;
		int y;
		int check; /* to control if the user enter as a integer or not */
		int direction;
		unsigned char M[N][N];/* Matrix */
		unsigned char arr[N*N];
		unsigned char arr2[N*N-1];
		filltheMatrix(M,arr,arr2,&flag_x,&flag_y);
		
	do{
		print(M,flag_x,flag_y,isitok); /* printing the current table to the screen */
		printf("Please enter the x coordinate of the point: ");
		check=scanf("%d",&x);
		while(check!=1||x<0||x>N-1){
			printf("Please enter a x valid coordinate: ");
			getchar(); /* scanning the coordinates */
			check=scanf("%d",&x);
		}
		printf("Please enter the y coordinate of the point: ");
		check=scanf("%d",&y);
		while(check!=1||y<0||y>N-1){ /* controlling each x and y whether they entered correctly or not */
			printf("Please enter a valid y coordinate: ");
			getchar();
			check=scanf("%d",&y);
		}
		printf("Please enter the direction to move (left:1,right:2,up:3,down:4):"); /*receiving input from the user as integer */
		scanf("%d",&direction);
		controlMove(M,x,y,&flag_x,&flag_y,direction,&isitok);
		}
		while(checkOk(M,arr2)!=1); /* UNTIL THE PUZZLE DONE */
		
		return 0;
	}
