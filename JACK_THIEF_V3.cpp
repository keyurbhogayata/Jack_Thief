/*
 		+++ JACK THIEF GAME +++
 		
@author RDP
*ASUMPTIONS*
	1.MACHINE HAS NO PREFERENCE IT PLAYS COMPLETELY RANDOMLY.
	2..

*LIMITATIONS*
	1..

*/
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;
/*
S= spade
C= club
d= diamond
h =heart
*/
//Collection of cards As an array of strings
string cards[]=
{
	"SA","S2","S3","S4","S5","S6","S7","S8","S9","S10","SJ","SQ","SK",
	"CA","C2","C3","C4","C5","C6","C7","C8","C9","C10","CJ","CQ","CK",
	"DA","D2","D3","D4","D5","D6","D7","D8","D9","D10","DJ","DQ","DK",
	"HA","H2","H3","H4","H5","H6","H7","H8","H9","H10","HJ","HQ","HK"
};
//Defining player class
class player
{
	private:
		//Collection of cards for the player.
		vector <string> pcards;
	public:
		//Main functions
		void get_card();
		void eliminate_cards();
		void getcard_from_player(player& );
		//Other functions
		void display();
		void shuffle();
		bool in_game();
		int give_noc();	
};
///Main functions
void player::get_card()
{
	/*
	This function will give one random card to player from deck.
	If any card is taken this function will mark flag on it's index.(flag="NO").
	*/
	srand(time(0));
	int c;
	while(1)
		{
			c=rand()%52;
			if(cards[c]!="NO")
				break;
		}
	//pushing cards in perticular player's cards.
	pcards.push_back(cards[c]);
	cards[c]="NO";
}
void player::eliminate_cards()
{
	/*
	This function will eliminate pair of similar cards from player's collection.
		First it will set flags for similar cards.(flag="NO").
		Then it will remove flaged cards from deck with the help of vector's erase function.
	*/
	for(int i=0;i<pcards.size();i++)
	{
		for(int j=i+1;j<pcards.size();j++)
		{
			//Setting flag.
			if(pcards[i][1]==pcards[j][1])
				pcards[i]=pcards[j]="NO";
		}
	}
	for(int i=0;i<pcards.size();i++)
		if(pcards[i]=="NO")
		{
			//Removing card.
			pcards.erase(pcards.begin()+i);
			i=-1;
		} 
}
void player::getcard_from_player(player &p)
{
	int c;
	/*
	//If human wants to play they can include this code and comment out "//FOR PC " code.
	
	//Start
	cout<<" PLEASE ENTER LESS THAN "<<p.pcards.size()+1<<" : ";
	cin>>c;
	c--;
	cout<<endl;
	while(c>p.pcards.size())
		{
			cout<<"ENTER AGAIN: ";
			cin>>c;
			cout<<endl;
			c--;
		}
	//End
	
	*/	
	//FOR PC
	//Start
	srand(time(0));
	c=rand()%p.pcards.size();
	//End
	
	cout<<c<<endl;
	//Pushing the chosen card in collection of player.
	pcards.push_back(p.pcards[c]);
	//Erasing card which was chosed from other player's collection.
	p.pcards.erase(p.pcards.begin()+c);
	//Checking and eliminating pairs.
	eliminate_cards();
}
//Other functions
void player::display()
{
	//Displaying cards using for_each loop.
	for(string card:pcards)
		cout<<card<<" ";
}
void player::shuffle()
{
	//Randomly shuffling player's cards.
	srand(time(0));
	for(int i=0;i<pcards.size();i++)
	{
		int c=rand()%pcards.size();
		swap(pcards[i],pcards[c]);
	}
}
bool player::in_game()
{
	/*
	This function return true if player is in game otherwise false.
		To be in game player must have 1 or more cards.
	*/
	if(pcards.size()==0) return false;
	else return true;
}
int player::give_noc()
{
	//Returns number of card player have.
	return pcards.size();
}
//Utility function to remove jack
remove_jack()
{
	char c;
	cout<<"WHICH JACK YOU WANT TO REMOVE (S= SPADE , C= CLUB , D= DIAMOND , H = HEART - ENTER S OR C OR D OR H)  : ";
	cin>>c;
	//Removing JACK according to choice.
	switch(c)
	{
		case 's':
		case 'S':cards[10]="NO"; break;
		
		case 'c':
		case 'C':cards[23]="NO"; break;
			
		case 'd':
		case 'D':cards[36]="NO"; break;
			
		case 'h':
		case 'H':cards[49]="NO"; break;
			
		default: cards[49]="NO"; 
		    cout<<"YOU HAVE ENTERED WRONG CHOICE SO WE HAVE REMOVED A RANDOM JACK !!!"<<endl;
	}
}
int main()
{
	cout<<"\t\t--------------> *** WELCOME TO JACK THIEF GAME *** <--------------"<<endl;
	//Removing jack.
	remove_jack();
	/*
		num= number of players.
		i,j = utility ints.
		cnt_moves = to count number of moves in game (Intialized with 0).
	*/
	int num,i=0,j=0,cnt_moves=0;
	//ACTUAL PROGRAM STARTS ;
	cout<<endl<<endl;
	cout<<"HOW MANY PLAYERS ARE GOING TO PLAY ? (Less than 52) : ";
	cin>>num;
	if(num>=52||num<=1)
		{
			cout<<"\nERROR : INVALID PLAYERS !!!!"<<endl;
			return 0;
		}
	// Creating 'num' number of objects of player class.
	player p[num];
	// Creating string array to store 'num' number of names. 
	string names[num];
	//SETTING NAME OF EACH PLAYER ;
	for(i=0;i<num;i++)
	{
		cout<<"\nENTER NAME OF PLAYER NO."<<i+1<<" :";
		cin>>names[i];
	}
	//DISTRIBUTING CARDS ;
	for(i=0;j<51;i=(i+1)%num,j++)
		p[i].get_card();
	cout<<endl;
	for(i=0;i<num;i++)
	{
		//DISPLAYING CARDS ;
		cout<<names[i]<<"'S CARDS : ";
		p[i].display();
		cout<<endl;
		//ELEMINATING CARDS ;
		p[i].eliminate_cards();
		cout<<names[i]<<"'S CARDS (AFTER ELEMINATING SAME CARDS) : ";
		//AGAIN DISPLAYING CARDS AFTER ELIMINATION OF CARDS.
		p[i].display();
		cout<<endl<<endl;
	}
	cout<<endl<<"\t\t--------------> *** THE REAL GAME IS STARTING NOW !!! *** <--------------"<<endl;
	//Circular loop for game.
	for(int i=0;i<num;i=(i+1)%num)
	{
		//If player has 0 cards he shouldn't be included in game.
		if(p[i].give_noc()==0)
			continue;
		else
		{
		//If next player has 0 cards we must search for other player with 1 or more cards.
			j=(i+1)%num;
			while(p[j].give_noc()==0)
			{
				j=(j+1)%num;
				/*
				If that other player is player himself than he lost.
					Because every other players have 0 cards.
				*/
				if(i==j)
				{
					// Giving him some sympathy... ;)
					cout<<"\nSORRY  "<<names[i]<<" !!! , YOU LOST :( ."<<endl;
					cout<<endl;
					//Displaying cards to make sure that only one player is left with only one card which is JACK.
					for(i=0;i<num;i++)
						{
						cout<<names[i]<<"'S CARDS :";
						p[i].display();
						cout<<endl;
						}
					//Displaying number of moves it took to complete the game.
					cout<<"\nGAME COMPLETED AFTER "<<cnt_moves<<" MOVES !!!"<<endl;	
					//Ending program here by returning 0 to main function.
					return 0;
				}
			}
			// If everything works out fine than player must pick card from next player.
			cout<<"HEY "<<names[i]<<", WHICH CARD YOU WANT TO PICK FROM "<<names[j];
			// Incrimenting moves.
			cnt_moves++;
			//Calling function for picking card from another player.
			p[i].getcard_from_player(p[j]);
			cout<<endl;
			//After each move we are displaying all player's cards.
			for(int k=0;k<num;k++)
			{
				cout<<names[k]<<"'S CARDS :";
				p[k].display();
				cout<<endl;
			}	
		}
	}
	return 0;
}
