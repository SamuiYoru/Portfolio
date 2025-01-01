#include <stdio.h> 
#include <stdlib.h> 

int main() 
{ 
	int a[5]; 
	int i,j,k,temp; 

	printf("叫块5璶逼计\n"); 
	for(i=0;i<=4;i++) 
	{ 
		scanf("%d",&a[i]); 
	} 
	printf("\n"); 

	for(i=0;i<=4;i++) 
	{ 
		for(j=i;j<=4;j++) 
		{ 
			if (a[i]>a[j+1]) //璝玡计ゑ计玥ユ传 
			{ 
				temp=a[i]; //︽ユ传 
				a[i]=a[j+1]; 
				a[j+1]=temp; 

				for (k=0;k<=4;k++) 
				{ 
					printf("%d ",a[k]); //ユ传逼 
				} 
				printf("\n"); 

			} 
		} 
	} 
system("PAUSE"); 
}
