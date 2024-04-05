/**
 * @file Address.h
 * @brief Address class declaration.
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <fstream>
#include <memory>

/**
 * @class Address
 * @brief Manages physical address details.
 */
class Address
{
private:
	const std::string street; ///< Street name.
	unsigned short postalCode; ///< Postal code.
	const std::string city; ///< City name.
	const std::string additionalInfo; ///< Additional address info.

public:
	/**
	 * @brief Constructs an Address object.
	 * @param street Street name.
	 * @param postalCode Postal code.
	 * @param city City name.
	 * @param additionalInfo Additional information.
	 */
	Address(const std::string street, unsigned short postalCode,
			const std::string city, const std::string additionalInfo);

	/**
	 * @brief Returns street name.
	 * @return Street name as a string.
	 */
	std::string getStreet() const;

	/**
	 * @brief Returns postal code.
	 * @return Postal code as unsigned short.
	 */
	unsigned short getPostalCode() const;

	/**
	 * @brief Returns city name.
	 * @return City name as a string.
	 */
	std::string getCity() const;

	/**
	 * @brief Returns additional information.
	 * @return Additional info as a string.
	 */
	std::string getAdditionalInfo() const;

	/**
	 * @brief Writes address to an output stream.
	 * @param out Output stream reference.
	 */
	void write(std::ostream &out) const;

	/**
	 * @brief Reads address from an input stream.
	 * @param in Input stream reference.
	 * @return Address object pointer.
	 */
	static std::shared_ptr<Address> read(std::istream &in);

	/**
	 * @brief Destructs the Address object.
	 */
	virtual ~Address();
};

#endif /* ADDRESS_H_ */
