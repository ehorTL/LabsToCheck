#include"randomfunctions.h"

#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;

int get_rand_from_range_incl(int l, int r)
{
    static int changer = 1;
    srand(time(0) + changer*changer/tan(changer));
    changer++;
    return rand()%(r-l+1) + l;
}
