#include <iostream> //Joseph Xavier Vinit Miranda 3035243778
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
struct Movie {
	string name;
	int price;
	int n;
};
struct Date {
	int date[2];
	int n;
	int price;
};
int closeCounter, movieCounter = 0, dayCounter = 0;
int getIndex(string movie);
void tomorrow(int date[]);
void showDay (ifstream& fin, int day, int month);
bool isBlank(char row, int column);
void showPlan (ifstream& fin, int date[], string time);
bool isBooked(char row, int column, int date[], string time);
int getPrice(ifstream& fin, int day, int month, string time);
void generateStat(int date[]);
void update(string seat, int date[], string time, int price);
void generateStatAll(Movie movie[], Date day[]);
string getMovie(int date[], string time);
void sortDay(Date day[]);
void sortMovie(Movie movie[]);
void tomorrow(int date[])
{
	int daysInMonth[12]= {31,29,31,30,31,30,31,31,30,31,30,31};
    if (date[0] == daysInMonth[date[1] - 1])
    {
        if (date[1] == 12)
        {
            date[0] = 1;
            date[1] = 1;
        }
        else
        {
            date[0] = 1;
            date[1] = date[1] + 1;
        }
    }
    else
        date[0] = date[0] + 1;
}
void showDay (ifstream& fin, int day, int month)
{
	fin.clear();
	fin.seekg(0, ios::beg);
	int dayFromFile, monthFromFile, price;
	string movie, time, dummy;
	char ch;
	while (fin.good())
	{
		getline(fin, movie, ',');
		while (ch != '*' && fin.good())
		{
			fin >> dayFromFile >> ch;
			fin >> monthFromFile >> ch;
			getline(fin, time, ',');
			fin >> price >> ch;
			if (dayFromFile == day && monthFromFile == month)
			{
				cout << movie << "..." << dayFromFile << "/" << monthFromFile << "..." << time << "...$" << price << endl;
			}
		}
		ch = '\0';
		getline(fin, dummy);
	}
}
bool isBlank(char row, int column)
{
	ifstream fin;
	fin.open("house.txt");
	fin.clear();
	fin.seekg(0, ios::beg);
	string dummy;
	char ch;
	getline(fin, dummy);
	getline(fin, dummy);
	getline(fin, dummy);
	for (int i = 1; i <= (int)(row - 'A'); i++)
	{
		getline(fin, dummy);
	} 
	int flag = 0;
	for (int i = 1; i < column && flag == 0; i++)
	{
		fin >> ch;
		if (ch == '|')
			flag = 1;
	}
	fin >> ch;
	fin.close();
	if (ch == 'o' && flag == 0)
		return false;
	else
		return true;
}
void showPlan (ifstream& fin, int date[], string time)
{
	fin.clear();
	fin.seekg(0, ios::beg);
	string dummy;
	char ch;
	char row = 'A';
	int column = 1;
	getline(fin, dummy);
	column = dummy.length() - 1;
	cout << "  .............." << endl << "  ... SCREEN ..." << endl << "  ..............";
	cout << endl << "  ";
	for (int i = 1; i <= column; i++)
	{
		cout << i / 10;
	}
	cout << endl << "  ";
	for (int i = 1; i <= column; i++)
	{
		cout << i % 10;
	}
	cout << endl;
	column = 1;
	getline(fin, dummy);
	getline(fin, dummy);
	while (fin >> ch)
	{
		cout << endl;
		cout << row << " ";
		column = 1;
		while (ch != '|')
		{
			if (isBooked(row, column, date, time))
			{
				cout << "-";
			}
			else if (ch == 'o')
			{
				cout << "o";
			}
			else
				cout << " ";
			column++;
			fin >> ch;
		}
		getline(fin, dummy);
		row++;
	}	
	cout << endl;
}
bool isAllBooked(int date[], string time)
{
	ifstream fin;
	string dummy;
	char ch;
	fin.open("house.txt");
	int column = 1;
	char row = 'A';
	getline(fin, dummy);
	getline(fin, dummy);
	getline(fin, dummy);
	while (fin >> ch)
	{
		column = 1;
		while (ch != '|')
		{
			if (ch == 'o')
			{
				if (!(isBooked(row, column, date, time)))
				{
					return false;
				}	
			}
			column++;
			fin >> ch;
		}
		getline(fin, dummy);
		row++;
	}
	fin.close();
	cout << "All seats are booked!" << endl;
	return true;
}
bool isBooked(char row, int column, int date[], string time)
{
	string dummy, timeFromFile, file;
	int columnFromFile, dateFromFile[2];
	char rowFromFile, ch;
	ifstream fin;
	fin.open("bookedTickets.txt");
	fin.clear();
	fin.seekg(0, ios::beg);
	while (fin.good())
	{	
		fin >> ch;
		if (ch == '*')
		{
			fin >> dateFromFile[0] >> ch >> dateFromFile[1] >> ch; 
			getline(fin, timeFromFile, ',');
			if (dateFromFile[0] == date[0] && dateFromFile[1] == date[1] && timeFromFile == time)
			{
				fin >> rowFromFile >> columnFromFile;
				if (row == rowFromFile && column == columnFromFile)
				{
					fin.close();
					return true;
				}
			}
		}
		getline(fin, dummy);
	}
	fin.close();
	return false;
}
int getPrice(ifstream& fin, int day, int month, string time)
{
	fin.clear();
	fin.seekg(0, ios::beg);
	int dayFromFile, monthFromFile, price;
	string movie, timeFromFile, dummy;
	char ch = '\0';
	while (fin.good())
	{
		getline(fin, movie, ',');
		while (ch != '*' && fin.good())
		{
			fin >> dayFromFile >> ch;
			fin >> monthFromFile >> ch;
			getline(fin, timeFromFile, ',');
			if (timeFromFile.length() == 4)
				timeFromFile = "0" + timeFromFile;
			fin >> price >> ch;
			if (dayFromFile == day && monthFromFile == month && timeFromFile == time)
			{
				return price;
			}
		}
		ch = '\0';
		getline(fin, dummy);
	}
	return price;
}
string getMovie(int date[], string time)
{
	ifstream fin;
	fin.open("schedule.txt");
	fin.clear();
	fin.seekg(0, ios::beg);
	int dayFromFile, monthFromFile, price;
	string movie ="", timeFromFile, dummy;
	char ch;
	
	while (fin.good())
	{
		ch = '\0';
		getline(fin, movie, ',');
		while(ch != '*' && fin.good())
		{
			fin >> dayFromFile >> ch;
			fin >> monthFromFile >> ch;
			getline(fin, timeFromFile, ',');
			if (timeFromFile.length() == 4)
				timeFromFile = "0" + timeFromFile;
			fin >> price >> ch;
			if (dayFromFile == date[0] && monthFromFile == date[1] && timeFromFile == time)
			{
				return movie;
			}
		}
		getline(fin, dummy);
	}
	return "";
}
void update(string seat, int date[], string time, int price)
{
	ofstream fout;
	fout.open("bookedTickets.txt", ios::app);
	fout << "*" << date[0] << "/" << date[1] << "," << time << "," << seat << "," << price << "*" << endl;  
	fout.close();
}
void getToPosition(ifstream& fin)
{
	string dummy;
	char ch;
	int i = 0;
	while (i < closeCounter)
	{
		fin >> ch;
		if (ch == '!')
			i++;
		getline(fin, dummy);
	}
}
void generateStatAll(Movie movie[], Date day[])
{
	int flag = 0, flag2 = 0;
	string temp, file;
	ifstream fin;
	ifstream fin2;
	fin2.open("schedule.txt");
	ofstream fout;
	fout.open("statAll.txt");
	int price = 0;
	int netPrice = 0;
	movieCounter = 0;
	dayCounter = 0;
	for (int i = 0; i <= 50; i++)
	{
		movie[i].price = 0;
		movie[i].n = 0;
	}
	for (int i = 0; i <= 366; i++)
	{
		day[i].price = 0;
		day[i].n = 0;
	}
	
		fin.open("bookedTickets.txt");
		fin.clear();
		fin.seekg(0, ios::beg);
		char ch;
		string dummy, timeFromFile;
		int dateFromFile[2] = {0};

		while (fin >> ch)
		{
			if (ch == '*')
			{
				fin >> dateFromFile[0] >> ch >> dateFromFile[1] >> ch;
				getline(fin, timeFromFile, ',');
				
				temp = getMovie(dateFromFile, timeFromFile);
				flag = 0;
				flag2 = 0;
				for (int i = 0; i < movieCounter; i++)
				{	
					if (temp == movie[i].name)
					{
						getline(fin, dummy, ',');
						fin >> price;
						movie[i].price += price;
						movie[i].n++;
						flag = 1; 
					}
				}
				for (int i = 0; i < dayCounter; i++)
				{
					if (dateFromFile[0] == day[i].date[0] && dateFromFile[1] == day[i].date[1] )
					{
						day[i].price += getPrice(fin2, dateFromFile[0], dateFromFile[1], timeFromFile);
						day[i].n++;
						flag2 = 1;
					}
				}
				if (flag != 1)
				{
					/*movie[movieCounter].date[0] = dateFromFile[0];
					movie[movieCounter].date[1] = dateFromFile[1];
					movie[movieCounter].time = timeFromFile;
					*/
					movie[movieCounter].name = getMovie(dateFromFile, timeFromFile);
					getline(fin, dummy, ',');
					fin >> price;
					movie[movieCounter].n++;
					movie[movieCounter].price = price;
					movieCounter++;
				}
				if (flag2 != 1)
				{
					day[dayCounter].date[0] = dateFromFile[0];
					day[dayCounter].date[1] = dateFromFile[1];
					day[dayCounter].n++;
					day[dayCounter].price = getPrice(fin2, dateFromFile[0], dateFromFile[1], timeFromFile);
					dayCounter++;
				}
			}
			getline(fin, dummy);
		}
		fin.close();
	sortDay(day);
	fout << "by date" << endl;
	for (int i = 0; i < dayCounter; i++)
	{
		netPrice = netPrice + day[i].price;
		fout << setw(2) << setfill('0') << day[i].date[0] << "/" << setw(2) << setfill('0') << day[i].date[1] << "," << day[i].n << ",$" << day[i].price << endl;
	}
	fout << "total $" << netPrice << endl;
	netPrice = 0;
	sortMovie(movie);
	fout << "by movie" << endl;
	for (int i = 0; i < movieCounter; i++)
	{
		netPrice = netPrice + movie[i].price;
		fout << movie[i].name << "," << movie[i].n << ",$" << movie[i].price << endl;
	}
	fout << "total $" << netPrice;
	fout.close();
	fin.close();	
}
void sortMovie(Movie movie[])
{
	string tempName;
	int tempPrice, tempN;
	for (int i = 0; i < movieCounter; i++)
	{
		for (int j = i; j < movieCounter; j++)
		{
			if (getIndex(movie[i].name) > getIndex(movie[j].name))
			{
				tempName = movie[i].name;
				movie[i].name = movie[j].name;
				movie[j].name = tempName;
				tempPrice = movie[i].price;
				movie[i].price = movie[j].price;
				movie[j].price = tempPrice;
				tempN = movie[i].n;
				movie[i].n = movie[j].n;
				movie[j].n = tempN;
			}
		}
	}
}
void sortDay(Date day[])
{
	int tempDay, tempMonth, tempPrice, tempN;
	for (int i = 0; i < dayCounter; i++)
	{
		for (int j = i; j < dayCounter; j++)
		{
			if ((day[i].date[1] > day[j].date[1]) || (day[i].date[1] == day[j].date[1] && day[i].date[0] > day[j].date[0]))
			{
				tempDay = day[i].date[0];
				day[i].date[0] = day[j].date[0];
				day[j].date[0] = tempDay;
				tempMonth = day[i].date[1];
				day[i].date[1] = day[j].date[1];
				day[j].date[1] = tempMonth;
				tempPrice = day[i].price;
				day[i].price = day[j].price;
				day[j].price = tempPrice;
				tempN = day[i].n;
				day[i].n = day[j].n;
				day[j].n = tempN;
			}
		}
	}
}
int getIndex(string movie)
{
	int i = -1;
	ifstream fin;
	string movieFromFile, dummy;
	fin.open("schedule.txt");
	while (fin.good())
	{
		i++;
		getline (fin, movieFromFile, ',');
		if (movieFromFile == movie)
		{
			fin.close();
			return i;
		}
		getline(fin, dummy);
	}
	fin.close();
	return -1;
}
void generateStat(int date[])
{
	movieCounter = 0;
	int flag = 0;
	string temp;
	ifstream fin;
	ofstream fout;
	string file;
	fin.open("bookedTickets.txt");
	fin.clear();
	fin.seekg(0, ios::beg);
	getToPosition(fin);
	fout.open("stat.txt");
	char ch;
	int price = 0, totalPrice = 0, netPrice = 0;
	int n = 0;
	string dummy, timeFromFile;
	int dateFromFile[2] = {0};
	fout << "by date" << endl;
	for (int i = 0; i <= 2; i++)
	{

		n = 0;
		totalPrice = 0;
		while (fin >> ch)
		{
			if (ch == '*')
			{
				fin >> dateFromFile[0] >> ch >> dateFromFile[1] >> ch;
				getline(fin, timeFromFile, ',');
				if (dateFromFile[0] == date[0] && dateFromFile[1] == date[1])
				{
					n++;
					getline(fin, dummy, ',');
					fin >> price;
					totalPrice += price; 
				}
			}
			getline(fin, dummy);
		}
		if (n > 0)
		{
			fout << setw(2) << setfill('0') << date[0] << "/" << setw(2) << setfill('0') << date[1] << "," << n << ",$" << totalPrice << endl;
			netPrice += totalPrice;
		}
		tomorrow(date);
		fin.clear();
		fin.seekg(0, ios::beg);
		getToPosition(fin);
	}
	fout << "total $" << netPrice << endl;
	netPrice = 0;
	fout << "by movie" << endl;
	Movie movie[50];
	for (int i = 0; i < 50; i++)
	{	
		movie[i].n = 0;
		movie[i].price = 0;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	getToPosition(fin);
	fin >> ch;
	fin >> dateFromFile[0] >> ch >> dateFromFile[1] >> ch; 
	getline(fin, timeFromFile, ',');
	movie[movieCounter].name = getMovie(dateFromFile, timeFromFile);
	getline(fin, dummy, ',');
	fin >> price;
	movie[movieCounter].price += price;
	if (price != 0)
	{
		movie[movieCounter].n++;
		movieCounter++;
	}
	getline(fin, dummy);
	while (fin >> ch)
	{
		if (ch == '*')
		{
			fin >> dateFromFile[0] >> ch >> dateFromFile[1] >> ch;
			getline(fin, timeFromFile, ',');
			temp = getMovie(dateFromFile, timeFromFile);
			flag = 0;
			for (int i = 0; i < movieCounter; i++)
			{	
				if (temp == movie[i].name)
				{
					getline(fin, dummy, ',');
					fin >> price;
					movie[i].price += price;
					if (price != 0)
					{
						movie[i].n++;
					}
					flag = 1; 
				}
			}
			if (flag != 1)
			{
				movie[movieCounter].name = getMovie(dateFromFile, timeFromFile);
				getline(fin, dummy, ',');
				fin >> price;
				movie[movieCounter].price = price;
				if (price != 0)
				{
					movie[movieCounter].n++;
				}
				movieCounter++;
			}
		}
		getline(fin, dummy);
	}
	sortMovie(movie);
	for (int i = 0; i < movieCounter; i++)
	{
		netPrice = netPrice + movie[i].price;
		fout << movie[i].name << "," << movie[i].n << ",$" << movie[i].price << endl;
	}
	fout << "total $" << netPrice;
	fout.close();
	fin.close();
}
int main()
{
	Movie movie[50];
	Date day[366];
	string input, showInput, time, statInput1, statInput2;
	char ch;
	int price = 0;
	string dummy;
	int date[2] = {0};
	int column;
	int tempDate[2] = {0};
	int x, numberOfTickets;
	string seat;
	cout << "open | show day | show all | buy day | stat | stat all | close | end" << endl;
	cin >> input;
	ifstream fin;
	ifstream fin2;
	ofstream fout;
	fout.open("bookedTickets.txt", ios::app);
	ifstream closein;
	ofstream closeout;
	closein.open("closeCounter.txt");
	if (!(closein.good()))
		closeCounter = 0;
	else
		closein >> closeCounter;
	
	while(input != "end")
	{
		if (input == "open")
		{
			closein.open("closeCounter.txt");
			closein.clear();
			closein.seekg(0, ios::beg);
			if (!(closein.good()))
				closeCounter = 0;
			else
				closein >> closeCounter;
			fin.open("schedule.txt");
			fin2.open("house.txt");
			cin >> date[0] >> ch >> date[1];
		}		
		else if (input == "show")
		{
			tempDate[0] = date[0];
			tempDate[1] = date[1];

			cin >> showInput;
			if (showInput == "all")
			{
				for (int i = 0; i <= 2; i++)
				{
					showDay(fin, tempDate[0], tempDate[1]);
					tomorrow(tempDate); 
				}	
			}
			else if (showInput == "day")
			{
				cin >> x;
				getline(cin, time);//CHECK TIME
				for (int i = 0; i < x; i++)
				{
					tomorrow(tempDate);
				}
				
				if (time.length() >= 5)
				{
					time = time.substr(1);
					if (time.length() == 4)
						time = "0" + time;
					
					showPlan(fin2, tempDate, time);
				}					
				else
				{
					//cout << tempDate[0] << tempDate[1];
					showDay(fin, tempDate[0], tempDate[1]);
				}
			}
		}
		else if (input == "buy")
		{
			tempDate[0] = date[0];
			tempDate[1] = date[1];

			cin >> dummy >> x >> time >> numberOfTickets;
			if (time.length() == 4)
				time = "0" + time;
			for (int i = 0; i < x; i++)
			{
				tomorrow(tempDate);
			}
			for (int i = 1; i <= numberOfTickets && !(isAllBooked(tempDate, time)); i++)
			{
				stringstream ss;
				cin >> seat;
				dummy = seat.substr(1);
				ss << dummy;
				ss >> column;
				if (!(isBooked(seat[0], column, tempDate, time)) && !(isBlank(seat[0], column)))
				{
					price = getPrice(fin, tempDate[0], tempDate[1], time);
					update(seat, tempDate, time, price);
					cout << "Booked" << endl;
				}
				else
				{
					i--;
				}
			}
			
		}
		else if (input == "stat")
		{				
			getline(cin, statInput1);
			if (statInput1 == " all")
				generateStatAll(movie, day);
			else
				generateStat(date);
			//else
			//	generateStat(date, time);
			//cout << ":" << statInput1 << ":";
			//cout << ":" << statInput2 << ":";
		}
		else if (input == "close")
		{	
			closeCounter++;
			closeout.open("closeCounter.txt");
			closeout << closeCounter;
			closein.clear();
			closein.seekg(0, ios::beg);
			closein >> closeCounter;
			closeout.close();
			fout << "!" << endl;
			fin2.close();
			fout.close();
			fin.close();
		}
		cout << "open | show day | show all | buy day | stat | stat all | close | end" << endl;
		cin >> input;	

	}
	closein.close();
	closeout.close();
	closeCounter = -1;
	
	return 0;
}