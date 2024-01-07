#include <bits/stdc++.h>
#include <time.h>

using namespace std;

int main(){
	int number,guess,nguess=1;
    srand(time(0));
    number = rand()%100 + 1;
    cout<<"Guess the number between 1 to 100.\n\n";
    do{
        cout<<"Enter your guess: \n";
        cin>>guess;
        if(guess>number){
            cout<<"Enter smaller number!\n\n";
        }
        else if(guess<number){
            cout<<"Enter higher number!\n\n";
        }
        else{
            cout<<"Congratulations! You have correctly guessed the number in "<<nguess<< " attempts.\n";
        }
        nguess++;
    }while(number!=guess);
    
    return 0;
}
