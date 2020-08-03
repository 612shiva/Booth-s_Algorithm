#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define maxsize  50
int BIT;

int * add(int *q,int *p,int n)
{
	int i,carry;
	carry=0;
	int *sum=(int *)calloc(sizeof(int),maxsize);
	for(i=n-1; i>=0; i--)
	{
		if(q[i]+p[i]+carry<=1)
		{
			sum[i]+=q[i]+p[i]+carry;
			carry=0;
		}
		else if(q[i]+p[i]+carry==2)
		{
			sum[i]=0;
			carry=1;
		}
		else if(q[i]+p[i]+carry==3)
		{
			sum[i]=1;
			carry=1;
		}
	}
	return sum;
}
int * compliment(int *q,int n)
{
	int i;
	int *o=(int *)malloc(sizeof(int )*maxsize);
	int *sum=(int *)malloc(sizeof(int )*maxsize);
	int *qu=(int *)calloc(sizeof(int ),maxsize);
	for(i=0; i<=n; i++) qu[i]=q[i];
	for(i=0; i<n; i++)
	{
		if(qu[i]==0) qu[i]=1;
		else qu[i]=0;
		o[i]=0;
	}
	o[n-1]=1;
	sum=add(qu,o,n);
	printf("2's compliment of m is: ");
	for(i=0; i<n; i++)
		printf("%d",sum[i]);
	printf("\n");
	return sum;
}

int* decToBinary(int n)
{
	long long binary_number = 0;
	int number=n;
	int *binary_array=(int *)malloc(sizeof(int)*maxsize);
	int remainder, i = 1, step = 0;
	binary_array[0]=0;
	n=abs(n);
	while (n!=0)
	{
		remainder = n%2;
		n /= 2;
		binary_number += remainder*i;
		i *= 10;
		step++;
	}
	BIT=step+1;
	int bn=binary_number;
	while(step!=0)
	{
		binary_array[step]=bn%10;
		bn/=10;
		step--;
	}
	binary_array[BIT]=0;
	if(number<0) binary_array=compliment(binary_array,BIT);
	printf("Value of decimal number %d is: ",number);
	for(i=0; i<BIT; i++)
		printf("%d",binary_array[i]);
	printf("\n");
	return binary_array;
}

void shiftRight(int *q,int n)
{
	if(n>=maxsize-1)
		printf("Size overflow\n");
	else
	{
		int i;
		for(i=n; i>0; i--)
			q[i]=q[i-1];
	}
}

int binToDecimal(int *ans, int n)
{
	int i,dec=0;
	if(!ans[0])
	{
		for(i=1; i<=n; i++)
			dec+=ans[i]*pow(2,n-i);
		return dec;
	}
	else
	{
		for(i=1; i<=n; i++)
			dec+=ans[i]*pow(2,n-i);
		dec=dec-pow(2,n);
		return dec;
	}
}
void equalize(int *q, int *m, int *l, int *BIT)
{
	int i,greater;
	if(*l!=*BIT)
	{
		if(*l<*BIT)
		{
			for(i=0; i<*BIT-(*l); i++)
				shiftRight(m,*BIT);
			greater=*BIT;
		}
		else
		{
			for(i=0; i<*l-(*BIT); i++)
				shiftRight(q,*l);
			greater=*l;
		}
	}
	*l=*BIT=greater;
	printf("\nAfter equlaizing\n");
	printf("q: ");
	for(i=0; i<*BIT; i++)
		printf("%d",q[i]);
	printf("\n");
	printf("m: ");
	for(i=0; i<*l; i++)
		printf("%d",m[i]);
	printf("\n");
}
int arrToNum(int *q,int n)
{
	int i, k = 0;
	for (i = 0; i <n; i++)
		k = 10 * k + q[i];
	if(q[0]==1) k=-1*k;
	return k;
}

void booth(int *q, int *m, int *a,int n)
{
	int i,count=1;
	int *ans=(int *)calloc(sizeof(int),maxsize);
	int *comp=(int *)calloc(sizeof(int),maxsize);
	comp=compliment(m,BIT);
	for(i=0; i<=n; i++)  ans[i]=a[i];
	for(; i<=2*n; i++)   ans[i]=q[i-n];
	printf("  a\t q   q-1    m\n");
	for(i=0; i<n; i++)
		printf("%d",ans[i]);
	printf("\t");
	for(i=n; i<2*n; i++)
		printf("%d",ans[i]);
	printf(" %d",ans[i]);
	printf("\t  ");
	for(i=0; i<n; i++)
		printf("%d",m[i]);
	printf("\tINITAL VALUE\n");
	printf("------------------------------------------------");
	while(count<=BIT)
	{
		if(ans[2*n-1]==1 && ans[2*n]==0)
		{
			printf("\n\t\t\tA = A - M\n");
			a=add(a,comp,n);
		}
		else if(ans[2*n-1]==0 && ans[2*n]==1)
		{
			printf("\n\t\t\tA = A + M\n");
			a=add(a,m,n);
		}
		for(i=0; i<=n; i++)  ans[i]=a[i];
		for(i=0; i<=n; i++)  ans[i+n]=q[i];
		if((ans[2*n-1]==1 && ans[2*n]==0) || (ans[2*n-1]==0 && ans[2*n]==1))
		{
			for(i=0; i<n; i++)
				printf("%d",ans[i]);
			printf("\t");
			for(i=n; i<2*n; i++)
				printf("%d",ans[i]);
			printf(" %d",ans[i]);
			printf("\t  ");
			for(i=0; i<n; i++)
				printf("%d",m[i]);
		}
		shiftRight(ans,2*n);
		printf("\n\t\t\tShift Right\n");
		for(i=0; i<=n; i++) a[i]=ans[i];
		for(i=n; i<=2*n; i++)  q[i-n]=ans[i];
		for(i=0; i<n; i++)
			printf("%d",ans[i]);
		printf("\t");
		for(i=n; i<2*n; i++)
			printf("%d",ans[i]);
		printf(" %d",ans[i]);
		printf("\t  ");
		for(i=0; i<n; i++)
			printf("%d",m[i]);
		printf("\n------------------------------------------------\n");
		count++;
	}
	printf("Final answer (in binary): ");
	for(i=0; i<n; i++)
		printf("%d",ans[i]);
	printf("\t");
	for(i=n; i<2*n; i++)
		printf("%d",ans[i]);
	printf("\n\nThe Product is %d",binToDecimal(ans,2*n-1));
}

int main()
{
	printf("\t\tBOOTH'S ALGORITHM\n\n");
	int *q=(int *)calloc(sizeof(int),maxsize);
	int *m=(int *)calloc(sizeof(int),maxsize);
	int *a=(int *)calloc(sizeof(int),maxsize);
	int i,n,l,multiplier,multiplicand;
	printf("Enter the multiplicand: ");
	scanf("%d",&multiplicand);
	printf("Enter the multiplier:   ");
	scanf("%d",&multiplier);
	m=decToBinary(multiplicand);
	l=BIT;
	q=decToBinary(multiplier);

	if(BIT!=l)
		equalize(q,m,&l,&BIT);
	printf("\n");
	booth(q,m,a,l);
	return 0;
}

