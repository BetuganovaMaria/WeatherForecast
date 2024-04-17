#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "city.h"
#include "iostream"

City::City(const std::string& city, double latitude, double longitude,  bool is_defined)
    : city_(city),
    latitude_(latitude),
    longitude_(longitude),
    is_defined_(is_defined)
{}

std::string City::GetCityName() const {
    return city_;
}

double City::GetLatitude() const {
    return latitude_;
}

double City::GetLongitude() const {
    return longitude_;
}

bool City::IsDefined() const {
    return is_defined_;
}

void City::ParseCityCoordinates(Configuration& configuration) {
    std::string url_city_info = kUrlCityInfo + city_;
    cpr::Response city_response = cpr::Get(cpr::Url{url_city_info},
                                           cpr::Header({{"X-Api-Key", configuration.GetApiKey()}}));

    if (city_response.status_code != 200) {
        std::cerr << "Error [" << city_response.status_code << "] making request";
        exit(EXIT_FAILURE);
    }

    if (!is_defined_) {
        std::filesystem::path city_response_tmp_path = std::filesystem::current_path().parent_path() / kCityResponseTmpFilename;
        std::ofstream city_response_tmp_output(city_response_tmp_path);
        city_response_tmp_output << city_response.text.substr(1, city_response.text.length() - 2);
        city_response_tmp_output.close();

        std::ifstream city_response_tmp_input(city_response_tmp_path);
        nlohmann::json city_info_tmp = nlohmann::json::parse(city_response_tmp_input);
        city_response_tmp_input.close();

        latitude_ = city_info_tmp[kLatitudeTag].get<double>();
        longitude_ = city_info_tmp[kLongitudeTag].get<double>();
        is_defined_ = true;

        std::filesystem::remove(city_response_tmp_path);
    }
}
