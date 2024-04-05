/**
 * @file Student.h
 * @brief Student class declaration.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "Address.h"
#include "Enrollment.h"
#include <Poco/DateTime.h>

/**
 * @class Student
 * @brief Represents a student with personal data, address, and enrollments.
 */
class Student
{
private:
	static unsigned int nextMatrikelNumber; ///< Static counter for generating unique matrikel numbers.
	const unsigned int matrikelNumber; ///< Unique matrikel number for the student.
	std::string firstName; ///< Student's first name.
	std::string lastName; ///< Student's last name.
	Poco::DateTime dateOfBirth; ///< Student's date of birth.
	std::shared_ptr<Address> address; ///< Student's address.
	std::vector<Enrollment> enrollments; ///< List of student's course enrollments.

	/**
	 * @brief Converts a string to a Poco::DateTime object.
	 * @param dateString The date in string format to be converted.
	 * @return A Poco::DateTime object representing the date.
	 */
	static Poco::DateTime convertDate(std::string dateString);

public:
	/**
	 * @brief Constructs a Student object.
	 * @param fName Student's first name.
	 * @param lName Student's last name.
	 * @param dob Student's date of birth.
	 * @param addressIn Student's address.
	 */
	Student(const std::string fName, const std::string lName,
			const Poco::DateTime dob,
			const std::shared_ptr<Address> &addressIn);

	unsigned int getMatrikelNumber() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	Poco::DateTime getDateOfBirth() const;
	void setFirstName(std::string firstName);
	void setLastName(std::string lastName);
	void setDateOfBirth(Poco::DateTime dateOfBirth);
	std::shared_ptr<Address> getAddress() const;
	std::vector<Enrollment> getEnrollments() const;

	/**
	 * @brief Adds a new enrollment to the student's record.
	 * @param newEnrollment The enrollment to add.
	 */
	void setEnrollments(const Enrollment &newEnrollment);

	/**
	 * @brief Updates the student's address.
	 * @param newAddress The new address.
	 */
	void setAddress(const std::shared_ptr<Address> &newAddress);

	/**
	 * @brief Updates the grade for a specific course enrollment.
	 * @param courseKey The course key identifying the enrollment.
	 * @param newGrade The new grade to set.
	 */
	void updateGradeForCourse(unsigned int courseKey, float newGrade);

	/**
	 * @brief Deletes an enrollment based on the course key.
	 * @param courseKey The course key of the enrollment to delete.
	 */
	void deleteEnrollment(unsigned int courseKey);

	/**
	 * @brief Writes the student's data to an output stream.
	 * @param out Output stream reference.
	 */
	void write(std::ostream &out) const;

	/**
	 * @brief Reads student data from an input stream and creates a Student object.
	 * @param in Input stream reference.
	 * @return A Student object.
	 */
	static Student read(std::istream &in);

	/**
	 * @brief Destructor for the Student class.
	 */
	virtual ~Student();
};

#endif /* STUDENT_H_ */
