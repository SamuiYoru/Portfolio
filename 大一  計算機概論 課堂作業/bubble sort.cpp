#include <stdio.h> 
#include <stdlib.h> 

int main() 
{ 
	int a[5]; 
	int i,j,k,temp; 

	printf("�п�J5�ӧA�n�ƧǪ���\n"); 
	for(i=0;i<=4;i++) 
	{ 
		scanf("%d",&a[i]); 
	} 
	printf("\n"); 

	for(i=0;i<=4;i++) 
	{ 
		for(j=i;j<=4;j++) 
		{ 
			if (a[i]>a[j+1]) //�Y�e�@�ӼƦr��᭱�Ʀr�j�h�洫 
			{ 
				temp=a[i]; //�H�U�T�欰�洫 
				a[i]=a[j+1]; 
				a[j+1]=temp; 

				for (k=0;k<=4;k++) 
				{ 
					printf("%d ",a[k]); //�C�L�洫��Ƨ� 
				} 
				printf("\n"); 

			} 
		} 
	} 
system("PAUSE"); 
}
