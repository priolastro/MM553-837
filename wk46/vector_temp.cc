#include <vector>
#include <iostream>
#include <random>


using namespace std;

double G_correlation(vector<vector<int>> &sigma, int &distance)
{
	cout << "Funizione Gcorr\n";
	double Gcorr;
	double L = sigma.size();
	for (int i=0; i<L ; i++)  
			for (int j=0; j<L ; j++) 
			{
				double ip; 
				double jp; 
				if (j>=(L-1)) 
					ip = sigma[i][j-L+distance];
                else if ((j+distance)>=L)
                    ip = sigma[i][j-L+distance];
				else
					ip = sigma[i][j+distance];
				if (i>=(L-1))  
					jp = sigma[i-L+distance][j];
                else if (i+distance>=L)
                    jp = sigma[i-L+distance][j];
				else
					jp = sigma[i+distance][j];
                cout <<  sigma[i][j] << " " << ip << " " << jp <<  " neighbours" << endl;
				Gcorr+=ip*jp;
			}
	return Gcorr;
}


int main(){

    mt19937 gen(time(NULL));
    uniform_int_distribution<int> sdist(-1,1); 


    int L = 5;
    vector<vector<int>> sigma(L,vector<int>(L,1));
    cout << "Dimension " << sigma.size() << endl;
    for (int i=0; i < sigma.size(); i++)
    {
        for (int j=0; j < sigma.size(); j++)
        {   
            int random_number = sdist(gen);
            if (random_number != 0)
                // cout << random_number << endl;
                sigma[i][j]=random_number;
        }
    }
    for (int i=0; i < sigma.size(); i++)
        {
            for (int j=0; j < sigma.size(); j++)
            {
                cout << sigma[i][j] << endl;
            }
        }  
    //iterate over random vector elements
    vector<int> vettore={0,1,2,3,4,5,6};
    shuffle(vettore.begin(), vettore.end(), gen);
    for (int i=0; i < vettore.size(); i++)
    {
        // cout << vettore[i] << endl;
    }
    // cout << " \n" << endl;

    vector<vector<int>> vettore_tre={{0,1,2},{3,4,5},{6,7,8}};

    for (int i = 0; i < vettore_tre.size(); i++)
    {
        for (int j = 0; j < vettore_tre[i].size(); j++)
        {
            // cout << vettore_tre[i][j] << endl;
        }
    }

    int distance = 1;   
    // cout << G_correlation(vettore_tre, distance) << endl;
return 0;
}