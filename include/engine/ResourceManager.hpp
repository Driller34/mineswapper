#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    ResourceManager(const std::string& resources);
    ~ResourceManager();

    sf::Font& getFont(const std::string& fileName) const;
    sf::SoundBuffer& getSound(const std::string& fileName) const;
    sf::Texture& getTexture(const std::string& fileName) const;

private:
    template<typename T>
    T& getResource(const std::string& fileName,
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

    const std::string _resources;
    mutable std::unordered_map<std::string, sf::Font> _fonts;
    mutable std::unordered_map<std::string, sf::SoundBuffer> _sounds;
    mutable std::unordered_map<std::string, sf::Texture> _textures;
};