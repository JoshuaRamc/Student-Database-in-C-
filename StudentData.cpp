#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <climits>
#include <sstream>
#include <ctype.h>
#include "StudentData.h"
using namespace std;


vector<string> MyParser::operator() (string& s)
{
	string editforoperator = s;

	//checking for too many quotes inside userinput
	int quote_count = 0;
	for (int y = 0; y < editforoperator.length(); y++)
	{

		if (editforoperator[y] == '"')
		{
			quote_count++;
		}
		if (quote_count > 2)
		{
			//cerr << "bad command!!!" << endl;
		}
	}

	string charRemoved = "";
	for (int x = 0; x < editforoperator.length(); x++)
	{
		if (editforoperator[x] != '>' and editforoperator[x] != '=' and editforoperator[x] != '<')
			charRemoved = charRemoved + editforoperator[x];
		else
			charRemoved = charRemoved + " " + editforoperator[x] + " ";
	}
	//cout << "charRemoved: " << charRemoved << endl;


	string str = charRemoved;
	int n = str.length();

	int i = 0, j = -1;

	// flag that sets to true is space is found with !spaceFound
	bool spaceFound = false;

	// Handles leading spaces
	while (j++ < n && str[j] == ' ');

	// read all characters of original string
	while (j < n)
	{
		// if current characters is non-space
		if (str[j] != ' ')
		{
			// remove preceding spaces before dot,
			// comma & question mark
			if ((str[j] == '.' || str[j] == ',' ||
				str[j] == '?') && i - 1 >= 0 &&
				str[i - 1] == ' ')
				str[i - 1] = str[j++];

			else
				// copy current character at index i
				// and increment both i and j
				str[i++] = str[j++];

			// set space flag to false when any
			// non-space character is found
			spaceFound = false;
		}
		else if (str[j++] == ' ')
		{
			if (!spaceFound)
			{
				str[i++] = ' ';
				spaceFound = true;
			}
		}
	}

	// Remove trailing spaces
	if (i <= 1)
	{
		str.erase(str.begin() + i, str.end());
	}
	else
	{
		if (str[i - 1] == ' ')
		{
			str.erase(str.begin() + i - 1, str.end());
		}
		else
		{
			str.erase(str.begin() + i, str.end());
		}

	}
	int quote_count2 = 0;
	char c = '"';
	for (int r = 0; r < str.size(); r++)
	{
		if (str[r] == '"')
		{
			quote_count2++;
		}
	}
	// cout << "Spaces Removed: " << str << endl;
 //  cout << "quote_count2: " << quote_count2 << endl;
	string element;
	vector<string> v;
	//Stores new string in vector based on single spaces and removes quotations.
	for (int i = 0; i < str.length(); ++i)
	{
		int count = 0;
		if (str[i] == ' ')
		{
			v.push_back(element);
			element = "";
		}
		else if (str[i] == '"' && quote_count2 == 2)
		{
			continue;
		}
		else
		{
			element.push_back(str[i]);
		}

	}
	v.push_back(element);

	//Additional Parsing based on type of command
	if (v[0] == "ADD" && quote_count2 == 2)
	{
		if (v.size() >= 5)
		{
			v[2] = v[2] + ' ' + v[3];
			v[3] = v[4];
			v.pop_back();
		}
	}

	if (v[0] == "REMOVE" && quote_count2 == 2)
	{
		if (v.size() >= 5)
		{
			v[3] = v[3] + ' ' + v[4];
			v.pop_back();
		}
	}

	if (v[0] == "FIND" && quote_count2 == 2)
	{
		if (v.size() >= 5)
		{
			v[3] = v[3] + ' ' + v[4];
			v.pop_back();
		}
	}

	//This Additional Parsing Is specifically only for HardDisk class.
	if (isdigit(v[0][0]) && v.size() == 4)
	{
		v[1] = v[1] + ' ' + v[2];
		v[2] = v[3];
		v.pop_back();
	}

	 // for(int i = 0; i < v.size(); i++)
	 //  cout << v[i] << endl;
	return v;

}

//constructor
MyParser::MyParser() {}

Student::Student(unsigned int student_id, std::string student_name, unsigned short student_age)
{
	id = student_id;
	name = student_name;
	age = student_age;
}

//Student Getters
unsigned int Student::GetStudentID() const
{
	return id;
}

string Student::GetStudentName() const
{
	return name;
}

unsigned short Student::GetStudentAge() const
{
	return age;
}



// void MyManager::setVector(std::vector<Student*> fromFile)
// {
//   for(int x{0}; x < fromFile.size(); x++)
//     {
//       student_tracker.push_back(fromFile[x]);
//     }

// }

MyManager::MyManager() {}

std::vector<Student*> MyManager::GetPreviousVector()
{
	return student_tracker;
}

bool MyManager::process(std::vector<std::string> v)
{
	if (v[0] == "ADD")
	{
		if (MyManager::AddErrorCheck(v) == false)
		{
			cerr << "bad command!!!" << endl;
		}
		else if (MyManager::AddErrorCheck(v) == true)
		{
			unsigned int tempstudent_id;
			unsigned short tempstudent_age;
			string for_id_conversion = v[1];
			string for_age_conversion = v[3];
			string tempname = v[2];
			tempstudent_id = stoi(for_id_conversion);
			tempstudent_age = stoi(for_age_conversion);
			MyManager::ADD(tempstudent_id, tempname, tempstudent_age);
		}
		
		return false;
	}

	else if (v[0] == "FIND")
	{
		if (MyManager::FindErrorCheck(v) == false)
		{
			cerr << "bad command!!!" << endl;
		}

		else if (MyManager::FindErrorCheck(v) == true)
		{
			string temp_parameter_specify = v[1];
			string temp_relationship_operator = v[2];

			string temp_third_operation = "";
			int if_third_is_num = 0;
			int letter_counter = 0;
			for (int i = 0; i < v[3].size(); i++)
			{
				if (isalpha(v[3][i]) or v[3][i] == ' ' or v[3][i] == ',' or v[3][i] == '.')
				{
					letter_counter++;
				}
			}
			//if we find that third paramater in FIND is fully string.
			if (letter_counter == v[3].size())
			{
				temp_third_operation = v[3];
			}
			else if (letter_counter != v[3].size() and letter_counter > 0)
			{
				cerr << "bad command!!!" << endl;
			}
			//in the case of it being an int such as age or ID
			else {
				string in_case_of_int = v[3];
				if_third_is_num = stoi(in_case_of_int);
			}

			if (temp_parameter_specify == "age")
			{
				if (temp_third_operation != "")
				{
					cerr << "bad command!!!" << endl;
					temp_parameter_specify = "";
				}
				else if (temp_parameter_specify == "id")
				{
					if (temp_third_operation != "")
					{
						cerr << "bad command!!!" << endl;
						temp_parameter_specify = "";
					}
				}
			}
			MyManager::FIND(temp_parameter_specify, temp_relationship_operator, temp_third_operation, if_third_is_num);
		}
		
		return false; //check later

	}

	else if (v[0] == "REMOVE")
	{
		if (MyManager::RemoveErrorCheck(v) == false)
		{
			cerr << "bad command!!!" << endl;
		}

		else if (MyManager::RemoveErrorCheck(v) == true)
		{
			string temp_parameter_specify = v[1];
			string temp_relationship_operator = v[2];

			string temp_third_operation = "";
			int if_third_is_num = 0;
			int letter_counter = 0;
			for (int i = 0; i < v[3].size(); i++)
			{
				if (isalpha(v[3][i]) or v[3][i] == ' ' or v[3][i] == ',' or v[3][i] == '.')
				{
					letter_counter++;
				}
			}
		//if we find that third paramater in FIND is fully string.
			if (letter_counter == v[3].size())
			{
				temp_third_operation = v[3];
			}
			else if (letter_counter != v[3].size() and letter_counter > 0)
			{
				cerr << "bad command!!!" << endl;
			}
		//in the case of it being an int such as age or ID
			else {
				string in_case_of_int = v[3];
				if_third_is_num = stoi(in_case_of_int);
			}
			MyManager::REMOVE(temp_parameter_specify, temp_relationship_operator, temp_third_operation, if_third_is_num);
		}
		return false;
	}
	else if (v[0] == "STOP" && v.size() == 1)
	{
		MyManager::STOP();
		return true;
	}
	else {
		cerr << "bad command!!!" << endl;
		return false;
	}
	return false;
}

bool MyManager::AddErrorCheck(std::vector<std::string> v)
{
	int error_counter = 0;
  if(v.size() != 4)
  {
      error_counter++;
  }
	for (int i = 0; i < v[1].size(); i++)
	{
		if (v[1][i] != '1' and v[1][i] != '2' and v[1][i] != '3' and v[1][i] != '4' and v[1][i] != '5' and v[1][i] != '6' and v[1][i] != '7' and v[1][i] != '8' and v[1][i] != '9' and v[1][i] != '0')
		{
			error_counter++;
		}
	}

	for (int j = 0; j < v[2].size(); j++)
	{
		if (isalpha(v[2][j]))
		{
			continue;
		}
		else if (v[2][j] == ' ')
		{
			continue;
		}
		else if (v[2][j] == '-')
		{
			continue;
		}
    else if (v[2][j] == ',')
    {
      continue;
    }
    else if (v[2][j] == '.')
    {
      continue;
    }
		else {
			error_counter++;
		}
	}


	if (v[3].size() > 3)
	{
		error_counter++;
	}

	for (int x = 0; x < v[3].size(); x++)
	{
		if (v[3][x] != '1' and v[3][x] != '2' and v[3][x] != '3' and v[3][x] != '4' and v[3][x] != '5' and v[3][x] != '6' and v[3][x] != '7' and v[3][x] != '8' and v[3][x] != '9' and v[3][x] != '0')
		{
			error_counter++;
		}
	}
	if (error_counter == 0)
	{
		return true;

	}
	else {
		cerr << "bad command!!!" << endl;
		return false;
	}

}

bool MyManager::FindErrorCheck(std::vector<std::string> v)
{
	int error_counter = 0;
  if(v.size() != 4)
  {
    error_counter++;
  }
	if (v[1] != "id" and v[1] != "age" and v[1] != "name")
	{
		error_counter++;
	}
	if (v[2] != "=" and v[2] != "<" and v[2] != ">")
	{
		error_counter++;
	}

  if(v[1] == "id" or v[1] == "age")
  {
    for(int x = 0; x < v[3].size(); x++)
    {
      if (v[3][x] != '1' and v[3][x] != '2' and v[3][x] != '3' and v[3][x] != '4' and v[3][x] != '5' and v[3][x] != '6' and v[3][x] != '7' and v[3][x] != '8' and v[3][x] != '9' and v[3][x] != '0')
		  {
			  error_counter++;
		  }
    }
  }

  if(v[1] == "name")
  {
    for (int j = 0; j < v[3].size(); j++)
	  {
		  if (isalpha(v[3][j]))
		  {
			  continue;
		  }
		  else if (v[3][j] == ' ')
		  {
			  continue;
		  }
		  else if (v[3][j] == '-')
		  {
			  continue;
		  }
      else if (v[3][j] == ',')
      {
        continue;
      }
      else if(v[3][j] == '.')
      {
        continue;
      }
		  else {
			  error_counter++;
		  }
	  }
  }
	if (error_counter == 0)
	{
		return true;
	}
	else {
		//cerr << "bad command!!!" << endl;
		return false;
	}
}

bool MyManager::RemoveErrorCheck(std::vector<std::string> v)
{
	int error_counter = 0;
  if(v.size() != 4)
  {
    error_counter++;
  }
	if (v[1] != "id" and v[1] != "age" and v[1] != "name")
	{
		error_counter++;
	}
	if (v[2] != "=" and v[2] != "<" and v[2] != ">")
	{
		error_counter++;
	}

  if(v[1] == "id" or v[1] == "age")
  {
    for(int x = 0; x < v[3].size(); x++)
    {
      if (v[3][x] != '1' and v[3][x] != '2' and v[3][x] != '3' and v[3][x] != '4' and v[3][x] != '5' and v[3][x] != '6' and v[3][x] != '7' and v[3][x] != '8' and v[3][x] != '9' and v[3][x] != '0')
		  {
			  error_counter++;
		  }
    }
  }

  if(v[1] == "name")
  {
    for (int j = 0; j < v[3].size(); j++)
	  {
		  if (isalpha(v[3][j]))
		  {
			  continue;
		  }
		  else if (v[3][j] == ' ')
		  {
			  continue;
		  }
		  else if (v[3][j] == '-')
		  {
			  continue;
		  }
      else if (v[3][j] == ',')
      {
        continue;
      }
      else if(v[3][j] == '.')
      {
        continue;
      }
		  else {
			  error_counter++;
		  }
	  }
  }
  

	if (error_counter == 0)
	{
		return true;
	}
	else {
		//cout << "bad command!!!" << endl;
		return false;
	}
}


void MyManager::ADD(unsigned int student_ID, std::string name, unsigned short age)
{
	Student* student_ptr = new Student(student_ID, name, age);
	student_tracker.push_back(student_ptr);
}

void MyManager::REMOVE(string parameter_specify, string relationship_operator, string name, int value)
{
	if (parameter_specify == "name")
	{
		for (int i{ 0 }; i < student_tracker.size(); i++)
		{
			if (student_tracker[i]->GetStudentName() == name)
			{
				student_tracker.erase(student_tracker.begin() + i);
        i--;
			}
		}
	}
	else if (parameter_specify == "age")
	{
		if (relationship_operator == ">")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentAge() > value)
				{
					student_tracker.erase(student_tracker.begin() + i);
          i--;
				}
			}
		}
		else if (relationship_operator == "<")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentAge() < value)
				{
					student_tracker.erase(student_tracker.begin() + i);
          i--;
				}
			}
		}
		else if (relationship_operator == "=")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentAge() == value)
				{
					student_tracker.erase(student_tracker.begin() + i);
          i--;
				}
			}

		}
	}
	else if (parameter_specify == "id")
	{
		if (relationship_operator == "=")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentID() == value)
				{
					student_tracker.erase(student_tracker.begin() + i);
          i--;
				}
			}
		}
		else if (relationship_operator == ">")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentID() > value)
				{
					student_tracker.erase(student_tracker.begin() + i);
          i--;
				}
			}
		}
		else if (relationship_operator == "<")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentID() < value)
				{
					student_tracker.erase(student_tracker.begin() + i);
          i--;
				}
			}
		}
	}
}
void MyManager::FIND(string parameter_specify, string relationship_operator, string name, int value)
{
	if (parameter_specify == "name")
	{
		if (relationship_operator != "=")
		{
			cerr << "bad command!!!" << endl;
		}
		else
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{

				if (student_tracker[i]->GetStudentName() == name)
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
			}
		}
	}
	else if (parameter_specify == "age")
	{
		if (relationship_operator != ">" && relationship_operator != "<" && relationship_operator != "=")
		{
			cerr << "bad command!!!" << endl;
		}
		//NOW LETS CHECK operators. 
		else if (relationship_operator == ">")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentAge() > value) //liststudents.begin() + (i-1); i-= 1
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
				// else{
				//   cerr << "bad command!!!" << endl;
				// }
			}
		}
		else if (relationship_operator == "<")
		{
			for (int i{ 0 }; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentAge() < value)
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
			}
		}
		else if (relationship_operator == "=")
		{
			for (int i = 0; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentAge() == value)
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
			}

		}
	}
	else if (parameter_specify == "id")
	{
		if (relationship_operator != ">" && relationship_operator != "<" && relationship_operator != "=")
		{
			cerr << "bad command!!!" << endl;
		}
		else if (relationship_operator == "=")
		{
			for (int i = 0; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentID() == value)
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
			}
		}
		else if (relationship_operator == ">")
		{
			for (int i = 0; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentID() > value)
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
			}
		}
		else if (relationship_operator == "<")
		{
			for (int i = 0; i < student_tracker.size(); i++)
			{
				if (student_tracker[i]->GetStudentID() < value)
				{
					cout << student_tracker[i]->GetStudentID() << "  " << student_tracker[i]->GetStudentName() << " " << student_tracker[i]->GetStudentAge() << endl;
				}
			}
		}
	}
}


void MyManager::STOP()
{
	DiskManager p;
	p.write_file(student_tracker);
	exit(1);
}

MyManager::~MyManager() {}

//
DiskManager::DiskManager()
{
	filename = "ListOfStudents.txt";
	// std::vector<Student*> listStudents;
	// fstream MYfile;
	// MYfile.open(filename, std::ios::out);
	// MYfile.close();
}

void DiskManager::write_file(std::vector<Student*> write)
{
	fstream myFile;
	myFile.open(filename, ios::out);
	if (myFile.is_open())
	{
		for (int i{ 0 }; i < write.size(); i++)
		{
			int quotecase = 0;
			for (int j{ 0 }; j < write[i]->GetStudentName().size(); j++)
			{
				if (isspace(write[i]->GetStudentName()[j]))
				{
					myFile << write[i]->GetStudentID() << " \"" << write[i]->GetStudentName() << "\" " << write[i]->GetStudentAge() << endl;
					quotecase++;
				}
				else {
					continue;
				}
			}
			if (quotecase == 1)
			{
				quotecase = 0;
			}
			else {
				myFile << write[i]->GetStudentID() << " " << write[i]->GetStudentName() << " " << write[i]->GetStudentAge() << endl;
			}
		}
	}
}
std::vector<std::string> DiskManager::read_file()
{
	MyParser parser;
	MyManager engine;
	//create a vector to store into if they open and close program
	std::vector<std::string> existing;
	std::fstream MyFile;
	MyFile.open(filename, std::ios::in);

	if (MyFile.is_open())
	{
		std::string line;
		while (getline(MyFile, line))
		{
			//cout << line << endl;
			std::string operation = "ADD";
			std::string auto_add = operation + " " + line;
			existing.push_back(auto_add);

		}
		MyFile.close();
	}
	return existing;
	// for(int j = 0; j<temporary.size(); j++)
	// {
	//   cout << temporary->GetStudentID() << " " << temporary->GetStudentName() << " " temporary->GetStudentAge() << endl;
	// }
	// MyManager x;
	// x.setVector(temporary);
	//MyManager::setVector(temporary);


}

DiskManager::~DiskManager() {}

// int main()
// {
// 	// MyParser parser;
//  //  MyManager engine;
//  //  string user_command = "";
//  // cout << "Enter a string: " ;
//  //  getline(cin, user_command);
// 	// //string user_command = "   ADD     67412  Smith,John       21          ";
//  //  //string user_command = "   FIND    name=JOsh ";
//  //  //string user_command = "      ADD   87243333  "
// 	// vector<string> parsed_command;
// 	// parsed_command = parser(user_command);
// 	// for (int i = 0; i < parsed_command.size(); i++)
// 	// {
// 	// 	cout << parsed_command[i] << endl;
// 	// }

//   //engine.process(parser(user_command));
//   MyManager  engine;
//   MyParser  parser;

//     std::vector<char>  separators{' ', '\t'};
//     std::string  userInput;
//     bool  shouldStop{false};
//     while(!shouldStop)
//     {
//           getline(cin, userInput); // pay attention, pure cin doesn't allow spaces or tabs in userInput
//           shouldStop = engine.process( parser(userInput) );
//     }

//    return 0;
// }
