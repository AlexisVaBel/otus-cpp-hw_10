#ifndef BULKPRODUCER_H
#define BULKPRODUCER_H

#include "../datahodor/bulkholder.h"
#include "../processor/cmdacceptor.h"

class BulkProducer
{
    std::shared_ptr<BulkHolder> m_blk;
    std::shared_ptr<BulkHolder> m_blk2;
    std::shared_ptr<CmdAcceptor> m_cmd;
public:
    BulkProducer(std::shared_ptr<BulkHolder> blk,std::shared_ptr<BulkHolder> blk2, std::shared_ptr<CmdAcceptor> cmd);
    void procsCmd();
    int  get_total_lines();
    int  get_total_cmds();
    int  get_total_blok();

};

#endif // BULKPRODUCER_H
