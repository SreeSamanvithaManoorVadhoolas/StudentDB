/**
 * @file Enrollment.cpp
 * @brief Enrollment class implementation.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "Enrollment.h"

Enrollment::Enrollment(Course *course, const std::string semester) :
		course(course), semester(semester), grade(0.0f)
{
}

Course* Enrollment::getCourse() const
{
	return this->course;
}

std::string Enrollment::getSemester() const
{
	return this->semester;
}

float Enrollment::getGrade() const
{
	return this->grade;
}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

void Enrollment::write(std::ostream &out) const
{
	out << this->course->getCourseKey() << ";" << this->getSemester() << ";";
	out << std::fixed << std::setprecision(1) << this->getGrade() << std::endl;
}

Enrollment Enrollment::read(std::istream &in)
{
	Course *course = nullptr;
	std::string semester;
	float grade;
	std::string inp;
	std::getline(in, semester, ';');
	std::getline(in, inp);
	grade = std::stof(inp);
	Enrollment eObj(course, semester);
	eObj.setGrade(grade);
	return eObj;
}

Enrollment::~Enrollment()
{
	// TODO Auto-generated destructor stub
}

