 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 using namespace std;

 int main()
 {
     int no_of_numbers = 100;
     int first_number = 1;
     srand(time(0)); 
 
     int random = rand() % no_of_numbers + first_number; 
     for (int i = 0; i<10; ++i)
     {
        random = rand() % no_of_numbers + first_number; 
        cout << random << endl;
     }


     return 0;
 }