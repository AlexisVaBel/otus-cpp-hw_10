#ifndef CONSOLECMDOBSERVER_H
#define CONSOLECMDOBSERVER_H

#include "icmdobserver.h"
#include <iostream>
#include <string>
#include <vector>

class ConsoleCmdObserver: public ICmdObserver{
public:
    ConsoleCmdObserver():m_iBlokCnt(0),
                     m_iCmdCnt(0){}

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


    void onNewCmd(const std::string &str){
        // none command here needed
    }

    void sharedProcess(CmdProducer *cmd, std::shared_ptr<BulkQueue<std::vector<std::string> > > que){
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        bool finished = false;
        while(!finished){
            finished = cmd->isFinished() && que->is_empty();
            if(finished) break;
            std::vector<std::string> t = que->pop();
            if(t.empty()) continue;
            t.pop_back();
            if(t.empty() || t.size() == 1) continue;
            ++m_iBlokCnt;
            m_iCmdCnt+= t.size();
            onCmdReceived(t);
        }
    }

    // ICmdObserver interface
    int get_blok_cnt(){
        return m_iBlokCnt;
    }
    int get_cmd_cnt(){
        return m_iCmdCnt;
    }

private:

    int         m_iBlokCnt;
    int         m_iCmdCnt;
};

#endif // CONSOLECMDOBSERVER_H
