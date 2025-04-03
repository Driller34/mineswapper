#include "ResourceManager.hpp"

ResourceManager::ResourceManager(const std::string resources)
    : _resources(resources)
{
}

ResourceManager::~ResourceManager() 
{
    _textures.clear();
    _fonts.clear();
    _sounds.clear();
}

sf::Font& ResourceManager::getFont(const std::string fileName) const
{
    if(!_fonts.contains(fileName)) 
    {
        if(!_fonts[fileName].openFromFile(_resources + "/fonts/" + fileName)) 
        {
            throw std::runtime_error("Failed to load font: " + fileName);
        }
    }
    return _fonts[fileName];
}

sf::SoundBuffer& ResourceManager::getSound(const std::string fileName) const
{
    if(!_sounds.contains(fileName) && !_sounds[fileName].loadFromFile(_resources + "/sounds/" + fileName))
    {
        throw std::runtime_error("Failed to load sound: " + fileName);
    }
    return _sounds[fileName];
}

sf::Texture& ResourceManager::getTexture(const std::string fileName) const
{
    if(!_textures.contains(fileName) && !_textures[fileName].loadFromFile(_resources + "/textures/" + fileName))
    {
        throw std::runtime_error("Failed to load sound: " + fileName);
    }
    return _textures[fileName];
}
