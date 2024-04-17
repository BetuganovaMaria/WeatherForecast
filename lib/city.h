#pragma once
#include "configuration.h"
#include <string>

class City {
public:
    City(const std::string& city, double latitude=0, double longitude=0, bool is_defined=false);

    std::string GetCityName() const;
    double GetLatitude() const;
    double GetLongitude() const;
    bool IsDefined() const;

    void ParseCityCoordinates(Configuration& configuration);

private:
    std::string city_;
    double latitude_;
    double longitude_;
    bool is_defined_;

    std::string weather_description_;

    const std::string kCityResponseTmpFilename = "city_coordinates_tmp.json";
    const std::string kUrlCityInfo = "https://api.api-ninjas.com/v1/city?name=";

    const std::string kLatitudeTag = "latitude";
    const std::string kLongitudeTag = "longitude";
};
