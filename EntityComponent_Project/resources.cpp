#include "resources.h"
#include <string>

#pragma pack(push, 1)
struct file_header
{
	char				Signature[4];		// RESF
	unsigned short		Revision;
	unsigned int		numberOfFiles;
	unsigned int		offsetToRegister;
};

struct file_register 
{
	unsigned int		offsetToData;
	unsigned int		fileSize;
	unsigned short		fileNameSize;
};

#pragma pack(pop)

resources::resources()
{
}

resources::~resources()
{
	close();
}

bool resources::open(const std::string& filename)
{
	close();

	_stream.open(filename, std::ios::binary);

	if( _stream.is_open() ) 
	{
		file_header header;
		_stream.read((char*)(&header), sizeof(file_header));
	
		// Kolla: Stämmer signaturen
		if( ::strncmp(header.Signature, "RESF", 4) != 0 )
		{
			_stream.close();
			return false;
		}

		_stream.seekg(header.offsetToRegister, std::ios::beg);

		for( unsigned int i = 0; i < header.numberOfFiles; i++ )
		{
			file_info info;
			file_register reg;

			_stream.read((char*)(&reg), sizeof(file_register));

			info.fileSize = reg.fileSize;
			info.offset = reg.offsetToData;
			
			char* name = new char[reg.fileNameSize +1];
			_stream.read(name, reg.fileNameSize);
			name[reg.fileNameSize] = 0;
			info.fileName = name;
			delete [] name;

			_files.push_back(info);
		}

		return true;
	}

	return false;
}

void resources::close()
{
	_stream.close();
	_files.clear();
}


std::vector<std::string> resources::files()
{

	std::vector<std::string> ret;

	for( unsigned int i = 0; i < _files.size(); i++ )
	{
		ret.push_back(_files[i].fileName);
	}


	return ret;
}

bool resources::get_file(	const std::string& filename,
							char*& data, 
							unsigned int& length		)
{
	if( _stream.is_open() )
	{
		for( unsigned int i = 0; i < _files.size(); i++ )
		{
			if( filename == _files[i].fileName )
			{
				_stream.seekg(_files[i].offset, std::ios::beg);

				length = _files[i].fileSize;
				data = new char[length];

				_stream.read(data, length);
				return true;
			}
		}

		return true;
	}
	return false;

}

sf::Image resources::getImage(std::string name)
{
	char* data = nullptr;
	unsigned int length;
	
	
	sf::Image *retImage = new sf::Image();
	if( _stream.is_open() )
	{
		for( unsigned int i = 0; i < _files.size(); i++ )
		{
			if( name == _files[i].fileName )
			{
				_stream.seekg(_files[i].offset, std::ios::beg);
				
				
				length = _files[i].fileSize;
				data = new char[length];

				_stream.read(data, length);
				
				retImage->LoadFromMemory(data, length);//length);
				//retImage->SaveToFile("hehe.png");
				return *retImage;
			}
		}

	}

}

sf::Font resources::getFont(std::string name)
{
	char* data = nullptr;
	unsigned int length;
	
	
	sf::Font *retFont = new sf::Font();
	if( _stream.is_open() )
	{
		for( unsigned int i = 0; i < _files.size(); i++ )
		{
			if( name == _files[i].fileName )
			{
				_stream.seekg(_files[i].offset, std::ios::beg);
				
				
				length = _files[i].fileSize;
				data = new char[length];

				_stream.read(data, length);
				
				retFont->LoadFromMemory(data, length);//length);
				//retImage->SaveToFile("hehe.png");
				return *retFont;
			}
		}

	}

}