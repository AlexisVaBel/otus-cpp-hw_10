#ifndef LOGCMDOBSERVER_H
#define LOGCMDOBSERVER_H
#include "icmdobserver.h"
#include <fstream>
#include <string>
#include <vector>
#include <fstream>



class LogCmdObserver:public ICmdObserver{
    // ICmdObserver interface
public:
    void onNewCmd(const std::string &str){
//        if(str.empty()) ++iCntHelper;
//        if(str.compare(strBulkName) == 0){
//            ++iCntHelper;
//        }else{
//            iCntHelper  = 0;
//            strBulkName = str;
//        }
    }

    void onCmdReceived(const std::vector<std::string> &vct_str)
    {
        std::string str="";
        for(std::vector<std::string>::const_iterator it = vct_str.cbegin(); it != vct_str.cend(); ++it){
            if( it != vct_str.cbegin() ) str +=", ";
            else str += "bulk: ";
            str+= *it;
        }
        writeLog(str);
    }


private:
    std::string makePrefix(){        
        return  strBulkName;
    }

    void writeLog(std::string &str){
        if(str.empty()) return;
        std::ofstream fout(makePrefix()+".log");
        fout << str;
        fout.close();        
    }

    int         iCntHelper;

    std::string strBulkName;



    // ICmdObserver interface
public:
    void sharedProcess(CmdProducer *cmd, std::shared_ptr<BulkQueue<std::vector<std::string> > > que){
        bool finished = false;
        while(!finished){
            finished = cmd->isFinished() && que->is_empty();
            if(finished) break;
            std::vector<std::string> t = que->pop();
            strBulkName = t.back();
            t.pop_back();
            onCmdReceived(t);
        }
    }
};
#endif // LOGCMDOBSERVER_H
