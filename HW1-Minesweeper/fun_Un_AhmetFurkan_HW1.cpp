//Ahmet Furkan Un - 28315

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "randgen.h"
using namespace std;

void Print(const vector<vector<char>> & mat);

int neighbour_bombs_calculator(const vector<vector<char>> & mat, int row, int column);

bool is_coordinate_valid(const vector<vector<char>> & mat, int row, int column);

bool is_game_won(const vector<vector<char>> & player, const vector<vector<char>> & hidden);



int main()
{
	int rows, columns;
	cout << "Give the dimensions of the matrix: ";
	cin >> rows >> columns;

	vector<vector<char>> hidden_matrix(rows,vector<char>(columns, 'X')); /*the matrix that will be shown at the end of the game*/
	vector<vector<char>> player_matrix(rows,vector<char>(columns, 'X')); /*the matrix that the player always see*/

	int number_of_cells = (rows*columns);
	int number_of_bombs = number_of_cells + 1;
	bool is_number_of_bombs_valid = false;
	cout << "How many bombs: ";
	cin >> number_of_bombs;
	
	/*until the given number of bombs is between 0 and number of cells, this loop asks to enter a valid number*/
	while (!is_number_of_bombs_valid) 
	{
		if (number_of_bombs < 1)
		{
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> number_of_bombs;
		}

		else if (number_of_bombs > number_of_cells -1)
		{
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> number_of_bombs;
		}

		else
		{
			is_number_of_bombs_valid = true;
		}
	}

	RandGen rnd;
	/*plant bombs in random locations*/
	for (int i = 0; i < number_of_bombs; i++)
	{
		bool is_bomb_planted = false; /*this variable makes sure that every cell has at most 1 bomb*/
		while (!is_bomb_planted)
		{
			int random_row = rnd.RandInt(0, rows-1);
			int random_column = rnd.RandInt(0, columns-1);
			if (hidden_matrix[random_row][random_column] != 'B') /*if this random coordinate do not have a bomb, plant it*/
			{
				hidden_matrix[random_row][random_column] = 'B';
				is_bomb_planted = true;
			}
		}
	}
	/*for every coordinate other than bombs, calculate the neighbour bombs and update the hidden matrix*/
	for (int i=0; i < hidden_matrix.size(); i++)
    {   
		for (int j=0; j < hidden_matrix[0].size(); j++)
        {   
			if (hidden_matrix[i][j] != 'B')
			{
				int neighbour_bombs = neighbour_bombs_calculator(hidden_matrix, i, j);
				hidden_matrix[i][j] = neighbour_bombs+48; /* +48 is to convert char to int*/
			}
        }
    }
	cout << endl;
	Print (player_matrix);
	
	/*cout << endl;
	Print (hidden_matrix);*/

	bool is_game_finished = false; /*this variable tells if the game is finished*/

	/*while game is not finished, repeatedly show the menu and do to corresponding action*/
	while (!is_game_finished)
	{
		string choice;
		cout << "Press: "<<endl;
		cout << "1. If you want to find out the surrounding of a cell" <<endl;
        cout << "2. If you want to open the cell" <<endl;
		cout << "3. If you want to exit."<<endl;
		cin >> choice;

		/*repeatedly ask for the input until it is valid*/
		while (choice != "1" && choice != "2" && choice != "3")  /*make sure the input is valid*/
		{
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3."<<endl;
			cin >> choice;
		}

		if (choice == "3")
		{
			cout << "Program exiting ..."<<endl;
			is_game_finished = true; /*game finished, so it won't enter the while loop again*/
		}

		else if (choice == "1")
		{
			int row_for_choice_1, column_for_choice_1;
			cout << "Give the coordinates: ";
			cin >> row_for_choice_1 >> column_for_choice_1;

			/*check whether the given coordinate valid or not*/
			/*repeatedly ask for the coordinates until it is valid*/
			while (!is_coordinate_valid(hidden_matrix, row_for_choice_1, column_for_choice_1))
			{
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> row_for_choice_1 >> column_for_choice_1;
			}
			cout << endl;
			cout << "Displaying the surrounding of ("<< row_for_choice_1 <<","<< column_for_choice_1 <<"): "<<endl;

			/*check whether it is opened already or not*/
			/*if not opened, show it and close it*/
			if (player_matrix[row_for_choice_1][column_for_choice_1] == 'X')
			{
				/*calculate the neighbour bombs and update the player matrix to show it*/
				char bomb_number = (char)neighbour_bombs_calculator(hidden_matrix, row_for_choice_1, column_for_choice_1) +48;
				player_matrix[row_for_choice_1][column_for_choice_1] = bomb_number;

				/*show the updated version*/
				Print(player_matrix);
				cout << "Around ("<<row_for_choice_1<<","<<column_for_choice_1<<") you have "<<player_matrix[row_for_choice_1][column_for_choice_1]<<" bomb(s)"<<endl;
				cout << endl;

				/*return to the old version because it is not opened completely yet*/
				player_matrix[row_for_choice_1][column_for_choice_1] = 'X';
			}
			else
			{
				/*show the existing version*/
				Print(player_matrix);
				cout << "Around ("<<row_for_choice_1<<","<<column_for_choice_1<<") you have "<<player_matrix[row_for_choice_1][column_for_choice_1]<<" bomb(s)"<<endl;
				cout << endl;
			}
		}

		else if (choice == "2")
		{
			int row_for_choice_2, column_for_choice_2;
			cout << "Give the coordinates: ";
			cin >> row_for_choice_2 >> column_for_choice_2;

			/*check whether the given coordinate valid or not*/
			/*repeatedly ask for the coordinates until it is valid*/
			while (!is_coordinate_valid(hidden_matrix, row_for_choice_2, column_for_choice_2))
			{
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> row_for_choice_2 >> column_for_choice_2;
			}
			cout << endl;
			cout << "Opening cell ("<< row_for_choice_2 <<","<< column_for_choice_2 <<"): "<<endl;

			/*update the player matrix to show what is in that coordinate*/
			player_matrix[row_for_choice_2][column_for_choice_2] = hidden_matrix[row_for_choice_2][column_for_choice_2];

			/*show the updated version of player matrix*/
			Print(player_matrix);
			cout << endl;

			/*if the player chooses a bomb, the game is over*/
			if (hidden_matrix[row_for_choice_2][column_for_choice_2] == 'B')
			{
				cout << "Unfortunately, you stepped on a mine"<< endl;
				cout << "Arrangement of mines: "<< endl;
				/*show the hidden matrix*/
				Print(hidden_matrix);
				cout << endl;
				cout << ">>>>> Game Over! <<<<<" << endl;
				is_game_finished = true; /*game finished, so it won't enter the while loop again*/
			}
		

			/*if the player won the game, print this information*/
			if (is_game_won(player_matrix, hidden_matrix))
			{
				cout << "Congratulations! All the non-mined cells opened successfully"<<endl;
				cout << "You won!"<<endl;
				cout << endl;
				cout << ">>>>> Game Over! <<<<<" << endl;
				is_game_finished = true; /*game finished, so it won't enter the while loop again*/
			}
		}
	}
	return 0;
}

void Print(const vector<vector<char>> & mat)
{
	/*From matdemo.cpp
	This function prints the matrix called mat*/
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
        {   
			cout << setw(4) << mat[j][k]; 
        }
        cout << endl;
    }
}

int neighbour_bombs_calculator(const vector<vector<char>> & mat, int row, int column)
{
	/*This function returns the number of bombs of a coordinate (row, column) in a given vector
	namely mat*/
	int neighbour_bomb_counter = 0; /*to store the number of bombs*/
	for (int i=-1; i < 2; i++) /*This nested for loops only examine a submatrix of 3x3 around the coordinate*/
    {   
		for (int j=-1; j < 2; j++)
        {
			if ((row + i >= 0 && (row + i) < mat.size()) && 
				(column + j >= 0 && (column + j) < mat[0].size())) /*to eliminate coordinates outside the matrix. For example, for a corner, the submatrix will be 2x2*/
			{
				if (mat[row + i][column + j] == 'B')
				{
					neighbour_bomb_counter++;
				}
			}
		}
	}

	if (mat[row][column] == 'B') /*if there is a bomb in the given coordinate, neighbour bombs should be decremented by 1*/
	{
		return neighbour_bomb_counter-1;
	}
	else
	{
		return neighbour_bomb_counter;
	}
}

bool is_coordinate_valid(const vector<vector<char>> & mat, int row, int column)
{
	/*This funciton returns true if the given coordinate (row, column) is inside the matrix mat
	and returns false if the coordinate is outside the matrix*/
	if ((row >= 0 && row < mat.size()) && (column >= 0 && column < mat[0].size()))
	{
		return true;
	}
	return false;
}

bool is_game_won(const vector<vector<char>> & player, const vector<vector<char>> & hidden)
{
	/*This function returns true if the player won the game*/
	for (int i=0; i < player.size(); i++)
    {   
		for (int j=0; j < player[0].size(); j++)
        {   
			if (player[i][j] == 'X' && hidden[i][j] != 'B') /*if at least one of the unopened coordinates is not a bomb, then the game is not finished yet*/
			{
				return false;
			}
		}
	}
	return true; /*if there is no cell that is not a bomb, the player won the game*/
}