#include <exception>
#include <functional>
#include <iostream>
#include <string>

template <typename T> class TreeChild {
  private:
    TreeChild<T> *smaller = nullptr;
    TreeChild<T> *bigger = nullptr;
    T value;
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
        this->value = *value;
        valueHash = std::hash<T>{}(this->value);
        weight = 1;
    }
    void add(T *value, size_t valueHash) {
        weight += 1;
        std::cout << "Branch HashValue: " << std::to_string(this->valueHash) << "\n";
        std::cout << "inputed Hash: " << std::to_string(valueHash) << "\n";
        if (valueHash > this->valueHash) {
            std::cout << "add bigger\n";
            this->addBigger(value, valueHash);
        } else if (valueHash < this->valueHash){
            std::cout << "add smaller\n";
            this->addSmaller(value, valueHash);
        } else {
            std::cout << "same Value";
        }
    }
    T get(unsigned int index) {
        if (weight == 1) {
            return this->value;
        }
        if (index < smaller->weight) {
            return this->smaller->get(index);
        } else {
            return this->bigger->get(index - smaller->weight);
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
        if (treeStart == nullptr) {
            throw "TreeMap Empty\n";
        }
        return treeStart->get(index);
    }
};
