#pragma once

#include "weather_forecast.h"

std::string Parse(int argc, char** argv);

class Application {
public:
    Application(const std::string& config_filename);

    void Run();

private:
    Configuration configuration_;

    const char kEscCode = 27;

    void ParseAllCityNames(std::vector<City>& cities);
    void ParseAllDaysWeatherForecast(std::vector<WeatherForecast>& weather_forecasts,
                                     City& city, Configuration& configuration);
    void PrintAllDaysWeatherForecast(const std::vector<WeatherForecast>& weather_forecasts,
                                     const std::string& city_name) const;
    std::string GetCityNameForPrint(const std::string& city_name) const;
    void CleanConsole() const;
    void SkipTimePeriod(uint32_t frequency) const;
};