#pragma once
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <string>
#include <vector>

class Configuration {
public:
    Configuration(const std::vector<std::string>& city_names, uint32_t frequency, uint32_t days, const std::string& api_key);
    Configuration(const std::string& config_path);
    Configuration() = default;

    std::vector<std::string>& GetCityNames();
    uint32_t GetFrequency() const;
    uint32_t GetDays() const;
    std::string GetApiKey() const;
    size_t GetCurrentCityIndex() const;

    void IncreaseCityIndex();
    void DecreaseCityIndex();

    void IncreaseDays();
    void DecreaseDays();

private:
    std::vector<std::string> city_names_;
    uint32_t frequency_;
    uint32_t days_;
    std::string api_key_;
    size_t current_city_index_;
};
