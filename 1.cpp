#include <iostream>
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
using namespace std;

struct S {
    int cost, curr_cost, procent, max_count, count, totalcost = 0;
};

void print_S (S x) {
    cout << "curr_cost=" << x.curr_cost <<" count=" << x.count << " procent=" << x.procent << " total_cost=" << x.totalcost << "\n";
}

int main() {
    S arr [19];
    arr[0].curr_cost = 200;
    arr[0].count = 5;
    arr[1].curr_cost = 600;
    arr[1].count = 0;//3
    arr[2].curr_cost = 200;
    arr[2].count = 3;
    arr[3].curr_cost = 200;
    arr[3].count = 5;

    arr[4].curr_cost = 900;
    arr[4].count = 2;
    arr[5].curr_cost = 300;
    arr[5].count = 2;
    arr[6].curr_cost = 300;
    arr[6].count = 2;
    arr[7].curr_cost = 300;
    arr[7].count = 2;

    arr[8].curr_cost = 5000;
    arr[8].count = 1;
    arr[9].curr_cost = 300;
    arr[9].count = 2;
    arr[10].curr_cost = 300;
    arr[10].count = 2;
    arr[11].curr_cost = 600;
    arr[11].count = 3;

    arr[12].curr_cost = 900;
    arr[12].count = 5;
    arr[13].curr_cost = 200;
    arr[13].count = 5;
    arr[14].curr_cost = 1666;
    arr[14].count = 1;//5
    arr[15].curr_cost = 10000;
    arr[15].count = 1;

    arr[16].curr_cost = 5000;
    arr[16].count = 2;
    arr[17].curr_cost = 200;
    arr[17].count = 2;
    arr[18].curr_cost = 200;
    arr[18].count = 1;

    forn(i, 19) arr[i].procent = arr[i].curr_cost / 10; 
    forn(i, 19) arr[i].cost = arr[i].curr_cost; 
    forn(i, 19) arr[i].max_count = arr[i].count; 
    forn(i, 19) forn(j, arr[i].count) arr[i].totalcost += (j+1) * arr[i].curr_cost;
    // forn(i, 19) {cout << i << " "; print_S(arr[i]);}

    int all_count = 0;
    forn(i, 19) all_count += arr[i].count;
    cout << "\nALL COUNT - " << all_count << "\n\n";

    int k = 0;
    int Sum = 0;
    while (all_count) {
        int max = 0, max_i = -1;
        forn(i, 19)
            if (arr[i].count) {
                int p = arr[i].cost * arr[i].max_count;
                int p1 = p + k * p / 10;
                if (p1 > max) {
                    max = p1;
                    max_i = i;
                }
            }
            // if (arr[i].count) {
            //     forn(j, arr[i].count) p += arr[i].curr_cost * j + (k + j) * arr[i].curr_cost / 10;
            //     if (p / arr[i].count > max) {
            //         max = p;
            //         max_i = i;
            //     }
            //     p = 0;
            // }
        cout << max_i << " - ";
        Sum += arr[max_i].curr_cost + k * arr[max_i].curr_cost / 10;
        cout << arr[max_i].curr_cost + k * arr[max_i].curr_cost / 10 << "; ";
        // arr[max_i].totalcost -= arr[max_i].curr_cost;
        arr[max_i].curr_cost += arr[max_i].cost;
        k++;
        arr[max_i].count--;
        all_count--;
    }
    cout << "\n" << Sum << "\n";

    return 0;
}