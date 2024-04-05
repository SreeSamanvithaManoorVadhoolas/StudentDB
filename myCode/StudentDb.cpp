/**
 * @file StudentDb.cpp
 * @brief StudentDb class implementation.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "StudentDb.h"

StudentDb::StudentDb()
{
	// TODO Auto-generated constructor stub

}

void StudentDb::addBlockedCourse(unsigned int courseKey,
		const std::string majorStr, const std::string title,
		unsigned int creditPts, const Poco::Data::Date startD,
		const Poco::Data::Date endD, const Poco::Data::Time startT,
		const Poco::Data::Time endT)
{

	this->courses.insert(
			std::make_pair(courseKey,
					std::make_unique < BlockCourse
							> (courseKey, majorStr, title, creditPts, startD, endD, startT, endT)));

}

bool StudentDb::courseExists(int courseKey) const
{
	return this->courses.find(courseKey) != this->courses.end();
}

void StudentDb::addWeeklyCourse(unsigned int courseKey,
		const std::string majorStr, const std::string title,
		unsigned int creditPts, const Poco::DateTime::DaysOfWeek dayOfWeek,
		const Poco::Data::Time startT, const Poco::Data::Time endT)
{

	this->courses.insert(
			std::make_pair(courseKey,
					std::make_unique < WeeklyCourse
							> (courseKey, majorStr, title, creditPts, dayOfWeek, startT, endT)));

}

void StudentDb::addStudent(const std::string fName, const std::string lName,
		const Poco::DateTime dob, const std::string street,
		unsigned short postalCode, const std::string city,
		const std::string additionalInfo)
{
	auto addressPtr = std::make_shared<Address>(street, postalCode, city,
			additionalInfo);
	Student s1(fName, lName, dob, addressPtr);
	this->students.insert(std::make_pair(s1.getMatrikelNumber(), s1));
}

bool StudentDb::matrikelNumberExists(int matrikelNumber) const
{
	return this->students.find(matrikelNumber) != this->students.end();
}

void StudentDb::addEnrollment(unsigned int matrikelNumber,
		unsigned int courseKey, const std::string semester)
{
	auto &coursePtr = this->courses.at(courseKey);
	Enrollment newEnrollment(coursePtr.get(), semester);
	this->students.at(matrikelNumber).setEnrollments(newEnrollment);
}

std::map<int, std::unique_ptr<Course>>& StudentDb::getCourses()
{
	return this->courses;
}

std::map<int, Student> StudentDb::getStudents() const
{
	return this->students;
}

void StudentDb::updateName(unsigned int matrikelNumber, const std::string fName,
		const std::string lName)
{
	this->students.at(matrikelNumber).setFirstName(fName);
	this->students.at(matrikelNumber).setLastName(lName);
}

void StudentDb::updateDOB(unsigned int matrikelNumber, const Poco::DateTime dob)
{
	this->students.at(matrikelNumber).setDateOfBirth(dob);
}

void StudentDb::updateAddress(unsigned int matrikelNumber,
		const std::string street, unsigned short postalCode,
		const std::string city, const std::string additionalInfo)
{
	auto addressPtr = std::make_shared<Address>(street, postalCode, city,
			additionalInfo);
	this->students.at(matrikelNumber).setAddress(addressPtr);
}

void StudentDb::updateGrade(unsigned int matrikelNumber, unsigned int courseKey,
		float grade)
{
	this->students.at(matrikelNumber).updateGradeForCourse(courseKey, grade);
}

void StudentDb::deleteEnrollment(unsigned int matrikelNumber,
		unsigned int courseKey)
{
	this->students.at(matrikelNumber).deleteEnrollment(courseKey);
}

void StudentDb::write(std::ostream &out)
{
	out << this->getCourses().size() << std::endl;
	for (const auto &course : this->getCourses())
	{
		course.second->write(out);
	}
	size_t enrollmentSize = 0;
	out << this->getStudents().size() << std::endl;
	for (const auto &student : this->getStudents())
	{
		enrollmentSize += student.second.getEnrollments().size();
		out << student.first << ";";
		student.second.write(out);
	}
	out << enrollmentSize << std::endl;
	for (const auto &student : this->getStudents())
	{
		for (const auto &enrollment : student.second.getEnrollments())
		{
			out << student.first;
			out << ";";
			enrollment.write(out);
		}
	}

}
bool StudentDb::read(std::istream &in)
{
	clearDatabase();
	bool status = false;
	bool noCourses = false;
	bool studentDataExists = false;
	bool firstItr = true;
	//coursesCount
	int coursesCount;
	in >> coursesCount;
	in.ignore();
	for (int i = 0; i < coursesCount; ++i)
	{
		auto course = Course::read(in);
		if (course != nullptr)
		{
			auto courseKey = course->getCourseKey();
			if (!courseExists(courseKey))
			{
				this->courses.insert(
				{ courseKey, std::move(course) });
				status = true;
			}
		}
		else
		{
			noCourses = true;
			status = false;
			break;

		}
	}

	//studentsCount
	int studentsCount;

	if (noCourses)
		studentsCount = coursesCount;
	else
	{
		in >> studentsCount;
		in.ignore();
	}

	for (int i = 0; i < studentsCount; ++i)
	{
		std::string inp1;
		std::getline(in, inp1, ';');
		if (firstItr)
		{
			try
			{
				std::stoi(inp1);
				studentDataExists = true;
			} catch (std::invalid_argument &e)
			{
				return false;
			}
		}
		firstItr = false;

		if (!studentDataExists)
		{
			return false;
		}

		auto student = Student::read(in);
		this->students.insert(
				std::make_pair(student.getMatrikelNumber(), student));
		status = true;

	}

	if (studentDataExists && !noCourses)
	{
		//enrollments
		int enrollments;
		unsigned int matrikelNumber;
		std::string inp;
		unsigned int courseKey;
		std::string semester;
		float grade;

		in >> enrollments;
		in.ignore();
		for (int i = 0; i < enrollments; ++i)
		{
			std::getline(in, inp, ';');
			matrikelNumber = static_cast<unsigned int>(std::stoi(inp));

			std::getline(in, inp, ';');
			courseKey = static_cast<unsigned int>(std::stoi(inp));

			auto eObj = Enrollment::read(in);
			semester = eObj.getSemester();
			grade = eObj.getGrade();

			if (matrikelNumberExists(matrikelNumber) && courseExists(courseKey))
			{
				this->addEnrollment(matrikelNumber, courseKey, semester);
				updateGrade(matrikelNumber, courseKey, grade);
				status = true;

			}
			else
			{
				status = false;
			}
		}
	}

	return status;
}
void StudentDb::clearDatabase()
{
	this->courses.clear();
	this->students.clear();

}
StudentDb::~StudentDb()
{
	// TODO Auto-generated destructor stub
}
