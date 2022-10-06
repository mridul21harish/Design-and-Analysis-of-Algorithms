#include<stdio.h>
#include<stdlib.h>					//header file for exit function
#include<string.h>
#include<time.h>                   //header file for using random function
#include<ctype.h>					
struct ques{
	char que[100];	
	char opta[50];
	char optb[50];
	char optc[50];
	char optd[50];
	int prize;
} q[13];                           //declaration of an array to store question and its options (12 questions + 1 extra)
int flag1=1,flag2=1;               //counter variables for keeping track of lifelines
char fiftyfifty(int,char);         //function to execute the fifty-fifty lifeline
void flip(int);					   //function to execute the flip the question lifeline
void prize(int);				   //function to calculate prize money if incorrect answer is chosen.
int main()
{
	int n,i;
	char ans[10], start, choice;
	char key[]={'B','B','D','C','A','D','D','D','D','A','D','C'};   // answer key for the questions
	q[0].prize=5000;               
    q[1].prize=10000;
    q[2].prize=20000;
    q[3].prize=40000;
    q[4].prize=80000;
    q[5].prize=160000;  				//// prize money for each questions
    q[6].prize=320000;
    q[7].prize=640000;
    q[8].prize=1250000;
    q[9].prize=2500000;
    q[10].prize=5000000;
    q[11].prize=10000000;
	printf("Welcome to the game KBC !\nRules: \n1) You have to answer 12 questions.\n2) There are two life lines available: 50:50 and Flip the question.\n");
	printf("3) In the lifeline 50:50, two incorrect options are deleted.\n4) In the lifeline Flip the question, You will get a new question on screen.\n");
	printf("5) You can use each lifeline only once.\n6)  -For using lifeline 50-50, press L\n    -For using lifeline flip the question, press F \n For quitting the game, press Q\n");
	printf("\n7) The prize money for each question upon answering correctly is given below:\n\n");
	printf("Q1- Rs.5,000\nQ2- Rs.10,000\nQ3- Rs.20,000\nQ4- Rs.40,000\nQ5- Rs.80,000\nQ6- Rs.1,60,000\nQ7- Rs. 3,20,000 \nQ8- Rs.6,40,000\nQ9- Rs.12,50,000\n");
	printf("Q10- Rs. 25,00,000\nQ11- Rs. 50,00,000\nQ12- Rs. 1 crore\n\n");
	printf("Do you want to begin the game ? Press any key to start\n");
	getchar();			
		FILE * fPtr;
		fPtr=fopen("ques.txt","r");                    //open the file containing questions
		for(i=0;i<13;i++) 
		{
				fgets(q[i].que,sizeof(q[i].que),fPtr);			
				fgets(q[i].opta,sizeof(q[i].opta),fPtr);			
				fgets(q[i].optb,sizeof(q[i].optb),fPtr);				// read questions from file
				fgets(q[i].optc,sizeof(q[i].optc),fPtr);
				fgets(q[i].optd,sizeof(q[i].optd),fPtr);	  
		}
    	fclose(fPtr);    	                    // close the file
    	for(i=0;i<12;i++)									//loop to display questions and options on screen
    	{
			printf("---------------------------------------------------------- Question--------------------------------------------------\n\n");
			puts(q[i].que);	
    		puts(q[i].opta);
    		puts(q[i].optb);
    		puts(q[i].optc);
    		puts(q[i].optd);    		   		
			printf("\nEnter your answer\n");								// taking inout from user
    		scanf(" %c", &choice);
    		choice=toupper(choice);					// to make input case insensitive
    		label:
			if(key[i]==choice)
    		{
    			printf("=================================== Correct Answer ===============================\nYou have won %d Rs\n", q[i].prize);  
			}
			else if(choice=='L')
			{
				if(flag1==1)
				{
					choice=fiftyfifty(i,key[i]);						// function  call for 50-50 lifeline
					if(key[i]==choice)
    				{
    					printf("=================================== Correct Answer ===============================\n");
    					printf("You have won Rs. %d\n",q[i].prize);
    					--flag1;                    // lifeline can be used only once.
					}
					else if(choice=='Q')								// option for the user to quit the game
					{
						printf("You are quitting the game now.\n");
						printf("%d", q[i-1].prize);
						exit(0);
					}
					else if(choice=='F')
					{
						if(flag2==1)
						{
							flip(i);
							flag2--;		
						}							// function call to use flip the question lifeline												}
						else
						{
							printf("You have already used this lifeline\n");
							printf("%s\n",q[12].optc); 	
							printf("%s\n",q[12].optd);	   		
							printf("\nEnter your answer\n");
    						scanf(" %c", &choice);	
    						if(choice=='D')
    						{
								printf("=================================== Correct Answer ===============================\n");
    							printf("You have won Rs. %d\n",q[i].prize);
							}
							else
							{
								printf("Wrong answer. Your game will exit now\n");
								exit(0);
							}
						}
					}
					else
					{
						printf("================================== Wrong answer ============================= \nYou will exit the game now.\n");
						prize(i);					//function call to display prize money if incorrect answer is selected
						exit(0);
					}
				}
				else
				{
					printf("You have already used this lifeline\n");
					puts(q[i].que);	
    				puts(q[i].opta);
    				puts(q[i].optb);
    				puts(q[i].optc);
    				puts(q[i].optd);    		   		
					printf("\nEnter your answer\n");
    				scanf(" %c", &choice);
    				goto label;				// to evaluate the question again if lifeline is already used
				}
			}
			else if(choice=='F')
			{
				if(flag2==1)
				{
					flip(i);									// function call to use flip the question lifeline
					flag2--;									//   lifeline can be used only once   
				}
				else
				{
					printf("You have already used this lifeline\n");
					puts(q[i].que);	
    				puts(q[i].opta);
    				puts(q[i].optb);
    				puts(q[i].optc);
    				puts(q[i].optd);    		   		
					printf("\nEnter your answer\n");
    				scanf(" %c", &choice);
					goto label;				// to display question again if user has already used lifeline.	
				}
			}
			else if(choice=='Q')						// if user wants to quit the game
			{
				printf("You are quitting the game now.\n");
				printf("You have won Rs. %d\n", q[i-1].prize);
				exit(0);
			}
			else
			{
				printf("================================== Wrong answer =============================\nYou will exit the game now.\n");
				prize(i);					//function call to display prize money if incorrect answer is selected
				--flag2;
				exit(0);
			}
		}
	return 0;
}
char fiftyfifty(int num,char choice)
{
	char *o[4];             // stores the options A,B,C and D
	char *p[3];										//        stores all options except the correct one so that it can eliminate any two out of the three
	char option[1][50];
	int k;
	int ctr=0;
 	int j=(rand() % (2 - 0 + 1)) + 0;				// random function to eliminate any two incorrect options 
	o[0]=q[num].opta;
	o[1]=q[num].optb;
	o[2]=q[num].optc;
	o[3]=q[num].optd;
	flag1--;
	for(k=0;k<4;k++)
	{
		if(o[k][0]==choice)
		{
			printf("%s\n",o[k]);
		}
		else
		{
			while(ctr<3)
			{
				p[ctr]=o[k];
				ctr++;
				break;
			}
		}
	}
	printf("%s\n",p[j]);	
	printf("Enter answer\n");
	char ans;
	scanf(" %c",&ans);
	ans=toupper(ans);
	return ans;													//statement to return the answer entered by user so that it can be evaluated
}
void flip(int num)
{
	printf("%d) ",num+1);
	puts(q[12].que);	       // printing the extra question for flip the question lifeline
    puts(q[12].opta);
    puts(q[12].optb);
    puts(q[12].optc);
    puts(q[12].optd); 
    flag2--;
	char choice;   	
	int i=12;	   		
	printf("\nEnter your answer\n");
    scanf(" %c", &choice);
    choice=toupper(choice);
    label:
	if(choice=='D')
    {
    	printf("=================================== Correct Answer =============================== \nYou have won Rs. %d \n", q[num].prize);
	}
	else if(choice=='L') 						//option to use 50-50 lifeline after using flip the question
	{
		if(flag1==1)
		{
			choice=fiftyfifty(12,'D');
			if(choice=='D')
    		{
    			printf("=================================== Correct Answer =============================== \nYou have won %d Rs \n", q[num].prize);
			}
			else
			{	
				printf(" ==========================  Wrong answer  ===================================\n");
				prize(num);
				exit(0);
			}
		}
		else
		{
			printf(" You have already used this lifeline\n");
			printf("%d) ",num+1);
			puts(q[12].que);	
    		puts(q[12].opta);
    		puts(q[12].optb);
    		puts(q[12].optc);
    		puts(q[12].optd);    		   		
			printf("\nEnter your answer\n");
    		scanf(" %c", &choice);
    		goto label;
		}
	}
	else if(choice=='F')
	{
		printf("You have already used this lifeline\n");
		printf("%d) ",num+1);
		puts(q[i].que);	
    	puts(q[i].opta);
    	puts(q[i].optb);
    	puts(q[i].optc);
    	puts(q[i].optd);    		   		
		printf("\nEnter your answer\n");
    	scanf(" %c", &choice);
		goto label;					
	}
	else if(choice=='Q')								// option for the user to quit the game
	{
		printf("You are quitting the game now.\n");
		printf("You have won Rs. %d", q[num-1].prize);
		exit(0);
	}
	else
	{
		printf(" ==========================  Wrong answer  ===================================\n ");
		prize(num);
		exit(0);
	}
}
void prize(int num)                // function to calculate prize money according to intermediate levels
{
	if(num<3)
	printf("You have won zero Rs.\n");
	else if(num>=3 && num<=7)
	printf("You have won %d Rs.\n",q[1].prize);
	else
	printf("You have won %d Rs.\n",q[6].prize);
}

