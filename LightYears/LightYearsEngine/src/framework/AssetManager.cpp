#include "framework/AssetManager.h"

namespace LightYears
{
    unique<AssetManager> AssetManager::assetManager_{nullptr};

    AssetManager &AssetManager::Get()
    {

        if (!assetManager_)
        {
            assetManager_ = unique<AssetManager>{new AssetManager};
        }
        // LOG("AssetManager::GET()");
        return *assetManager_;
    }
    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        return LoadAsset(path, LoadedTextureMap_);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {

        return LoadAsset(path, loadedFontMap_);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(LoadedTextureMap_);
        CleanUniqueRef(loadedFontMap_);
    }

    void AssetManager::SetAssetRootDirectory(const std::string &directory)
    {
        rootDirectory_ = directory;
    }

    AssetManager::AssetManager()
        : rootDirectory_{}
    {
    }

} // namespace LightYears
