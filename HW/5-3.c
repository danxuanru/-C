#include <stdio.h>
#include <math.h>

int M_inverse(int , int , int , int );
int GCD(int, int);

int main(void) {

    // GCD(a,b) => 互質
    // c = 0~b-1 && ac%b=1
    // 
    int T,a,b,c;
    scanf("%d", &T);

    for(int i=0; i<T; i++)
    {
        scanf("%d %d", &a, &b);

        if(GCD(a,b)!=1)
        {
            printf("Inverse doesn't exist\n");
        }
        else
        {
            int x, y;
            y = M_inverse(a, b, 0,1);
            x = (abs(b*y)+1)/a;
            printf("multiplicative inverse is %d\n", x);
        }
    }
    

	return 0;
}

int M_inverse(int i, int j, int t1, int t2)
{
    // a % b = c
    // b->a , c->b
    // sum of a/b

    // t1=0 , t2=1
    // t1 - (a/b)t2 = t
    // t2->t1 , t->t2
    int q, remainder, t;
    remainder = i%j;
    q = i/j;
    t = t1 - q*t2;
    // y = t2, t+t2 取負數
    if(remainder==0) return t2<0 ? t2 : t+t2;
    // a*x - y*b = 1
    // x = (y*b + 1) / a
    return M_inverse(j, remainder, t2, t);
}



int GCD(int i, int j)
{
    int gcd=1;
    if(i<j){ // keep i>j
        int temp = i;
        i = j;
        j = temp;
    }
    for (int n=2; n<=j; n++){
        if(i%n==0 && j%n==0) gcd = n;
    }

    return gcd;
}