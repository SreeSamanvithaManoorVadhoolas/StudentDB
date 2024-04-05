/**
 * @file Course.h
 * @brief Course class declaration.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <map>
#include <string>
#include <fstream>
#include <memory>

/**
 * @class Course
 * @brief Abstract base class for course information.
 */
class Course
{
private:
	unsigned int courseKey; ///< Unique identifier for the course.
	std::string title; ///< Title of the course.
	unsigned char major; ///< Major code associated with the course.
	float creditPoints; ///< Number of credit points for the course.
	static std::map<unsigned char, std::string> majorById; ///< Static map to hold major codes by ID.

public:
	/**
	 * @brief Constructs a Course object.
	 * @param courseKey Unique course identifier.
	 * @param title Title of the course.
	 * @param major Major associated with the course.
	 * @param creditPoints Credit points of the course.
	 */
	Course(unsigned int courseKey, const std::string title,
			const std::string major, float creditPoints);

	/**
	 * @brief Returns the major of the course.
	 * @return Major as a string.
	 */
	std::string getMajor() const;

	/**
	 * @brief Returns the unique course key.
	 * @return Course key as an unsigned integer.
	 */
	unsigned int getCourseKey() const;

	/**
	 * @brief Returns the title of the course.
	 * @return Title as a string.
	 */
	std::string getTitle() const;

	/**
	 * @brief Returns the credit points of the course.
	 * @return Credit points as a float.
	 */
	float getCreditPoints() const;

	/**
	 * @brief Writes course details to an output stream.
	 * @param out Output stream reference.
	 */
	virtual void write(std::ostream &out) const;

	/**
	 * @brief Reads course details from an input stream and creates a Course object.
	 * @param in Input stream reference.
	 * @return Unique pointer to a Course object.
	 */
	static std::unique_ptr<Course> read(std::istream &in);

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Course() = 0;
};

#endif /* COURSE_H_ */
