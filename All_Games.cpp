#include <iostream>
#include <conio.h>
#include <cwchar>
#include <windows.h>
#include <time.h>

using namespace std;

int pColors[9] = {247,247,247,247,247,247,247,247,247};
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

char board[3][3] = {'1','2','3',
					'4','5','6',
					'7','8','9'};
int turn = 1;   //1 - P1 | 0 - P2
char mark = 'O';//O - P1 | X - P2
int input;

void setConsoleSize(int f_size){
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = f_size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Calibri");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),FALSE,&cfi);
}

void printInputMatrix(){
	cout<<endl<<endl<<"INPUT MATRIX"<<endl;
	cout<<" 1 | 2 | 3 "<<endl;
	cout<<"-----------"<<endl;
	cout<<" 4 | 5 | 6 "<<endl;
	cout<<"-----------"<<endl;
	cout<<" 7 | 8 | 9 "<<endl;
}

void printBoard(){
	for(int i=0,k=1; i<3; i++){
		for(int j=0; j<3; j++,k++){
			SetConsoleTextAttribute(console, pColors[k-1]);
			cout<<" "<<board[i][j];
			SetConsoleTextAttribute(console, 247);
			if(j<2) cout<<" |";
		}
		cout<<endl;
		if(i<2) cout<<"-----------------"<<endl;
	}
}

int addMark(){
	for(int i=0,k=1; i<3; i++){
		for(int j=0; j<3; j++,k++){
			if( k==input ){
				if( board[i][j]!='X' && board[i][j]!='O' ){
					board[i][j] = mark;
					return 1;
				}
				else{
					cout<<"Invalid Input";
					getch();
					return 0;
				}
			}	
		}
	}
}

int check(){
	// checking rows
	if( board[0][0]==mark && board[0][1]==mark && board[0][2]==mark )
		return 1;
	if( board[1][0]==mark && board[1][1]==mark && board[1][2]==mark )
		return 1;
	if( board[2][0]==mark && board[2][1]==mark && board[2][2]==mark )
		return 1;
		
	
	// checking cols
	if( board[0][0]==mark && board[1][0]==mark && board[2][0]==mark )
		return 1;
	if( board[0][1]==mark && board[1][1]==mark && board[2][1]==mark )
		return 1;
	if( board[0][2]==mark && board[1][2]==mark && board[2][2]==mark )
		return 1;
	
	// checking diagonals
	if( board[0][0]==mark && board[1][1]==mark && board[2][2]==mark )
		return 1;
	if( board[0][2]==mark && board[1][1]==mark && board[2][0]==mark )
		return 1;
		
	return 0;
}

void tictactoe(){                                       //-------------------------------------------------------------------------------------
	setConsoleSize(30);
	SetConsoleTextAttribute(console, BACKGROUND_BLUE|BACKGROUND_GREEN|
									 BACKGROUND_RED|BACKGROUND_INTENSITY);
	int won = 0;
	int validInput = 0;
	
	for( int i=0; i<9; i++ ){
		system("cls");
		printBoard();
		
		if( turn ){
			SetConsoleTextAttribute(console,242);
			cout<<"O - Player 1:"<<endl;	
		} 
		else{
			SetConsoleTextAttribute(console,242);
			cout<<"X - Player 2:"<<endl;	
		} 
		//printInputMatrix();
		//cout<<"Enter Input from Input Matrix: ";
		cin>>input;
		while(input<0 || input >9){
			cout<<"Invalid Input please Re-Enter Input:";
			cin>>input;
		}
		
		if( turn ) pColors[input-1] = 242;
		else pColors[input-1] = 252;
		
		if( turn ) mark = 'O';
		else mark = 'X';
		
		validInput = addMark();
		if( !validInput ){
			i--;
			continue;
		}
		won = check();
		if( won ){
			system("cls");
			printBoard();
			if( turn )
			{
				SetConsoleTextAttribute(console,242);
				cout<<endl<<"**********";
				cout<<endl<<"* Player 1 - You Won *";
				cout<<endl<<"**********";
			}
			else{
				SetConsoleTextAttribute(console,252);
				cout<<endl<<"**********";
				cout<<endl<<"* Player 2 - You Won *";
				cout<<endl<<"**********";
			}
			getch();
			break;
		}
		
		if( i==8 ){
			system("cls");
			printBoard();
			cout<<endl<<"* MATCH DRAW *";
		}
		turn = !turn;
	}
}

void quiz(){                             //----------------------------------------------------------------------------------------------------
	string questions[10] = {
	"Which of the following is Tricontinental Country?",
	"Famous fast food restaurant company Burger King belongs to which Country?",
	"Office of strategic service (OSS) was old name of which Intelligence agency?",
	"The first person to draw the map of earth?",
	"Who laid first step on the Moon?",
	"What is the name of Chinese parliament?",
	"Ogaden desert is present in____?",
	"Capital of America is_____?",
	"Wadi Rum which resemblance to the surface of Mars is located in____?",
	"Borneo Island is in which Ocean?"
						};
	string options[10][4] = {
	{"chad","Chile","Mali","Switzerland"},
	{"America","England","Turkey","None of these"},
	{"MI6","CIA","ISI","N.O.T"},
	{"Heraclitus","phythagoras","Anaximander","Thales"},
	{"LMP Edgar","CMP Stuart","Neil Armstrong","None of them"},
	{"National Assembly","National people’s Congress","Fedral parliament","None"},
	{"Europe","Asia","Africa","America"},
	{"Washington Dc","Alaska","Hawaii","California"},
	{"Argentina","Israel","Jordan","Egypt"},
	{"Indian Ocean","Pacific Ocean","Arctic Ocean","Atlantic"},
					    };
	string correctOptions[10] = {
		"Chile","America","CIA","Anaximander",
		"Neil Armstrong","National people’s Congress","Africa",
		"Washington DC","Jordan","Pacific Ocean"
								};
	int userOptions[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int totalQs = 10;	
	int op;

	//----- Conducting Quiz -----
	for( int i=0; i<totalQs; i++ ){
		cout<<"Question # "<<(i+1)<<endl;
		cout<< questions[i]<<endl;
		cout<< "1."<<options[i][0]<<endl;
		cout<< "2."<<options[i][1]<<endl;
		cout<< "3."<<options[i][2]<<endl;
		cout<< "4."<<options[i][3]<<endl<<endl;
		
		cout<<"Select Option (1-4) or 0 to skip and press enter: ";
		cin >> userOptions[i];
		cout<<endl<<"-----------------------------"<<endl<<endl;
	}
	
	//----- Printing Correct Options -----
	cout<<"======= ======= ======= ======= "<<endl;
	cout<<"======= Correct Options ======= "<<endl;
	cout<<"======= ======= ======= ======= "<<endl;

	for( int i=0; i<totalQs; i++ ){
		cout<<"Question # "<<(i+1)<<endl;
		cout<< questions[i]<<endl;
		cout<< "1."<<options[i][0]<<endl;
		cout<< "2."<<options[i][1]<<endl;
		cout<< "3."<<options[i][2]<<endl;
		cout<< "4."<<options[i][3]<<endl;
		
		if( userOptions[i] == 0 ){
			cout<< "You Skipped this Question."<<endl;		
		}else{
			cout<< "You Selected : "<<options[i][userOptions[i]-1]<<endl;		
		}
		cout<< "Correct Option : "<<correctOptions[i]<<endl<<endl;

		cout<<"Press any key to continue..."<<endl;
		getch();
		cout<<endl<<"------------------"<<endl;
	}
	
	//----- Printing Result -----
	cout<<endl<<endl;
	cout<<"======= ======= ======= ======= "<<endl;
	cout<<"=======      Result     ======= "<<endl;
	cout<<"======= ======= ======= ======= "<<endl;

	int correct = 0;
	int incorrect = 0;
	int skipped = 0;
	for( int i=0; i<totalQs; i++ ){
		if( userOptions[i] != 0 ){
			if( correctOptions[i] == options[i][userOptions[i]-1] ){
				correct++;
				}else{
				incorrect++;
			}
		}else{
			skipped++;
		}
	}
	cout<< "Total Questions : "<< totalQs <<endl;	
	cout<< "Correct : "<< correct <<endl;
	cout<< "In-Correct : "<< incorrect <<endl;
	cout<< "Skipped : "<< skipped <<endl;
	
	getch();
}

void guess(){                                            //------------------------------------------------------------------------------------
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
}

int main(){
	
	int choice;
	cout<<"Enter '1' for 'TicTac Toe game': \nEnter '2' for 'Quiz game': \nEnter '3' for 'Number guessing game': \n";
	cin>>choice;
	
	switch(choice){
	case 1:
		tictactoe();
	break;

	case 2:
		quiz();
	break;
	
	case 3:
		guess();
	break;
	}
	
	return 0;
}

