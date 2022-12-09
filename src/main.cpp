/**
 * Точка входа в приложение.
 */

#include <boost/log/trivial.hpp>
using namespace std;

int main()
{
    BOOST_LOG_TRIVIAL(info) << "Запуск обработчика пакетов";
    return 0;
}