#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

int factorial ( int n) 
{
    int i , ret = 1; 
    for ( i = 2; i <=  n ; i++)ret *= i ; 
    return ret ; 
}

int factorial_while( int n)
{
    int i = 2 , ret = 1; 
    while(i<=n) 
    {
        ret *= i++ ; 
    }
    return ret;
}


double rand_double() 
{
    /*generate random number in [ 0 , 1 ) */ 
    double ret = (double)rand () ; 
    return ret /(RAND_MAX+1); 
} 
int sample_geometric_rv ( double p) 
{
    double q ; 
    int n = 0; 
    do { 
    q  = rand_double() ; 
    n++; 
    } while (q  >=  p ) ; 
    return n ; 
}

int sample_geometric_rv_while( double p) 
{
    double q ; 
    int n = 0; 
    bool check = true ; 
    while (check)
    {
        q = rand_double();
        n++ ; 
        check = (q>=p) ;
    }
    return n ; 
}

int main()
{
    printf("%d\n",factorial(3));
    printf("%d\n",factorial_while(3));
    return 0;
}