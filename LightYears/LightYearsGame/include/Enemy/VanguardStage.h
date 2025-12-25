#pragma once
#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    class VanguardStage : public GameStage
    {
    public:
        VanguardStage(World *world);

        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;

        /**
         * @brief 生成一个 Vanguard 敌人
         *
         */
        void SpawnVanguard();
        /**
         * @brief 切换到下一行
         *
         */
        void SwitchRow();

    private:
        /* ===================== 时间与距离参数 ===================== */

        /// 两次生成 Vanguard 之间的时间间隔(秒)
        float spawnInterval_{};
        /// 两行 Vanguard 之间切换的时间间隔（秒）
        float switchInterval_{};
        /// 生成点距离屏幕边缘的偏移量
        float spawnDistanceToEdge_{};

        /* ===================== 生成位置 ===================== */

        /// 从屏幕左侧生成 Vanguard 的位置
        sf::Vector2f leftSpawnLoc_{};
        /// 从屏幕右侧生成 Vanguard 的位置
        sf::Vector2f rightSpwanLoc_{};
        /// 当前使用的生成位置（左或右）
        sf::Vector2f spawnLoc_{};

        /* ===================== 定时器 ===================== */

        /// Vanguard 生成定时器句柄
        TimerHandle spawnTimerHandle_;
        /// 行切换定时器句柄
        TimerHandle switchTimerHandle_;

        /* ===================== 行与数量控制 ===================== */

        /// 总共需要生成的行数
        int rowsToSpawn_{};
        /// 已经生成完成的行数
        int rowsSpawnCount_{};
        /// 每一行中 Vanguard 的数量
        int vangaurdsPerRow_{};
        /// 当前行已经生成的 Vanguard 数量
        int currentRowVanguardCount_{};
    };
}
