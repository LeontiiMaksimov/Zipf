#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

bool sortbysec(const std::pair<std::string, long long>& a,
	const std::pair<std::string, long long>& b)
{
	return (a.second > b.second);
}

void addCount(std::string word, std::vector<std::pair<std::string, long long>>& counter)
{
	if (word == "")
	{
		return;
	}
	for (std::pair<std::string, long long>& elem : counter)
	{
		if (word == elem.first)
		{
			elem = std::make_pair(word, elem.second + 1);
			return;
		}
	}
	std::pair<std::string, long long> temp;
	temp = std::make_pair(word, 1);
	counter.push_back(temp);
}

int main()
{
	std::vector <std::pair<std::string, long long>> counter;
	std::string name, file_contents, word, data;
	//std::cin >> name;
	std::ifstream file;
	file.open("text.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file_contents = buffer.str();
	file_contents.push_back(' ');
	std::cout << "Content loaded..." << std::endl;
	for (auto elem : file_contents)
	{
		elem = std::tolower(elem);
		if ((elem > 64 && elem < 123) || elem == 32 || elem == 10 || elem == 45)
		{
			if (elem == 10 || elem == 32 || elem == 45)
			{
				addCount(word, counter);
				word = "";
			}
			else
			{
				word.push_back(elem);
			}
		}
		else
		{
			continue;
		}
	}
	std::cout << "Content analysed, sorting..." << std::endl;
	std::sort(counter.begin(), counter.end(), sortbysec);
	std::ofstream out("out.txt");
	for (auto elem : counter)
	{
		data = elem.first + " - ";
		data += std::to_string(elem.second);
		out << data << std::endl;
	}
	return 0;
}
