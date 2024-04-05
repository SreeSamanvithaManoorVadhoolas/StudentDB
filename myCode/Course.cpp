/**
 * @file Course.cpp
 * @brief Course class implementation.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "Course.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

using namespace std;
std::map<unsigned char, std::string> Course::majorById =
{
{ 'A', "Automation" },
{ 'C', "Communication" },
{ 'E', "Embedded" },
{ 'G', "General" },
{ 'P', "Power" }, };

Course::Course(unsigned int courseKey, const std::string title,
		const std::string major, float creditPoints) :
		courseKey(courseKey), title(title), creditPoints(creditPoints)
{
	for (const auto &pair : majorById)
	{
		if (pair.second == major)
		{
			this->major = pair.first;
			break;
		}
	}
}

std::string Course::getMajor() const
{
	auto it = majorById.find(major);
	if (it != majorById.end())
	{
		return it->second;
	}
	return "";
}

std::unique_ptr<Course> Course::read(std::istream &in)
{
	char type;
	in >> type;
	in.ignore();
	std::unique_ptr<Course> course;

	if (type == 'W')
	{
		course = WeeklyCourse::read(in);
	}
	else if (type == 'B')
	{
		course = BlockCourse::read(in);
	}
	else
	{
		return nullptr;
	}
	return course;
}

unsigned int Course::getCourseKey() const
{
	return this->courseKey;
}

std::string Course::getTitle() const
{
	return this->title;
}

float Course::getCreditPoints() const
{
	return this->creditPoints;
}

void Course::write(std::ostream &out) const
{
	out << this->getCourseKey() << ";" << this->getTitle() << ";"
			<< this->getMajor() << ";" << this->getCreditPoints();
}

Course::~Course()
{
	// TODO Auto-generated destructor stub
}

