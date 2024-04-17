include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(city city.cpp city.h)
add_library(configuration configuration.cpp configuration.h)
add_library(weather_forecast weather_forecast.cpp weather_forecast.h)
add_library(app application.cpp application.h)

target_link_libraries(city PRIVATE configuration)
target_link_libraries(city PRIVATE cpr::cpr)
target_link_libraries(city PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(configuration PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(weather_forecast PRIVATE city)
target_link_libraries(weather_forecast PRIVATE configuration)
target_link_libraries(weather_forecast PRIVATE cpr::cpr)
target_link_libraries(weather_forecast PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(app PRIVATE city)
target_link_libraries(app PRIVATE configuration)
target_link_libraries(app PRIVATE weather_forecast)
target_link_libraries(app PRIVATE cpr::cpr)
target_link_libraries(app PRIVATE nlohmann_json::nlohmann_json)