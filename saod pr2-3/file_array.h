#pragma once

#include <fstream>
#include <string>
#include <exception>

template <typename T>
class File_array
{
private:
	class Utility;
public:
	File_array(std::string filename)
		: file(filename, std::ios::binary | std::ios::out | std::ios::in), utility(this->file)
	{
		if (!file.is_open())
			throw std::runtime_error(std::string("ERROR: the file cannot be opened"));

		file.seekg(0, file.end);
		this->utility.size = file.tellg();
		file.seekg(0, file.beg);
	}
	~File_array()
	{
		file.close();
	}

	/*set/get var from/into file*/
	Utility& operator[](unsigned long long pos)
	{
		this->utility.pos = pos;
		return utility;
	}
	const Utility& operator[](unsigned long long pos) const
	{
		this->utility.pos = pos;
		return utility;
	}

	/*in byte!*/
	const unsigned long long& size() const
	{
		return this->utility.size;
	}

	/*in T counts!*/
	unsigned long long length() const
	{
		return this->utility.size / sizeof(T);
	}

	void resize(unsigned long long count)
	{
		this->utility.resize(count);
	}

	void clear()
	{
		this->utility.clear();
	}

	void push_back(const T& var)
	{
		this->utility.push_back(var);
	}
	
private:
	std::fstream file;
	mutable Utility utility;

	class Utility
	{
	public:
		Utility(std::fstream& file)
			: file(file), pos(0ull), size(0ull) {};

		operator T() const
		{
			if (pos * sizeof(T) < size)
			{
				file.seekg(pos * sizeof(T), std::ios_base::beg);
				T tmp;
				file.read((char*)&tmp, sizeof(T));
				return tmp;
			}
			else
			{
				throw std::range_error("ERROR: Read pos(byte): " + std::to_string(pos * sizeof(T)) + ", length file(byte): " + std::to_string(size));
			}
		}

		void operator=(const T& var)
		{
			if (pos * sizeof(T) < size)
			{
				file.seekp(pos * sizeof(T), std::ios_base::beg);
				file.write((char*)&var, sizeof(T));
			}
			else
			{
				throw std::range_error("ERROR: Write pos(byte): " + std::to_string(pos * sizeof(T)) + ", length file(byte): " + std::to_string(size));
			}
		}
		void operator=(const Utility& in_array_var)
		{
			if (pos * sizeof(T) < size)
			{
				file.seekp(pos * sizeof(T), std::ios_base::beg);
				T tmp{ T(in_array_var) };
				file.write((char*)&tmp, sizeof(T));
			}
			else
			{
				throw std::range_error("ERROR: Write pos(byte): " + std::to_string(pos * sizeof(T)) + ", length file(byte): " + std::to_string(size));
			}
		}

	private:
		std::fstream& file;
		unsigned long long pos;
		unsigned long long size;

		friend File_array;

		void resize(unsigned long long count)
		{
			if (count > this->size / sizeof(T))
			{
				file.seekp(this->size, std::ios_base::beg);
				for (size_t i = 0; i < count - (this->size / sizeof(T)); i++)
				{
					T var{};
					file.write((char*)&var, sizeof(T));
				}
			}
			this->size = count * sizeof(T);
			this->pos = 0ull;
		}
		void push_back(const T& var)
		{
			file.seekp(this->size, std::ios_base::beg);
			file.write((char*)&var, sizeof(T));
			this->size += sizeof(T);
		}
		void clear()
		{
			this->size = 0ull;
			this->pos = 0ull;
		}
	};
};