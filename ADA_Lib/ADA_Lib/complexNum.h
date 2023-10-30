class complexNum
{
public:
	complexNum();
	complexNum addition(complexNum);
	bool read_errNumber();
	double get_x();
	double get_y();
	void set_x(double);
	void set_y(double);
	complexNum square_root();
	void show();
private:
	double x;
	double y;
	bool errNumber;
};