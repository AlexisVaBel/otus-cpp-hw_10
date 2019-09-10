#ifndef CMDPRODUCER_H
#define CMDPRODUCER_H
#include <mutex>
#include <condition_variable>

#include "../processor/cmdacceptor.h"
#include "../queue/bulkqueue.h"

class CmdProducer
{
public:
    CmdProducer(uint iArg, const std::shared_ptr<BulkQueue<std::vector<std::string> > > &que, const std::shared_ptr<BulkQueue<std::vector<std::string> > > &queFile);

    void procsCmd();
    int  get_total_lines();
    int  get_total_cmds();
    int  get_total_blok();

private:
    CmdAcceptor             m_cmdAcceptor;
    std::mutex              m_mutex;
    std::condition_variable m_cond;

    std::shared_ptr<BulkQueue<std::vector<std::string>>>   m_queue;
    std::shared_ptr<BulkQueue<std::vector<std::string>>>   m_queueFile;
};

#endif // CMDPRODUCER_H
