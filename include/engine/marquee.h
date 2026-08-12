// #pragma once

// #include "platform/context-manager.h"
// #include "user/entity.h"
// #include "engine/timer.h"

// namespace Engine
// {
//   class Marquee : public User::Entity, public Engine::Timer
//   {
//   public:
//     Marquee(Platform::ContextManager &ctx) : User::Entity(defaultTexture, topPosition),
//                                              Engine::Timer{ctx.time},
//                                              contextManager{ctx} {}
//     void displayNumber(uint16_t value);

//     static constexpr int8_t width = 3;
//     static constexpr int8_t height = 4;
//     static constexpr uint32_t oneTexture[] = {0x000000, 0xffff00, 0x000000, 0x000000, 0xffff00, 0x000000, 0x000000, 0xffff00, 0x000000, 0x000000, 0xffff00, 0x000000};
//     static constexpr User::Texture defaultTexture{width, height, oneTexture};
//     static constexpr User::Point topPosition{7, 0};
//     static constexpr User::Point bottomPosition{7, 2};

//   private:
//     Platform::ContextManager &contextManager;
//   };
// }