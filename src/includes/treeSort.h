#include <exception>
#include <iostream>
#include <string>

namespace treeSortLog{
static void writeSourceLocation(const char *fileName, int lineNumber){
#ifdef ENABLE_LOGGING_TREE
    std::cout << "file: " << fileName << " @:" << std::to_string(lineNumber) << " | ";
#endif
}

template <typename T>
inline void LOG(T text){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation(__FILE__, __LINE__);
    std::cout << text << "\n";
#endif
}
template <typename T> 
inline void LOG_VARS(std::string text, T variable){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation(__FILE__, __LINE__);
    std::cout << text << std::to_string(variable) << "\n";
#endif
}
template <typename T> 
inline void LOG_VARS_SIMPLE(std::string text, T variable){
#ifdef ENABLE_LOGGING_TREE
    writeSourceLocation(__FILE__, __LINE__);
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
};

template <typename T> class TreeMap {
  private:
    TreeChild<T> *treeStart = nullptr;

  public:
    int size = 0;
    TreeMap() {}
    void add(T *value) {
        size_t valueHash = std::hash<T>{}(*value);
        treeSortLog::LOG("add start. ########################");
        treeSortLog::LOG_VARS("total added: ",++size);
        treeSortLog::LOG_VARS("value added: ",*value);
        if (treeStart == nullptr) {
            treeSortLog::LOG("start Tree");
            treeStart = new TreeChild<T>(value);
            return;
        }
        treeStart->add(value, valueHash);
        treeSortLog::LOG("add end ########################");
    }
    T get(int index) {
        treeSortLog::LOG("get start. ########################");
        if (treeStart == nullptr) {
            treeSortLog::LOG("no map ):");
            throw "TreeMap Empty\n";
        }
        return *(treeStart->get(index));
        treeSortLog::LOG("get end ########################");
    }
    void writeTreeAddresses(){
        if(treeStart != nullptr){
            treeStart->writeAdresses();
        } else {
            treeSortLog::LOG("no tree to write addressed");
        }
    }
};
