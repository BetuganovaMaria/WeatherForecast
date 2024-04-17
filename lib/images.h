#pragma once
#include <string>

namespace WeatherImages {
    static const std::vector<std::vector<std::string>> kWeatherImages{
         // 0 - sunny
        {"   \\ . /   ",
         "  - .-. -  ",
         " ‒ (   ) ‒ ",
         "  . `-᾿ .  ",
         "   / ' \\   "},

         // 1 - partly cloudy
        {"  \\  /     ",
         "_ /\"\".-.   ",
         "  \\_(   ). ",
         "  /(___(__)",
         "           "},

         // 2 - cloudy
        {"           ",
         "    .--.   ",
         " .-(    ). ",
         "(___.__)__)",
         "           "},

         // 3 - fog
        {"           ",
         "_ - _ - _ -",
         " _ - _ - _ ",
         "_ - _ - _ -",
         "           "},

         // 4 - light rain
        {"    .-.    ",
         "   (   ).  ",
         "  (___(__) ",
         "   ʻ ʻ ʻ ʻ ",
         "  ʻ ʻ ʻ ʻ  "},

         // 5 - heavy rain
        {"    .-.    ",
         "   (   ).  ",
         "  (___(__) ",
         "  ‚ʻ ️ ʻ ‚ʻ  ",
         " ‚ʻ‚ʻ ‚ʻ   "},

         // 6 - snow
        {"    .-.    ",
         "   (   ).  ",
         "  (___(__) ",
         "   *  *  * ",
         "  *  *  *  "},

         // 7 - unknown
        {"   .-.     ",
         "    __)    ",
         "   (       ",
         "    `-᾿    ",
         "     •     "}
    };
};