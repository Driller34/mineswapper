#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    ResourceManager(const std::string resources);
    ~ResourceManager();

    sf::Font& getFont(const std::string fileName) const;
    sf::SoundBuffer& getSound(const std::string fileName) const;
    sf::Texture& getTexture(const std::string fileName) const;

private:
    template<typename T>
    T& getResource(const std::string& fileName,
                   std::unordered_map<std::string, T>& container,
                   const std::string& subfolder) const;

    const std::string _resources;
    mutable std::unordered_map<std::string, sf::Font> _fonts;
    mutable std::unordered_map<std::string, sf::SoundBuffer> _sounds;
    mutable std::unordered_map<std::string, sf::Texture> _textures;
};