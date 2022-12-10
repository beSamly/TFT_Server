#include "pch.h"
#include "InputValidator.h"

bool InputValidator::IsEmail(std::string email)
{
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, pattern);
}

bool InputValidator::IsValidPassword(std::string password)
{
	const int MIN_LENGTH = 8;
	const int MAX_LENGTH = 15;

	bool meetsLengthRequirements = password.size() >= MIN_LENGTH && password.size() <= MAX_LENGTH;
	bool hasUpperCaseLetter = false;
	bool hasLowerCaseLetter = false;
	bool hasDecimalDigit = false;

	if (meetsLengthRequirements)
	{
		for (auto& c : password)
		{
			if (isupper(c)) hasUpperCaseLetter = true;
			else if (islower(c)) hasLowerCaseLetter = true;
			else if (isdigit(c)) hasDecimalDigit = true;

			if (hasUpperCaseLetter && hasLowerCaseLetter && hasDecimalDigit) {
				return true;
			}
		}
	}

	bool isValid = meetsLengthRequirements
		&& hasUpperCaseLetter
		&& hasLowerCaseLetter
		&& hasDecimalDigit
		;
	return isValid;
}
