#include "observer/consolecmdobserver.h"
#include "observer/logcmdobserver.h"

#include "prodcons/cmdproducer.h"

#include <memory>
#include <thread>


int main(int argc, char ** argv){
    if(argc < 2) throw  std::length_error("need at least one parameter to work");
    auto val = std::stoi(argv[1]);

    std::shared_ptr<BulkQueue<std::vector<std::string>>>  m_queue(new BulkQueue<std::vector<std::string>>(std::vector<std::string>()));
    std::shared_ptr<BulkQueue<std::vector<std::string>>>  m_queueFile(new BulkQueue<std::vector<std::string>>(std::vector<std::string>()));

    std::unique_ptr<LogCmdObserver>         file1 = std::unique_ptr<LogCmdObserver>(new LogCmdObserver());
    std::unique_ptr<LogCmdObserver>         file2 = std::unique_ptr<LogCmdObserver>(new LogCmdObserver());
    std::unique_ptr<ConsoleCmdObserver>     log = std::unique_ptr<ConsoleCmdObserver>(new ConsoleCmdObserver());



    CmdProducer producerMain(val, m_queue, m_queueFile);
    std::thread thr1(&ICmdObserver::sharedProcess, log.get(),   m_queue);
    std::thread thr2(&ICmdObserver::sharedProcess, file1.get(), m_queueFile);
//    std::thread thr3(&ICmdObserver::sharedProcess, file2.get(), m_queueFile);

    producerMain.procsCmd();

    thr1.join();

    thr2.join();

//    thr3.join();

    std::cout <<"main thread - "<< producerMain.get_total_lines() << " lines, " << producerMain.get_total_cmds() <<  " commands, "<< producerMain.get_total_blok() << " bloks" << std::endl;
    std::cout <<"log thread - "<<  log->get_cmd_cnt() <<  " commands, "<< log->get_blok_cnt() << " bloks" << std::endl;
    std::cout <<"file1 thread - "<<  file1->get_cmd_cnt() <<  " commands, "<< file1->get_blok_cnt() << " bloks" << std::endl;
    std::cout <<"file1 thread - "<<  file2->get_cmd_cnt() <<  " commands, "<< file2->get_blok_cnt() << " bloks" << std::endl;



    return 0;
}
