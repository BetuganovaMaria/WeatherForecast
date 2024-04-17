#include "application.h"
#include <conio.h>
#include <ctime>
#include <iostream>

std::string Parse(int argc, char** argv) {
    if (argc != 2) {
        throw std::runtime_error("Invalid arguments");
    }
    std::string filename = argv[1];
    std::filesystem::path path = std::filesystem::current_path().parent_path() / filename;
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Invalid arguments");
    }
    if (std::filesystem::path(path).extension().string() != ".json") {
        throw std::runtime_error("Invalid arguments");
    }
    return path.string();
}

Application::Application(const std::string& config_path) {
    configuration_ = Configuration(config_path);
}

void Application::Run() {
    CleanConsole();
    std::vector<City> cities;
    ParseAllCityNames(cities);
    cities.front().ParseCityCoordinates(configuration_);

    std::vector<WeatherForecast> weather_forecasts(configuration_.GetDays());
    ParseAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()], configuration_);
    PrintAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()].GetCityName());

    char symbol = '\0';
    while (symbol != kEscCode) {
        SkipTimePeriod(configuration_.GetFrequency());
        if (_kbhit()) {
            symbol = _getch();
            switch (symbol) {
                case 'p':
                    configuration_.DecreaseCityIndex();
                    ParseAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()],
                                                configuration_);
                    break;
                case 'n':
                    configuration_.IncreaseCityIndex();
                    if (!cities[configuration_.GetCurrentCityIndex()].IsDefined()) {
                        cities[configuration_.GetCurrentCityIndex()].ParseCityCoordinates(configuration_);
                    }
                    ParseAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()],
                                                configuration_);
                    break;
                case '+':
                    configuration_.IncreaseDays();
                    weather_forecasts.emplace_back(WeatherForecast());
                    ParseAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()],
                                                configuration_);
                    break;
                case '-':
                    configuration_.DecreaseDays();
                    weather_forecasts.pop_back();
                    ParseAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()],
                                                configuration_);
                    break;
                default:
                    break;
            }
        }
        CleanConsole();
        PrintAllDaysWeatherForecast(weather_forecasts, cities[configuration_.GetCurrentCityIndex()].GetCityName());
    }
}

void Application::ParseAllCityNames(std::vector<City>& cities) {
    for (std::string& city_name : configuration_.GetCityNames()) {
        cities.emplace_back(City(city_name));
    }
}

void Application::ParseAllDaysWeatherForecast(std::vector<WeatherForecast>& weather_forecasts,
                                              City& city, Configuration& configuration) {
    for (uint32_t day_number = 0; day_number < weather_forecasts.size(); ++day_number) {
        weather_forecasts[day_number].ParseWeatherForecast(city, configuration, day_number);
    }
}

void Application::PrintAllDaysWeatherForecast(const std::vector<WeatherForecast>& weather_forecasts,
                                              const std::string& city_name) const {
    std::cout << "Weather Forecast: " << GetCityNameForPrint(city_name) << "\n";
    for (int i = 0; i < weather_forecasts.size(); ++i) {
        weather_forecasts[i].PrintWeatherForecast();
    }
}

std::string Application::GetCityNameForPrint(const std::string& city_name) const {
    std::stringstream city_name_corrected;
    for (int i = 0; i < city_name.size(); ++i) {
        if (city_name[i] == '%') {
            i += 2;
            city_name_corrected << " ";
        } else {
            city_name_corrected << city_name[i];
        }
    }
    return city_name_corrected.str();
}

void Application::CleanConsole() const {
    system("cls");
}

void Application::SkipTimePeriod(uint32_t frequency) const {
    clock_t start_clock = clock();
    while (!_kbhit()) {
        if (clock() >= start_clock + frequency * CLOCKS_PER_SEC) {
            break;
        }
    }
}
