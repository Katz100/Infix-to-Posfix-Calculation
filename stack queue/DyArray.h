#include <iostream>
#include <cassert>
#include <fstream>


#ifndef DYARRAY_H
#define DYARRAY_H

namespace Dynamic {
	template<typename T>
	class DyArray
	{
	private:


		int size;
		int max_size;
		T* array;
	public:


		DyArray(int size);
		DyArray();
		DyArray(const DyArray& other);
		~DyArray();

		int get_size() const;
		int get_max_size() const;

		T& operator[](int index);
		const T& operator[](int index) const;

		void add(const T& value);
		void remove(int index);
		void unitTest();
		void write(const char* file_name);
		void read(const char* file_name);
		void swap(int a, int b);
		T remove_last();
		T remove_first();
		T topofstack();
		void clear();

		bool isOutOfBounds(int index) const;
		bool isEmpty() const;

	};

	template<typename T>
	DyArray<T>::DyArray(int size) : size(size), max_size(size * 2), array(new T[max_size])
	{
	}

	template<typename T>
	DyArray<T>::DyArray() : size(0), max_size(2), array(new T[max_size])
	{
	}

	template<typename T>
	DyArray<T>::DyArray(const DyArray& other)
	{

		size = other.size;
		max_size = other.max_size;

		T* temp_array = new T[max_size];

		for (int i = 0; i < size; i++)
		{
			temp_array[i] = other.array[i];
		}
		delete[] array;
		array = temp_array;
	}

	template<typename T>
	DyArray<T>::~DyArray()
	{
		delete[] array;
	}





	template<typename T>
	void DyArray<T>::add(const T& value)
	{
		if (size >= max_size)
		{
			max_size *= 2;
			T* temp_array = new T[max_size];

			for (int i = 0; i < size; i++)
			{
				temp_array[i] = array[i];
			}

			delete[] array;

			array = temp_array;
		}

		assert((size < max_size) && "Array has overflowed");
		array[size] = value;
		size++;
	}

	template<typename T>
	void DyArray<T>::remove(int index)
	{
		assert(isOutOfBounds(index) && "Index out of bounds");
		T* temp_array = new T[max_size];


		for (int i = 0; i < index; i++)
		{
			temp_array[i] = array[i];
		}

		for (int i = index + 1; i < size; i++)
		{
			temp_array[i - 1] = array[i];
		}

		delete[] array;
		array = temp_array;
		size--;
	}

	template<typename T>
	int DyArray<T>::get_size() const
	{
		return size;
	}

	template<typename T>
	int DyArray<T>::get_max_size() const
	{
		return max_size;
	}

	template<typename T>
	T& DyArray<T>::operator[](int index)
	{
		assert(isOutOfBounds(index) && "Array index out of bounds");

		return array[index];
	}

	template<typename T>
	const T& DyArray<T>::operator[](int index) const
	{
		assert(isOutOfBounds(index) && "Array index out of bounds");

		return array[index];
	}

	template<typename T>
	void DyArray<T>::unitTest()
	{

		DyArray<int> TestArray;

		assert((TestArray.size == 0) && ("Constructer failure"));
		assert((TestArray.max_size == 2) && ("Constructer failure"));
		assert(TestArray.array && "Constructer failure");
		std::cout << "Constructer succesful" << std::endl;

		TestArray.add(5);
		TestArray.add(3);
		TestArray.add(2);

		assert(TestArray[0] == 5 && TestArray[1] == 3 && TestArray[2] == 2 && "Add method failure");

		assert(TestArray.size == 3 && "Unexpected size occured");

		std::cout << "Add() method succesful" << std::endl;



		DyArray<int> newTestArray = TestArray;

		assert(newTestArray[0] == 5 && newTestArray[1] == 3 && TestArray[2] == 2 && "Copy constructer failure");
		std::cout << "Copy constructer succesful" << std::endl;

		newTestArray.clear();

		assert(newTestArray.isEmpty() && "Clear() method failure");
		std::cout << "Clear() method succesful" << std::endl;
	}





	template<typename T>
	bool DyArray<T>::isOutOfBounds(int index) const
	{
		return (index > -1 && index < max_size) ? 1 : 0;

	}

	template<typename T>
	bool DyArray<T>::isEmpty() const
	{
		return (size == 0);
	}

	template<typename T>
	void DyArray<T>::write(const char* file_name)
	{

		std::ofstream write_file(file_name);

		if (!write_file)
		{
			std::cerr << file_name << " could not be opened for writing.\n";
		}

		for (int i = 0; i < size; i++)
		{
			write_file << array[i] << ' ';
		}

		write_file.close();
	}

	template<typename T>
	void DyArray<T>::read(const char* file_name)
	{
		std::ifstream read_file(file_name);

		if (!read_file)
		{
			std::cerr << file_name << " could not be opended for reading.\n";
		}

		T value;

		while (read_file >> value)
		{
			add(value);
		}

		read_file.close();
	}

	template<typename T>
	void DyArray<T>::swap(int a, int b)
	{
		assert(isOutOfBounds(a) && isOutOfBounds(b) && "Index out of bounds");
		T temp = array[a];
		array[a] = array[b];
		array[b] = temp;
	}

	template<typename T>
	T DyArray<T>::remove_last()
	{
		assert((size > 0) && "Array is empty");
		T value = array[get_size() - 1];
		remove(get_size() - 1);
		return value;
	}

	template<typename T>
	inline T DyArray<T>::remove_first()
	{
		assert((size > 0) && "Array is empty");
		T value = array[0];
		remove(0);
		return value;
	}

	template<typename T>
	inline T DyArray<T>::topofstack()
	{
		return array[get_size() - 1];
	}

	template<typename T>
	void DyArray<T>::clear()
	{
		//Get size of array before looping
		int n = get_size();
		for (int i = 0; i < n; i++)
		{
			//Removes first element and shifts following elements to the left by one.
			remove(0);
		}
	}


	template<typename T>
	std::ostream& operator<<(std::ostream& ostr, const DyArray<T>& m)
	{
		for (int i = 0; i < m.get_size(); i++)
		{
			ostr << m[i] << " ";
		}

		return ostr;
	}

	int precedence(char op)
	{
		switch (op)
		{
		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
			return 3;
		case '#':
			return 1;
		default:
			return 0;
		}
	}

	auto perform(auto op1, auto op2, char token)
	{
		switch (token)
		{
		case '+':
			return op1 + op2;
		case '-':
			return op2 - op1;
		case '*':
			return op1 * op2;
		case '/':
			return op2 / op1;
		}
	}
}
#endif