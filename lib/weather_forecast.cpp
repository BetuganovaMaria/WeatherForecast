#include "weather_forecast.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

std::string WeatherForecast::GetDate() const {
    return date_;
}

std::string WeatherForecast::GetWeatherDescription() const {
    return weather_description_;
}

double WeatherForecast::GetTemperatureMax() const {
    return temperature_max_;
}

double WeatherForecast::GetTemperatureMin() const {
    return temperature_min_;
}

double WeatherForecast::GetPrecipitation() const {
    return precipitation_;
}

uint16_t WeatherForecast::GetPrecipitationProbability() const {
    return precipitation_probability_;
}

double WeatherForecast::GetWindSpeed() const {
    return wind_speed_;
}

void WeatherForecast::ParseWeatherForecast(City& city, Configuration& configuration_, uint32_t day_number) {
    std::string url_weather_info = std::vformat(kUrlWeatherForecast,
                                                std::make_format_args(city.GetLatitude(),city.GetLongitude(),
                                                configuration_.GetDays()));
    cpr::Response weather_response = cpr::Get(cpr::Url{url_weather_info},
                                              cpr::Header({{"X-Api-Key",
                                              configuration_.GetApiKey()}}));
    if (weather_response.status_code != 200) {
        std::cerr << "Error [" << weather_response.status_code << "] making request";
        exit(EXIT_FAILURE);
    }

    std::filesystem::path weather_response_path = std::filesystem::current_path().parent_path() / kWeatherResponseFilename;
    std::ofstream weather_response_output(weather_response_path);
    weather_response_output << weather_response.text;
    weather_response_output.close();

    std::ifstream weather_response_input(weather_response_path);
    nlohmann::json weather_forecast = nlohmann::json::parse(weather_response_input);
    weather_response_input.close();

    uint8_t weather_code = weather_forecast[kWeatherForecastPeriod][kWeatherCodeTag][day_number];
    weather_description_ = WeatherCodeProcessing(weather_code);
    temperature_max_ = weather_forecast[kWeatherForecastPeriod][kTemperatureMaxTag][day_number];
    temperature_min_ = weather_forecast[kWeatherForecastPeriod][kTemperatureMinTag][day_number];
    precipitation_ = weather_forecast[kWeatherForecastPeriod][kPrecipitationTag][day_number];
    precipitation_probability_ = weather_forecast[kWeatherForecastPeriod][kPrecipitationProbabilityTag][day_number];
    wind_speed_ = weather_forecast[kWeatherForecastPeriod][kWindSpeedTag][day_number];
    date_ = weather_forecast[kWeatherForecastPeriod][kDateTag][day_number];

    std::filesystem::remove(weather_response_path);
}

void WeatherForecast::PrintWeatherForecast() const {
    std::vector<std::stringstream> output(kLineNumbers);
    for (int line_number = 1; line_number < kLineNumbers; ++line_number) {
        output[line_number] << WeatherImages::kWeatherImages[image_number_][line_number - 1] << "\t";
    }
    output[kDateLineNumber] << GetDate();
    output[kWeatherDescriptionLineNumber] << GetWeatherDescription();
    output[kTemperatureLineNumber] << GetPlusIfNeed(GetTemperatureMax()) << GetTemperatureMax()
                                   << " " << kTemperature << kDelimiter << GetPlusIfNeed(GetTemperatureMax())
                                   << GetTemperatureMin() << " " << kTemperature;
    output[kWindLineNumber] << GetWindSpeed() << " " << kWindSpeed;
    output[kPrecipitationLineNumber] << GetPrecipitation() << " " << kPrecipitation << kDelimiter
                                     << GetPrecipitationProbability() << " " << kPrecipitationProbability;

    for (int line_number = 0; line_number < kLineNumbers; ++line_number) {
        std::cout << output[line_number].str() << kEndLine;
    }
}

std::string WeatherForecast::WeatherCodeProcessing(int weather_code) {
    switch (weather_code) {
        case 0:
            image_number_ = 0;
            return "Clear sky";
        case 1:
        case 2:
        case 3:
            image_number_ = 1;
            return "Mainly clear, partly cloudy, and overcast";
        case 45:
        case 48:
            image_number_ = 3;
            return "Fog and depositing rime fog";
        case 51:
        case 53:
        case 55:
            image_number_ = 4;
            return "Drizzle: Light, moderate, and dense intensity";
        case 56:
        case 57:
            image_number_ = 4;
            return "Freezing Drizzle: Light and dense intensity";
        case 61:
        case 63:
        case 65:
            image_number_ = 4;
            return "Rain: Slight, moderate and heavy intensity";
        case 66:
        case 67:
            image_number_ = 5;
            return "Freezing Rain: Light and heavy intensity";
        case 71:
        case 73:
        case 75:
            image_number_ = 6;
            return "Snow fall: Slight, moderate, and heavy intensity";
        case 77:
            image_number_ = 6;
            return "Snow grains";
        case 80:
        case 81:
        case 82:
            image_number_ = 5;
            return "Rain showers: Slight, moderate, and violent";
        case 85:
        case 86:
            image_number_ = 6;
            return "Snow showers slight and heavy";
        case 95:
            image_number_ = 5;
            return "Thunderstorm: Slight or moderate";
        case 96:
        case 99:
            image_number_ = 5;
            return "Thunderstorm with slight and heavy hail";
        default:
            image_number_ = 7;
            return "Unknown";
    }
}

std::string WeatherForecast::GetPlusIfNeed(double temperature) const {
    if (temperature > 0) {
        return "+";
    }
    return "";
}
