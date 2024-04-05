/**
 * @file StudentDb.h
 * @brief StudentDb class declaration for managing student and course data.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include "Address.h"
#include "Student.h"
#include "Enrollment.h"
#include "Course.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

/**
 * @class StudentDb
 * @brief Manages a database of students and courses.
 */
class StudentDb
{
private:
	std::map<int, Student> students; ///< Stores student records indexed by matrikel number.
	std::map<int, std::unique_ptr<Course>> courses; ///< Stores courses, allowing polymorphic course management.

	/**
	 * @brief Clears the current state of the database, removing all students and courses.
	 */
	void clearDatabase();

public:
	/**
	 * @brief Initializes a new Student Database.
	 */
	StudentDb();

	/**
	 * @brief Determines if a course exists in the database.
	 * @param courseKey The unique identifier for the course.
	 * @return True if the course is found, false otherwise.
	 */
	bool courseExists(int courseKey) const;

	/**
	 * @brief Checks for the existence of a student by their matrikel number.
	 * @param matrikelNumber The student's unique identifier.
	 * @return True if the student exists, false otherwise.
	 */
	bool matrikelNumberExists(int matrikelNumber) const;

	/**
	 * @brief Retrieves the courses map.
	 * @return A reference to the map storing unique pointers to Course objects.
	 */
	std::map<int, std::unique_ptr<Course>>& getCourses();

	/**
	 * @brief Retrieves a copy of the students map.
	 * @return A map of student objects indexed by their matrikel numbers.
	 */
	std::map<int, Student> getStudents() const;

	/**
	 * @brief Adds a new BlockCourse to the database.
	 */
	void addBlockedCourse(unsigned int courseKey, const std::string majorStr,
			const std::string title, unsigned int creditPts,
			const Poco::Data::Date startD, const Poco::Data::Date endD,
			const Poco::Data::Time startT, const Poco::Data::Time endT);

	/**
	 * @brief Adds a new WeeklyCourse to the database.
	 */
	void addWeeklyCourse(unsigned int courseKey, const std::string majorStr,
			const std::string title, unsigned int creditPts,
			const Poco::DateTime::DaysOfWeek dayOfWeek,
			const Poco::Data::Time startT, const Poco::Data::Time endT);

	/**
	 * @brief Registers a new student in the database.
	 */
	void addStudent(const std::string fName, const std::string lName,
			const Poco::DateTime dob, const std::string street,
			unsigned short postalCode, const std::string city,
			const std::string additionalInfo);

	/**
	 * @brief Enrolls a student in a specified course.
	 */
	void addEnrollment(unsigned int matrikelNumber, unsigned int courseKey,
			const std::string semester);

	/**
	 * @brief Updates the name of an existing student.
	 */
	void updateName(unsigned int matrikelNumber, const std::string fName,
			const std::string lName);

	/**
	 * @brief Updates the date of birth for an existing student.
	 */
	void updateDOB(unsigned int matrikelNumber, const Poco::DateTime dob);

	/**
	 * @brief Updates the address for an existing student.
	 */
	void updateAddress(unsigned int matrikelNumber, const std::string street,
			unsigned short postalCode, const std::string city,
			const std::string additionalInfo);

	/**
	 * @brief Updates the grade for a student's enrollment in a specific course.
	 */
	void updateGrade(unsigned int matrikelNumber, unsigned int courseKey,
			float grade);

	/**
	 * @brief Removes an enrollment for a student in a specific course.
	 */
	void deleteEnrollment(unsigned int matrikelNumber, unsigned int courseKey);

	/**
	 * @brief Serializes the database to an output stream.
	 * @param out The output stream to write data to.
	 */
	void write(std::ostream &out);

	/**
	 * @brief Deserializes data from an input stream to populate the database.
	 * @param in The input stream from which to read data.
	 * @return True if the operation is successful, otherwise false.
	 */
	bool read(std::istream &in);

	/**
	 * @brief Destructs the StudentDb object, freeing up resources.
	 */
	virtual ~StudentDb();
};

#endif /* STUDENTDB_H_ */
