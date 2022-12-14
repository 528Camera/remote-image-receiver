/**
 * Точка входа в приложение.
 */

#include <boost/log/trivial.hpp>
#include <csignal>
#include <iostream>
#include "ReceiverService.h"

using namespace std;
using namespace receiver;

/** Объект для записи лямбды обработки остановки сервиса. */
function<void(int)> shutdownHandler;

/**
 * Обработчик сигнала завершения работы сервиса.
 * @param signal код сигнала.
 */
void signalHandler(int signal) { shutdownHandler(signal); }

/**
 * Основная функция приложения.
 * @param argc количество аргументов.
 * @param argv значения аргументов.
 *      [0] - имя и путь до бинарного файла приложения.
 *      [1] - имя и путь до конфигурационного файла приложения.
 * @return код ошибки. 0 - выполнение завершено успешно.
 */
int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Используйте аргументы:\n\t[0] - имя конфигурационного файла." << endl;
        return 0;
    }

    ReceiverService service(argv[1]);
    service.start();

    shutdownHandler = [&service](int signum) {
        service.stop();
    };

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    while (service.isStarted()) {
        sleep(1);
    }

    return 0;
}