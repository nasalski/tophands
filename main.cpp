#include <iostream>
#include <string>
#include <cstdlib> // ��� ������ � �������� system()
#include <stdio.h>
#include<ctime>
#include <sstream>
using namespace std;

class Deck{       // ���� ������ ���� � ��������� �� 6 �� 10
                  // � ������� �����(V), ����(D), ������(K), ���(T). ��� �� ���� 4 �����: �����(k), ����(p), �����(b), �����(c)
	public:
		static const int N = 36; //���������� ���� � ������
 		string deck[N]; // ������ ���� 
 		char tr;
 		void create(){                      // ������� ������ ����
 			int i = 0;
 			string b;
 			int c = 0;
 			for(int i = 0; i <= 3; i++) {
               
 				switch (i)
 					{	case 0:
 							b = "k";
							break;
				    	case 1:
				    		b = "p";
							break;
						case 2:
							b = "b";
							break;
						case 3:
							b = "c";
							break;
					 }
		 		deck[c] = " 6" + b; c++;
				deck[c] = " 7" + b; c++;
				deck[c] = " 8" + b; c++;
				deck[c] = " 9" + b; c++;
				deck[c] = "10" + b;  c++;
				deck[c] = " V" + b; c++;
				deck[c] = " D" + b; c++;
				deck[c] = " K" + b; c++;
				deck[c] = " T" + b;  c++;
 			}
 		}
 		
 		void view(){                    // ���������� ��� �����, ��� �������
 			for(int i=0;i<N;i++){
 				cout<< deck[i] <<" ";


 			}
 		}
 		
 		void mix(){                   // ������������ ������
 			string deck2[N]; 
 			int tmp=N;
 			for(int i=0;i<N;i++){ 
 			    srand(time(0));
				int t=rand()%tmp;
				deck2[i]=deck[t];
				deck[t]=deck[tmp-1];
				--tmp;
			}
			 for (int i = 0; i<N; i++)
      			deck[i] = deck2[i];
    				
 		}
 		
 		char trump(int t){        // ���������� ����� ��������� �����, ����� ��� ������ ������
 			char *to = (char *) deck[t].c_str();
 			return to[2];
 		}
 		
 	     void setTrump(char t){ // ������ ������
 	     	tr = t;
 	     }
 	     
 	     char getTrump(){      // ���������� ������
 	     	return tr;
 	     }
 	     
 	     string* getDeck(){    // ���������� ������
 	     	
 	     	return deck;
 	     }
	
};
class Player{                // ����� ������
	static const int N = 6; //���������� ���� � ����
	string hand[N];
	char tr;
	int points;
public:
    void addCards(string *cards){           // ��������� ����� � ����
		for(int i=0;i<N;i++){
 				hand[i] = cards[i];
 			}
	}
	void viewHand(){                         // ���������� ����� �� ����
		for(int i=0;i<N;i++){
 				cout<< hand[i] <<" ";
 		}
 		cout<<endl;
 	}
 	void setTrump(char t){                     // �������� ������ ������
 		tr = t;
 	}
 	void sortHand(){                           // ���������� ���� �� ���� � ������ �������
 		string temp;
 		for (int i = 0; i < N - 1; i++) {
        	for (int j = 0; j < N - i - 1; j++) {
        		
        		string card;
        		ostringstream buffer;
    			buffer << hand[j][0];
    			buffer << hand[j][1];
    			card = buffer.str();                // ����������� 1 � ������� ������� ������ � ��������� ������
        		if(card==" V") card = "11";        //������� ��������� ���� ��� �������� ���������
        		if(card==" D") card = "12";
        		if(card==" K") card = "13";
        		if(card==" T") card = "14";
        		char mast = hand[j][2];
        		
        		string nextCard;
        		ostringstream buffer2;
    			buffer2 << hand[j+1][0];
    			buffer2 << hand[j+1][1];
    			nextCard = buffer2.str();
        		if(nextCard==" V") nextCard = "11";
        		if(nextCard==" D") nextCard = "12";
        		if(nextCard==" K") nextCard = "13";
        		if(nextCard==" T") nextCard = "14";
        		
        		
        		char nextMast = hand[j+1][2];
        		
            	if ((mast!=tr && nextMast==tr) || ((mast==tr && nextMast==tr)&&(card<nextCard)) || ((mast!=tr && nextMast!=tr)&&(card<nextCard))) {
                
                temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            	}
        	}
    	}
 	}
 	string getCard(int num){                     // ���������� ������� �����, ����� ��� ���������
 			string card;
        	ostringstream buffer;
    		buffer << hand[num][0];
    		buffer << hand[num][1];
    		card = buffer.str();                // ����������� 1 � ������� ������� ������ � ��������� ������
        	if(card==" V") card = "11";        //������� ��������� ���� ��� �������� ���������
        	if(card==" D") card = "12";
        	if(card==" K") card = "13";
        	if(card==" T") card = "14";
        	return card;
 	}
 	char getMast(int num){                       // ���������� ����� ����� � ���� ������
 		char mast = hand[num][2];
        	return mast; 
 	}
 	void countPoints(){                         // ������� �����
 			
 			points = 0;
 		for(int i=0;i<N;i++){
 			string card;
 			int point=0;
        	ostringstream buffer;
    		buffer << hand[i][0];
    		buffer << hand[i][1];
    		card = buffer.str();                // ����������� 1 � ������� ������� ������ � ��������� ������
        	if(card==" V") point = 11;        //������� ��������� ���� ��� �������� ���������
        	else if(card==" D") point = 12;
        	else if(card==" K") point = 13;
        	else if(card==" T") point = 14;
        	else point = atoi(card.c_str());
        	char mast = hand[i][2];
        	if(mast==tr) point = point + 9;
        	points = points + point;
 		}
 	}
 	int getPoints(){                    // ���������� �����
 		return points;
 	}
 	
};

int main(int argc, char** argv) {
	setlocale(0,"rus");
	int com = 0;   // commands
	int number=0;   // ����� �������
	static const int maxNumber = 6; // ������������ ����� �������
	Deck deck;  //�������������� ����� ������
	while(number< 1 || number > 6){
		cout<< "Specify the number of players(max 6) \n";
    	cin>> number;
    }
	deck.create(); // ������� ������
	cout<<"-----------------------------------------"<<endl;
	deck.mix();   //  ��������������
	while(com < 1 || com > 5){
		cout<< "Choose a card from 1 to 5 to choose a trump \n"; // ���� ������� ������
    	cin>> com;
	} 
    deck.setTrump(deck.trump(com));   //������������� �������� �����
    char trump = deck.getTrump();     // ������
    switch(trump){
    	case 'k': cout<<"Trump is krest!";
    			break;
    	case 'b': cout<<"Trump is bubna!";
    			break;
    	case 'c': cout<<"Trump is chirva!";
    			break;
    	case 'p': cout<<"Trump is pika!";
    			break;
    }
    Player players[number]; // �������������� ������ �������
    
    for(int i=0;i<number;i++){
		string* d;
		string* hand = new string[6];
		int from =i*6;
		d= deck.getDeck();           // ����� ��� ������
		for(int j=0;j<6;j++){
			hand[j] = d[i*6+j];      // �� 6 ���� ������� �������
		}
    	players[i].addCards(hand);  // ��������� ����� � ���� ������� ������
    	delete[] hand;
    }
    cout<<endl;
    for(int i=0;i<number;i++){
    	players[i].setTrump(trump);  //������� ������� ������ ������
    	players[i].sortHand();       // ��������� ����� ������� ������, ������ ���� ������, ����� ��������� �����, ��� � ������� ��������
    	players[i].viewHand();      //�������  ����� ������� ������
    }
    //���������� ������ � ���� ������������� �����
    Player player;
    for(int i=0;i<number-1;i++){
    	for(int j=0;j<number-1-i;j++){
    		string card = players[j].getCard(0);
    		char mast = players[j].getMast(0);
    		string nextCard = players[j+1].getCard(0);
    		char nextMast = players[j+1].getMast(0);
    		if ((mast!=trump && nextMast==trump) || ((mast==trump && nextMast==trump)&&(card<nextCard)) || ((mast!=trump && nextMast!=trump)&&(card<nextCard))) {
                player = players[j];
                players[j] = players[j + 1];
                players[j + 1] = player;
            	}
    	}
	}
	//
	
	
	cout<<"-----------------------------------------"<<endl;
    cout<<"Top card is here:"<<endl;
    players[0].viewHand();      // �� ������ ����� ���� � ����� ������� ������.
    for(int i=0;i<number;i++){
    	players[i].countPoints(); //������� �����
    }
    cout<<"-----------------------------------------"<<endl;
    
    for(int i=0;i<number-1;i++){
    	for(int j=0;j<number-1-i;j++){
    		int points = players[j].getPoints();
    		int pointsNext = players[j+1].getPoints();
    		if (points<pointsNext) {
                player = players[j];
                players[j] = players[j + 1];
                players[j + 1] = player;
            	}
    	}
	}
	for(int i=0;i<number;i++){
		
    	players[i].viewHand();      //��������� ����� ������� ������
    	cout<<players[i].getPoints()<< " points"<<endl;
    	cout<<"----"<<endl;
    }
	cout<<"Top hand is here:"<<endl;
	players[0].viewHand();      // �� ������ ����� ���������� c ����� ������� ������.
    
	system("pause"); // ������� �������� ������
	return 0;
}
