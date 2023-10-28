#include <exception>
#include <functional>
#include <iostream>
#include <string>

template <typename T> class TreeChild {
  private:
    TreeChild<T> *smaller = nullptr;
    TreeChild<T> *bigger = nullptr;
    T *value = new T;
    void addBigger(T *value, size_t valueHash) {
        std::cout << "bigger start\n";
        if (bigger == nullptr) {
            std::cout << "added bigger tree\n";
            bigger = new TreeChild<T>(value);
            std::cout << "bigger end\n";
            return;
        }
        std::cout << "bigger branch\n";
        bigger->add(value, valueHash);
    }
    void addSmaller(T *value, size_t valueHash) {
        std::cout << "smaller start\n";
        if (smaller == nullptr) {
            std::cout << "added smaller tree\n";
            smaller = new TreeChild<T>(value);
            std::cout << "smaller end\n";
            return;
        }
        std::cout << "smaller branch\n";
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
        std::cout << "Branch HashValue: " << std::to_string(this->valueHash)
                  << "\n";
        std::cout << "inputed Hash: " << std::to_string(valueHash) << "\n";
        if (valueHash > this->valueHash) {
            std::cout << "add bigger\n";
            this->addBigger(value, valueHash);
        } else if (valueHash < this->valueHash) {
            std::cout << "add smaller\n";
            this->addSmaller(value, valueHash);
        } else {
            std::cout << "same Value";
        }
    }
    T *get(unsigned int index) {
        std::cout << "get brach start\n";
        if (index == 0 && this->smaller == nullptr) {
            std::cout << "return value\n";
            return this->value;
        }
        std::cout << "find Next Branch\n";
        std::cout << "index: " << std::to_string(index) << "\n";
        std::cout << nullptr << "\n";
        std::cout << this->smaller << "\n";
        std::cout << this->bigger << "\n";
        if (this->smaller == nullptr) {
            std::cout << "smaller is null\n";
        } else {
            std::cout << "smaller branch weight: "
                      << std::to_string(this->smaller->weight) << "\n";
        }
        if(this->smaller == nullptr){
            if(this->bigger == nullptr){
                throw "tree get error. both branches null";
            }
            return this->bigger->get(index-1);
        }

        if (index <= this->smaller->weight) {
            std::cout << "smaller Branch\n";
            int outindex = index - (this->bigger == nullptr ? 1 : this->bigger->weight);
            return this->smaller->get(outindex);
        } else { // else index is in bigger branc
            std::cout << "bigger Branch\n";
            int outindex = index - (this->smaller == nullptr ? 1 : this->smaller->weight);
            return this->bigger->get(outindex);
        }
    }
    void writeAdresses(){
        std::cout << "smaller: " << this->smaller << "\n";
        std::cout << "bigger: " << this->bigger << "\n";
        if(this->smaller != nullptr){
            std::cout << "into smaller\n";
            this->smaller->writeAdresses();
        }
        if(this->bigger != nullptr){
            std::cout << "into bigger\n";
            this->bigger->writeAdresses();
        }
        std::cout << "exeting branch\n";
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
        std::cout << "add start. ########################\n";
        std::cout << "total added: " << std::to_string(++size) << "\n";
        std::cout << "value added: " << std::to_string(*value) << "\n";
        if (treeStart == nullptr) {
            std::cout << "start Tree\n";
            treeStart = new TreeChild<T>(value);
            return;
        }
        treeStart->add(value, valueHash);
        std::cout << "add end ########################\n";
    }
    T get(int index) {
        std::cout << "get start. ########################\n";
        if (treeStart == nullptr) {
            std::cout << "no map ):\n";
            throw "TreeMap Empty\n";
        }
        return *(treeStart->get(index));
        std::cout << "get end ########################\n";
    }
    void writeTreeAddresses(){
        if(treeStart != nullptr){
            treeStart->writeAdresses();
        } else {
            std::cout << "no tree to write addressed\n";
        }
    }
};
