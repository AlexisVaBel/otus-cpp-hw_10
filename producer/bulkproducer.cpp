#include "bulkproducer.h"

BulkProducer::BulkProducer(std::shared_ptr<BulkHolder> blk, std::shared_ptr<BulkHolder> blk2, std::shared_ptr<CmdAcceptor> cmd):m_blk(blk),m_blk2(blk2),m_cmd(cmd)
{

}


void BulkProducer::procsCmd(){

    for(std::string line; std::getline(std::cin, line);){
        if(m_cmd->procsCmd(line)){
            m_blk->push_back(m_cmd->getCmds());
            m_blk2->push_back(m_cmd->getCmds());
            m_cmd->clearProcessd();
        }
    }    
    m_blk->push_back(m_cmd->getCmds());
    m_blk2->push_back(m_cmd->getCmds());
    m_cmd->clearProcessd();
    m_blk->setFinalised();
    m_blk2->setFinalised();
}

int BulkProducer::get_total_lines()
{
    return m_cmd->get_lin_cnt();
}

int BulkProducer::get_total_cmds()
{
    return m_cmd->get_cmds_cnt();
}

int BulkProducer::get_total_blok()
{
    return m_cmd->get_blok_cnt();
}
