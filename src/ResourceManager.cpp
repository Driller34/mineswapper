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

template<typename T>
T& ResourceManager::getResource(const std::string& fileName,
                                std::unordered_map<std::string, T>& container,
                                const std::string& subfolder) const
{
    if(!container.contains(fileName)) 
    {
        auto& resource = container[fileName];
        bool condition;

        if constexpr (std::is_same_v<T, sf::Font>)
        {
            condition = resource.openFromFile(_resources + subfolder + fileName);
        }
        else
        {
            condition = resource.loadFromFile(_resources + subfolder + fileName);
        }

        if(!condition)
        {
            throw std::runtime_error("Failed to load " + subfolder + " : " + fileName);
        }
    }

    return container[fileName];
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
