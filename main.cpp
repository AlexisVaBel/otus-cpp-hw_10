#include "datahodor/bulkholder.h"


#include <memory>
#include <thread>


#include "producer/bulkproducer.h"
#include "consumer/consumtoterminal.h"
#include "consumer/consumtofile.h"





int main(int argc, char ** argv){
    if(argc < 2) throw  std::length_error("need at least one parameter to work");
    auto val = std::stoi(argv[1]);



    std::shared_ptr<BulkHolder>  sh_bulk(new BulkHolder());
    std::shared_ptr<BulkHolder>  sh_bulkFile(new BulkHolder());
    std::shared_ptr<CmdAcceptor> sh_cmd(new CmdAcceptor(val));

    std::unique_ptr<BulkProducer>     u_prod        = std::unique_ptr<BulkProducer>(new BulkProducer(sh_bulk, sh_bulkFile, sh_cmd));
    std::unique_ptr<ConsumToTerminal> u_consTerm    = std::unique_ptr<ConsumToTerminal>(new ConsumToTerminal());
    std::unique_ptr<ConsumToFile>     u_consFile1   = std::unique_ptr<ConsumToFile>(new ConsumToFile());
    std::unique_ptr<ConsumToFile>     u_consFile2   = std::unique_ptr<ConsumToFile>(new ConsumToFile());




    std::thread thr1(&BulkProducer::procsCmd, u_prod.get());
    std::thread thr2(&IBulkConsumer::sharedProcess, u_consTerm.get(), sh_bulk);
    std::thread thr3(&IBulkConsumer::sharedProcess, u_consFile1.get(), sh_bulkFile);
    std::thread thr4(&IBulkConsumer::sharedProcess, u_consFile2.get(), sh_bulkFile);



    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();



    std::cout <<"main thread - "<< u_prod->get_total_lines() << " lines, " << u_prod->get_total_cmds() <<  " commands, "<< u_prod->get_total_blok() << " bloks" << std::endl;
    std::cout <<"log thread - "<<  u_consTerm->get_cmd_cnt() <<  " commands, "<< u_consTerm->get_blok_cnt() << " bloks" << std::endl;
    std::cout <<"file1 thread - "<<  u_consFile1->get_cmd_cnt() <<  " commands, "<< u_consFile1->get_blok_cnt() << " bloks" << std::endl;
    std::cout <<"file1 thread - "<<  u_consFile2->get_cmd_cnt() <<  " commands, "<< u_consFile2->get_blok_cnt() << " bloks" << std::endl;




    return 0;
}
