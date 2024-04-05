/**
 * @file Enrollment.h
 * @brief Enrollment class declaration.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include <iomanip>
#include <string>
#include "Course.h"

/**
 * @class Enrollment
 * @brief Represents a student's enrollment in a course.
 */
class Enrollment
{
private:
	Course *course; ///< Pointer to the course in which the student is enrolled.
	std::string semester; ///< The semester of enrollment.
	float grade; ///< The grade received in the course.

public:
	/**
	 * @brief Constructs an Enrollment object.
	 * @param course Pointer to the Course object.
	 * @param semester Semester of enrollment.
	 */
	Enrollment(Course *course, const std::string semester);

	/**
	 * @brief Returns the enrolled course.
	 * @return Pointer to the Course object.
	 */
	Course* getCourse() const;

	/**
	 * @brief Returns the semester of enrollment.
	 * @return Semester as a string.
	 */
	std::string getSemester() const;

	/**
	 * @brief Returns the grade received.
	 * @return Grade as a float.
	 */
	float getGrade() const;

	/**
	 * @brief Sets the grade for the enrollment.
	 * @param grade Grade received in the course.
	 */
	void setGrade(float grade);

	/**
	 * @brief Writes enrollment details to an output stream.
	 * @param out Output stream reference.
	 */
	void write(std::ostream &out) const;

	/**
	 * @brief Reads enrollment details from an input stream and creates an Enrollment object.
	 * @param in Input stream reference.
	 * @return Enrollment object.
	 */
	static Enrollment read(std::istream &in);

	/**
	 * @brief Destructor for Enrollment.
	 */
	virtual ~Enrollment();
};

#endif /* ENROLLMENT_H_ */
