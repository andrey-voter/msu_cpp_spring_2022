#include <iostream>

#include "serializer.hpp"


namespace my_namespace
{
	Serializer::Serializer() : out_(nullptr) { }


	Serializer::Serializer(std::ostream & out) : out_(&out) { }


	Error Serializer::operator()()
	{
		return Error::Ok;
	}


	Error Serializer::process(bool arg)
	{
		(*out_) << std::boolalpha << arg << Separator;
		return Error::Ok;
	}


	Error Serializer::process(uint64_t arg)
	{
		(*out_) << arg << Separator;
		return Error::Ok;
	}


	Deserializer::Deserializer() : in_(nullptr) { }


	Deserializer::Deserializer(std::istream & in): in_(&in) { }


	Error Deserializer::operator()()
	{
		return Error::Ok;
	}


	Error Deserializer::process(bool & arg)
	{
		std::string text;
		(*in_) >> text;

		if (text == "true")
			arg = true;
		else if (text == "false")
			arg = false;
		else
			return Error::Spoiled;

		return Error::Ok;
	}


	Error Deserializer::process(uint64_t & arg)
	{
		std::string text;
		(*in_) >> text;

		if (text.length() == 0)
			return Error::Spoiled;

		for (auto c : text)
			if (c < '0' || c > '9')
				return Error::Spoiled;

		size_t i = 0;
		for (; i < text.length() - 1 && text[i] == 0; ++i);
		text = text.substr(i, text.length() - i);

		if (text.length() >= 20 && text > "18446744073709551615")
			return Error::Spoiled;

		std::stringstream sst;
		sst << text;
		sst >> arg;

		return Error::Ok;
	}
}