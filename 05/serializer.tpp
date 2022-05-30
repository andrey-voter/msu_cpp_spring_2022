#pragma once

#include <iostream>
#include <sstream>

#include "serializer.hpp"


namespace my_namespace
{
	template<typename Type>
	Error Serializer::save(Type & object, typename std::enable_if<is_serializable<Type>::value>::type*)
	{
		try
		{
			return object.serialize(*this);
		}
		catch (...)
		{
			return Error::CantSerialize;
		}
	}


	template<typename Type>
	Error Serializer::save(Type &, typename std::enable_if<!is_serializable<Type>::value>::type*)
	{
		return Error::CantSerialize;
	}


	template<typename Type>
	Error Serializer::operator()(Type arg)
	{
		return process(arg);
	}


	template<typename Type, typename... Types>
	Error Serializer::operator()(Type arg, Types... args)
	{
		Error err = process(arg);
		if (err != Error::Ok)
			return err;
		return (*this)(args...);
	}


	template<typename Type>
	Error Serializer::process(Type)
	{
		return Error::CantSerialize;
	}


	template<typename Type>
	Error Deserializer::load(Type & object, typename std::enable_if<is_deserializable<Type>::value>::type*)
	{
		try
		{
			Error err = object.deserialize(*this);
			std::string(std::istreambuf_iterator<char>(*in_), {});
			if (std::string(std::istreambuf_iterator<char>(*in_), {}) != "")
				return Error::Spoiled;
			return err;
		}
		catch (...)
		{
			return Error::CantSerialize;
		}
	}


	template<typename Type>
	Error Deserializer::load(Type &, typename std::enable_if<!is_deserializable<Type>::value>::type*)
	{
		return Error::CantSerialize;
	}


	template<typename Type>
	Error Deserializer::operator()(Type & arg)
	{
		return process(arg);
	}


	template<typename Type, typename... Types>
	Error Deserializer::operator()(Type & arg, Types&... args)
	{
		Error err = process(arg);
		if (err != Error::Ok)
			return err;
		return (*this)(args...);
	}


	template<typename Type>
	Error Deserializer::process(Type &)
	{
		return Error::CantSerialize;
	}
}