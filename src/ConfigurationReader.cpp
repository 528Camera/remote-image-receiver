/**
 * Реализация объекта для чтения и хранения конфигурационных параметров.
 */

#include <json/json.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ConfigurationReader.h"

using namespace std;
using namespace Json;
using namespace receiver;

bool Configuration::fromFile(const std::string &filename)
{
    // Буфер для записи конфигурации.
    Value config;
    ifstream file(filename);
    if (!file.is_open()) return false;
    file >> config;
    file.close();
    // Набор названий полей объекта.
    auto keys = config.getMemberNames();
    if (find(keys.begin(), keys.end(), "worker_port") == keys.end() || !config["worker_port"].isUInt() ||
        find(keys.begin(), keys.end(), "processed_size") == keys.end() || !config["processed_size"].isUInt() ||
        find(keys.begin(), keys.end(), "version") == keys.end() || !config["version"].isUInt()) {
        return false;
    }
    workerPort = config["worker_port"].asUInt();
    backetSize = config["processed_size"].asUInt();
    version = config["version"].asUInt();
    return true;
}