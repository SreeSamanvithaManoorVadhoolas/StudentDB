/**
 * @file WeeklyCourse.cpp
 * @brief WeeklyCourse class implementation.
 * @date 24-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "WeeklyCourse.h"

WeeklyCourse::WeeklyCourse(unsigned int courseKey, const std::string major,
		const std::string title, unsigned int creditPts,
		const Poco::DateTime::DaysOfWeek day, const Poco::Data::Time sTime,
		const Poco::Data::Time eTime) :
		Course(courseKey, title, major, creditPts), daysOfWeek(day), startTime(
				sTime), endTime(eTime)
{
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDayOfWeek() const
{
	return this->daysOfWeek;
}

Poco::Data::Time WeeklyCourse::getStartTime() const
{
	return this->startTime;
}

Poco::Data::Time WeeklyCourse::getEndTime() const
{
	return this->endTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	out << ";" << this->getDayOfWeek();
	out << ";" << std::setfill('0') << std::setw(2)
			<< this->getStartTime().hour() << ":" << std::setfill('0')
			<< std::setw(2) << this->getStartTime().minute();
	out << ";" << std::setfill('0') << std::setw(2) << this->getEndTime().hour()
			<< ":" << std::setfill('0') << std::setw(2)
			<< this->getEndTime().minute() << std::endl;

}

std::unique_ptr<Course> WeeklyCourse::read(std::istream &in)
{
	unsigned int courseKey;
	std::string title, major;
	unsigned int creditPoints;
	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Time startTime, endTime;

	std::string inp;
	std::getline(in, inp, ';');
	courseKey = static_cast<unsigned int>(std::stoi(inp));
//	std::cout << "coursekey: " << courseKey << std::endl;

	std::getline(in, title, ';');
//	std::cout << "title: " << title << std::endl;

	std::getline(in, major, ';');
//	std::cout << "major: " << major << std::endl;

	std::getline(in, inp, ';');
	creditPoints = static_cast<unsigned int>(std::stoi(inp));
//	std::cout << "creditPoints: " << creditPoints << std::endl;

	std::getline(in, inp, ';');
	dayOfWeek = convertDay(inp);
//	std::cout << "dayOfWeek: " << dayOfWeek << std::endl;

	std::getline(in, inp, ';');
	startTime = convertTime(inp);
//	std::cout << "startTime: " << startTime.hour() << ":" << startTime.minute()
//			<< std::endl;

	std::getline(in, inp);
	endTime = convertTime(inp);
//	std::cout << "endTime: " << endTime.hour() << ":" << endTime.minute()
//			<< std::endl;

	auto courses =
			std::make_unique < WeeklyCourse
					> (courseKey, major, title, creditPoints, dayOfWeek, startTime, endTime);

	return courses;

}

Poco::DateTime::DaysOfWeek WeeklyCourse::convertDay(std::string day)
{

	if (day == "1")
		return Poco::DateTime::DaysOfWeek::MONDAY;
	if (day == "2")
		return Poco::DateTime::DaysOfWeek::TUESDAY;
	if (day == "3")
		return Poco::DateTime::DaysOfWeek::WEDNESDAY;
	if (day == "4")
		return Poco::DateTime::DaysOfWeek::THURSDAY;
	if (day == "5")
		return Poco::DateTime::DaysOfWeek::FRIDAY;
	if (day == "6")
		return Poco::DateTime::DaysOfWeek::SATURDAY;
	if (day == "0")
		return Poco::DateTime::DaysOfWeek::SUNDAY;
	return Poco::DateTime::DaysOfWeek::SUNDAY;

}

Poco::Data::Time WeeklyCourse::convertTime(std::string timeString)
{
	int hour, minute, second = 0;
	sscanf(timeString.c_str(), "%d:%d", &hour, &minute);
	return Poco::Data::Time(hour, minute, second);

}

WeeklyCourse::~WeeklyCourse()
{
	// TODO Auto-generated destructor stub
}
