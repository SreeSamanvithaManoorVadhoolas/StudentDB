/**
 * @file WeeklyCourse.h
 * @brief WeeklyCourse class declaration for courses scheduled on a weekly basis.
 * @date 24-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include <iomanip>
#include <memory>
#include "Poco/DateTime.h"
#include "Poco/Data/Time.h"
#include "Course.h"

/**
 * @class WeeklyCourse
 * @brief Extends Course with specific day and times for weekly courses.
 */
class WeeklyCourse: public Course
{
private:
	Poco::DateTime::DaysOfWeek daysOfWeek; ///< Day of the week the course occurs.
	Poco::Data::Time startTime; ///< Start time of the course.
	Poco::Data::Time endTime; ///< End time of the course.

	/**
	 * @brief Converts a string to a Poco::DateTime::DaysOfWeek.
	 * @param day String representation of the day.
	 * @return Corresponding Poco::DateTime::DaysOfWeek value.
	 */
	static Poco::DateTime::DaysOfWeek convertDay(std::string day);

	/**
	 * @brief Converts a string to a Poco::Data::Time.
	 * @param timeString String representation of the time.
	 * @return Poco::Data::Time object.
	 */
	static Poco::Data::Time convertTime(std::string timeString);

public:
	/**
	 * @brief Constructor for WeeklyCourse.
	 * @param courseKey Unique identifier for the course.
	 * @param major Major associated with the course.
	 * @param title Title of the course.
	 * @param creditPts Credit points awarded for the course.
	 * @param day Day of the week the course is held.
	 * @param sTime Start time of the course.
	 * @param eTime End time of the course.
	 */
	WeeklyCourse(unsigned int courseKey, const std::string major,
			const std::string title, unsigned int creditPts,
			const Poco::DateTime::DaysOfWeek day, const Poco::Data::Time sTime,
			const Poco::Data::Time eTime);

	/**
	 * @brief Gets the day of the week the course is held.
	 * @return The day of the week as Poco::DateTime::DaysOfWeek.
	 */
	Poco::DateTime::DaysOfWeek getDayOfWeek() const;

	/**
	 * @brief Gets the start time of the course.
	 * @return Start time as Poco::Data::Time.
	 */
	Poco::Data::Time getStartTime() const;

	/**
	 * @brief Gets the end time of the course.
	 * @return End time as Poco::Data::Time.
	 */
	Poco::Data::Time getEndTime() const;

	/**
	 * @brief Writes course details to an output stream. Overrides Course::write.
	 * @param out Output stream reference.
	 */
	void write(std::ostream &out) const override;

	/**
	 * @brief Reads course details from an input stream and creates a WeeklyCourse object.
	 * @param in Input stream reference.
	 * @return Unique pointer to a Course object.
	 */
	static std::unique_ptr<Course> read(std::istream &in);

	/**
	 * @brief Destructor for WeeklyCourse.
	 */
	virtual ~WeeklyCourse();
};

#endif /* WEEKLYCOURSE_H_ */
