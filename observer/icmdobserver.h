#ifndef ICMDOBSERVER_H
#define ICMDOBSERVER_H

#include <vector>
#include <string>
#include <memory>

#include "../prodcons/cmdproducer.h"
#include "../queue/bulkqueue.h"


class ICmdObserver{
public:
    virtual ~ICmdObserver(){}

    virtual void onCmdReceived(const std::vector<std::string> &vct_str) = 0;

    virtual void sharedProcess(std::shared_ptr<BulkQueue<std::vector<std::string>>>  que) = 0;

    virtual int  get_blok_cnt() = 0;
    virtual int  get_cmd_cnt() = 0;
};

#endif // ICMDOBSERVER_H
