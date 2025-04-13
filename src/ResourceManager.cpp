#include "ResourceManager.hpp"

ResourceManager::ResourceManager(const std::string& resources)
    : _resources(resources)
{
}

ResourceManager::~ResourceManager() 
{
    _textures.clear();
    _fonts.clear();
    _sounds.clear();
}

sf::Font& ResourceManager::getFont(const std::string& fileName) const
{
    return getResource<sf::Font>(fileName, _fonts, "/fonts/");
}

sf::SoundBuffer& ResourceManager::getSound(const std::string& fileName) const
{
    return getResource<sf::SoundBuffer>(fileName, _sounds, "/sounds/");
}

sf::Texture& ResourceManager::getTexture(const std::string& fileName) const
{
    return getResource<sf::Texture>(fileName, _textures, "/textures/");
}
