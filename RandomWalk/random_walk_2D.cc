/************************************************************************
 * Random walk in 2D 
 * 
 * **********************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include<sstream>


using namespace std;

int main(int argc, char **argv)
{
    int x,y;

    mt19937 gen(time(NULL));
    discrete_distribution<int> drandom{1,1,1,1};


    string name_file_data; stringstream(argv[1]) >> name_file_data; 
    string name_file_dataR; stringstream(argv[2]) >> name_file_dataR;
    int nsimulation; stringstream(argv[3]) >> nsimulation;
    int nsteps; stringstream(argv[4]) >> nsteps;
    cout << "Number sim" << nsimulation << " " << nsteps << endl;

    ofstream data(name_file_data);
    ofstream dataR(name_file_dataR);  
    dataR.precision(17); 
    data.precision(17);

    for (int sim = 0; sim <= nsimulation; sim++)
    {   
        cout << sim << " simulation number" <<  endl;
        x=0;y=0;
        data.open(name_file_data);
        for (int ste = 0; ste <= nsteps; ste++)
        {
            cout << ste << " step number" <<  endl;
            int ir = drandom(gen);
            switch(ir)
            {
                case 0:
                    x += 1.0;
                    break;
                case 1:
                    x -= 1.0;
                    break;
                case 2:
                    y += 1.0;
                    break;
                case 3:
                    y -= 1.0;
                    break;
            }
            data << x << "\t" << y << endl;
        } 
        data.close();
        dataR << pow(x,2)+pow(y,2) << endl;
    }
    dataR.close();
}
