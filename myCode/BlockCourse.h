/**
 * @file BlockCourse.h
 * @brief BlockCourse class declaration.
 * @date 24-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include <iomanip>
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"
#include "Course.h"

/**
 * @class BlockCourse
 * @brief Extends Course with specific dates and times for block courses.
 */
class BlockCourse: public Course
{
private:
	Poco::Data::Date startDate; ///< Course start date.
	Poco::Data::Date endDate; ///< Course end date.
	Poco::Data::Time startTime; ///< Course start time.
	Poco::Data::Time endTime; ///< Course end time.

	/**
	 * @brief Converts string to Poco::Data::Date.
	 * @param dateString String representation of a date.
	 * @return Poco::Data::Date object.
	 */
	static Poco::Data::Date convertDate(std::string dateString);

	/**
	 * @brief Converts string to Poco::Data::Time.
	 * @param timeString String representation of a time.
	 * @return Poco::Data::Time object.
	 */
	static Poco::Data::Time convertTime(std::string timeString);

public:
	/**
	 * @brief Constructor for BlockCourse.
	 * @param courseKey Unique course identifier.
	 * @param majorStr Major associated with the course.
	 * @param title Course title.
	 * @param creditPts Credit points of the course.
	 * @param startD Start date of the course.
	 * @param endD End date of the course.
	 * @param startT Start time of the course.
	 * @param endT End time of the course.
	 */
	BlockCourse(unsigned int courseKey, const std::string majorStr,
			const std::string title, unsigned int creditPts,
			const Poco::Data::Date startD, const Poco::Data::Date endD,
			const Poco::Data::Time startT, const Poco::Data::Time endT);

	/**
	 * @brief Gets the start date of the course.
	 * @return Start date.
	 */
	Poco::Data::Date getStartDate() const;

	/**
	 * @brief Gets the end date of the course.
	 * @return End date.
	 */
	Poco::Data::Date getEndDate() const;

	/**
	 * @brief Gets the start time of the course.
	 * @return Start time.
	 */
	Poco::Data::Time getStartTime() const;

	/**
	 * @brief Gets the end time of the course.
	 * @return End time.
	 */
	Poco::Data::Time getEndTime() const;

	/**
	 * @brief Writes course details to an output stream.
	 * @param out Output stream reference.
	 */
	void write(std::ostream &out) const override;

	/**
	 * @brief Reads course details from an input stream and creates a BlockCourse object.
	 * @param in Input stream reference.
	 * @return Unique pointer to a Course object.
	 */
	static std::unique_ptr<Course> read(std::istream &in);

	/**
	 * @brief Destructor for BlockCourse.
	 */
	virtual ~BlockCourse();
};

#endif /* BLOCKCOURSE_H_ */
