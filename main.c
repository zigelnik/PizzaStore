/*

Name: Tal Zigelnik
...........................................
This programs is designed to order a pizza.
The user will enter his real ID Number, followed by his desired: size, amount, dough type and different kinds of toppings.
After every pizza chosen, the program will print a sketch of the specified pizza and will show its size and price without tax.
In the end, a summary of the order will be shown and an option for delivery, the user will also choose how much to pay and it will show how much is left to pay.
If there's change, calculate the minimum amount of coins needed to return.

*/


#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 40
#define MIN_LENGTH 10
#define MAX_WIDTH 80
#define MIN_WIDTH 10
#define NOT_EVEN 1
#define BASIC_LENGTH 40
#define BASIC_WIDTH 50
#define MAX_POSSIBLE_IDN 999999999
#define OLIVES_PRICE 10
#define MUSHROOM_PRICE 12
#define TOMATOES_PRICE 9
#define PINEAPPLE_PRICE 14
#define PIZZA_AREA 2000
#define REGULAR_DOUGH 0
#define VEGAN_DOUGH 5
#define WHEAT_DOUGH 3
#define GLUTENFREE_DOUGH 4
#define TAX 1.17
#define BASIC_PIZZA_PRICE 70.0
#define WHOLE_PIZZA 1
#define HALF_PIZZA 0.5
#define QUARTER_PIZZA 0.25
#define NONE 0
#define TEN_NIS 10
#define FIVE_NIS 5
#define TWO_NIS 2
#define ONE_NIS 1
#define DELIVERY_FEE 15
#define DELIVERY "Delivery\n"
#define PICKUP "Pick-up\n"
#include <stdio.h>


struct PIZZA {
	int width;
	int length;
	int quantity;
	int current;
	long int costumerID;
	char dough_type;
	char dough_char;
	double price;
	double totalPrice;
};
struct TOPPINGS {
	double olives;
	double mushrooms;
	double tomatoes;
	double pineapples;
	char q1;
	char q2;
	char q3;
	char q4;
};
typedef struct PIZZA Pizza;
typedef struct TOPPINGS Topping;

int checkDigit(int num);
void printWelcome();
void printMenu();
void printErrorTooMuchToppings();
void printSketch(Topping t, Pizza p);
void getPayment(Pizza p);
Pizza calcPrice(Topping t, Pizza p);
Pizza getID();
Pizza checkNumOfPizzas(Pizza p);
Pizza getSizes(Pizza p);
Pizza chooseDough(Pizza p);
Pizza chooseDelivery(Topping t, Pizza p);
Topping chooseTopping();
Topping chooseAmountofOlives(Topping t);
Topping chooseAmountofMushrooms(Topping t);
Topping chooseAmountofTomatoes(Topping t);
Topping chooseAmountofPineapples(Topping t);

void main()
{
	Pizza p; Topping t;

	printWelcome();
	p = getID();
	printMenu();
	p = checkNumOfPizzas(p);
	int currentPizza; p.totalPrice = 0, p.price = 0;

	for (p.current = 1; p.current <= p.quantity; p.current++)
	{
		p = getSizes(p);
		p = chooseDough(p);
		t = chooseTopping();
		p = calcPrice(t, p);
		printf("Pizza price (without tax): %.2lf\n", p.price);
		p.totalPrice += p.price;     // Sum the pizzas
		printSketch(t, p);           // Print how the pizza will look like
	}
	p = chooseDelivery(t, p);
	getPayment(p);                   // Pay for the pizza

}
void printSketch(Topping t, Pizza p)
{
	// In this function we devided the pizza to 4 quarters so we can alter and print each quarter according to the user's choice of desired topping.
	// Each topping is represeted by its first capital letters and the dough type in small letters that will be printed in the frame. e.g: 'M' for Mushrooms, 'w' for whole-wheat dough.
	int crust, half1, half2, top_left, top_right, bottom_left, bottom_right;

	for (crust = 0; crust < p.width; crust++)
		printf("%c", p.dough_char);
	printf("\n");

	for (half1 = 0; half1 < (p.length - 2) / 2; half1++)
	{
		printf("%c", p.dough_char);

		for (top_left = 0; top_left < (p.width / 2) - 1; top_left++)
		{
			printf("%c", t.q4);
		}
		for (top_right = 0; top_right < (p.width / 2) - 1; top_right++)
		{
			printf("%c", t.q1);
		}
		printf("%c", p.dough_char);
		printf("\n");
	}
	for (half2 = 0; half2 < (p.length - 2) / 2; half2++)
	{
		printf("%c", p.dough_char);

		for (bottom_left = 0; bottom_left < (p.width / 2) - 1; bottom_left++)
		{
			printf("%c", t.q3);
		}
		for (bottom_right = 0; bottom_right < (p.width / 2) - 1; bottom_right++)
		{
			printf("%c", t.q2);
		}
		printf("%c", p.dough_char);
		printf("\n");
	}

	for (crust = 0; crust < p.width; crust++)
		printf("%c", p.dough_char);
	printf("\n");
}
void printWelcome()
{
	printf("Welcome to MyPizzaStore!\n\n*****\n ***\n  *\n");
	printf("\nPlease enter your ID number: \n");
}
void printMenu()
{
	printf("\nOur menu:\n");
	printf("*********\n");
	printf("Basic pizza: %.2lf NIS for %dx%d size pizza\n\n", BASIC_PIZZA_PRICE, BASIC_LENGTH, BASIC_WIDTH);
	printf("Toppings for basic size pizza:\n");
	printf("Olives: %d NIS\nMushrooms: %d NIS\n", OLIVES_PRICE, MUSHROOM_PRICE);
	printf("Tomatoes: %d NIS\nPineapple: %d NIS\n\n", TOMATOES_PRICE, PINEAPPLE_PRICE);
	printf("Dough type for basic size pizza:\n");
	printf("Regular: %d NIS \nVegan: %d NIS \n", REGULAR_DOUGH, VEGAN_DOUGH);
	printf("Whole wheat: %d NIS\nGluten free: %d NIS\n\n", WHEAT_DOUGH, GLUTENFREE_DOUGH);
	printf("How many pizzas would you like to order? ");
}
void printErrorTooMuchToppings() {
	printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
}
void getPayment(Pizza p)
{
	int payment, change;
	while (p.totalPrice > NONE)
	{
		printf("\nPlease enter your payment: ");
		scanf("%d", &payment);

		// If the user paid the exact amount, end the program, but if there's change, return it in minimum coins needed by 10/5/2/1 coins.
		if (payment >= (int)p.totalPrice)
		{
			change = payment - (int)p.totalPrice;
			p.totalPrice -= payment;
			if (change == NONE)
			{
				printf("Thank you for your order!");
				return;
			}
			else
				printf("Your change is %d NIS using: \n", change);
			if (change > NONE)
			{
				if (change >= TEN_NIS)
				{
					printf("%d coin(s) of ten\n", change / TEN_NIS);
					change = change % TEN_NIS;
				}
				if (change >= FIVE_NIS)
				{
					printf("%d coin(s) of five\n", change / FIVE_NIS);
					change = change % FIVE_NIS;
				}
				if (change >= TWO_NIS)
				{
					printf("%d coin(s) of two\n", change / TWO_NIS);
					change = change % TWO_NIS;
				}
				if (change >= ONE_NIS)
				{
					printf("%d coin(s) of one\n", change / ONE_NIS);
					change = change % ONE_NIS;
				}
				if (change == NONE)
					printf("Thank you for your order!");
			}
		}
		else
		{
			change = p.totalPrice - payment; //If the payment is not enough, tell the user how much left to pay
			printf("Your remaining balance is: %d", change);
			p.totalPrice -= payment;
		}
	}
}
int checkDigit(int num)
{
	// In this function after the user put his ID, sum each digit by multiplying it by 2 and 1 and repeat after all digits have been checked.
	int last_dig, id, count, sum = 0, bikoret;
	id = num;

	bikoret = id % 10;
	id = id / 10;

	last_dig = (id % 10) * 2;		 	// 316593292 % 10 * 2 = 4
	count = last_dig;			        // count = 4
	sum = (count / 10) + (count % 10);  // sun = 0 + 4 = 4
	id = id / 10;						// id = 316593292 / 10 = 31659329

	last_dig = (id % 10) * 1;			// 31659329 % 10 = 9 * 1 = 9
	count = last_dig;					// count = 9;
	sum = sum + (count / 10) + (count % 10); // sum = 4 + 0 + 9 = 13
	id = id / 10;						// 31659329 / 10 = 3165932 ...

	last_dig = (id % 10) * 2;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;

	last_dig = (id % 10) * 1;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;

	last_dig = (id % 10) * 2;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;

	last_dig = (id % 10) * 1;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;

	last_dig = (id % 10) * 2;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;

	last_dig = (id % 10) * 1;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;

	last_dig = (id % 10) * 2;
	count = last_dig;
	sum = sum + (count / 10) + (count % 10);
	id = id / 10;
	sum += bikoret;

	// Finally, return check number to getID.
	return sum;
}
Pizza getID()
{
	Pizza p;
	int num;

	// The user will enter his ID and the program will check if its real using checkDigit function and a limit of possible mumbers.
	// If the user's ID is not "real" or check digit is invalid, ask again.
	scanf("%ld", &p.costumerID);
	while (p.costumerID > MAX_POSSIBLE_IDN || p.costumerID <= 0)
	{
		printf("Invalid ID number! Try again.\n"
			"Please enter your ID number: \n");
		scanf("%ld", &p.costumerID);
	}

	num = checkDigit(p.costumerID);

	while (num % 10 != 0)
	{
		printf("Invalid check digit! Try again.\n");
		printf("Please enter your ID number: \n");
		scanf("%ld", &p.costumerID);
		while (p.costumerID > MAX_POSSIBLE_IDN || p.costumerID <= 0)
		{
			printf("Invalid ID number! Try again.\n"
				"Please enter your ID number: \n");
			scanf("%ld", &p.costumerID);
		}
		num = checkDigit(p.costumerID);
	}
	return p;

}

Pizza calcPrice(Topping t, Pizza p)
{
	printf("\nPizza #%d details:\n*******************\n", p.current);
	printf("Pizza size: %dx%d\n", p.length, p.width);

	// Calculate all of ingredients to form the price of the pizza
	double chosenSize = (double)p.length * (double)p.width;
	double addDough = (chosenSize * p.dough_type) / PIZZA_AREA;
	double addMushrooms = chosenSize * t.mushrooms * (double)MUSHROOM_PRICE / (double)PIZZA_AREA;
	double addOlives = chosenSize * t.olives * (double)OLIVES_PRICE / (double)PIZZA_AREA;
	double addTomatoes = chosenSize * t.tomatoes * (double)TOMATOES_PRICE / (double)PIZZA_AREA;
	double addPineapples = chosenSize * t.pineapples * (double)PINEAPPLE_PRICE / (double)PIZZA_AREA;
	double pizzaPrice = chosenSize * (double)BASIC_PIZZA_PRICE / (double)PIZZA_AREA;
	double pizzaNoTax = pizzaPrice + addDough + addOlives + addMushrooms + addTomatoes + addPineapples;
	p.price = pizzaNoTax;

	return p;
}
Pizza checkNumOfPizzas(Pizza p)
{
	scanf("%d", &p.quantity);
	while (p.quantity < 1) {
		printf("Invalid choice! Try again.\n");
		printf("How many pizzas would you like to order? ");
		scanf("%d", &p.quantity);
	}
	return p;
}
Pizza getSizes(Pizza p)
{
	// Ask the user for desired pizza's width (between 10-80cm) and length (between 10-40cm), even numbers only. 
	// If chosen wrong, ask again.

	printf("\n*************************************************\nPizza #%d: \n\n", p.current);
	printf("Please enter your pizza's length (cm): ");
	scanf(" %d", &p.length);
	while ((p.length < MIN_LENGTH || p.length > MAX_LENGTH) || p.length % 2 == NOT_EVEN) {
		printf("Invalid length! Try again.\n");
		printf("Please enter your pizza's length (cm): ");
		scanf(" %d", &p.length);
	}

	printf("Please enter your pizza's width (cm): ");
	scanf(" %d", &p.width);
	while ((p.width < MIN_WIDTH || p.width > MAX_WIDTH) || p.width % 2 == NOT_EVEN) {
		printf("Invalid width! Try again.\n");
		printf("Please enter your pizza's width (cm): ");
		scanf(" %d", &p.width);
	}
	return p;
}
Pizza chooseDough(Pizza p)
{
	// Ask the user to choose his desired dough type, each option will be printed later in the frame represented by it's word first small letters.
	printf("\nPlease enter the pizza's dough type:\n"
		"r - for regular\n"
		"v - for vegan\n"
		"w - for whole wheat\n"
		"f - for gluten-free\n");
	scanf(" %c", &p.dough_type);

	while (p.dough_type != 'r' && p.dough_type != 'v' && p.dough_type != 'w' && p.dough_type != 'f') {
		printf("Invalid choice! Try again.\n");
		printf("\nPlease enter the pizza's dough type:\n"
			"r - for regular\n"
			"v - for vegan\n"
			"w - for whole wheat\n"
			"f - for gluten-free\n");
		scanf(" %c", &p.dough_type);
	}
	switch (p.dough_type)
	{
	case 'r':
		p.dough_type = REGULAR_DOUGH;
		p.dough_char = 'r';
		break;
	case 'v':
		p.dough_type = VEGAN_DOUGH;
		p.dough_char = 'v';
		break;
	case 'w':
		p.dough_type = WHEAT_DOUGH;
		p.dough_char = 'w';
		break;
	case 'f':
		p.dough_type = GLUTENFREE_DOUGH;
		p.dough_char = 'f';
		break;
	}
	return p;
}
Pizza chooseDelivery(Topping t, Pizza p)
{
	// In this function the user will choose delivery option, using numbers 1 or 0 only.
	// Price will be printed and calculated accordinly.
	int del;
	printf("\n*************************************************\n");
	printf("Do you want delivery for the price of %d NIS? Enter 1 for delivery or 0 for pick-up: ", DELIVERY_FEE);
	scanf("%d", &del);
	while (del != 1 && del != 0)
	{
		printf("Invalid choice! Try again.\n");
		printf("Do you want delivery for the price of %d NIS? Enter 1 for delivery or 0 for pick-up: ", DELIVERY_FEE);
		scanf("%d", &del);
	}
	if (del == 1)
	{
		printf("\nYour order details:\n");
		printf("*******************\n");
		printf("ID number: %09ld\n", p.costumerID);
		printf("Number of pizzas: %d\n", p.quantity);
		printf(DELIVERY);
		printf("Total price: %.2lf\n", p.totalPrice + DELIVERY_FEE);
		p.totalPrice = (p.totalPrice + DELIVERY_FEE) * TAX;
		printf("Total price with tax (rounded down): %d\n", (int)p.totalPrice);
	}
	else
	{
		printf("\nYour order details:\n");
		printf("*******************\n");
		printf("ID number: %09ld\n", p.costumerID);
		printf("Number of pizzas: %d\n", p.quantity);
		printf(PICKUP);
		printf("Total price: %.2lf\n", p.totalPrice);
		p.totalPrice = p.totalPrice * TAX;
		printf("Total price with tax (rounded down): %d\n", (int)p.totalPrice);
	}

	return p;
}
Topping chooseTopping()
{
	// In this function the user will choose his desired amount of toppings.
	// If the user chose a topping filling more than whole out of one pizza, the topping will not be added and an error message will be shown.
	Topping t; Pizza p;
	t.q1 = ' ';
	t.q2 = ' ';
	t.q3 = ' ';
	t.q4 = ' ';
	t.olives = NONE;
	t.mushrooms = NONE;
	t.tomatoes = NONE;
	t.pineapples = NONE;

	printf("\nPlease choose the toppings: \n");
	printf("\nOlives (choose 0-3):\n");
	t = chooseAmountofOlives(t);

	if (t.olives < 1)
	{
		printf("\nMushrooms (choose 0-3):\n");
		t = chooseAmountofMushrooms(t);

		while (t.olives + t.mushrooms > WHOLE_PIZZA)
		{
			printErrorTooMuchToppings();
			t = chooseAmountofMushrooms(t);
		}
		if (t.olives + t.mushrooms != WHOLE_PIZZA)
		{
			printf("\nTomatos (choose 0-3):\n");
			t = chooseAmountofTomatoes(t);

			while (t.olives + t.mushrooms + t.tomatoes > WHOLE_PIZZA)
			{
				printErrorTooMuchToppings();
				t = chooseAmountofTomatoes(t);
			}
			if (t.olives + t.mushrooms + t.tomatoes != WHOLE_PIZZA)
			{
				printf("\nPineapple (choose 0-3):\n");
				t = chooseAmountofPineapples(t);

				while (t.olives + t.mushrooms + t.tomatoes + t.pineapples > WHOLE_PIZZA)
				{
					printErrorTooMuchToppings();
					t = chooseAmountofPineapples(t);
				}
			}
		}
	}
	return t;
}
Topping chooseAmountofOlives(Topping t) {

	int amountOlives;
	printf("0. None\n"
		"1. Whole pizza\n"
		"2. Half pizza\n"
		"3. Quarter pizza\n");
	scanf(" %d", &amountOlives);

	while (amountOlives != 0 && amountOlives != 1 && amountOlives != 2 && amountOlives != 3)
	{
		printf("Invalid choice! Try again.\n"
			"0. None\n"
			"1. Whole pizza\n"
			"2. Half pizza\n"
			"3. Quarter pizza\n");
		scanf(" %d", &amountOlives);
	}

	switch (amountOlives)
	{
	case 0:
		t.olives = NONE;
		break;
	case 1:
		t.olives = WHOLE_PIZZA;
		t.q1 = 'O'; t.q2 = 'O'; t.q3 = 'O'; t.q4 = 'O';
		break;
	case 2:
		t.olives = HALF_PIZZA;
		t.q1 = 'O'; t.q2 = 'O';
		break;
	case 3:
		t.olives = QUARTER_PIZZA;
		t.q1 = 'O';
		break;
	}
	return t;
}
Topping chooseAmountofMushrooms(Topping t) {

	int amountMushrooms;
	printf("0. None\n"
		"1. Whole pizza\n"
		"2. Half pizza\n"
		"3. Quarter pizza\n");
	scanf(" %d", &amountMushrooms);

	while (amountMushrooms != 0 && amountMushrooms != 1 && amountMushrooms != 2 && amountMushrooms != 3)
	{
		printf("Invalid choice! Try again.\n"
			"0. None\n"
			"1. Whole pizza\n"
			"2. Half pizza\n"
			"3. Quarter pizza\n");
		scanf(" %d", &amountMushrooms);
	}

	switch (amountMushrooms)
	{
	case 0:
		t.mushrooms = NONE;
		break;
	case 1:
		t.mushrooms = WHOLE_PIZZA;
		if (t.q1 == ' ')
		{
			t.q1 = 'M'; t.q2 = 'M'; t.q3 = 'M'; t.q4 = 'M';
		}
		break;
	case 2:
		t.mushrooms = HALF_PIZZA;
		if (t.q1 != 'O')
		{
			t.q1 = 'M'; t.q2 = 'M';
		}
		else if (t.q2 != 'O')
		{
			t.q2 = 'M'; t.q3 = 'M';
		}
		else if (t.q3 = 'O');
		{
			t.q3 = 'M'; t.q4 = 'M';
		}
		break;
	case 3:
		t.mushrooms = QUARTER_PIZZA;
		if (t.q1 != 'O')
			t.q1 = 'M';
		else if (t.q2 != 'O')
			t.q2 = 'M';
		else if (t.q2 = 'O')
			t.q3 = 'M';
		else
			t.q4 = 'M';
		break;
	}
	return t;
}

Topping chooseAmountofTomatoes(Topping t) {

	int amountTomatoes;
	printf("0. None\n"
		"1. Whole pizza\n"
		"2. Half pizza\n"
		"3. Quarter pizza\n");
	scanf(" %d", &amountTomatoes);

	while (amountTomatoes != 0 && amountTomatoes != 1 && amountTomatoes != 2 && amountTomatoes != 3)
	{
		printf("Invalid choice! Try again.\n"
			"0. None\n"
			"1. Whole pizza\n"
			"2. Half pizza\n"
			"3. Quarter pizza\n");
		scanf(" %d", &amountTomatoes);
	}
	switch (amountTomatoes)
	{
	case 0:
		t.tomatoes = NONE;
		break;
	case 1:
		t.tomatoes = WHOLE_PIZZA;
		if (t.q1 == ' ')
		{
			t.q1 = 'T'; t.q2 = 'T'; t.q3 = 'T'; t.q4 = 'T';
		}
		break;

	case 2:
		t.tomatoes = HALF_PIZZA;
		if (t.q4 = ' ')
		{
			if (t.q1 != 'O' && (t.q1 != 'M'))
			{
				t.q1 = 'T'; t.q2 = 'T';
			}
			else if (t.q2 != 'O' && (t.q2 != 'M'))
			{
				t.q2 = 'T'; t.q3 = 'T';
			}
			else if (t.q3 != 'O' && (t.q3 != 'M'))
			{
				t.q3 = 'T'; t.q4 = 'T';
			}
		}
		break;
	case 3:
		t.tomatoes = QUARTER_PIZZA;
		if (t.q1 != 'O' && (t.q1 != 'M'))
			t.q1 = 'T';
		else if (t.q2 != 'O' && (t.q2 != 'M'))
			t.q2 = 'T';
		else if (t.q3 != 'M')
			t.q3 = 'T';
		else if (t.q3 = 'M')
			t.q4 = 'T';

		break;
	}
	return t;
}
Topping chooseAmountofPineapples(Topping t) {

	int amountPineapples;
	printf("0. None\n"
		"1. Whole pizza\n"
		"2. Half pizza\n"
		"3. Quarter pizza\n");
	scanf(" %d", &amountPineapples);

	while (amountPineapples != 0 && amountPineapples != 1 && amountPineapples != 2 && amountPineapples != 3)
	{
		printf("Invalid choice! Try again.\n"
			"0. None\n"
			"1. Whole pizza\n"
			"2. Half pizza\n"
			"3. Quarter pizza\n");
		scanf(" %d", &amountPineapples);
	}
	switch (amountPineapples)
	{
	case 0:
		t.pineapples = NONE;
		break;
	case 1:
		t.pineapples = WHOLE_PIZZA;
		if (t.q4 = ' ') {
			t.q1 = 'P'; t.q2 = 'P'; t.q3 = 'P'; t.q4 = 'P';
		}
		break;
	case 2:
		t.pineapples = HALF_PIZZA;

		if (t.q4 = ' ')
		{
			if (t.q1 != 'O' && (t.q1 != 'M') && (t.q1 != 'T'))
			{
				t.q1 = 'P'; t.q2 = 'P';
			}
			else if (t.q2 != 'O' && (t.q2 != 'M') && (t.q2 != 'T'))
			{
				t.q2 = 'P'; t.q3 = 'P';
			}
			else
			{
				t.q3 = 'P'; t.q4 = 'P';
			}
		}
		break;
	case 3:
		t.pineapples = QUARTER_PIZZA;
		if (t.q1 != 'O' && (t.q1 != 'M') && (t.q1 != 'T'))
			t.q1 = 'P';
		else if (t.q2 != 'O' && (t.q2 != 'M') && (t.q2 != 'T'))
			t.q2 = 'P';
		else if (t.q3 != 'O' && (t.q3 != 'M') && (t.q3 != 'T'))
			t.q3 = 'P';
		else
			t.q4 = 'P';

		break;
	}
	return t;
}