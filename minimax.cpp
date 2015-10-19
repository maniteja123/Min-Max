# include <bits/stdc++.h>
using namespace std;

int oldx = -1, oldy = -1 , newx = -1 , newy = -1;

int hue(int **a) {
	int i , j ;
	int score = 0 ;
	int n = 8;
	for( i= 0 ; i < n ; i++) {
		for(j = 0  ; j < n ; j++) {
			if((i==0) &&(a[i][j] == -1) )
				return INT_MAX;
			if( (i==n-1) && (a[i][j] == 1))
				return INT_MIN;
			if(a[i][j] == 1)
				score -= n-i-1;
			if(a[i][j] == -1)
				score += i;
		}
	}
	return score;
}

int minimax(int **a, int level) {
	int i , j ;
	int huecost= (level%2)?INT_MAX:INT_MIN;
	int newhue; 
	int turn = (level%2)?-1:1;;
	if(level == 0) {
		return hue(a);
	}
	for(i = 0 ;i < 8 ; i++) {
		for(j=  0 ; j < 8 ; j++) {
			if( a[i][j] == turn) {
				if( (i+turn) == -1 && (level%2 == 1))
					return INT_MAX;
				if( (i+turn) == 8 && (level%2 == 0))
					return INT_MIN;
                if(a[i+turn][j+1] == -1*turn && j+1 != 8) {                	
                    a[i][j] = 0;
                    a[i+turn][j+1] = turn;
                    if(level % 2 == 1)  {
                		newhue = minimax(a,level-1);
                		huecost = min(newhue,huecost);
                	}
                    else {
                    	newhue = minimax(a,level-1);
                    	huecost = max(newhue,huecost);
                    }    
                    a[i][j] = turn;
                    a[i+turn][j+1] = -1*turn;
                } else if(a[i+turn][j-1] == -1*turn && j-1 != -1)   {
                    a[i][j] = 0;
                    a[i+turn][j-1] = turn;
                    if(level % 2 == 1) {
                		newhue = minimax(a,level-1);
                		huecost = min(newhue,huecost);
                	}
                    else {
                    	newhue = minimax(a,level-1);
                    	huecost = max(newhue,huecost);
                    }                   
                    a[i][j] = turn;
                    a[i+turn][j-1] = -1*turn;
                }  else if ( a[i+turn][j] == 0)  {
                    a[i][j] = 0;
                    a[i+turn][j] = turn;
                    if(level % 2 == 1)  {
                		newhue = minimax(a,level-1);
                		huecost = min(newhue,huecost);
                	} else {
                    	newhue = minimax(a,level-1);
                    	huecost = max(newhue,huecost);
                    }                   
                    a[i][j] = turn;
                    a[i+turn][j] = 0;                  
                }
			}
		}
	}		
	return huecost;
}

void nextmove(int **a,int level) {

	int i , j ;
	int huecost= INT_MAX;
	int newhue; 
	int turn = 1;
	for(i = 0 ;i < 8 ; i++) {
		for(j=  0 ; j < 8 ; j++) {
			if( a[i][j] == turn) {
				if( (i+turn) == -1 || (i+turn) == 8) {
					oldx = -1, oldy = -1 , newx = -1 , newy = -1;
					return;
				}
                if(a[i+turn][j+1] == -1*turn && j+1 != 8)     { 
                	a[i][j] = 0;
                    a[i+turn][j+1] = turn;                    
                    newhue = minimax(a,level-1);
                    if(newhue < huecost)  {
                    	oldx = i;
                    	oldy = j;
                    	newx = i+turn;
                    	newy = j+1;
                    	huecost = newhue;
                    }                    
                    a[i][j] = turn;
                    a[i+turn][j+1] = -1*turn;
                } else if(a[i+turn][j-1] == -1*turn && j-1 != -1)   {	
                    a[i][j] = 0;
                    a[i+turn][j-1] = turn;
                    newhue = minimax(a,level-1);
                    if(newhue < huecost) {
                    	oldx = i;
                    	oldy = j;
                    	newx = i+turn;
                    	newy = j-1;
                    	huecost = newhue;
                    }                    
                    a[i][j] = turn;
                    a[i+turn][j-1] = -1*turn;
                } else if ( a[i+turn][j] == 0) {                	
                    a[i][j] = 0;
                    a[i+turn][j] = turn;
                    newhue = minimax(a,level-1);
                    if(newhue < huecost)   {
                    	oldx = i;
                    	oldy = j;
                    	newx = i+turn;
                    	newy = j;
                    	huecost = newhue;                    	
                    }                    
                    a[i][j] = turn;
                    a[i+turn][j] = 0;                  
                }
			}
		}
	}
}
int main()
{	
	int i , j;
	int n = 8;	
	int **arr=(int **)malloc(sof(int *)*n);
	for(i=0;i<n;i++)
		arr[i]=(int *)malloc(sizeof(int)*n);
	for(i= 0 ; i < n  ; i++) {
		for( j= 0 ; j < n ; j++) {
			cin >> arr[i][j];
		}
	}
	int size = 11 ;
	nextmove(arr,size);
	cout << "Old " << oldx << " " << oldy  << endl ;
	cout << "new " << newx << " " << newy  << endl ;
	return 0 ;
}