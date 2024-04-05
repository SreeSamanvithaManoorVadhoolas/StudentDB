/**
 * @file SimpleUI.cpp
 * @brief SimpleUI class implementation for interacting with the student database.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "SimpleUI.h"
#include <boost/json/src.hpp>

using namespace std;

SimpleUI::SimpleUI(StudentDb &db) :
		studentDb(db)
{
}

Poco::Data::Date SimpleUI::convertDate(const string dateString)
{
	int year, month, day;
	sscanf(dateString.c_str(), "%d.%d.%d", &day, &month, &year);
	try
	{
		Poco::Data::Date date(year, month, day);
		return date;
	} catch (const Poco::Exception &e)
	{
		throw invalid_argument(
				"Invalid date format. Expected format: DD.MM.YYYY");
	}
}

Poco::Data::Time SimpleUI::convertTime(const string timeString)
{
	int hour, minute, second = 0;
	sscanf(timeString.c_str(), "%d:%d", &hour, &minute);
	try
	{
		Poco::Data::Time time(hour, minute, second);
		return time;
	} catch (const Poco::Exception &e)
	{
		throw invalid_argument("Invalid time format. Expected format: HH::MM");
	}
}

Poco::DateTime::DaysOfWeek SimpleUI::convertDay(const string dayString)
{
	string day = dayString;
	for (char &i : day)
	{
		i = toupper(i);
	}
	if (day == "MONDAY")
		return Poco::DateTime::DaysOfWeek::MONDAY;
	if (day == "TUESDAY")
		return Poco::DateTime::DaysOfWeek::TUESDAY;
	if (day == "WEDNESDAY")
		return Poco::DateTime::DaysOfWeek::WEDNESDAY;
	if (day == "THURSDAY")
		return Poco::DateTime::DaysOfWeek::THURSDAY;
	if (day == "FRIDAY")
		return Poco::DateTime::DaysOfWeek::FRIDAY;
	if (day == "SATURDAY")
		return Poco::DateTime::DaysOfWeek::SATURDAY;
	if (day == "SUNDAY")
		return Poco::DateTime::DaysOfWeek::SUNDAY;
	return Poco::DateTime::DaysOfWeek::SUNDAY;
}

Poco::DateTime SimpleUI::convertDateTimeDate(const string dateString)
{
	int year, month, day;
	sscanf(dateString.c_str(), "%d.%d.%d", &day, &month, &year);

	try
	{
		Poco::DateTime date(year, month, day);
		return date;
	} catch (const Poco::Exception &e)
	{
		throw invalid_argument(
				"Invalid date format. Expected format: DD.MM.YYYY");
	}
}

void SimpleUI::run()
{
	int choice;
	do
	{
		cout << "\n1. Add new Course\n2. List courses\n3. Add new student\n"
				"4. Add enrollment\n5. Print student\n6. Search student\n"
				"7. Update student\n8. Write to file "
				"\n9. Read from file \n10. Generate server data"
				"\n0. Exit\nEnter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			addNewCourse();
			break;
		case 2:
			listCourses();
			break;
		case 3:
			addNewStudent();
			break;
		case 4:
			addEnrollment();
			break;
		case 5:
			printStudent();
			break;
		case 6:
			searchStudent();
			break;
		case 7:
			updateStudent();
			break;
		case 8:
			writeToFile();
			break;
		case 9:
			readFromFile();
			break;
		case 10:
			generateStudentData();
			break;

		case 0:
			cout << "Exiting..." << endl;
			break;

		default:
			cout << "Invalid option, try again.\n";
			break;
		}

	} while (choice != 0);
}

void SimpleUI::generateStudentData()
{
	unsigned int studentCount;
	cout << "Enter the number of students to generate data for: ";
	cin >> studentCount;

	boost::asio::ip::tcp::iostream stream;
	stream.connect("www.hhs.users.h-da.cloud", "4242");

	for (unsigned int i = 0; i < studentCount; i++)
	{

		stream << "generate" << endl;
		stream.flush();
		string line1, line2, line3;
		getline(stream, line1);
		getline(stream, line2);
		parseData(line2);

		getline(stream, line3);
	}
	stream << "quit" << endl;
	stream.flush();
}

void SimpleUI::addNewCourse()
{
	cout << "Enter course type\n1.BlockCourse\n2.WeeklyCourse\n";
	int choice;
	cin >> choice;

	unsigned int courseKey;
	string title;
	unsigned int majorChoice;
	string majorStr;
	float creditPoints;
	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Date startDate, endDate;
	Poco::Data::Time startTime, endTime;
	string inputDate, inputTime, inputDay;
	map<int, string> majors =
	{
	{ 1, "Automation" },
	{ 2, "Communication" },
	{ 3, "Embedded" },
	{ 4, "General" },
	{ 5, "Power" } };

	switch (choice)
	{
	case 1:
	{ //BlockCourse
		cout << "Enter course key: ";
		cin >> courseKey;
		if (!this->studentDb.courseExists(courseKey))
		{
			cout << "Enter title: ";
			cin.ignore();
			getline(cin, title);
			cout
					<< "Choose major 1.Automation 2.Communication 3.Embedded 4.General 5.Power: ";
			cin >> majorChoice;

			auto it = majors.find(majorChoice);
			if (it != majors.end())
			{
				majorStr = it->second;
				cout << "Enter credit points: ";
				cin >> creditPoints;

				cout << "Enter start date (DD.MM.YYYY): ";
				cin >> inputDate;
				try
				{
					startDate = convertDate(inputDate);
				} catch (const std::invalid_argument &e)
				{
					cout << "Date conversion failed: " << e.what() << std::endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),
							'\n');
					break;
				}

				cout << "Enter end date (DD.MM.YYYY): ";
				cin >> inputDate;

				try
				{
					endDate = convertDate(inputDate);
				} catch (const std::invalid_argument &e)
				{
					cout << "Date conversion failed: " << e.what() << std::endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),
							'\n');
					break;
				}

				cout << "Enter start time (HH:MM): ";
				cin >> inputTime;
				try
				{
					startTime = convertTime(inputTime);
				} catch (const std::invalid_argument &e)
				{
					cout << "Time conversion failed: " << e.what() << std::endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),
							'\n');
					break;
				}

				cout << "Enter end time (HH:MM): ";
				cin >> inputTime;

				try
				{
					endTime = convertTime(inputTime);
				} catch (const std::invalid_argument &e)
				{
					cout << "Time conversion failed: " << e.what() << std::endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),
							'\n');
					break;
				}

				this->studentDb.addBlockedCourse(courseKey, majorStr, title,
						creditPoints, startDate, endDate, startTime, endTime);

				cout << "Course successfully added." << endl;

			}
			else
			{
				cout << "Invalid Major choice." << endl;
			}

		}
		else
		{
			cout << "Course key already exists." << endl;
		}
		break;
	}
	case 2:
	{
		//WeeklyCourse
		cout << "Enter course key: ";
		cin >> courseKey;
		if (!this->studentDb.courseExists(courseKey))
		{
			cout << "Enter title: ";
			cin.ignore();
			getline(cin, title);
			cout
					<< "Choose major 1.Automation 2.Communication 3.Embedded 4.General 5.Power: ";
			cin >> majorChoice;
			auto it = majors.find(majorChoice);
			if (it != majors.end())
			{
				majorStr = it->second;
				cout << "Enter credit points: ";
				cin >> creditPoints;

				cout << "Enter day of the week: ";
				cin >> inputDay;
				dayOfWeek = convertDay(inputDay);
				cout << "Enter start time (HH:MM): ";
				cin >> inputTime;
				try
				{
					startTime = convertTime(inputTime);
				} catch (const std::invalid_argument &e)
				{
					cout << "Time conversion failed: " << e.what() << std::endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),
							'\n');
					break;
				}

				cout << "Enter end time (HH:MM): ";
				cin >> inputTime;

				try
				{
					endTime = convertTime(inputTime);
				} catch (const std::invalid_argument &e)
				{
					cout << "Time conversion failed: " << e.what() << std::endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(),
							'\n');
					break;
				}

				this->studentDb.addWeeklyCourse(courseKey, majorStr, title,
						creditPoints, dayOfWeek, startTime, endTime);

				cout << "Course successfully added." << endl;

			}
			else
			{
				cout << "Invalid Major choice." << endl;
			}
		}
		else
		{
			cout << "Course key already exists." << endl;
		}
		break;
	}
	default:
		cout << "Invalid option, try again.\n";
	}
}

void SimpleUI::listCourses()
{
	map<int, string> daysMap =
	{
	{ 0, "Sunday" },
	{ 1, "Monday" },
	{ 2, "Tuesday" },
	{ 3, "Wednesday" },
	{ 4, "Thursday" },
	{ 5, "Friday" },
	{ 6, "Saturday" } };
	const map<int, unique_ptr<Course>> &courses = this->studentDb.getCourses();
	if (courses.empty())
	{
		cout << "No courses available." << endl;
	}
	else
	{
		for (const auto &coursePair : courses)
		{
			const Course *course = coursePair.second.get();

			const BlockCourse *blockCourse =
					dynamic_cast<const BlockCourse*>(course);
			const WeeklyCourse *weeklyCourse =
					dynamic_cast<const WeeklyCourse*>(course);
			if (weeklyCourse != nullptr)
			{
				cout << endl;
				cout << "Type: WeeklyCourse\nCoursekey: " << coursePair.first
						<< "\nTitle:" << course->getTitle() << "\nMajor: "
						<< course->getMajor() << "\nCredits: "
						<< course->getCreditPoints() << "\nDay: "
						<< daysMap.at(weeklyCourse->getDayOfWeek())
						<< "\nStartTime: " << setfill('0') << setw(2)
						<< weeklyCourse->getStartTime().hour() << ":"
						<< setfill('0') << setw(2)
						<< weeklyCourse->getStartTime().minute()
						<< "\nEndTime: " << setfill('0') << setw(2)
						<< weeklyCourse->getEndTime().hour() << ":"
						<< setfill('0') << setw(2)
						<< weeklyCourse->getEndTime().minute() << endl;
			}
			else if (blockCourse != nullptr)
			{
				cout << endl;
				cout << "Type: BlockedCourse\nCoursekey: " << coursePair.first
						<< "\nTitle: " << course->getTitle() << "\nMajor: "
						<< course->getMajor() << "\nCredits: "
						<< course->getCreditPoints() << "\nStartDate: "
						<< setfill('0') << setw(2)
						<< blockCourse->getStartDate().day() << "."
						<< setfill('0') << setw(2)
						<< blockCourse->getStartDate().month() << "."
						<< blockCourse->getStartDate().year() << "\nEndDate: "
						<< setfill('0') << setw(2)
						<< blockCourse->getEndDate().day() << "."
						<< setfill('0') << setw(2)
						<< blockCourse->getEndDate().month() << "."
						<< blockCourse->getEndDate().year() << "\nStartTime: "
						<< setfill('0') << setw(2)
						<< blockCourse->getStartTime().hour() << ":"
						<< setfill('0') << setw(2)
						<< blockCourse->getStartTime().minute() << "\nEndTime: "
						<< setfill('0') << setw(2)
						<< blockCourse->getEndTime().hour() << ":"
						<< setfill('0') << setw(2)
						<< blockCourse->getEndTime().minute() << endl;
			}
			else
			{
				cout << "Issue in fetching courses." << endl;
			}
		}
	}
}

void SimpleUI::addNewStudent()
{
	string firstName;
	string lastName;
	string dob;
	Poco::DateTime dateOfBirth;
	string streetName;
	unsigned short postalCode;
	string city;
	string additionalInfo;
	cout << "Enter First Name: ";
	cin.ignore();
	getline(cin, firstName);
	cout << "Enter Last Name: ";
	getline(cin, lastName);
	cout << "Enter Date of Birth (DD.MM.YYYY): ";
	cin >> dob;

	try
	{
		dateOfBirth = convertDateTimeDate(dob);
	} catch (const std::invalid_argument &e)
	{
		cout << "Date conversion failed: " << e.what() << std::endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	cout << "Enter Address - Street name: ";
	cin.ignore();
	getline(cin, streetName);
	cout << "Enter Postal Code: ";
	cin >> postalCode;
	cout << "Enter City: ";
	cin.ignore();
	getline(cin, city);
	cout << "Enter Additional Info (Enter - or null for no Additional Info): ";
	getline(cin, additionalInfo);
	if (additionalInfo == "null" || additionalInfo == "-")
		additionalInfo = "";
	this->studentDb.addStudent(firstName, lastName, dateOfBirth, streetName,
			postalCode, city, additionalInfo);
	cout << "Student successfully added." << endl;
}

void SimpleUI::addEnrollment()
{
	unsigned int matrikelNumber;
	unsigned int courseKey;
	bool enrollmentExists = false;
	string semester;
	cout << "Enter matrikel number: ";
	cin >> matrikelNumber;
	if (this->studentDb.matrikelNumberExists(matrikelNumber))
	{
		cout << "Enter Course ID: ";
		cin >> courseKey;
		if (this->studentDb.courseExists(courseKey))
		{
			auto itr = this->studentDb.getStudents().find(matrikelNumber);
			for (auto &enrollment : itr->second.getEnrollments())
			{
				if (enrollment.getCourse()->getCourseKey() == courseKey)
				{
					enrollmentExists = true;
					break;
				}
			}
			if (!enrollmentExists)
			{
				cout << "Enter semester: ";
				cin >> semester;
				this->studentDb.addEnrollment(matrikelNumber, courseKey,
						semester);
				cout << "Enrollment successfully done." << endl;

			}
			else
			{
				cout << "Enrollment exists" << endl;
			}

		}
		else
		{
			cout << "Course doesn't exist" << endl;
		}
	}
	else
	{
		cout << "Matrikel Number doesn't exist" << endl;
	}

}

void SimpleUI::printStudent()
{
	const map<int, Student> students = this->studentDb.getStudents();
	if (!students.empty())
	{
		for (const auto &student : students)
		{
			const auto studentObj = student.second;
			const auto address = studentObj.getAddress();
			const auto enrollments = studentObj.getEnrollments();
			cout << "\nMatrikel Number: " << student.first << "\nFirst Name: "
					<< studentObj.getFirstName() << "\nLast Name: "
					<< studentObj.getLastName() << "\nDOB: " << setfill('0')
					<< setw(2) << studentObj.getDateOfBirth().day() << "."
					<< setfill('0') << setw(2)
					<< studentObj.getDateOfBirth().month() << "."
					<< studentObj.getDateOfBirth().year() << "\nAddress: "
					<< address->getStreet() << ", " << address->getPostalCode()
					<< ", " << address->getCity() << ", ";
			if (!address->getAdditionalInfo().empty())
				cout << address->getAdditionalInfo() << endl;

			if (!enrollments.empty())
			{
				for (const auto &enrollment : enrollments)
				{
					cout << "\nEnrollment Data\nCourse: "
							<< enrollment.getCourse()->getCourseKey()
							<< "\nSemester: " << enrollment.getSemester();

					if (enrollment.getGrade() != 0)
					{
						cout<< "\nGrade: ";
						cout << fixed << setprecision(1)
								<< enrollment.getGrade();
					}

				}
			}
			cout << endl;
		}
	}
	else
		(cout << "No students available.");

}

void SimpleUI::searchStudent()
{
	string searchStr;
	unsigned int found = 0;
	cout << "Enter search string: ";
	cin.ignore();
	getline(cin, searchStr);
	cout << "Search Results: " << endl;
	map<int, Student> students = this->studentDb.getStudents();
	for (const auto &student : students)
	{
		string fullName = student.second.getFirstName() + " "
				+ student.second.getLastName();
		if (fullName.find(searchStr) != string::npos)
		{
			cout << "\nFound: Matrikel Number: " << student.first << " Name: "
					<< student.second.getFirstName() << " "
					<< student.second.getLastName() << endl;
			++found;

		}
	}
	if (found == 0)
	{
		cout << "Not Found";
	}
	cout << endl;
}

void SimpleUI::updateStudent()
{
	unsigned int matrikelNumber;
	unsigned int choice;

	cout << "Enter Matrikel Number: ";
	cin >> matrikelNumber;
	if (this->studentDb.matrikelNumberExists(matrikelNumber))
	{
		cout << "1. Update Student Name"
				"\n2. Update Student DOB"
				"\n3. Update Student Address"
				"\n4. Update Student Enrollment Data"
				"\n0. Cancel Update"
				"\nEnter choice: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			cout << "Update Cancelled" << endl;
			break;
		case 1:
		{
			string firstName;
			string lastName;
			cout << "Enter First Name:";
			cin.ignore();
			getline(cin, firstName);
			cout << "Enter Last Name:";
			getline(cin, lastName);
			this->studentDb.updateName(matrikelNumber, firstName, lastName);
			cout << "Updated." << endl;
			break;
		}
		case 2:
		{
			string dob;
			Poco::DateTime dateOfBirth;
			cout << "Enter Date of Birth (DD.MM.YYYY): ";
			cin >> dob;
			try
			{
				dateOfBirth = convertDateTimeDate(dob);
			} catch (const std::invalid_argument &e)
			{
				cout << "Date conversion failed: " << e.what() << std::endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			this->studentDb.updateDOB(matrikelNumber, dateOfBirth);
			cout << "Updated." << endl;
			break;
		}
		case 3:
		{
			string streetName;
			unsigned short postalCode;
			string city;
			string additionalInfo;
			cout << "Enter Address - Street name: ";
			cin.ignore();
			getline(cin, streetName);
			cout << "Enter Postal Code: ";
			cin >> postalCode;
			cout << "Enter City: ";
			cin.ignore();
			getline(cin, city);
			cout << "Enter Additional Info (Enter - "
					"or null for no Additional Info): ";
			getline(cin, additionalInfo);
			if (additionalInfo == "null" || additionalInfo == "-")
				additionalInfo = "";
			this->studentDb.updateAddress(matrikelNumber, streetName,
					postalCode, city, additionalInfo);
			cout << "Updated." << endl;
			break;
		}
		case 4:
		{
			unsigned int courseKey;
			string semester;
			bool enrollmentExists = false;
			unsigned int option;
			float grade;
			cout << "Enter course ID: ";
			cin >> courseKey;
			auto itr = this->studentDb.getStudents().at(matrikelNumber);
			if (!this->studentDb.courseExists(courseKey))
			{
				cout << "Course doesn't exist." << endl;
				break;
			}
			for (auto &enrollment : itr.getEnrollments())
			{
				if (enrollment.getCourse()->getCourseKey() == courseKey)
				{
					enrollmentExists = true;
					break;
				}
			}

			if (!enrollmentExists)
			{
				cout << "Enrollment doesn't exist." << endl;
				break;
			}
			cout << "Enter choice 1. Delete enrollment 2. Update Grade: ";
			cin >> option;
			switch (option)
			{
			case 1:
			{
				this->studentDb.deleteEnrollment(matrikelNumber, courseKey);
				cout << "Deleted." << endl;
				break;
			}
			case 2:
			{
				cout << "Enter grade: ";
				cin >> grade;
				this->studentDb.updateGrade(matrikelNumber, courseKey, grade);
				cout << "Updated." << endl;
				break;
			}
			default:
				cout << "Invalid option selected." << endl;
				break;
			}

			break;
		}

		default:
			cout << "Invalid option selected." << endl;
			break;
		}

	}
	else
	{
		cout << "Matrikel Number doesn't exist." << endl;
	}
}

void SimpleUI::writeToFile()
{
	if (!(this->studentDb.getStudents().empty()
			&& this->studentDb.getCourses().empty()))
	{
		string fileName;
		cout << "Enter the name of the file to save data: ";
		cin >> fileName;

		ofstream outFile(fileName);
		if (!outFile.is_open())
		{
			cerr << "Error opening file for writing: " << fileName << endl;
			return;
		}
		this->studentDb.write(outFile);

		outFile.close();
		cout << "Data has been written to " << fileName << endl;
	}
	else
	{
		cout << "Database empty." << endl;
	}
}

void SimpleUI::readFromFile()
{
	string filePath;
	bool status;
	cout << "Enter the path to the CSV file to load data: ";
	cin.ignore();
	getline(std::cin, filePath);
	ifstream inFile(filePath);
	if (!inFile)
	{
		cerr << "Could not open file: " << filePath << std::endl;
		return;
	}
	status = this->studentDb.read(inFile);
	if (status)
		cout << "Data loaded successfully from " << filePath << std::endl;
	else
		cout << "Data loading failed.";

	inFile.close();
}

void SimpleUI::parseData(std::string str)
{
	boost::json::value parsedData = boost::json::parse(str);
	std::string firstName =
			parsedData.at("name").at("firstName").as_string().c_str();

	std::string lastName =
			parsedData.at("name").at("lastName").as_string().c_str();

	int date = parsedData.at("dateOfBirth").at("date").as_int64();
	int month = parsedData.at("dateOfBirth").at("month").as_int64() + 1;
	int year = parsedData.at("dateOfBirth").at("year").as_int64() + 1900;
	Poco::DateTime dateOfBirth = Poco::DateTime(year, month, date);

	std::string street =
			parsedData.at("location").at("street").as_string().c_str();
	std::string postal =
			parsedData.at("location").at("postCode").as_string().c_str();
	std::string city = parsedData.at("location").at("city").as_string().c_str();
	std::string additionalInfo =
			parsedData.at("location").at("state").as_string().c_str();
	if (checkData(firstName, lastName, street, postal, city, additionalInfo))
	{
		unsigned short postalCode = stoi(postal);
		this->studentDb.addStudent(firstName, lastName, dateOfBirth, street,
				postalCode, city, additionalInfo);
	}
}

bool SimpleUI::checkData(std::string firstName, std::string lastName,
		std::string street, std::string postalCode, std::string city,
		std::string additionalInfo)
{

	bool fName =
			std::all_of(firstName.begin(), firstName.end(), ::isalpha) ?
					true : false;
	bool lName =
			std::all_of(lastName.begin(), lastName.end(), ::isalpha) ?
					true : false;
	bool streetOK =
			std::all_of(street.begin(), street.end(), ::isprint) ? true : false;
	bool postal =
			std::all_of(postalCode.begin(), postalCode.end(), ::isdigit) ?
					true : false;
	bool cityOK =
			std::all_of(city.begin(), city.end(), ::isprint) ? true : false;
	bool additionalOK =
			std::all_of(additionalInfo.begin(), additionalInfo.end(),
					::isprint) ? true : false;
	if (fName && lName && streetOK && postal && postal && cityOK
			&& additionalOK)
	{
		return true;
	}

	return false;
}

SimpleUI::~SimpleUI()
{
// TODO Auto-generated destructor stub
}

