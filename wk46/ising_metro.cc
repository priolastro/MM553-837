/****************************************************************************
 * ising_metro.cc
 * **************************************************************************/

#include<iostream>
#include<random>
#include<time.h>
#include<sstream>
#include<stdio.h>
#include<vector>

using namespace std;

double G_correlation(vector<vector<int>> &sigma, int &distance)
{
	// cout << "Funizione Gcorr\n";
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
                // cout <<  sigma[i][j] << " " << ip << " " << jp <<  " neighbours" << endl;
				Gcorr+=ip*jp;
			}
	return Gcorr;
}



int main(int argc, char** argv) 
{

	if (argc != 9) 
	{
		cerr << "usage: " << argv[0] <<" <L> <k> <ntherm> <nstep> <nmeas>  <cold or hot> <typewriter or random> <distance>" << endl;
		exit(1);
	}

	int L ;         stringstream(argv[1]) >> L;
	double kappa;   stringstream(argv[2]) >> kappa;      // J/kT    
	int ntherm; stringstream(argv[3]) >> ntherm;  //Number of thermalization steps
	int nstep;  stringstream(argv[4]) >> nstep;  //The number of steps 
	int nmeas;  stringstream(argv[5]) >> nmeas;  //Freq. of measurement , how many to skip between measurments
	string Type; stringstream(argv[6]) >> Type; //Type of start, cold or hot
	string Update; stringstream(argv[7]) >> Update; //Type of update, typewriter or random
	int distance; stringstream(argv[8]) >> distance; //Distance parameter for gcorrelation function
	//--------------------------------------------------------------------------

	mt19937 gen(time(NULL));
	uniform_int_distribution<int> dist01(-1,1);
	uniform_real_distribution<double> adist(0,1); 
	uniform_int_distribution<int> sdist(0,L-1); 
	double acc=0.0;

	vector<vector<int>> sigma(L,vector<int>(L,1));

	if (Type == "hot")
	{
		for (int i=0; i < L; i++)
    	{
    	    for (int j=0; j < L; j++)
			{	
				int random_number = dist01(gen);
            	if (random_number != 0)
 		    		sigma[i][j]=random_number;
			}		
    	}
	}

double somma = 0.0;
	for (int i = 0 ; i < L ; i++)
		for (int j = 0 ; j < L ; j++) 
		{
			somma+=double(sigma[i][j]);
		}
	
cout << abs(somma/(double(L)*double(L))) << endl;


	for (int t=0; t<(ntherm+nstep); t++) 
	{
		// if (Update == "random") //to update the sites in a random fashion
			// shuffle(sigma.begin(), sigma.end(), gen);

		for (int i=0; i<L ; i++)  
			for (int j=0; j<L ; j++) 
			{
				//First correctly handle the boundaries
				double im1; 
				if (i==0) 
					im1=sigma[L-1][j];
				else
					im1=sigma[i-1][j]; 
				double ip1; 
				if (i==(L-1)) 
					ip1=sigma[0][j];
				else
					ip1=sigma[i+1][j]; 
				double jm1; 
				if (j==0) 
					jm1=sigma[i][L-1];
				else
					jm1=sigma[i][j-1]; 
				double jp1; 
				if (j==(L-1)) 
					jp1=sigma[i][0];
				else
					jp1=sigma[i][j+1];
				//Now the sign of the proposed spin flip
				double flip; 
				if (sigma[i][j] == 1)
					flip=-2.0;
				else
					flip=2.0; 
				//Sum over the nearest nieghbors
				double nn = ip1+im1+jp1+jm1; //can be max 4 min -4
				//Calculate the change in energy
				double p = exp(kappa*flip*nn);	//fliip = -2sigma
				//accettare o no 
				if (p > 1) 
				{ 
					sigma[i][j] *= -1;
					acc++;
				} 
				else if (adist(gen) < p) 
				{
					sigma[i][j] *= -1; 
					acc++;
				}
			}

		if ((t>=ntherm)&&(((t-ntherm) % nmeas)==0)) 
		{
			double m = 0.0; 
			for (int i = 0 ; i < L ; i++)
				for (int j = 0 ; j < L ; j++) 
				{
					m+=double(sigma[i][j]);
				}
		    m /= (double(L)*double(L));
			double G = G_correlation(sigma, distance);
			cout << abs(m) << endl;  // 
		}
	
	}

	cerr << "acc = "<<(double)acc/(L*L*(nstep+ntherm))<<endl;

	


	return 0;

}