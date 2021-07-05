#include "utils.h"

double measureDistance(double lat1, double lon1, double lat2, double lon2) {
    double R = 6378.137;
    double dLat = lat2 * M_PI / 180.0 - lat1 * M_PI / 180.0;
    double dLon = lon2 * M_PI / 180.0 - lon1 * M_PI / 180.0;
    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) + std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) * std::sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * std::atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;
    return std::abs(d * 1000.0);
}

double measureLatitudeDistance(double lat1, double lon1, double lat2, double lon2) {
    double R = 6378.137;
    double dLat = lat2 * M_PI / 180.0 - lat1 * M_PI / 180.0;
    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0);
    double c = 2.0 * std::atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;
    return std::abs(d * 1000.0);
}

double measureLongitudeDistance(double lat1, double lon1, double lat2, double lon2) {
    double R = 6378.137;
    double dLon = lon2 * M_PI / 180.0 - lon1 * M_PI / 180.0;
    double a = std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) * std::sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * std::atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;
    return std::abs(d * 1000.0);
}