#include"complexNum.h"
#include<math.h>
#include<iostream>
using namespace std;
complexNum::complexNum()
{
	errNumber = false;//initialization
	x = 0;
	y = 0;
}
complexNum complexNum::addition(complexNum num)
{
	complexNum outcome;
	if (num.get_x() == 0 && num.get_y() == 0)//if the operand is 0+0i
		errNumber = true;//change the value of errNumber
	else//else do the addition
	{
		outcome.set_x(x + num.get_x());
		outcome.set_y(y + num.get_y());
	}
	return outcome;
}
bool complexNum::read_errNumber()
{
	return errNumber;//get the errNumber
}
double complexNum::get_x()
{
	return x;//get the real part
}
double complexNum::get_y()
{
	return y;//get the imaginary part
}
void complexNum::set_x(double a)
{
	errNumber = false;
	x = a;//change the real part
}
void complexNum::set_y(double a)
{
	errNumber = false;
	y = a;//change the imaginary part
}

complexNum complexNum::square_root()
{
	double xx = sqrt((x + sqrt(x * x + y * y)) / 2);//get the real part of the outcome
	int sgn;
	//get sgn
	if (y < 0)
		sgn = -1;
	else if (y == 0)
		sgn = 0;
	else if (y > 0)
		sgn = 1;
	double yy = sqrt((-x + sqrt(x * x + y * y)) / 2) * sgn;//get the imaginary part of the outcome
	complexNum sq_result;
	sq_result.set_x(xx);
	sq_result.set_y(yy);
	return sq_result;
}
void complexNum::show()//show a complex number in an appropriate format
{
	if (y < 0)
		cout << x << y << 'i';
	else
		cout << x << "+" << y << 'i';
}