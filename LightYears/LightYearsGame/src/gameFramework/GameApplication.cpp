#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "gameFramework/GameApplication.h"
#include "Level/GameLevelOne.h"
#include "Level/MainMenuLevel.h"
#include "config.h"

LightYears::Application *GetApplication()
{
    return new LightYears::GameApplication();
}

std::unique_ptr<LightYears::Application> GetApplicationSmart()
{
    return std::make_unique<LightYears::GameApplication>();
}

namespace LightYears
{
    GameApplication::GameApplication()
        : Application{600, 980, "LightYears", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResoureDir());
        weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
    }

} // namespace LightYears
