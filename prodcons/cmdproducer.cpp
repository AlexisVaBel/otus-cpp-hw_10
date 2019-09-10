#include "cmdproducer.h"


CmdProducer::CmdProducer(uint iArg, std::shared_ptr<BulkQueue<std::vector<std::string>>> const &que, const std::shared_ptr<BulkQueue<std::vector<std::string> > > &queFile): m_cmdAcceptor(CmdAcceptor(iArg)){
    m_queue     = que;
    m_queueFile = queFile;
}

void CmdProducer::procsCmd()
{
    for(std::string line; std::getline(std::cin, line);){
        if(m_cmdAcceptor.procsCmd(line)) {
            m_queue->push(m_cmdAcceptor.getCmds());
            m_queueFile->push(m_cmdAcceptor.getCmds());
            m_cmdAcceptor.clearProcessd();
        }
    }

    m_queue->push(m_cmdAcceptor.getCmds());
    m_queueFile->push(m_cmdAcceptor.getCmds());    
    m_queue->set_finalized();
    m_queueFile->set_finalized();


    m_cmdAcceptor.clearProcessd();
}


int CmdProducer::get_total_lines()
{
    return m_cmdAcceptor.get_lin_cnt();
}

int CmdProducer::get_total_cmds()
{
    return m_cmdAcceptor.get_cmds_cnt();
}

int CmdProducer::get_total_blok()
{
    return m_cmdAcceptor.get_blok_cnt();
}
