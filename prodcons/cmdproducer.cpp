#include "cmdproducer.h"

CmdProducer::CmdProducer(uint iArg, std::shared_ptr<BulkQueue<std::vector<std::string>>> const &que, const std::shared_ptr<BulkQueue<std::vector<std::string> > > &queFile): m_cmdAcceptor(CmdAcceptor(iArg)),m_bFinished(false){
    m_queue     = que;
    m_queueFile = queFile;
}

void CmdProducer::procsCmd()
{
    for(std::string line; std::getline(std::cin, line);){
        if(m_cmdAcceptor.procsCmd(line)) {
//            std::cout << __PRETTY_FUNCTION__ << std::endl;
            m_queue->push(m_cmdAcceptor.getCmds());
            m_queueFile->push(m_cmdAcceptor.getCmds());
            m_cmdAcceptor.clearProcessd();
        } // cmd begin detected
    }
    m_queue->push(m_cmdAcceptor.getCmds());
    m_queueFile->push(m_cmdAcceptor.getCmds());
    m_queue->set_finalized();
    m_queueFile->set_finalized();

//    std::cout <<" finalizing quee "<< std::endl;
    m_bFinished = true;
}

bool CmdProducer::isFinished()
{
    return m_bFinished;
}
