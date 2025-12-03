#include "engine/ResourceManager.hpp"

ResourceManager::ResourceManager(const std::filesystem::path& resources)
    : _resources(resources)
{
}

ResourceManager::~ResourceManager() 
{
    _textures.clear();
    _fonts.clear();
    _sounds.clear();
}

sf::Font& ResourceManager::getFont(const std::filesystem::path& fileName) const
{
    return getResource<sf::Font>(fileName, _fonts, "fonts");
}

sf::SoundBuffer& ResourceManager::getSound(const std::filesystem::path& fileName) const
{
    return getResource<sf::SoundBuffer>(fileName, _sounds, "sounds");
}

sf::Texture& ResourceManager::getTexture(const std::filesystem::path& fileName) const
{
    return getResource<sf::Texture>(fileName, _textures, "textures");
}
