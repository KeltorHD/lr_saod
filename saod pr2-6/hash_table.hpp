#pragma once

#include <fstream>
#include <string>
#include <iostream>

class Hash_table
{
public:
	Hash_table();
	~Hash_table();

	/*������� �������� � �������, to_insert - �� ������ �����, data - ��� ���������*/
	void insert(std::string to_insert, std::string data);

	/*����� �������� � �������: 1 - ���� ������� ��������, to_insert - �� ������ ����� ����, data - ���� ��������� �����*/
	bool find(std::string to_find, std::string& data);

private:
	/*����������*/
	/*������ ���-�������*/
	const size_t table_size{ 1000 };
	/*���� ������ �����*/
	const size_t id_size{ 50 };
	/*���� ������ �������� ������*/
	const size_t data_size{ 100 };

	/*������*/
	std::fstream file;


	/*���������� �������*/
	/*��������� ����� �� ������, ����� ������� (xor)*/
	size_t get_key(std::string& id);

	/*���������� �������� �� ������� ������� ��������� ������������*/
	size_t correct_collision_insert(size_t key);

	/*���������� �������� �� �����, 1 - ���� ������ ���� �������, key - ���� ��������� ����*/
	bool correct_collision_find(size_t& key, std::string to_find);
};