#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <format>

class ResourceManager
{
public:
    ResourceManager(const std::filesystem::path& resources);
    ~ResourceManager();

    sf::Font& getFont(const std::filesystem::path& fileName) const;
    sf::SoundBuffer& getSound(const std::filesystem::path& fileName) const;
    sf::Texture& getTexture(const std::filesystem::path& fileName) const;

private:
    template<typename T>
    T& getResource(const std::filesystem::path& fileName,
                   std::unordered_map<std::filesystem::path, T>& container,
                   const std::filesystem::path& subfolder) const
    {
        if(!container.contains(fileName)) 
        {
            auto& resource = container[fileName];
            bool condition;

            if constexpr (std::is_same_v<T, sf::Font>)
            {
                condition = resource.openFromFile(_resources / subfolder / fileName);
            }
            else
            {
                condition = resource.loadFromFile(_resources / subfolder / fileName);
            }

            if(!condition)
            {
                throw std::runtime_error(std::format("Failed to load {}", 
                    _resources / subfolder / fileName));
            }
        }

        return container[fileName];
    }

    const std::filesystem::path _resources;
    mutable std::unordered_map<std::filesystem::path, sf::Font> _fonts;
    mutable std::unordered_map<std::filesystem::path, sf::SoundBuffer> _sounds;
    mutable std::unordered_map<std::filesystem::path, sf::Texture> _textures;
};