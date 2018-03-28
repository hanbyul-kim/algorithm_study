#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int DIGIT_NUM = 10;
const bool CONTRADICT = false;
const int MAX_DIGITS = 10;

int toNumber(char ch) { return ch - '0'; }

class PhoneNumber {
    bool inserted;
    vector<PhoneNumber*> children;

public:
    PhoneNumber() : inserted(false), children(DIGIT_NUM, 0) {}

    bool insert(const char* digit) {
        auto& currentNode = children[toNumber(*digit)];
        if (currentNode == 0) currentNode = new PhoneNumber();

        if (currentNode->inserted) return CONTRADICT;

        if (*(digit + 1) == 0) {
            currentNode->inserted = true;
            return !CONTRADICT;
        }

        return currentNode->insert(digit + 1);
    }
};

int main() {
    int testCase;
    scanf("%d", &testCase);

    for (int c = 0; c < testCase; ++c) {
        int numOfItems;
        scanf("%d", &numOfItems);

        vector<string> phoneBook;
        for (int i = 0; i < numOfItems; ++i) {
            char number[MAX_DIGITS+1];
            scanf("%s", number);

            string numberStr(number);
            phoneBook.push_back(numberStr);
        }

        sort(phoneBook.begin(), phoneBook.end());

        PhoneNumber pn;
        bool result;
        for (string number : phoneBook) {
            result = pn.insert(number.c_str());
            if (result == CONTRADICT) {
                printf("NO\n");
                break;
            }
        }
        if (result == !CONTRADICT) printf("YES\n");
    }

}