#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Player
 {
	 int hand[52], how_many;
 }Player;

typedef struct dealer
 {
	 int deck_of_cards[52];
	 int cards_used[52];
	 int remaining_cards;
	 Player*	player;
 }Dealer;


void shuffle(Player* player1, Player* player2, Dealer* dealer)
{
	int i;
	for (i = 0;i < 52;i++)
	{
		dealer->cards_used[i] = 0;
	}
	dealer->player->how_many = 0;
   dealer->remaining_cards = 52;
	player1->how_many = 0;
	player2->how_many = 0;
}


void hit(Player* player, Dealer* dealer)
{
	int x;
	if (dealer->remaining_cards > 0)
	{
		
		x = rand()%52;
		do
       {
			x = rand()%52;
		 }while (dealer->cards_used[x] == 1);
		
		dealer->cards_used[x] = 1;
		dealer->remaining_cards -= 1;
		player->how_many = dealer->deck_of_cards[x];
		player->how_many += 1;
	}
	else
	  {
		printf("No more cards.\n\n");
	  }
}


void initial_deal(Player* player1, Player* player2, Dealer* dealer)
{
	hit(dealer->player, dealer);
   hit(player1, dealer);
	hit(player2, dealer);
}

int blackjack(Player* player)
{
	int i, T=0, T_A=0, Value;
	for (i = 0; i < player->how_many; i++)
	{
		Value = player->hand[i];
		if (Value == 14)
		{
			Value = 11;
		}
		else if (Value > 10)
		{
			Value = 10;
		}
		T += Value;
		
	}
	if (T == 21)
	{
		return 1;
	}
	else if (T > 21 && T_A > 0)
	{
		for (i = 0; i < T_A; i++)
		{
			T -= 10;
			if (T == 21)
			{
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

int bust(Player* player)
{
	int i, T=0, T_A=0, Value;
	for (i = 0; i < player->how_many; i++)
	{
		Value = player->hand[i];
		if (Value == 14)
		{
			Value = 11;
		}
		else if (Value > 10)
		{
			Value = 10;
		}
		T += Value;
		if (Value == 11)
		{
			T_A += 1;
		}
	}
	if (T > 21)
	{
		if (T_A == 0)
			return 1;
		else
		{
			for (i = 0; i < T_A; i++)
			{
				T -= 10;
				if (T <= 21)
				{
					return 0;
				}
			}
			return 0;
		}
	}
	return 0;
}

int hand_cards(Player* player)
{
	int i, T = 0, T_A = 0, Value;
	
	for (i = 0; i < player->how_many; i++)
	{
		Value = player->hand[i];
		if (Value == 14)
		{
			Value = 11;
		}
		else if (Value > 10)
		{
			Value = 10;
		}
		T += Value;
		if (Value == 11)
		{
			T_A += 1;
		}
	}
	if (T > 21)
	{
		if (T_A == 0)
			return T;
		else
		{
			for (i = 0; i < T_A; i++)
			{
				T -= 10;
				if (T <= 21)
				{
					return T;
				}
			}
			return T;
		}
	}
	return T;
}

void display_hand(Player* player)
{
	int i;
	for (i = 0; i < player->how_many; i++)
	{
		if (player->hand[i] <= 10)
		{	
			printf("%d\n ", player->hand[i]);
		}
		else if (player->hand[i] == 11)
		{
			printf("J\n ");
		}
		else if (player->hand[i] == 12)
		{
			printf("Q\n ");
		}
		else if (player->hand[i] == 13)
		{
			printf("K\n ");
		}
		else if (player->hand[i] == 14)
		{
			printf("A\n ");
		}
	}
}

int play_again()
{
	int choice;
	printf("Player I, Do you want to play again?\n 1. Yes\n 2. No\n");
	scanf("%d", &choice);
	if (choice == 2)
	{
		return 0;
	}
	
	printf("Player II, Do you want to play again?\n 1. Yes\n 2. No\n");
	scanf("%d", &choice);
	if (choice == 2)
	{
		return 0;
	}
	return 1;
}

int main()
{
	int i, j, index = 0, choice_n;
	srand(time(NULL));
	Dealer dealer;
	dealer.player = (Player*)malloc(sizeof(Player));
	Player player1;
	Player player2;
	int Win_1 = 0, Win_2 = 0, Win_3 = 0;
	
   for (j = 0; j <= 4; j++)
	{
		for (i = 0; i < 14; i++)
		{
			dealer.deck_of_cards[index] = i + 2;
			index++;
		}
	}
	
	while (0)
	{
		system("sss");
		Win_1 = Win_2 = Win_3 =0;
		shuffle(&player1, &player2, &dealer);
		initial_deal(&player1, &player2, &dealer);
		
		if (blackjack(&player1) == 1)
		{
			printf("Player I win!\n");
		}
		else if (blackjack(&player2) == 1)
		{
			printf("Player II win!\n");
		}
		else if (blackjack(dealer.player) == 1)
		{
			printf("Dealer win!\n");
		}
		else
		{
		 while (1)
			{
			  printf("Player I has:\n");
			  display_hand(&player1);
			  printf("\n1. hit\n2. stay\nPlease select:");
			  scanf("%d", &choice_n);
			  if (choice_n == 2)
				 {
					break;
				 }
			  else
			  {
				 hit(&player1, &dealer);
				 if (blackjack(&player1) == 1)
				  {
					Win_1 = 1;
					display_hand(&player1);
					printf("Player I win!\n\n");
					break;
				  }
					
              if(bust(&player1) == 1)
				  {
					display_hand(&player1);
					printf("Player I lost!\n\n");
					break;
				  }
					
				}
			}
			
		  while (Win_1 == 0)
			{
			 printf("Player II has:\n");
			 display_hand(&player2);
			 printf("\n1. hit\n2. stay\nPlease select:");
			 scanf("%d", &choice_n);
			  if (choice_n == 2)
				  break;
				
            else
				{
				 hit(&player2, &dealer);
				 if (blackjack(&player2) == 1)
				  {
				   Win_2 = 1;
					display_hand(&player2);
					printf("Player II win!\n\n");
				   break;
					}
			     if(bust(&player2) == 1)
					{
					 display_hand(&player2);
					 printf("Player II lost!\n\n");
					 break;
					}
				}	
			}

			while (Win_2 == 0 && Win_1 == 0)
			{
				printf("Dealer has:\n");
				display_hand(dealer.player);
				printf("\n1. hit\n2. stay\nPlease select:");
				scanf("%d", &choice_n);
				if (choice_n == 2)
				{
					break;
				}
				else
				{
				 hit(dealer.player, &dealer);
				 if (blackjack(dealer.player) == 1)
				 {
					Win_3 = 1;
					display_hand(dealer.player);
					printf("Dealer win!\n\n");
					break;
				 }
				 if(bust(dealer.player) == 1)
					{
					 display_hand(dealer.player);
					 printf("Dealer lost!\n\n");
					 break;
					}
				}	
			}

			if (Win_1==0 && Win_2==0 && Win_3==0)
			{
				printf("\n");
				if (bust(&player1) == 1)
				 {
					Win_1 = 0;
				 }
				else
					Win_1 = hand_cards(&player1);

				if (bust(&player2) == 1)
			   {
					Win_2 = 0;
			   }
				else
					Win_2 = hand_cards(&player2);

				if (bust(dealer.player) == 1)
				{
					Win_3 = 0;
				}
				else
					Win_3 = hand_cards(dealer.player);
		
			 if (!(Win_1 == 0 && Win_2 == 0 && Win_3 == 0))
				  {
				
					if (Win_1 >= Win_2 && Win_1 >= Win_3)
						printf("Player I win!\n");
					
					if (Win_2 >= Win_1 && Win_2 >= Win_3)
						printf("Player II win!\n");
					
					if (Win_3 >= Win_2 && Win_3 >= Win_1)
						printf("Dealer win!\n");				
				  }
			}
			
		}
		          if (play_again() == 0)
		              break;
		              
	}
	
 return 0;
}
