#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace treeSortLog{
static void writeSourceLocation(const char *fileName, int lineNumber, std::string *_location){
#ifdef ENABLE_LOGGING_TREE
    static std::vector<std::string> LogList = std::vector<std::string>();
    if(LogList.empty()){
        LogList.push_back("main");
    }
    if(_location != nullptr){
        if(*_location == "___Remove___"){
            LogList.pop_back();
            return;
        }
        LogList.push_back(*_location);
        return;
    }
    for(std::string section : LogList){
        std::cout << section << ">";
    }
    std::cout << " | file: " << fileName << " @:" << std::to_string(lineNumber) << " | ";
#endif
}
inline void endLogSection(){
#ifdef ENABLE_LOGGING_TREE
    std::string removeString = "___Remove___";
    writeSourceLocation("", 0, &removeString);
#endif
}

inline void setLogLocation(std::string location){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation("", 0, &location);
#endif
}
template <typename T>
inline void LOG(T text){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation(__FILE__, __LINE__, nullptr);
    std::cout << text << "\n";
#endif
}
template <typename T> 
inline void LOG_VARS(std::string text, T variable){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation(__FILE__, __LINE__, nullptr);
    std::cout << text << std::to_string(variable) << "\n";
#endif
}
template <typename T> 
inline void LOG_VARS_SIMPLE(std::string text, T variable){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation(__FILE__, __LINE__, nullptr);
    std::cout << text << variable << "\n";
#endif
}
}


template <typename T> class TreeChild {
  private:
    TreeChild<T> *smaller = nullptr;
    TreeChild<T> *bigger = nullptr;
    T *value = new T;
    void addBigger(T *value, size_t valueHash) {
        treeSortLog::LOG("bigger start");
        if (bigger == nullptr) {
            treeSortLog::LOG("added bigger tree");
            bigger = new TreeChild<T>(value);
            treeSortLog::LOG( "bigger end");
            return;
        }
        treeSortLog::LOG( "bigger branch");
        bigger->add(value, valueHash);
    }
    void addSmaller(T *value, size_t valueHash) {
        treeSortLog::LOG("smaller start");
        if (smaller == nullptr) {
            treeSortLog::LOG("added smaller tree");
            smaller = new TreeChild<T>(value);
            treeSortLog::LOG("smaller end");
            return;
        }
        treeSortLog::LOG("smaller branch");
        smaller->add(value, valueHash);
    }

  public:
    size_t valueHash;
    int weight;
    TreeChild(T *value) {
        *this->value = *value;
        valueHash = std::hash<T>{}(*this->value);
        weight = 1;
    }
    void add(T *value, size_t valueHash) {
        weight += 1;
        treeSortLog::LOG_VARS("Branch HashValue: ", this->valueHash);
        treeSortLog::LOG_VARS("inputed Hash: ",valueHash);
        if (valueHash > this->valueHash) {
            treeSortLog::LOG("add bigger");
            this->addBigger(value, valueHash);
        } else if (valueHash < this->valueHash) {
            treeSortLog::LOG("add smaller");
            this->addSmaller(value, valueHash);
        } else {
            treeSortLog::LOG("same Value");
        }
    }
    T *get(unsigned int index) {
        treeSortLog::LOG("get brach start");
        treeSortLog::LOG_VARS("value: ",valueHash);
        treeSortLog::LOG_VARS("index: ",index);
        if (this->smaller != nullptr){
            if(index == this->smaller->weight){
                treeSortLog::LOG("return mid value");
                return this->value;
            }
        }else if (index == 0){
            treeSortLog::LOG("return end value");
            return this->value;
        }
        if(false){
            treeSortLog::LOG("find Next Branch");
            treeSortLog::LOG_VARS("index: ",index);
            treeSortLog::LOG(nullptr);
            treeSortLog::LOG(this->smaller); 
            treeSortLog::LOG(this->bigger); 
        }


        if(this->smaller == nullptr){
            treeSortLog::LOG("smaller is null");
            if(this->bigger == nullptr){
                treeSortLog::LOG("this should not work!!!");
                throw "tree get error. both branches null";
            }
            return this->bigger->get(index-1);
        }else {
            treeSortLog::LOG_VARS("smaller branch weight: ",this->smaller->weight);
        }

        if (index <= this->smaller->weight) {
            treeSortLog::LOG("smaller Branch");
            return this->smaller->get(index);
        } else { // else index is in bigger branc
            treeSortLog::LOG("bigger Branch");
            if(this->bigger == nullptr){
                treeSortLog::LOG("bigger null");
            }
            int outindex = index - (this->smaller == nullptr ? 1 : (this->smaller->weight + 1));
            return this->bigger->get(outindex);
        }
    }
    void writeAdresses(){
        treeSortLog::LOG_VARS_SIMPLE("value: ", this->value);
        treeSortLog::LOG_VARS_SIMPLE("smaller: ", this->smaller);
        treeSortLog::LOG_VARS_SIMPLE("bigger: ", this->bigger );
        if(this->smaller != nullptr){
            treeSortLog::LOG("into smaller");
            this->smaller->writeAdresses();
        }
        if(this->bigger != nullptr){
            treeSortLog::LOG("into bigger");
            this->bigger->writeAdresses();
        }
        treeSortLog::LOG("exeting branch");
    }
    T* getValue(){
        return this->value;
    }
    TreeChild<T> *getSmaller(){
        return this->smaller;
    }
    TreeChild<T> *getBigger(){
        return this->bigger;
    }
    void SetValue(T *pointer){
        this->value = pointer;
        valueHash = std::hash<T>{}(*this->value);
    }
    void SetSmaller(TreeChild<T> *pointer){
        this->smaller = pointer;
    }
    void SetBigger(TreeChild<T> *pointer){
        this->smaller = pointer;
    }
    void deleteTree(){
        if(this->smaller != nullptr){
            this->smaller->deleteTree();
            delete this->smaller;
        }
        if(this->bigger != nullptr){
            this->bigger->deleteTree();
            delete this->bigger;
        }
        
    }
};

template <typename T> class TreeMap {
  private:
    TreeChild<T> *treeStart = nullptr;

  public:
    int size = 0;
    TreeMap() {}
    void add(T *value) {
        treeSortLog::setLogLocation("addTree");
        size_t valueHash = std::hash<T>{}(*value);
        treeSortLog::LOG_VARS("total added: ",++size);
        treeSortLog::LOG_VARS("value added: ",*value);
        if (treeStart == nullptr) {
            treeSortLog::LOG("start Tree");
            treeStart = new TreeChild<T>(value);
            treeSortLog::endLogSection();
            return;
        }
        treeStart->add(value, valueHash);
        treeSortLog::endLogSection();
    }
    T get(int index) {
        treeSortLog::setLogLocation("getTreeItem");
        if (treeStart == nullptr) {
            treeSortLog::LOG("no map ):");
            throw "TreeMap Empty\n";
        }
        treeSortLog::endLogSection();
        return *(treeStart->get(index));
    }
    void writeTreeAddresses(){
        treeSortLog::setLogLocation("logTreeAddress");
        if(treeStart != nullptr){
            treeStart->writeAdresses();
        } else {
            treeSortLog::LOG("no tree to write addressed");
        }
        treeSortLog::endLogSection();
    }
    void balanceTree(){
        treeSortLog::setLogLocation("treeBalance");
        if(treeStart == nullptr){
            treeSortLog::LOG("no tree :(");
            throw "missing tree start";
        }

        int amount = treeStart->weight;
        TreeChild<T> *newTreeStart = nullptr;
        int jumps = 1;
        float pastLevel = -1;
        float lastLevel = std::floor(std::log2(amount)) + 1;
        bool movedIndexes[amount];
        for(int i = 0; i < amount; i++){
            movedIndexes[i] = false;
        }
        for(int i = 1; i <= amount; i++){
            float level = std::floor(std::log2(i)) + 1;
            if(pastLevel != level){
                pastLevel = level;
                jumps = 1;
            }else{
                jumps += 2;
            }
            treeSortLog::LOG_VARS("\nloop: ", i);
            treeSortLog::LOG_VARS("level: ", level);
            treeSortLog::LOG_VARS("jumps: ", jumps);
            treeSortLog::LOG_VARS("amount: ", amount);
            int position = -1;
            if(lastLevel <= level){
                treeSortLog::setLogLocation("ramaining");
                int remaining = 0;
                for(int ii = 0; ii < amount; ii++){
                    if(!movedIndexes[ii]){
                        remaining++;
                        if(position == -1){
                            position = ii;
                        }
                    }
                }
                treeSortLog::LOG_VARS("remaining:", amount);
                treeSortLog::endLogSection();
            }else{
                position = jumps * int(std::floor(amount / (std::pow(2, level))));
            }
            treeSortLog::LOG_VARS("pos:", position);
            treeSortLog::setLogLocation("getValue");
            T valueOut = *(treeStart->get(position));
            treeSortLog::endLogSection();
            if(movedIndexes[position]){
                treeSortLog::LOG("DUPLICATE POSITION");
            }
            movedIndexes[position] = true;
            treeSortLog::LOG("AFTER");
            if(i == 1){
                treeSortLog::setLogLocation("newTreeStart");
                newTreeStart = new TreeChild<T>(&valueOut);
                treeSortLog::endLogSection();
                continue;
            }
            treeSortLog::LOG_VARS("Position abc: ", position);
            size_t hashOut = std::hash<T>{}(valueOut);
            treeSortLog::setLogLocation("addValue");
            newTreeStart->add(&valueOut, hashOut); 
            treeSortLog::endLogSection();
        }
        treeStart->deleteTree();
        treeStart = newTreeStart;
        treeSortLog::endLogSection();
    }
};
