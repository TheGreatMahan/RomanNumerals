/*
File Name: Roman_MahanMehdipour
Author: Mahan Mehdipour
Date: January 29,2020
Purpose: Converts arabic to roman and roman To arabic

*/


// importing the c libraries needed
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

// declaring macro constant
#define CAPACITY 40
//calling the methods in order to be able to use method at the top
float romanToArabic(char roman[], size_t size);
void arabicToRoman(float arabic, char arr[]);


int main()
{
	
	//A while loop that will run as long as we are not getting quit as input

	while (1)
	{

		//two char arrays for geting the input and output with size of the constant
		char input[CAPACITY] = { '\0' };
		char output[CAPACITY] = { '\0' };

		//asking for user input and storing it as a string(char array)
		printf("Enter a Roman or Arabic Number: ");
		scanf_s("%s", input, CAPACITY);

		
		//changing the input to uppercase if letter
		//if it's a number it wouldn't affect it 
		for (size_t i = 0; i < CAPACITY; i++)
		{
			input[i] = toupper(input[i]);
			
		}
	
		//This if statement will detect wether if it's number or not
		if (isdigit(input[0]))
		{
			//printf("it's a digit\n");

			//changing the string to float by atof function
			float finalNumber = atof(input);

			//This will pass the number to the function and will populate the array
			arabicToRoman(finalNumber, output);

			//prints the result based on user input
			printf("\n>>> %s is %s\n", input, output);
			printf("\n\n");
		}

		//Detects if the first letter of input is roman and if it is, it will think that it is a Roman
		else if (input[0] == 'X' || input[0] == 'I' ||
			input[0] == 'C' || input[0] == 'M' ||
			input[0] == 'V' || input[0] == 'L' ||
			input[0] == 'D' || input[0] == 'S' || input[0] == '.')
		{
			//printf("it's a roman\n");

			//This will give use input and size of the input parameters to return float as a result
			float outputFloat = romanToArabic(input, strlen(input));
			//use this boolean to get rid of the trailing zeros
			bool hasOneDec = false;
			bool hasTwoDec = false;
			//goes throught the whole array
			for (size_t i = 0; i < strlen(input); i++)
			{
				//if there is a s or . in the input, the result would likley have decimal places
				if (input[i] == '.' )
					hasTwoDec = true;
				if (input[i] == 'S')
					hasOneDec = true;
			}
			//if else statement to format the output based on decimal number
			if (hasOneDec == false && hasTwoDec == false)
				printf("\n>>> %s is %.0f\n\n\n", input, outputFloat);
			else if (hasOneDec == true && hasTwoDec == false)
				printf("\n>>> %s is %.1f\n\n\n", input, outputFloat);
			else
				printf("\n>>> %s is %.2f\n\n\n", input, outputFloat);

		}
		//it will get out of loop if user enters quit
		else if (input[0] == 'Q' && input[1] == 'U' &&
			input[2] == 'I' && input[3] == 'T')
		{
			break;
			
		
		}
		//in case the first letter is not roman or the whole word is 
		//not quit or it's not a numnber it will print invalid input 
		else 
		{
			printf("This is an invalid input. please try again.\n");
		}
	}
	
}	
	//function that will get a float as a result as an arabic number
float romanToArabic(char roman[], size_t size)
{
	//declaring needed variables that are mostly unsigned int in order to countwhat is going on
	size_t cNumber=0;
	size_t backCNumber = 0;
	size_t location = 0;
	bool isAp=false;
	size_t counter=0;
	float number=0;

		//a do while loop that goes through the array and calculates the appostrophus
		do 
		{
			//detect wether it's an appostrophus or not
			if (roman[counter] == ')') 
			{
				isAp = true;
				for (size_t i =0;i<size;i++) 
				{
					//counts c numbers
					if (roman[i] == 'C')
						cNumber++;
					//counts ) numbers
					else if (roman[i] == ')')
						backCNumber++;
					//would not count additional c 
					for (size_t j = 0; j < size; j++)
					{
						if (roman[i] == ')' && roman[j] == 'C'&&j>i)
							cNumber--;
					}
				}
				
				//we need a location that continues instead of going all over again
				location = cNumber + backCNumber + 1;

				//doing the math behind the appostrophus
				if (cNumber > 0 && backCNumber > 0 && backCNumber > cNumber)
				{
					number = 1000 * pow(10, cNumber - 1) + 500 * pow(10, backCNumber - cNumber - 1);

				}
				else if(cNumber > 0 && backCNumber > 0 && backCNumber == cNumber)
				{
					number = 1000 * pow(10, cNumber - 1);
				}
				else if (cNumber == 0 && backCNumber > 0)
				{
					number = 500 * pow(10, backCNumber - 1);
				}
			}
				
			counter++;
		
		} while (isAp==false&& counter<size);

		//goes through the array and will add or subtract based on the values and positions
		//multiplies the number by 1000 every time that sees - or _
		for (size_t i = location; i < size; i++) 
		{
			switch (roman[i])
			{
			//char romansLetter[7] = { 'I','V','X','L','C','D','M' };
			case 'M':
				number += 1000;
				break;

			case 'D':
				if (roman[i + 1] == 'M')
					number -= 500;
				else
					number += 500;
				break;

			case 'C':
				if (roman[i + 1] == 'M' || roman[i + 1] == 'D')
					number -= 100;
				else
					number += 100;
				break;

			case 'L':
				if (roman[i + 1] == 'M' || roman[i + 1] == 'D' || roman[i + 1] == 'C')
					number -= 50;
				else
					number += 50;
				break;

			case 'X':
				if (roman[i + 1] == 'M' || roman[i + 1] == 'D' || roman[i + 1] == 'C' || roman[i + 1] == 'L')
					number -= 10;
				else
					number += 10;
				break;

			case 'V':
				if (roman[i + 1] == 'M' || roman[i + 1] == 'D' || roman[i + 1] == 'C' || roman[i + 1] == 'L' || roman[i + 1] == 'X')
					number -= 5;
				else
					number += 5;
				break;
			
			case 'I':
				if (roman[i + 1] == 'M' || roman[i + 1] == 'D' || roman[i + 1] == 'C' || roman[i + 1] == 'L' || roman[i + 1] == 'X' || roman[i+1] == 'V')
					number -= 1;
				else
					number += 1;
				break;

			case 'S':
				number += 0.5;
				break;

			case '.':
				number += (1.0/12);
				break;
			
			case '_':
				number *= 1000;
				break;

			case '-':
				number *= 1000;
				break;
			default:
				break;
			}
		
		}
		//returns the number as a result
		return number;

}
	
//since we are not returning any variable we would have to populate an array given to function as a parameter	
void arabicToRoman(float arabic,char arr[]) 
{
	//number is used in order to get remainders
	size_t number = arabic;
	//counter is used to go and add letters to the arr[] array
	size_t counter = 0;
	
	//will go to the if statment if the number entered is greater than 4000
	if (arabic >= 4000)
	{
		////will go to the if statment if the number entered is greater than 4000000
		if (arabic >= 4000000)
		{
			//we get the digits that are after 1000000 and treat them like numbers less than 4000
			//we then get the arabic just as remainder
			number = arabic;
			number /= 1000000;
			arabic -= (number * 1000000);
			//use while when the number letter can be used more than once
			//use if statement when the letter can be use fust once
			//subtract every time that the number is higher than the letter and add one to counter
			//for two letters we would use two elements of the array and at the end we will add -
			while (number >= 1000)
			{
				arr[counter] = 'M';
				counter++;
				number -= 1000;
			}
			if (number >= 900)
			{
				arr[counter] = 'C';
				counter++;
				arr[counter] = 'M';
				counter++;
				number -= 900;
			}
			if (number >= 500)
			{
				arr[counter] = 'D';
				counter++;
				number -= 500;
			}
			if (number >= 400)
			{
				arr[counter] = 'C';
				counter++;
				arr[counter] = 'D';
				counter++;
				number -= 400;
			}
			while (number >= 100)
			{
				arr[counter] = 'C';
				counter++;
				number -= 100;
			}
			if (number >= 90)
			{
				arr[counter] = 'X';
				counter++;
				arr[counter] = 'C';
				counter++;
				number -= 90;
			}
			if (number >= 50)
			{
				arr[counter] = 'L';
				counter++;
				number -= 50;
			}
			if (number >= 40)
			{
				arr[counter] = 'X';
				counter++;
				arr[counter] = 'L';
				counter++;
				number -= 40;
			}
			while (number >= 10)
			{
				arr[counter] = 'X';
				counter++;
				number -= 10;
			}
			if (number >= 9)
			{
				arr[counter] = 'I';
				counter++;
				arr[counter] = 'X';
				counter++;
				number -= 9;
			}
			if (number >= 5)
			{
				arr[counter] = 'V';
				counter++;
				number -= 5;
			}
			if (number >= 4)
			{
				arr[counter] = 'I';
				counter++;
				arr[counter] = 'V';
				counter++;
				number -= 4;
			}
			while (number >= 1)
			{
				arr[counter] = 'I';
				counter++;
				number -= 1;
			}
			arr[counter] = '-';
			counter++;

		}
			
		//we get the digits that are after 1000 and treat them like numbers less than 4000 
		//we then get the arabic just as remainder
		
			number = arabic;
			number /= 1000;
			arabic -= (number * 1000);

			//use while when the number letter can be used more than once
			//use if statement when the letter can be use just once
			//subtract every time that the number is higher than the letter and add one to counter
			//for two letters we would use two elements of the array and at the end we will add -
			while (number >= 1000)
			{
				arr[counter] = 'M';
				counter++;
				number -= 1000;
			}
			if (number >= 900)
			{
				arr[counter] = 'C';
				counter++;
				arr[counter] = 'M';
				counter++;
				number -= 900;
			}
			if (number >= 500)
			{
				arr[counter] = 'D';
				counter++;
				number -= 500;
			}
			if (number >= 400)
			{
				arr[counter] = 'C';
				counter++;
				arr[counter] = 'D';
				counter++;
				number -= 400;
			}
			while (number >= 100)
			{
				arr[counter] = 'C';
				counter++;
				number -= 100;
			}
			if (number >= 90)
			{
				arr[counter] = 'X';
				counter++;
				arr[counter] = 'C';
				counter++;
				number -= 90;
			}
			if (number >= 50)
			{
				arr[counter] = 'L';
				counter++;
				number -= 50;
			}
			if (number >= 40)
			{
				arr[counter] = 'X';
				counter++;
				arr[counter] = 'L';
				counter++;
				number -= 40;
			}
			while (number >= 10)
			{
				arr[counter] = 'X';
				counter++;
				number -= 10;
			}
			if (number >= 9)
			{
				arr[counter] = 'I';
				counter++;
				arr[counter] = 'X';
				counter++;
				number -= 9;
			}
			if (number >= 5)
			{
				arr[counter] = 'V';
				counter++;
				number -= 5;
			}
			if (number >= 4)
			{
				arr[counter] = 'I';
				counter++;
				arr[counter] = 'V';
				counter++;
				number -= 4;
			}
			while (number >= 1)
			{
				arr[counter] = 'I';
				counter++;
				number -= 1;
			}
			arr[counter] = '-';
			counter++;
			
	}
	//We use arabic as a remainder and use number to do subtractions until the decimal places
	number = arabic;
	arabic -= number ;
	while (number >= 1000)
	{
		arr[counter] = 'M';
		counter++;
		number -= 1000;
	}
	if (number >= 900)
	{
		arr[counter] = 'C';
		counter++;
		arr[counter] = 'M';
		counter++;
		number -= 900;
	}
	if (number >= 500)
	{
		arr[counter] = 'D';
		counter++;
		number -= 500;
	}
	if (number >= 400)
	{
		arr[counter] = 'C';
		counter++;
		arr[counter] = 'D';
		counter++;
		number -= 400;
	}
	while (number >= 100)
	{
		arr[counter] = 'C';
		counter++;
		number -= 100;
	}
	if (number >= 90)
	{
		arr[counter] = 'X';
		counter++;
		arr[counter] = 'C';
		counter++;
		number -= 90;
	}
	if (number >= 50)
	{
		arr[counter] = 'L';
		counter++;
		number -= 50;
	}
	if (number >= 40)
	{
		arr[counter] = 'X';
		counter++;
		arr[counter] = 'L';
		counter++;
		number -= 40;
	}
	while (number >= 10)
	{
		arr[counter] = 'X';
		counter++;
		number -= 10;
	}
	if (number >= 9)
	{
		arr[counter] = 'I';
		counter++;
		arr[counter] = 'X';
		counter++;
		number -= 9;
	}
	if (number >= 5)
	{
		arr[counter] = 'V';
		counter++;
		number -= 5;
	}
	if (number >= 4)
	{
		arr[counter] = 'I';
		counter++;
		arr[counter] = 'V';
		counter++;
		number -= 4;
	}
	while (number >= 1)
	{
		arr[counter] = 'I';
		counter++;
		number -= 1;
	}
	//we use arabic variable because it contains our decimals	
	if (arabic >= 0.5)
		{
		arr[counter] = 'S';
		counter++;
		arabic -= 0.5;
	}
		while (arabic >= 1.0/12)
		{
			arr[counter] = '.';
			counter++;
			arabic -= 1.0/12;
		}
		
}

