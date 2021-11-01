 #include <iostream>
 #include <random>
 #include  <ctime>
 using namespace std;

int main()
{   
    mt19937 generator;
    generator.seed(time(0));
    uniform_int_distribution<int> dice(1,6);
    int random = dice(generator);
    for (int i=0; i<10; ++i)
    {
        random = dice(generator);
        cout << random << endl;
    }

    return 0;
}
