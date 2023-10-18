#include <functional>

template <typename T> class TreeChild {
  private:
    TreeChild<T>* smaller;
    TreeChild<T>* bigger;
    T *value;
    void addBigger(T *value, size_t *valueHash) {
        if (bigger != nullptr) {
            bigger = new TreeChild<T>(value);
            return;
        }
        bigger->add(value, valueHash);
    }
    void addSmaller(T *value, size_t *valueHash) {
        if (smaller != nullptr) {
            smaller = new TreeChild<T>(value);
            return;
        }
        smaller->add(value, valueHash);
    }

  public:
    size_t valueHash;
    int weight;
    TreeChild(T *value) {
        this->value = value;
        valueHash = std::hash<T>{}(*value);
        weight = 1;
    }
    void add(T *value, size_t *valueHash) {
        weight++;
        if (*valueHash >= this->valueHash) {
            this->addBigger(value, valueHash);
        } else {
            this->addSmaller(value, valueHash);
        }
    }
    T* get(unsigned int index) {
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
    TreeChild<T>* treeStart = nullptr;

  public:
    TreeMap() {}
    void add(T *value) {
        size_t valueHash = std::hash<T>{}(*value);
        if (treeStart == nullptr) {
            treeStart = new TreeChild<T>(value);
            return;
        }
        treeStart->add(value, &valueHash);
    }
    T *get(int index) {
        if (treeStart == nullptr) {
            return nullptr;
        }
        return treeStart->get(index);
    }
};
