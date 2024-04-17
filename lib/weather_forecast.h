#pragma once
#include "city.h"
#include "configuration.h"
#include "images.h"
#include <string>

class WeatherForecast {
public:
    WeatherForecast() = default;

    std::string GetDate() const;
    std::string GetWeatherDescription() const;
    double GetTemperatureMax() const;
    double GetTemperatureMin() const;
    double GetPrecipitation() const;
    uint16_t GetPrecipitationProbability() const;
    double GetWindSpeed() const;

    void ParseWeatherForecast(City& city, Configuration& configuration, uint32_t day_number);
    void PrintWeatherForecast() const;

private:
    std::string weather_description_;
    double temperature_max_;
    double temperature_min_;
    double precipitation_;
    uint16_t precipitation_probability_;
    double wind_speed_;
    uint16_t image_number_;
    std::string date_;

    const std::string kWeatherResponseFilename = "weather_response.json";
    const std::string kUrlWeatherForecast = "https://api.open-meteo.com/v1/forecast?latitude={}&longitude={}"
                                            "&daily=weather_code,temperature_2m_max,temperature_2m_min,"
                                            "precipitation_sum,precipitation_probability_max,"
                                            "wind_speed_10m_max&forecast_days={}";

    const std::string kWeatherForecastPeriod = "daily";
    const std::string kLatitudeTag = "latitude";
    const std::string kLongitudeTag = "longitude";
    const std::string kWeatherCodeTag = "weather_code";
    const std::string kTemperatureMaxTag = "temperature_2m_max";
    const std::string kTemperatureMinTag = "temperature_2m_min";
    const std::string kPrecipitationTag = "precipitation_sum";
    const std::string kPrecipitationProbabilityTag = "precipitation_probability_max";
    const std::string kWindSpeedTag = "wind_speed_10m_max";
    const std::string kDateTag = "time";

    const std::string kTemperature = "°C";
    const std::string kWindSpeed = "km/h";
    const std::string kPrecipitation = "mm";
    const std::string kPrecipitationProbability = "%";
    const std::string kDelimiter = " | ";
    const std::string kEndLine = "\n";

    const uint8_t kLineNumbers = 6;
    const uint8_t kDateLineNumber = 0;
    const uint8_t kWeatherDescriptionLineNumber = 1;
    const uint8_t kTemperatureLineNumber = 2;
    const uint8_t kWindLineNumber = 3;
    const uint8_t kPrecipitationLineNumber = 4;

    std::string WeatherCodeProcessing(int weather_code);
    std::string GetPlusIfNeed(double temperature) const;
};
