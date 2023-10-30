#include<iostream>
#include"complexNum.h"//the header file of the class complexNum
#include<fstream>
using namespace std;
bool menu();//used to continuously show the user interface
bool login();//used to login
complexNum num1, num2;//num1 is the complex number that being operated, (2+3i in the requirement sheet), num2 is the operand(5+7i in the requirement sheet)
int main()
{
	bool log = login();//login
	if (log == false)//if failed to login,end the program
		return 0;
	bool exitflag = false;//used to define when the menu loop will end
	while (exitflag == false)
	{
		exitflag = menu();
	}
	return 0;
}
bool menu()
{
	char choice;//store the user input choice

	cout << "a.Enter one complex numbers and one operand." << endl;
	cout << "b.Display two complex numbers." << endl;
	cout << "c.Addition" << endl;
	cout << "d.Square root of the complex number." << endl;
	cout << "q.Quit" << endl;
	cout << "Please enter your choice: ";
	cin >> choice;
	//input a character for choice

	complexNum result;//store the operation result of addtion or sqaure root
	double m, n;//store the real part and the imaginary part of a complex number 
	/*pro1*/


	switch (choice)
	{
	case 'a'://input the two complex numbers
		cout << "Please enter a complex number: " << endl;
		cout << "The real part: ";
		cin >> m ;
		cout << "The imaginary part: ";
		cin >> n;
		num1.set_x(m);
		num1.set_y(n);
		cout << "Please enter an operand: " << endl;
		cout << "The real part: ";
		cin >> m;
		cout << "The imaginary part: ";
		cin >> n;
		num2.set_x(m);
		num2.set_y(n);
		break;
	case 'b'://show the two complex numbers
		cout << "The first complex number is ";
		/*pro2 show()*/

		num1.show();
		cout << endl;
		cout << "The operand is ";
		num2.show();
		cout << endl;
		break;
	case 'c'://do addition and show the result
		result = num1.addition(num2);
		if (num1.read_errNumber() == true)
			//if the operand is 0+0i, private member variable errNumber of num1 will be set to true, in that case, show the below error message.
			cout << "The operand is 0+0i. Please enter two valid complex numbers again!" << endl;
		else
		{
			cout << "The addition result is ";
			result.show();
			cout << endl;
		}
		break;
	case 'd'://output two square roots of the first complex nunmber
		result = num1.square_root();//firstly, use result to store one of the square root 
		cout << "The square roots of the first complex number are: ";
		result.show();
		cout << " and ";
		//let result be the other square root and show it
		result.set_x(-result.get_x());
		result.set_y(-result.get_y());
		result.show();
		cout << endl;
		break;
	case 'q'://return true to end the program
		cout << "Goodbye!" << endl;
		return true;
	default://if other inputs are input, show the error message
		cout << "Invalid input! Please Enter again!" << endl;
	}
	return false;//if the user does not press 'q', return false to continuously show the menu
}

bool login()
{
	/*
	The format of each line in the file should be like "username password"
	each line only store one piece of user information
	The space is not allowed in username
 */
	char input_name[100];//store the username input by the user
	cout << "Please input your username: ";
	cin.getline(input_name, 100);
	int len = strlen(input_name);//len is the length of the input username
	ifstream fin("user", ios::in);//read the file from the start
	char user_inf[100];//store a line in the file
	bool exist = true;//check whether the username has been stored in the file already

	while (fin.getline(user_inf, 100))//while it is not the end of the file
	{
		exist = true;//reset exist
		char stored_user[100] = {};//used to get the username stored in the file
		char stored_password[100] = {};//used to get the password stored in the file
		int count = 0;//record the length of the username stored in the file
		for (count = 0; user_inf[count] != ' '; count++)
			//if the current character in the line is not ' ',
			//which indicates that the username stored in the file has not been fully got
			stored_user[count] = user_inf[count];//get the character for username
		count--;
		//when ending the loop above, the count if the position of the character ' ', 
		//move count to the position of the last character of the username 
		if (len == count + 1)//if the username input by the user and the username stored in the file has the same length
		{
			for (int i = 0; i <= len - 1; i++)
				if (stored_user[i] != input_name[i])
					//compare the content character by character, in this process, 
					//if one difference is detected, which means the input username is not the username stored in the file, 
					//set the exist to false 
				{
					exist = false;
					break;
				}
		}
		else
			exist = false;//if the length of the two strings are different, no need to check character by character
		if (exist == true)
			//Through the process above, if exist is still true, 
			//the username input by the user is the username stored in the file
		{
			int times = 1;//store how many times the user has attempted to input the password.
			count += 2;
			//The count before this line shows the last character's position of the username, 
			//count+1 is the position of the ' ' between the username and the password, 
			//and count+2 is the position of the first character of the password. 
			for (int i = count; i <= strlen(user_inf) - 1; i++)//get all characters of the password in the file
				stored_password[i - count] = user_inf[i];
			int lenp = strlen(user_inf) - count;//store the length of the password in the file
			while (times <= 3)// The user can only try three times when inputing a password
			{
	
				bool flag1 = true;//used to check whether the password is correct.
				cout << "Please enter your password: ";
				char password[100];
				cin.getline(password, 100);//let the user input the password
				int lenpw = strlen(password);//store the length of the password input by the user
				if (lenpw == lenp)//if the password input by the user is of the same length of the password stored in the file
				{
					for (int i = 0; i <= lenpw - 1; i++)
						if (password[i] != stored_password[i])//check character by character, if one difference is detected
						{
							times++;//add one time 
							flag1 = false;//set the flag
							cout << "Wrong password!" << endl;//show message
							break;
						}
					if (flag1 == true)
						//if throught the check process above, the flag is still true, 
						//close the file and show message. return true.
					{
						cout << "You have successfully logged in." << endl;
						fin.close();
						return true;
					}
				}
				else//if the two strings are of different length,no need to check character by character
				{
					flag1 = false;
					times++;
					cout << "Wrong password!" << endl;
				}
			}
			//if the program is currently here, 
			//which indicates that the user inputs an exsiting username but fails to input the correct password in three times, 
			//show the message and close the file,return false
			cout << "You have entered the password wrongly three times!" << endl;
			fin.close();
			return false;
		}
	}
	//if the username does not exist in the file, let user set the password
	fin.close();
	cout << "Please set your password: ";
	char set[100];//store the password the user wants to set
	cin.getline(set, 100);
	ofstream fout("user", ios::app);
	fout << input_name << " " << set << endl;
	cout << "You have successfully registered!" << endl;
	return true;


}
