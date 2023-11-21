#include "logging.h"
#include <cmath>
#include <sstream>
class node {
  private:
    bool addLeft(int num) {
        LOG_ADD_SECTION("addLeft");
        if (left == nullptr) {
            LOG("Create new LEFT node ----------");
            left = new node(num);
            if (right == nullptr) {
                LOG("Right is also null. returning true to adjust height");
                LOG_EXIT_SECTION();
                return true;
            }
        } else {
            LOG("Enter Left to add -----------");
            bool temp = left->add(num);
            LOG_EXIT_SECTION();
            return temp;
        }
        LOG_EXIT_SECTION();
        return false;
    }
    bool addRight(int num) {
        LOG_ADD_SECTION("addRight");
        if (right == nullptr) {
            LOG("Create new NODE ----------");
            right = new node(num);
            if (left == nullptr) {
                LOG("Left is also null. returning true to adjust height");
                LOG_EXIT_SECTION();
                return true;
            }
        } else {
            LOG("Enter Right to add -----------");
            bool temp = right->add(num);
            LOG_EXIT_SECTION();
            return temp;
        }
        LOG_EXIT_SECTION();
        return false;
    }
    bool updateHeight() {
        LOG_ADD_SECTION("updateHeght");
        if (left == nullptr) {
            LOG("LEFT NULL");
        }
        if (right == nullptr) {
            LOG("RIGHT NULL");
        }
        int leftHeight = left == nullptr ? 0 : left->height;
        LOG_VARS("leftHeight: ", leftHeight);
        int rightHeight = right == nullptr ? 0 : right->height;
        LOG_VARS("rightHeight: ", rightHeight);
        int newHeight = std::max(leftHeight, rightHeight) + 1;
        bool flag = height == newHeight;
        LOG_VARS("heightBefore: ", height);
        height = newHeight;
        LOG_VARS("heightAfter: ", height);
        LOG_EXIT_SECTION();
        return !flag;
    }
    node *rotateLeft() {
        LOG_ADD_SECTION("rotateLeft");
        node *r = right;
        right = r->left;
        r->left = this;
        updateHeight();
        updateWeight();
        r->updateHeight();
        r->updateWeight();
        LOG_EXIT_SECTION();
        return r;
    }
    node *rotateRight() {
        LOG_ADD_SECTION("rotateRight");
        node *l = left;
        left = l->right;
        l->right = this;
        updateHeight();
        updateWeight();
        l->updateHeight();
        l->updateWeight();
        LOG_EXIT_SECTION();
        return l;
    }
    node *rotateLeftRight() {
        LOG_ADD_SECTION("rotateLeftRight");
        left = left->rotateLeft();
        updateWeight();
        node *temp = rotateRight();
        temp->updateHeight();
        LOG_EXIT_SECTION();
        return temp;
    }
    node *rotateRightLeft() {
        LOG_ADD_SECTION("rotateRightLeft");
        right = right->rotateRight();
        updateWeight();
        node *temp = rotateLeft();
        temp->updateHeight();
        LOG_EXIT_SECTION();
        return temp;
    }

    void getLevelValuesFake(std::stringstream *stream, std::string *paddedString,
                int paddingSize, int amountThings, int depth) {
        LOG_VARS("depth: ", depth);
        LOG_ADD_SECTION("getLevelValuesFake");
        if (depth <= 0) {
            for (int i = 0; i < amountThings; i++) {
                *stream << *paddedString;
            }
            LOG_EXIT_SECTION();
            return;
        }
        getLevelValuesFake(stream, paddedString, paddingSize, amountThings / 2, depth - 1);
        getLevelValuesFake(stream, paddedString, paddingSize, amountThings / 2, depth - 1);
        LOG_EXIT_SECTION();
    }
  public:
    int value, height = 1, weight = 1;
    node *left = nullptr;
    node *right = nullptr;
    node(int num) {
        LOG_ADD_SECTION("nodeCreation");
        LOG("created Node");
        value = num;
        LOG_EXIT_SECTION();
    }
    int get(int index) {
        LOG_ADD_SECTION("getNode");
        if (left != nullptr) {
            if (index == left->weight) {
                LOG("node == index, returning value");
                LOG_EXIT_SECTION();
                return value;
            }

        } else if (index == 0) {
            LOG("no left node and index = 0, returning value");
            LOG_EXIT_SECTION();
            return value;
        }
        int outValue = getFromNextNode(index);
        LOG_EXIT_SECTION();
        return outValue;
    }
    int getFromNextNode(int index) {
        LOG_ADD_SECTION("findNextNode");
        int numOut;
        if (left == nullptr) {
            LOG("left is null");
            if (right == nullptr) {
                LOG("right also null. ERROR");
                LOG_VARS("thisWeight: ", weight);
                throw "tree get error. both branches null";
            }
            numOut = right->get(index - 1);
        } else if (index <= left->weight) {
            LOG("smaller Branch");
            numOut = left->get(index);
        } else { // else index is in bigger branc
            LOG("bigger Branch");
            int outindex = index - (left == nullptr ? 1 : (left->weight + 1));
            numOut = right->get(outindex);
        }
        LOG_EXIT_SECTION();
        return numOut;
    }
    int size() { return weight; }
    void updateWeight() {
        LOG_ADD_SECTION("updateWeight");
        if (left == nullptr) {
            LOG("LEFT NULL");
        }
        if (right == nullptr) {
            LOG("RIGHT NULL");
        }
        int leftWeight = left == nullptr ? 0 : left->weight;
        LOG_VARS("leftWeight: ", leftWeight);
        int rightWeight = right == nullptr ? 0 : right->weight;
        LOG_VARS("rightWeight: ", rightWeight);
        LOG_VARS("beforeWeight: ", weight);
        weight = leftWeight + rightWeight + 1;
        LOG_VARS("afterWeight: ", weight);
        LOG_EXIT_SECTION();
    }
    int getBalance() {
        LOG_ADD_SECTION("getBalance");
        if (left == nullptr) {
            LOG("LEFT NULL");
        }
        if (right == nullptr) {
            LOG("RIGHT NULL");
        }
        int leftHeight = left == nullptr ? 0 : left->height;
        LOG_VARS("leftHeight: ", leftHeight);
        int rightHeight = right == nullptr ? 0 : right->height;
        LOG_VARS("rightHeight: ", rightHeight);
        LOG_EXIT_SECTION();
        return rightHeight - leftHeight;
    }
    node *rebalance() {
        LOG_ADD_SECTION("rebalance");
        LOG("rebalance NODE");
        int thisBalance = getBalance();
        LOG_VARS("thisBalance", thisBalance);
        int leftBalance = left == nullptr ? 0 : left->getBalance();
        LOG_VARS("leftBalance", leftBalance);
        int rightBalance = right == nullptr ? 0 : right->getBalance();
        LOG_VARS("rightBalance", rightBalance);
        node *returnNode = this;
        if (thisBalance < -1) {
            if (leftBalance == 1) {
                returnNode = rotateLeftRight();
            } else if (leftBalance == -1) {
                returnNode = rotateRight();
            }
        } else if (thisBalance > 1) {
            if (rightBalance == -1) {
                returnNode = rotateRightLeft();
            } else if (rightBalance == 1) {
                returnNode = rotateLeft();
            }
        }
        LOG_VARS_SIMPLE("NODE ADDRESS: ", returnNode);
        LOG_EXIT_SECTION();
        return returnNode;
    }
    bool add(int num) {
        LOG_ADD_SECTION("addNode");
        bool flag = false;
        if (num == value) {
            LOG("inputed value is the same as node");
            LOG_EXIT_SECTION();
            return false;
        } else if (num < value) {
            LOG("Add to left");
            if (addLeft(num)) {
                LOG("need to UpdateHeight");
                flag = updateHeight();
            }
            LOG("Rebalance left");
            left = left->rebalance();
            if (flag) {
                LOG("Need to tell parent to update height");
            }
        } else if (num > value) {
            LOG("Add to Right");
            if (addRight(num)) {
                LOG("need to UpdateHeight");
                flag = updateHeight();
            }
            LOG("Rebalance Right");
            right = right->rebalance();
            if (flag) {
                LOG("Need to tell parent to update height");
            }
        }
        LOG("Need to update weight");
        updateWeight();
        LOG_EXIT_SECTION();
        return flag;
    }
    void getLevelValues(std::stringstream *stream, std::string *paddedString,
                  int paddingSize, int amountThings, int depth) {
        LOG_ADD_SECTION("getLevelValues");
        LOG_VARS("height: ", height);
        LOG_VARS("depth: ", depth);
        LOG_VARS("paddingSectionAmount: ", amountThings);
        if (depth <= 0) {
            LOG("yes");
            *stream << getValuePadded(paddingSize);
            LOG("yes");
            for (int i = 0; i < amountThings - 1; i++) {
                *stream << *paddedString;
            }
            LOG("exiting");
            LOG_EXIT_SECTION();
            return;
        }
        if (left != nullptr) {
            left->getLevelValues(stream, paddedString, paddingSize, amountThings / 2,
                           depth - 1);
        } else {
            getLevelValuesFake(stream, paddedString, paddingSize, amountThings / 2,
                   depth - 1);
        }
        if (right != nullptr) {
            right->getLevelValues(stream, paddedString, paddingSize, amountThings / 2,
                            depth - 1);
        } else {
            getLevelValuesFake(stream, paddedString, paddingSize, amountThings / 2,
                   depth - 1);
        }
        LOG_EXIT_SECTION();
    }
    std::string getValuePadded(int paddingSize) {
        LOG_ADD_SECTION("getValuePadded");
        std::stringstream chunkOut;
        chunkOut << std::to_string(value);
        for (int i = std::to_string(value).size(); i < paddingSize; i++) {
            chunkOut << " ";
        }
        LOG_EXIT_SECTION();
        return chunkOut.str();
    }
};

class TreeStart {
  private:
    node *root = nullptr;

  public:
    TreeStart() {}
    void add(int num) {
        LOG_ADD_SECTION("TreeAdd");
        if (root == nullptr) {
            LOG("treeRoot null. creating root.");
            root = new node(num);
            LOG_EXIT_SECTION();
            return;
        }
        LOG("Adding to root");
        root->add(num);
        root = root->rebalance();
        LOG_EXIT_SECTION();
    }
    int get(int index) {
        LOG_ADD_SECTION("TreeGet");
        if (root == nullptr) {
            LOG("Nothing in tree");
            LOG_EXIT_SECTION();
            throw "Nothing in tree";
        }
        int valueOut = root->get(index);
        LOG_EXIT_SECTION();
        return valueOut;
    }
    bool contains(int num) { return true; }
    int size() {
        LOG_ADD_SECTION("TreeSize");
        int temp = root == nullptr ? 0 : root->size();
        LOG_EXIT_SECTION();
        return temp;
    }
    void drawTreeLOG() {
        LOG_ADD_SECTION("printTree");
        if (root == nullptr) {
            LOG("no tree qwq");
            return;
        }
        LOG_TOGGLE();
        std::stringstream stream;
        int sectionSize = std::log10(root->get(root->size() - 1)) + 1;
        LOG_VARS("sectionSize: ", sectionSize);
        int totalSectionAmount = std::pow(2, root->height-1);
        LOG_VARS("height: ", root->height);
        LOG_VARS("totalSectionAmount: ", totalSectionAmount);
        std::string paddingString = generatePaddedString(sectionSize, '_');
        for (int i = 0; i < root->height; i++) {
            LOG_VARS("i/height: ", i);
            root->getLevelValues(&stream, &paddingString, sectionSize,
                           totalSectionAmount, i);
            std::cout << stream.str() << "\n";
            stream.str("");
        }
        LOG("finished");
        LOG_EXIT_SECTION();
    }
    std::string generatePaddedString(int amount, char charecter) {
        std::stringstream stream;
        for (int i = 0; i < amount; i++) {
            stream << charecter;
        }
        return stream.str();
    }
};
