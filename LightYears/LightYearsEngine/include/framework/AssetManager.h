#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace LightYears
{
    /**
     * @brief 资产管理类，负责统一加载和管理游戏纹理(Texture)资源.
     * @note 这里使用了单例模式
     *
     * AssetManager是一个单例类，用于：
     * - 集中管理所有纹理资源的加载
     * - 避免重复加载相同的纹理（缓存机制）
     * - 自动清理不再使用的纹理资源
     */
    class AssetManager
    {
    public:
        /**
         * @brief 获得一个 AssetManager 的单例实例
         *
         * @return AssetManager& 返回AssetManager单例的引用
         *
         * 如果单例尚未创建, 则该函数会创建一个单例实例
         * 这是访问 AssetManager 的唯一公开方式
         */
        static AssetManager &Get();
        /**
         * @brief 加载指定路径的Texture
         *
         * @param path  texture 的文件路径
         * @return shared<sf::Texture> 返回 texture 的 shared_ptr
         *                              - 如果纹理已加载过，返回缓存中的纹理
         *                              - 如果纹理未加载过，从文件加载并缓存
         *                              - 如果加载失败，返回nullptr
         */
        shared<sf::Texture> LoadTexture(const std::string &path);
        shared<sf::Font> LoadFont(const std::string &path);
        /**
         * @brief 执行资源清理周期,释放不再使用的 Texture
         *
         */
        void CleanCycle();
        void SetAssetRootDirectory(const std::string &directory);

    protected:
        /**
         * @brief 构造函数，设置为 protected以实现单例模式
         *
         * 外部无法直接创建AssetManager实例，只能通过Get()获取单例
         */
        AssetManager();

    private:
        template <typename T>
        shared<T> LoadAsset(const std::string &path, Dictionary<std::string, shared<T>> &constainer);

        template <typename T>
        void CleanUniqueRef(Dictionary<std::string, shared<T>> &container);

    private:
        /**
         * @brief Assetmanager 的唯一实例,使用 unique_ptr管理生命周期
         *
         */
        static unique<AssetManager> assetManager_;
        /**
         * @brief 已经加载的 Texture 列表: <Texture文件路径, Texture shared_ptr指针>
         *
         */
        Dictionary<std::string, shared<sf::Texture>> LoadedTextureMap_{};
        Dictionary<std::string, shared<sf::Font>> loadedFontMap_;
        std::string rootDirectory_{};
    };

    template <typename T>
    inline shared<T> AssetManager::LoadAsset(const std::string &path, Dictionary<std::string, shared<T>> &constainer)
    {
        auto found = constainer.find(path);
        if (found != constainer.end())
        {
            return found->second;
        }

        shared<T> newAsset{new T};
        if (newAsset->loadFromFile(rootDirectory_ + path))
        {
            constainer.insert({path, newAsset});
            return newAsset;
        }

        return shared<T>{nullptr};
    }

    template <typename T>
    inline void AssetManager::CleanUniqueRef(Dictionary<std::string, shared<T>> &container)
    {
        // 如果 shared_ptr 独占纹理资源，说明游戏中没有对象再引用该纹理。
        // 在这种情况下，可以安全地从资源管理器的缓存中删除它。
        for (auto iter = container.begin(); iter != container.end();)
        {
            // unique() 表示：只有当前容器中的这一份引用，外部没有引用它. 当前的引用是 map 自己的引用
            if (iter->second.unique())
            {
                LOG("cleaning: %s", iter->first.c_str());
                iter = container.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
} // namespace LightYesrs
