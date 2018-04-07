#include<iostream.h>
#include<fstream.h>

double downmat(int, int, double &, double**, double*);
double detmat(int, double &, double**, double*);
double detfront(int, double*);
double detback(double**);

void main()
{
	int m,n,i,j;
	double **A,*C,sum=0;

	ifstream infile;
	infile.open("data.txt");
	infile>>n;
	m=n-3;

	A=new double*[n];
	for(i=0;i<n;i++)
		A[i]=new double[n];

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			infile>>A[i][j];

	if(m!=0)
	{
		C=new double[m];
		for(i=0;i<m;i++)
			C[i]=1.0;
	}
	else
	{
		C=new double[1];
		C[0]=1.0;
	}

	ofstream outfile;
	outfile.open("data2.txt" , ios::app);
	outfile<<"您輸入的矩陣為"<<n<<"階矩陣:"<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			outfile<<A[i][j]<<" ";
		outfile<<endl;
	}
	outfile<<endl;

	if(n>3)
		sum=downmat(m, n, sum, A, C);
	else
		sum=detmat(m, sum, A, C);

	outfile<<"此矩陣的Det為:"<<sum<<endl<<endl;

	infile.close();
	outfile.close();
}

double downmat(int m, int n, double &sum, double **A, double *C)
{
	int i,j,x=0,y=0,k=0;
	double **B;

	n--;

	B=new double*[n];
	for(i=0;i<n;i++)
		B[i]=new double[n];
	while(k<n+1)
	{
		x=0;
		y=0;
		for(i=0;i<n+1;i++)
		{
			for(j=0;j<n+1;j++)
			{
				if(i!=0 && j!=k)
				{
					B[x][y]=A[i][j];
					y++;
				}
			}
			if(y!=0)
			{
				x++;
				y=0;
			}
		}

		C[n-3]=A[0][k];
		if((k+1)%2==0)
			C[n-3]=C[n-3]*(-1);

		if(n>3)
			downmat(m, n, sum, B, C);
		else
			detmat(m, sum, B, C);

		k++;
	}

	return sum;
}

double detmat(int m, double &sum, double **A, double *B)
{
	sum=sum+detfront(m, B)*detback(A);
	return sum;
}

double detfront(int m, double *A)
{
	int i;
	double front=1;
	for(i=0;i<m;i++)
		front=front*A[i];
	return front;
}

double detback(double **A)
{
	double back;
	back=A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] - A[0][2]*A[1][1]*A[2][0] - A[0][0]*A[1][2]*A[2][1] - A[0][1]*A[1][0]*A[2][2];
	return back;
}