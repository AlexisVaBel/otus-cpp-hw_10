#include <observer/consolecmdobserver.h>
#include <observer/logcmdobserver.h>

#include "prodcons/cmdproducer.h"

#include <memory>
#include <thread>


int main(int argc, char ** argv){
    if(argc < 2) throw  std::length_error("need at least one parameter to work");
    auto val = std::stoi(argv[1]);

    std::shared_ptr<BulkQueue<std::vector<std::string>>>  m_queue(new BulkQueue<std::vector<std::string>>(std::vector<std::string>()));
    std::shared_ptr<BulkQueue<std::vector<std::string>>>  m_queueFile(new BulkQueue<std::vector<std::string>>(std::vector<std::string>()));

    ConsoleCmdObserver *consoleObserver = new ConsoleCmdObserver();
    LogCmdObserver *log1 = new LogCmdObserver();
    LogCmdObserver *log2 = new LogCmdObserver();


    CmdProducer producerMain(val, m_queue, m_queueFile);
    std::thread thr1(&ICmdObserver::sharedProcess, consoleObserver, &producerMain, m_queue);
    std::thread thr2(&ICmdObserver::sharedProcess, log1, &producerMain, m_queueFile);
//    std::thread thr3(&ICmdObserver::sharedProcess, log2, &producerMain, m_queueFile);



    producerMain.procsCmd();


    thr1.join();
    thr2.join();
//    thr3.join();


    delete  consoleObserver;
    delete  log1;
    delete  log2;
    std::cout << "quiting" << std::endl;
    return 0;
}
