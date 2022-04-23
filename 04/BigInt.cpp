#include "BigInt.hpp"

#include <iostream>
#include <string>
#include <stdint.h>


namespace custom
{

    BigInt BigInt::operator+(const BigInt & other) const
    {
        if (this->sign_ == Sign::pls && other.sign_ == Sign::zr)
            return *this;
        if (this->sign_ == Sign::zr)
            return other;


        if (this->sign_ == Sign::pls && other.sign_ == Sign::pls)
        {

            BigInt res;
            delete[] res.data_;
            res.sign_ = Sign::pls;
            size_t maximum = std::max(this->size_, other.size_);
            res.size_ = maximum + 1;
            res.data_ = new signed char[res.size_];
            for (size_t i = 0; i < res.size_; i++)
                res.data_[i] = 0;
            int carry = 0;
            for (size_t i = 0; i < maximum || carry != 0; ++i)
            {
                if (i < other.size_ && i < this->size_)
                    res.data_[i] = carry + this->data_[i] + other.data_[i];
                else if(i < other.size_)
                    res.data_[i] = carry + other.data_[i];
                else
                    res.data_[i] = carry + this->data_[i];

                carry = res.data_[i] >= 10;
                if (carry != 0) res.data_[i] -= 10;
            }
            if (res.data_[maximum] == 0)
            {
                BigInt result;
                delete[] result.data_;
                result.sign_ = Sign::pls;
                result.size_ = maximum;
                result.data_ = new signed char[res.size_];
                for (size_t i = 0; i < maximum; i++)
                    result.data_[i] = res.data_[i];
                return result;
            }
            else
                return res;
        }
        if (this->sign_ == Sign::pls && other.sign_ == Sign::mns)
        {
            BigInt res;
            delete[] res.data_;
            res.sign_ = Sign::pls;
            size_t maximum = std::max(this->size_, other.size_);
            size_t minimum = std::min(this->size_, other.size_);
            res.size_ = maximum;
            res.data_ = new signed char[res.size_];
            for (size_t i = 0; i < res.size_; i++)
                res.data_[i] = 0;
            int carry = 0;
            for (size_t i = 0; i < maximum || carry != 0; ++i)
            {
                if (i < minimum)
                    res.data_[i] = -carry + this->data_[i] - other.data_[i];
                else
                    res.data_[i] = -carry + this->data_[i];
                carry = res.data_[i] < 0;
                if (carry != 0) res.data_[i] += 10;
            }
            if (res.data_[maximum-1] == 0)
            {
                BigInt result;
                delete[] result.data_;
                result.sign_ = Sign::pls;
                result.size_ = maximum - 1;
                result.data_ = new signed char[res.size_];
                for (size_t i = 0; i < maximum - 1; i++)
                    result.data_[i] = res.data_[i];
                return result;
            }
            else
                return res;
        }
        BigInt tmp;
        return tmp;
    }


    BigInt::BigInt()
	{
		sign_ = Sign::zr;
		size_ = 1;
		data_ = new signed char[size_];
		data_[0] = 0;
	}

	BigInt::BigInt(int32_t number)
	{
		if (number > 0)
			sign_ = Sign::pls;
		else if (number == 0)
			sign_ = Sign::zr;
		else
			sign_ = Sign::mns;

		int64_t num = abs(number);

		for (size_ = 0; num > 0; size_++)
			num /= 10;
		if (number == 0)
			size_ = 1;

		data_ = new signed char[size_];

		num = abs(number);
		for (size_t i = 0; i < size_; i++)
		{
			data_[i] = num % 10;
			num /= 10;
		}
	}

	BigInt::BigInt(const std::string & number)
	{
		if (number.length() == 0)
			throw std::invalid_argument("len is 0");

		sign_ = Sign::pls;

		size_t i = 0;
		if (number[0] == '-')
		{
			sign_ = Sign::mns;
			i++;
		}

		for (size_t j = i; j < number.length(); j++)
		{
			if (number[j] < '0' || number[j] > '9')
			{
				sign_ = Sign::zr;
				throw std::invalid_argument("there are some other symbols");
			}
		}

		for (; i < number.length() && number[i] == '0'; i++);

		if (i == number.length())
		{
			sign_ = Sign::zr;
			i--;
		}

		size_ = number.length() - i;
		data_ = new signed char[size_];

		for (size_t j = 0; j < size_; j++)
			data_[j] = number[number.length() - j - 1] - '0';
	}

	BigInt::BigInt(const BigInt & other)
	{
		sign_ = other.sign_;
		size_ = other.size_;
		data_ = new signed char[size_];
		for (size_t i = 0; i < size_; i++)
			data_[i] = other.data_[i];
	}

	BigInt::BigInt(BigInt && other)
	{
		sign_ = other.sign_;
		size_ = other.size_;
		data_ = new signed char[size_];
		for (size_t i = 0; i < size_; i++)
			data_[i] = other.data_[i];

		other.sign_ = Sign::zr;
		other.size_ = 0;
		delete[] other.data_;
		other.data_ = nullptr;
	}

	BigInt::~BigInt()
	{
		if (data_)
			delete[] data_;
	}

	BigInt & BigInt::operator=(const BigInt & other)
	{
		if (this == &other)
			return *this;

		if (data_)
			delete[] data_;

		sign_ = other.sign_;
		size_ = other.size_;
		data_ = new signed char[size_];
		for (size_t i = 0; i < size_; i++)
			data_[i] = other.data_[i];

		return *this;
	}

    BigInt BigInt::pow(const BigInt & number, size_t pow)
    {
        BigInt res;
        delete[] res.data_;
        res.sign_ = number.sign_;
        res.size_ = number.size_ + pow;
        res.data_ = new signed char[res.size_];
        for (size_t i = 0; i < pow; i++)
            res.data_[i] = 0;
        for (size_t i = 0; i < number.size_; i++)
            res.data_[i + pow] = number.data_[i];
        return res;
    }

    BigInt & BigInt::operator=(BigInt && other)
    {
        if (this == &other)
            return *this;

        if (data_)
            delete[] data_;

        sign_ = other.sign_;
        size_ = other.size_;
        data_ = new signed char[size_];
        for (size_t i = 0; i < size_; i++)
            data_[i] = other.data_[i];

        other.sign_ = Sign::zr;
        other.size_ = 0;
        delete[] other.data_;
        other.data_ = nullptr;

        return *this;
    }

    BigInt BigInt::operator+(const int32_t & other) const
	{
		return *this + BigInt(other);
	}

	BigInt BigInt::operator-(const BigInt & other) const
	{
		return *this + (-other);
	}

	BigInt BigInt::operator-(const int32_t & other) const
	{
		return *this + (-BigInt(other));
	}

	BigInt BigInt::operator*(const BigInt & other) const
	{
		if (sign_ == Sign::mns && other.sign_ == Sign::mns)
			return (-(*this)) * (-other);
		if (sign_ == Sign::mns && other.sign_ == Sign::zr)
			return other;
		if (sign_ == Sign::mns && other.sign_ == Sign::pls)
			return -((-(*this)) * other);
		if (sign_ == Sign::zr)
			return *this;

		if (sign_ == Sign::pls && other.sign_ == Sign::mns)
			return -((*this) * (-other));
		if (sign_ == Sign::pls && other.sign_ == Sign::zr)
			return other;

		BigInt res;
		for (size_t i = 0; i < size_; i++)
		{
			BigInt term;
			for (size_t j = 0; j < size_t(data_[i]); j++)
				term = term + other;
			res = res + BigInt::pow(term, i);
		}

		return res;
	}

	BigInt BigInt::operator*(const int32_t & other) const
	{
		return *this * BigInt(other);
	}

	BigInt BigInt::operator-() const
	{
		BigInt res(*this);

		if (res.sign_ == Sign::pls)
			res.sign_ = Sign::mns;
		else if (res.sign_ == Sign::mns)
			res.sign_ = Sign::pls;

		return res;
	}

	bool BigInt::operator<(const BigInt & other) const
	{
		if (sign_ == Sign::mns && other.sign_ == Sign::mns)
			return -other < -(*this);
		if (sign_ == Sign::mns && other.sign_ == Sign::zr)
			return true;
		if (sign_ == Sign::mns && other.sign_ == Sign::pls)
			return true;

		if (sign_ == Sign::zr && other.sign_ == Sign::mns)
			return false;
		if (sign_ == Sign::zr && other.sign_ == Sign::zr)
			return false;
		if (sign_ == Sign::zr && other.sign_ == Sign::pls)
			return true;

		if (sign_ == Sign::pls && other.sign_ == Sign::mns)
			return false;
		if (sign_ == Sign::pls && other.sign_ == Sign::zr)
			return false;

		if (size_ < other.size_)
			return true;
		if (size_ > other.size_)
			return false;

		for (size_t i = 0; i < size_; i++)
		{
			if (data_[size_ - i - 1] < other.data_[size_ - i - 1])
				return true;
			if (data_[size_ - i - 1] > other.data_[size_ - i - 1])
				return false;
		}
		return false;
	}

	bool BigInt::operator<=(const BigInt & other) const
	{
		return !(other < *this);
	}

	bool BigInt::operator>(const BigInt & other) const
	{
		return other < *this;
	}

	bool BigInt::operator>=(const BigInt & other) const
	{
		return !(*this < other);
	}

	bool BigInt::operator==(const BigInt & other) const
	{
		return !(*this < other) && !(other < *this);
	}

	bool BigInt::operator!=(const BigInt & other) const
	{
		return *this < other || other < *this;
	}

	std::ostream & operator<<(std::ostream & os, const BigInt & num)
	{
		if (num.sign_ == BigInt::Sign::zr)
		{
			os << 0;
			return os;
		}

		if (num.sign_ == BigInt::Sign::mns)
			os << '-';
		for (size_t i = 0; i < num.size_; i++)
			os << char(num.data_[num.size_ - i - 1] + '0');
		return os;
	}
}
