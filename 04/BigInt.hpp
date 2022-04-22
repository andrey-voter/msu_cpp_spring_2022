#pragma once

#include <iostream>
#include <string>
#include <stdint.h>


namespace custom
{
	class BigInt
	{
	private:
		enum class Sign {mns, zr, pls};
	public:
		BigInt();

		BigInt(int32_t number);

		BigInt(const std::string & number);

		BigInt(const BigInt & other);

		BigInt(BigInt && other);

		~BigInt();

		BigInt & operator=(const BigInt & other);

		BigInt & operator=(BigInt && other);

		BigInt operator+(const BigInt & other) const;

		BigInt operator+(const int32_t & other) const;

		BigInt operator-(const BigInt & other) const;

		BigInt operator-(const int32_t & other) const;

		BigInt operator*(const BigInt & other) const;

		BigInt operator*(const int32_t & other) const;

		BigInt operator-() const;

		bool operator<(const BigInt & other) const;

		bool operator<=(const BigInt & other) const;

		bool operator>(const BigInt & other) const;

		bool operator>=(const BigInt & other) const;

		bool operator==(const BigInt & other) const;

		bool operator!=(const BigInt & other) const;

		friend std::ostream & operator<<(std::ostream & os, const BigInt & num);

	private:
		static BigInt pow(const BigInt & number, size_t pow);

	private:
		Sign sign_ = Sign::zr;
		size_t size_ = 0;
		signed char * data_ = nullptr;
	};

	std::ostream & operator<<(std::ostream & os, const BigInt & num);
}