#ifndef ICMDOBSERVER_H
#define ICMDOBSERVER_H

#include <vector>
#include <string>
#include <memory>

#include "prodcons/cmdproducer.h"
#include "queue/bulkqueue.h"


class ICmdObserver{
public:
    virtual ~ICmdObserver(){}

    virtual void onCmdReceived(const std::vector<std::string> &vct_str) = 0;
    virtual void onNewCmd(const std::string &str) = 0;
    virtual void sharedProcess(CmdProducer *cmd,std::shared_ptr<BulkQueue<std::vector<std::string>>>  que) = 0;
};

#endif // ICMDOBSERVER_H
