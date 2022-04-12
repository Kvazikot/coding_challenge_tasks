//http://acm.timus.ru/problem.aspx?space=1&num=1086
#include <QDebug>
#include "cryptography1086.h"

#define MAX_PRIME_LIMIT 1000000

std::vector<bool> numbers;
std::map<int,int> tab;
int max_n=1;

// реализует алгоритм решето Эратосфена
int find_n_prime(int n)
{

    int p = 2;

    if(numbers.size() == 0)
    {
        numbers.resize(MAX_PRIME_LIMIT);
        for(int i=0; i < MAX_PRIME_LIMIT; i++)
            numbers[i] = true;
        tab[0] = 2;
        qDebug() << "prime " << 0 << " = " << 2;

    }

    int cnt = 1;
    while( p < MAX_PRIME_LIMIT)
    {
        for(int i=2*p; i < MAX_PRIME_LIMIT; i+=p)
        {
            numbers[i] = false;
        }

        for(int i=p+1; i < MAX_PRIME_LIMIT; i++)
        {
            if( numbers[i] )
            {
                p = i;
                qDebug() << "prime " << cnt << " = " << i;
                tab[cnt] = i;
                cnt++;
                if( n == cnt) return i;
                break;
            }
        }

    }

    return 1;
}

Cryptography1086::Cryptography1086(std::vector<int> input)
{
    qDebug() << "\n";
    std::vector<int>::iterator result;
    result = std::max_element(input.begin(),input.end()) ;
    find_n_prime( *result );
    for(int i=0; i<input.size(); i++)
        qDebug() << input[i] << "\t" << tab[input[i]-1];
}
