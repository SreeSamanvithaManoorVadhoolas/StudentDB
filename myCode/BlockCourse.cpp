/**
 * @file BlockCourse.cpp
 * @brief BlockCourse class implementation.
 * @date 24-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "BlockCourse.h"

BlockCourse::BlockCourse(unsigned int courseKey, const std::string majorStr,
		const std::string title, unsigned int creditPts,
		const Poco::Data::Date startD, const Poco::Data::Date endD,
		const Poco::Data::Time startT, const Poco::Data::Time endT) :
		Course(courseKey, title, majorStr, creditPts), startDate(startD), endDate(
				endD), startTime(startT), endTime(endT)
{
}

Poco::Data::Date BlockCourse::convertDate(std::string dateString)
{
	int year, month, day;
	sscanf(dateString.c_str(), "%d.%d.%d", &day, &month, &year);
	return Poco::Data::Date(year, month, day);
}

Poco::Data::Time BlockCourse::convertTime(std::string timeString)
{
	int hour, minute, second = 0;
	sscanf(timeString.c_str(), "%d:%d", &hour, &minute);
	return Poco::Data::Time(hour, minute, second);
}

Poco::Data::Date BlockCourse::getStartDate() const
{
	return this->startDate;
}

Poco::Data::Date BlockCourse::getEndDate() const
{
	return this->endDate;
}

Poco::Data::Time BlockCourse::getStartTime() const
{
	return this->startTime;
}

Poco::Data::Time BlockCourse::getEndTime() const
{
	return this->endTime;
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write(out);
	out << ";" << this->startDate.day() << "." << this->startDate.month() << "."
			<< this->startDate.year() << ";" << this->endDate.day() << "."
			<< this->endDate.month() << "." << this->endDate.year() << ";"
			<< std::setfill('0') << std::setw(2) << this->startTime.hour()
			<< ":" << std::setfill('0') << std::setw(2)
			<< this->startTime.minute() << ";" << std::setfill('0')
			<< std::setw(2) << this->endTime.hour() << ":" << std::setfill('0')
			<< std::setw(2) << this->endTime.minute() << std::endl;
}

std::unique_ptr<Course> BlockCourse::read(std::istream &in)
{
	unsigned int courseKey;
	std::string title, major;
	unsigned int creditPoints;
	Poco::Data::Date startDate, endDate;
	Poco::Data::Time startTime, endTime;
	std::string inp;
	std::getline(in, inp, ';');
	courseKey = static_cast<unsigned int>(std::stoi(inp));

	std::getline(in, title, ';');

	std::getline(in, major, ';');

	std::getline(in, inp, ';');
	creditPoints = static_cast<unsigned int>(std::stoi(inp));

	std::getline(in, inp, ';');
	startDate = convertDate(inp);

	std::getline(in, inp, ';');
	endDate = convertDate(inp);

	std::getline(in, inp, ';');
	startTime = convertTime(inp);
	std::getline(in, inp);
	endTime = convertTime(inp);
	auto courses =
			std::make_unique < BlockCourse
					> (courseKey, major, title, creditPoints, startDate, endDate, startTime, endTime);

	return courses;

}

BlockCourse::~BlockCourse()
{
	// TODO Auto-generated destructor stub
}
