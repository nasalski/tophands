#include <iostream>
#include <string>
#include <cstdlib> // Для работы с функцией system()
#include <stdio.h>
#include<ctime>
#include <sstream>
using namespace std;

class Deck{       // наша колода карт с наминалом от 6 до 10
                  // и картами Валет(V), Дама(D), Король(K), Туз(T). Так же есть 4 масти: Крест(k), Пика(p), Бубна(b), Черва(c)
	public:
		static const int N = 36; //количество карт в колоде
 		string deck[N]; // колода карт 
 		char tr;
 		void create(){                      // создает колоду карт
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
 		
 		void view(){                    // показывает все карты, для отладки
 			for(int i=0;i<N;i++){
 				cout<< deck[i] <<" ";


 			}
 		}
 		
 		void mix(){                   // перемешивает колоду
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
 		
 		char trump(int t){        // возвращает масть выбранной карты, нужна для выбора козыря
 			char *to = (char *) deck[t].c_str();
 			return to[2];
 		}
 		
 	     void setTrump(char t){ // вводит козырь
 	     	tr = t;
 	     }
 	     
 	     char getTrump(){      // возвращает козырь
 	     	return tr;
 	     }
 	     
 	     string* getDeck(){    // возвращает колоду
 	     	
 	     	return deck;
 	     }
	
};
class Player{                // класс игрока
	static const int N = 6; //количество карт в руке
	string hand[N];
	char tr;
	int points;
public:
    void addCards(string *cards){           // добавляет карты в руку
		for(int i=0;i<N;i++){
 				hand[i] = cards[i];
 			}
	}
	void viewHand(){                         // показывает карты на руке
		for(int i=0;i<N;i++){
 				cout<< hand[i] <<" ";
 		}
 		cout<<endl;
 	}
 	void setTrump(char t){                     // сообщает игроку козырь
 		tr = t;
 	}
 	void sortHand(){                           // сортировка карт на руке с учетом козырей
 		string temp;
 		for (int i = 0; i < N - 1; i++) {
        	for (int j = 0; j < N - i - 1; j++) {
        		
        		string card;
        		ostringstream buffer;
    			buffer << hand[j][0];
    			buffer << hand[j][1];
    			card = buffer.str();                // объединение 1 и второго символа строки в отдельную строку
        		if(card==" V") card = "11";        //продлим нумерацию карт для удобства сравнения
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
 	string getCard(int num){                     // возвращает номинал карты, нужно для сравнения
 			string card;
        	ostringstream buffer;
    		buffer << hand[num][0];
    		buffer << hand[num][1];
    		card = buffer.str();                // объединение 1 и второго символа строки в отдельную строку
        	if(card==" V") card = "11";        //продлим нумерацию карт для удобства сравнения
        	if(card==" D") card = "12";
        	if(card==" K") card = "13";
        	if(card==" T") card = "14";
        	return card;
 	}
 	char getMast(int num){                       // возвращает масть карты с руки игрока
 		char mast = hand[num][2];
        	return mast; 
 	}
 	void countPoints(){                         // считает баллы
 			
 			points = 0;
 		for(int i=0;i<N;i++){
 			string card;
 			int point=0;
        	ostringstream buffer;
    		buffer << hand[i][0];
    		buffer << hand[i][1];
    		card = buffer.str();                // объединение 1 и второго символа строки в отдельную строку
        	if(card==" V") point = 11;        //продлим нумерацию карт для удобства сравнения
        	else if(card==" D") point = 12;
        	else if(card==" K") point = 13;
        	else if(card==" T") point = 14;
        	else point = atoi(card.c_str());
        	char mast = hand[i][2];
        	if(mast==tr) point = point + 9;
        	points = points + point;
 		}
 	}
 	int getPoints(){                    // возвращает баллы
 		return points;
 	}
 	
};

int main(int argc, char** argv) {
	setlocale(0,"rus");
	int com = 0;   // commands
	int number=0;   // число игроков
	static const int maxNumber = 6; // максимальное число игроков
	Deck deck;  //инициализируем класс колоды
	while(number< 1 || number > 6){
		cout<< "Specify the number of players(max 6) \n";
    	cin>> number;
    }
	deck.create(); // создаем колоду
	cout<<"-----------------------------------------"<<endl;
	deck.mix();   //  перетасовываем
	while(com < 1 || com > 5){
		cout<< "Choose a card from 1 to 5 to choose a trump \n"; // даем выбрать козырь
    	cin>> com;
	} 
    deck.setTrump(deck.trump(com));   //устанавливаем козырную карту
    char trump = deck.getTrump();     // козырь
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
    Player players[number]; // инициализируем массив игроков
    
    for(int i=0;i<number;i++){
		string* d;
		string* hand = new string[6];
		int from =i*6;
		d= deck.getDeck();           // берем всю колоду
		for(int j=0;j<6;j++){
			hand[j] = d[i*6+j];      // по 6 карт раздаем игрокам
		}
    	players[i].addCards(hand);  // добавляем карты в руку каждому игроку
    	delete[] hand;
    }
    cout<<endl;
    for(int i=0;i<number;i++){
    	players[i].setTrump(trump);  //сообщим каждому игроку козырь
    	players[i].sortHand();       // сортируем карты каждого игрока, сперва идут козыря, потом остальные карты, все в порядке убывания
    	players[i].viewHand();      //покажем  карты каждого игрока
    }
    //сравниваем колоды у кого найсильнейшая карта
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
    players[0].viewHand();      // на первом месте рука с самой сильной картой.
    for(int i=0;i<number;i++){
    	players[i].countPoints(); //считаем баллы
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
		
    	players[i].viewHand();      //проверяем карты каждого игрока
    	cout<<players[i].getPoints()<< " points"<<endl;
    	cout<<"----"<<endl;
    }
	cout<<"Top hand is here:"<<endl;
	players[0].viewHand();      // на первом месте победитель c самой сильной картой.
    
	system("pause"); // Команда задержки экрана
	return 0;
}
