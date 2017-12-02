#ifndef _resources_h_
#define _resources_h_

#include <string>
#include <fstream>	
#include <vector>
#include <SFML\Graphics.hpp>

class resources
{
public:
	resources();
	~resources();

	bool open(const std::string& filename);
	void close();

	std::vector<std::string> files();

	bool get_file(const std::string& filename, char*& data, unsigned int& length);
	sf::Image getImage(std::string name);
	sf::Font getFont(std::string name);

private:

	struct file_info 
	{
		std::string		fileName;
		unsigned int	fileSize;
		unsigned int	offset;
	};

	std::vector<file_info>	_files;
	std::ifstream			_stream;

};	

#endif // _pach_reader_h_