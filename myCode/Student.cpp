/**
 * @file Student.cpp
 * @brief Student class implementation.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "Student.h"

unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(const std::string fName, const std::string lName,
		const Poco::DateTime dob, const std::shared_ptr<Address> &addressIn) :
		matrikelNumber(nextMatrikelNumber++), firstName(fName), lastName(lName), dateOfBirth(
				dob), address(addressIn)
{
}

Poco::DateTime Student::convertDate(std::string dateString)
{
	int year, month, day;
	sscanf(dateString.c_str(), "%d.%d.%d", &day, &month, &year);
	return Poco::DateTime(year, month, day);
}
unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

std::string Student::getFirstName() const
{
	return firstName;
}

std::string Student::getLastName() const
{
	return lastName;
}

Poco::DateTime Student::getDateOfBirth() const
{
	return dateOfBirth;
}

void Student::setFirstName(std::string firstNameIN)
{
	this->firstName = firstNameIN;
}

void Student::setLastName(std::string lastNameIN)
{
	this->lastName = lastNameIN;
}

void Student::setDateOfBirth(Poco::DateTime dateOfBirthIN)
{
	this->dateOfBirth = dateOfBirthIN;
}
std::shared_ptr<Address> Student::getAddress() const
{
	return this->address;
}

std::vector<Enrollment> Student::getEnrollments() const
{
	return this->enrollments;
}

void Student::setAddress(const std::shared_ptr<Address> &newAddress)
{
	this->address = newAddress;
}

void Student::setEnrollments(const Enrollment &newEnrollment)
{
	this->enrollments.push_back(newEnrollment);
}

void Student::updateGradeForCourse(unsigned int courseKey, float newGrade)
{
	for (auto &enrollment : this->enrollments)
	{
		if (enrollment.getCourse()->getCourseKey() == courseKey)
		{
			enrollment.setGrade(newGrade);
			return;
		}
	}
}

void Student::deleteEnrollment(unsigned int courseKey)
{
	for (auto it = this->enrollments.begin(); it != this->enrollments.end();
			++it)
	{
		if (it->getCourse()->getCourseKey() == courseKey)
		{
			this->enrollments.erase(it);
			return;
		}
	}
}

void Student::write(std::ostream &out) const
{
	out << this->getFirstName() << ";" << this->getLastName() << ";"
			<< this->getDateOfBirth().day() << "."
			<< this->getDateOfBirth().month() << "."
			<< this->getDateOfBirth().year() << ";";
	this->getAddress()->write(out);
	out << std::endl;
}

Student Student::read(std::istream &in)
{
	std::string firstName;
	std::string lastName;
	Poco::DateTime dateOfBirth;
	std::shared_ptr<Address> address;
	std::string inp;
	std::getline(in, firstName, ';');
	std::getline(in, lastName, ';');
	std::getline(in, inp, ';');
	dateOfBirth = convertDate(inp);
	address = Address::read(in);
	Student sObj(firstName, lastName, dateOfBirth, address);
	return sObj;

}

Student::~Student()
{
	// TODO Auto-generated destructor stub
}
