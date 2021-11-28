#include <iostream>
#include <vector>
using namespace std;



int main()
{
    vector<int> g = {4, 2, 3, 4, 5};
    for (auto i: g)
    {
        cout << i << " ";
    }
    return 0;
}