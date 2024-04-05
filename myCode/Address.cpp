/**
 * @file Address.cpp
 * @brief Address class implementation.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#include "Address.h"

Address::Address(const std::string street, unsigned short postalCode,
		const std::string city, const std::string additionalInfo) :
		street(street), postalCode(postalCode), city(city), additionalInfo(
				additionalInfo)
{
}

std::string Address::getStreet() const
{
	return street;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

std::string Address::getCity() const
{
	return city;
}

std::string Address::getAdditionalInfo() const
{
	return additionalInfo;
}

void Address::write(std::ostream &out) const
{
	out << this->getStreet() << ";" << this->getPostalCode() << ";"
			<< this->getCity() << ";";
	if (!this->getAdditionalInfo().empty())
	{
		out << this->getAdditionalInfo();
	}
}

std::shared_ptr<Address> Address::read(std::istream &in)
{
	std::string street;
	unsigned short postalCode;
	std::string city;
	std::string additionalInfo;
	std::string inp;
	std::getline(in, street, ';');
	std::getline(in, inp, ';');
	postalCode = static_cast<unsigned int>(std::stoi(inp));
	std::getline(in, city, ';');
	std::getline(in, additionalInfo);

	auto addrPtr = std::make_shared<Address>(street, postalCode, city,
			additionalInfo);
	return addrPtr;
}

Address::~Address()
{
	// TODO Auto-generated destructor stub
}
