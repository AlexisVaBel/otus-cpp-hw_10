#ifndef CMDPRODUCER_H
#define CMDPRODUCER_H
#include "cmdacceptor.h"
#include "queue/bulkqueue.h"

class CmdProducer
{
public:
    CmdProducer(uint iArg, const std::shared_ptr<BulkQueue<std::vector<std::string> > > &que, const std::shared_ptr<BulkQueue<std::vector<std::string> > > &queFile);

    void procsCmd();
    bool isFinished();

private:
    CmdAcceptor m_cmdAcceptor;
    bool        m_bFinished;

    std::shared_ptr<BulkQueue<std::vector<std::string>>>   m_queue;
    std::shared_ptr<BulkQueue<std::vector<std::string>>>   m_queueFile;
};

#endif // CMDPRODUCER_H
