 #include <iostream>
 #include <random>
 #include  <ctime>
 using namespace std;

int main()
{   
    cout << "Random number generator for dice roller.\n";
    mt19937 gen(time(NULL));
    uniform_int_distribution<int> dice(1,6);
    int random = dice(gen);
    for (int i=0; i<10; ++i)
    {
        random = dice(gen);
        cout << random << endl;
    }

    cout << "Random direction generator for xy system.\n";
    discrete_distribution<int> ir{0,1,1,1,1};
    for (int i=0; i<10; ++i)
    {
        int random2 = ir(gen);
        cout << random2 << endl;
    }

    return 0;
}
