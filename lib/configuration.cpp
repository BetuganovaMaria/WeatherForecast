#include <nlohmann/json.hpp>
#include "configuration.h"
#include <iostream>

Configuration::Configuration(const std::string& config_path) {
    std::ifstream config(config_path);
    try {
        nlohmann::json parameters = nlohmann::json::parse(config);
        city_names_ = parameters["cities"].get<std::vector<std::string>>();
        frequency_ = parameters["frequency"].get<uint32_t>();
        days_ = parameters["days"].get<uint32_t>();
        api_key_ = parameters["api_key"].get<std::string>();
        current_city_index_ = 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what();
        exit(EXIT_FAILURE);
    }
}

Configuration::Configuration(const std::vector<std::string>& city_names, uint32_t frequency, uint32_t days, const std::string& api_key)
    : city_names_(city_names),
    frequency_(frequency),
    days_(days),
    api_key_(api_key)
{}

std::vector<std::string>& Configuration::GetCityNames() {
    return city_names_;
}

uint32_t Configuration::GetFrequency() const {
    return frequency_;
}

uint32_t Configuration::GetDays() const {
    return days_;
}

std::string Configuration::GetApiKey() const {
    return api_key_;
}

size_t Configuration::GetCurrentCityIndex() const {
    return current_city_index_;
}

void Configuration::IncreaseCityIndex() {
    current_city_index_ = std::min(city_names_.size(), current_city_index_ + 2) - 1;
}

void Configuration::DecreaseCityIndex() {
    current_city_index_ = std::max(current_city_index_, static_cast<size_t>(1)) - 1;
}

void Configuration::IncreaseDays() {
    ++days_;
}

void Configuration::DecreaseDays() {
    days_ = std::max(days_, static_cast<uint32_t>(1)) - 1;
}