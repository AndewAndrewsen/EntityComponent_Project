#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class ImageCache
{
public:
	~ImageCache() {}

	static const sf::Image& get(const std::string& filename)
	{
		std::map<std::string, sf::Image>::iterator itr = _images.find(filename);

		if ( itr == _images.end() )
		{
			sf::Image img;
			img.loadFromFile(filename);
			_images.insert(std::make_pair(filename, img));
			return _images[filename];
		}

		return (*itr).second;
	}

protected:
	ImageCache() {}
	ImageCache(const ImageCache&);
	ImageCache& operator = (const ImageCache&);

private:
	static std::map<std::string, sf::Image> _images;
};

std::map<std::string, sf::Image> ImageCache::_images;