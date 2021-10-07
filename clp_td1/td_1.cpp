#include <iostream>
#include <cmath>

using namespace std;

double sin_x_plus_cos_sqrt2_times_x(double x)
{
    return sin(x) + cos(sqrt(2)*x);
};

void print_sin_x_plus_cos_sqrt2_times_x( double begin, double end, double step )
{
    for (int i(begin); i<=end ; i+=step){
        std::cout << "sin_x_plus_cos_sqrt2_times_x(" 
        << i 
        << "): " 
        << sin_x_plus_cos_sqrt2_times_x( i ) 
        << endl;
    };
};

double compute_derivative( std::function< double( double ) > func, double x, double epsilon )
{
    return (func(x+epsilon)-func(x))/epsilon;
};

double find_zero( std::function< double( double ) > func, double begin, double end, double precision )
{
    double mid(( begin + end ) / 2);

    if (func(begin) * func(end) > 0)
    {   
        return (0); 
    };

    if (std::abs(func(mid)) <= precision)
    {   
        return (mid); 
    };

    if (std::abs(func(mid)) > precision)
    {
        if (func(mid) * func(end) < 0)
        {
            return(find_zero(func,mid,end,precision));
        };
        if (func(mid) * func(begin) < 0)
        {
            return(find_zero(func,begin,mid,precision));
        };
    };
};

int find_all_zeros( std::function< double( double ) > func, double begin, double end, double width, 
double precision, double results[], double max_number_of_results )
{

};


void test11()
{
    std::cout << "sin_x_plus_cos_sqrt2_times_x( 1 ): " << sin_x_plus_cos_sqrt2_times_x( 1 ) << endl;
    std::cout << "sin_x_plus_cos_sqrt2_times_x( -4.5 ): " << sin_x_plus_cos_sqrt2_times_x( -4.5 ) << endl;

};

void test12()
{
    std::cout << "Quel est la valeur souhaitée ?" << endl;
    double valeur(0.0);
    std::cin >> valeur;
    std::cout << "sin_x_plus_cos_sqrt2_times_x(" << valeur << "): " << sin_x_plus_cos_sqrt2_times_x( valeur ) << endl;

};

void test21()
{
    std::cout << "Quel est la valeur intiale souhaitée ?" << endl;
    double valeur(0.0);
    std::cin >> valeur;
    for(int i(1); i<=10 ; i++)
    {
        std::cout << "sin_x_plus_cos_sqrt2_times_x(" 
        << valeur 
        << "): " 
        << sin_x_plus_cos_sqrt2_times_x( valeur ) 
        << endl;
        valeur++;
    };
};

void test22()
{
    print_sin_x_plus_cos_sqrt2_times_x(-10, 10, 2);
};

void test23()
{
    std::cout << "Quel est la borne basse souhaitée ?" << endl;
    double begin(0.0);
    std::cin >> begin;

    std::cout << "Quel est la borne haute souhaitée ?" << endl;
    double end(0.0);    
    std::cin >> end;

    
    while (end<begin){
        std::cout << "Hésite pas à donner une borne haute plus haute !!" << endl;
        std::cout << "Quel est la borne haute souhaitée ?" << endl;  
        std::cin >> end;
    }; 

    std::cout << "Quel est le nombre de valeurs souhaitée ?" << endl;
    int values(0);    
    std::cin >> values;

    
    while (values<2){
        std::cout << "Hésite pas à demander plus de deux valeurs!!" << endl;
        std::cout << "Quel est le nombre de valeurs souhaitée ?" << endl;   
        std::cin >> values;
    }; 

    print_sin_x_plus_cos_sqrt2_times_x(begin, end, values);
};

void test31()
{
    double begin(-4.6);
    double end(-4.5);
    double step(0.01);
    double epsilon(pow(10,-5));
    double estimate(0);

    for (double i(begin); i<=end ; i+=step){

        double estimate = compute_derivative(sin_x_plus_cos_sqrt2_times_x,i,epsilon);

        std::cout << "derivative of sin_x_plus_cos_sqrt2_times_x(" 
        << i 
        << "): " 
        << estimate
        << endl;
    };
};

void test32()
{
    double zero = find_zero(sin_x_plus_cos_sqrt2_times_x, -2, 0, pow(10,-5));
    std::cout << zero << endl;

    std::cout << "sin_x_plus_cos_sqrt2_times_x(" 
    << zero
    << "): " 
    << sin_x_plus_cos_sqrt2_times_x(zero)
    << endl;
};

void test41()
{
    double results[] = results[]
    find_all_zeros(sin_x_plus_cos_sqrt2_times_x, -10,10,0.5, pow(10,-5)),, 10)
}

int main()
{
    test32();
    return 0;
}
 