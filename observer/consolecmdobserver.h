#ifndef CONSOLECMDOBSERVER_H
#define CONSOLECMDOBSERVER_H

#include "icmdobserver.h"
#include <iostream>
#include <string>
#include <vector>

class ConsoleCmdObserver: public ICmdObserver{
public:
    ~ConsoleCmdObserver(){

    }
    // ICmdObserver interface
    void onCmdReceived(const std::vector<std::string>  &vct_str){
        for(std::vector<std::string>::const_iterator it = vct_str.cbegin(); it != vct_str.cend(); ++it){
            if( it != vct_str.cbegin() ) std::cout << ", ";
            else std::cout << "bulk: ";
            std::cout << *it;
        }
        std::cout << std::endl;
    }

    // ICmdObserver interface
public:
    void onNewCmd(const std::string &str){
        // none command here needed
    }

    // ICmdObserver interface
public:
    void sharedProcess(CmdProducer *cmd, std::shared_ptr<BulkQueue<std::vector<std::string> > > que){
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        bool finished = false;
        while(!finished){
            finished = cmd->isFinished() && que->is_empty();
            if(finished) break;
            std::vector<std::string> t = que->pop();
            t.pop_back();
            onCmdReceived(t);
        }
    }
};

#endif // CONSOLECMDOBSERVER_H
