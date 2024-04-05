/**
 * @file SimpleUI.h
 * @brief SimpleUI class declaration for interacting with the student database.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <memory>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <Poco/DateTime.h>
#include <boost/asio.hpp>
#include <string>
#include <boost/json.hpp>
#include <cctype>
#include <algorithm>
#include "StudentDb.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

/**
 * @class SimpleUI
 * @brief Manages the user interface for interacting with the student database.
 *
 * This class provides methods for adding courses and students, enrolling students in courses,
 * printing student information, searching for students, updating student records, and managing
 * data persistence through file operations. It leverages Poco for date/time operations and Boost
 * for network communication and JSON parsing.
 */
class SimpleUI
{
private:
	StudentDb &studentDb; ///< Reference to the student database for data management.

	/**
	 * @brief Converts a string to a Poco::Data::Date object.
	 * @param dateString The date in string format to be converted.
	 * @return A Poco::Data::Date object representing the date.
	 */
	Poco::Data::Date convertDate(const std::string dateString);

	/**
	 * @brief Converts a string to a Poco::Data::Time object.
	 * @param timeString The time in string format to be converted.
	 * @return A Poco::Data::Time object representing the time.
	 */
	Poco::Data::Time convertTime(const std::string timeString);

	/**
	 * @brief Converts a string to a Poco::DateTime::DaysOfWeek enum value.
	 * @param dayString The day in string format to be converted.
	 * @return A Poco::DateTime::DaysOfWeek enum value representing the day of the week.
	 */
	Poco::DateTime::DaysOfWeek convertDay(const std::string dayString);

	/**
	 * @brief Converts a string representing date and time to a Poco::DateTime object.
	 * @param dateTimeString The date and time in string format to be converted.
	 * @return A Poco::DateTime object representing the specified date and time.
	 */
	Poco::DateTime convertDateTimeDate(const std::string dateTimeString);

	/**
	 * @brief Adds a new course to the database.
	 */
	void addNewCourse();

	/**
	 * @brief Lists all courses in the database.
	 */
	void listCourses();

	/**
	 * @brief Adds a new student to the database.
	 */
	void addNewStudent();

	/**
	 * @brief Enrolls a student in a course.
	 */
	void addEnrollment();

	/**
	 * @brief Prints information of a specific student.
	 */
	void printStudent();

	/**
	 * @brief Searches for a student in the database.
	 */
	void searchStudent();

	/**
	 * @brief Updates information of a specific student.
	 */
	void updateStudent();

	/**
	 * @brief Writes the current state of the database to a file.
	 */
	void writeToFile();

	/**
	 * @brief Reads the database state from a file and updates the current database.
	 */
	void readFromFile();

	/**
	 * @brief Generates random student data for testing purposes.
	 */
	void generateStudentData();

	/**
	 * @brief Parses string data to extract student or course information.
	 * @param str The string containing data to be parsed.
	 */
	void parseData(std::string str);

	/**
	 * @brief Checks the validity of the input data for a new student
	 * @param firstName Student's first name.
	 * @param lastName Student's last name.
	 * @param street Student's street address.
	 * @param postalCode Student's postal code.
	 * @param city Student's city.
	 * @param additionalInfo Any additional information.
	 * @return True if the data is valid, false otherwise.
	 */
	bool checkData(std::string firstName, std::string lastName,
			std::string street, std::string postalCode, std::string city,
			std::string additionalInfo);

public:
	/**
	 * @brief Constructs a SimpleUI object with a reference to a StudentDb.
	 * @param db Reference to the student database to manage.
	 */
	SimpleUI(StudentDb &db);

	/**
	 * @brief Initiates the user interaction loop.
	 */
	void run();

	/**
	 * @brief Destructor for SimpleUI.
	 */
	virtual ~SimpleUI();
};

#endif /* SIMPLEUI_H_ */
