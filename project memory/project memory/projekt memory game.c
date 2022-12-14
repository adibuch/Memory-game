//adi buchris ID 206147647
//esty friedman ID 209531482
//malky rotshild ID 308464262

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define C 6
#define N 20
enum status { close, open };
struct Memory
{
	char* word;
	enum status s;
};
struct Memory** initGame(int *psize);
void printGame(struct Memory** mat, int row);
void chooseCard(struct Memory** arr, int size);
int winGame(struct Memory** mat, int row);


int main()
{
	int n, i, v;
	int try = 1;
	struct Memory** game;
	do
	{
		printf("Enter num of row\n");
		scanf_s("%d", &n);
		getchar();
	} while (n < 1);
	game = initGame(&n);
	v = winGame(game, n);
	for (i = 0; v == 0; ++i)
	{

		printGame(game, n);
		printf("Number experience is:%d\n", try);
		chooseCard(game, n);
		if (try > 3 * n)//נבדוק האם כל הקלפים גלויים רק אחרי מינימום (3*מס השורות) בחירותות
			v = winGame(game, n);
		++try;
	}
	//all the cards are open
	printf("Bravo!!!!!!!!!!!!!well done!");
	printf("The number of guesses is:%d", try);


}
struct Memory** initGame(int *psize)
{
	struct Memory** array;
	int i, j, x, y, z;
	char word[N];

	array = (struct Memory**)malloc(*psize * sizeof(struct Memory*));
	if (!array)
		return NULL;
	for (i = 0; i < *psize; ++i)
	{
		array[i] = (struct Memory*)malloc(C * sizeof(struct Memory));
		if (!array[i])
			return NULL;
	}
	for (i = 0; i < *psize; ++i)
	{
		for (j = 0; j < C; ++j)
		{
			array[i][j].word = NULL;
			array[i][j].s = close;
		}

	}
	for (i = 0; i < 3 * (*psize); ++i)
	{
		printf("Enter word for game:\n");
		gets_s(word, N);
		for (z = 0; z < *psize; ++z)
		{
			for (j = 0; j < C; ++j)
			{
				if (array[z][j].word != NULL)
				{
					if (strcmp(array[z][j].word, word) == 0)
					{
						printf("Error!!\n Enter again word for game:\n");
						gets_s(word, N);
						z = 0;
						j = 0;
					}
				}
			}
		}
		do
		{
			x = rand() % (*psize);
			y = rand() % (C);
		} while (array[x][y].word != NULL);
		array[x][y].word = (char*)malloc((strlen(word) + 1) * sizeof(char));
		if (!array[x][y].word)
		{
			return NULL;

		}
		strcpy(array[x][y].word, word);

		do
		{
			x = rand() % (*psize);
			y = rand() % (C);
		} while (array[x][y].word != NULL);
		array[x][y].word = (char*)malloc((strlen(word) + 1) * sizeof(char));
		if (!array[x][y].word)
		{
			return NULL;

		}
		strcpy(array[x][y].word, word);
	}
	return array;


}
void printGame(struct Memory** mat, int row)
{
	int i, j;

	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < C; ++j)
		{
			if (mat[i][j].s == open)
				printf("%9s\t", mat[i][j].word);
			else//the card is close
				printf("---------\t");
		}
		printf("\n");
	}
	printf("\n");
}
void chooseCard(struct Memory** arr, int size)
{
	int row1, col1, row2, col2;
	printf("Enter the row number and column number of the first card you are picking up\n");
	scanf_s("%d%d", &row1, &col1);
	getchar();
	while (row1 > size || row1<1 || col1>C || col1 < 1 || arr[row1 - 1][col1 - 1].s == open)
	{
		printf("Error!! try again\n");
		scanf_s("%d%d", &row1, &col1);
		getchar();
	}
	arr[row1 - 1][col1 - 1].s = open;
	//printf("\nUpdated game board after lifting the card\n");
	printGame(arr, size);
	printf("Enter the row numberand column number of the second card you are picking up\n");
	scanf_s("%d%d", &row2, &col2);
	getchar();
	while (row2 > size || row2<1 || col2>C || col2 < 1 || arr[row2 - 1][col2 - 1].s == open || (row1 == row2 && col1 == col2))
	{
		printf("Error!! try again\n");
		scanf_s("%d%d", &row2, &col2);
		getchar();
	}
	arr[row2 - 1][col2 - 1].s = open;
	//printf("\nUpdated game board after lifting the card\n");
	printGame(arr, size);
	if (strcmp(arr[row1 - 1][col1 - 1].word, arr[row2 - 1][col2 - 1].word) != 0)
	{
		arr[row1 - 1][col1 - 1].s = close;
		arr[row2 - 1][col2 - 1].s = close;
		printf("You didn't make it maybe next time.\n");
	}
	else
	{
		printf("Bravo!You made a set.\n");
	}

}

int winGame(struct Memory** mat, int row)
{

	int i, j;
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < C; ++j)
		{
			if (mat[i][j].s == close)
				return 0;
		}
	}
	return 1;
}