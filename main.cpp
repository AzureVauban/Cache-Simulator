// Michael Elder
// Extra Credit 3 - Cache Simulator

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <deque>

using namespace std;

class CacheSimulator {
private:
    int blockSize;
    int numBlocks;
    int associativity;
    string replacementPolicy;
    vector<deque<pair<int, int>>> cache; // Each set contains a deque of (tag, time) pairs
    int hits;
    int misses;
    int currentTime;

public:
    CacheSimulator(int blockSize, int numBlocks, int associativity, string replacementPolicy)
        : blockSize(blockSize), numBlocks(numBlocks), associativity(associativity),
          replacementPolicy(replacementPolicy), hits(0), misses(0), currentTime(0) {
        cache.resize(numBlocks / associativity);
    }

    pair<int, int> computeIndexTag(int address) {
        int blockAddress = address / blockSize;
        int index = blockAddress % (numBlocks / associativity);
        int tag = blockAddress / (numBlocks / associativity);
        return {index, tag};
    }

    void accessCache(int address) {
        currentTime++;
        auto [index, tag] = computeIndexTag(address);

        auto &set = cache[index];
        for (auto &entry : set) {
            if (entry.first == tag) {
                hits++;
                entry.second = currentTime; // Update LRU time
                cout << "Index: " << hex << index << "\tTag: " << hex << tag << "\tHIT\n";
                return;
            }
        }

        misses++;
        cout << "Index: " << hex << index << "\tTag: " << hex << tag << "\tMISS\n";

        if (set.size() == associativity) {
            if (replacementPolicy == "LRU") {
                set.pop_front(); // Remove least recently used
            } else if (replacementPolicy == "MRU") {
                set.pop_back(); // Remove most recently used
            }
        }

        set.push_back({tag, currentTime});
    }

    void printStats() const {
        int totalAccesses = hits + misses;
        double hitRate = (double)hits / totalAccesses * 100;
        double missRate = (double)misses / totalAccesses * 100;

        cout << "\nCache Statistics:\n";
        cout << "Total Accesses: " << totalAccesses << endl;
        cout << "Hits: " << hits << endl;
        cout << "Misses: " << misses << endl;
        cout << "Hit Rate: " << hitRate << "%" << endl;
        cout << "Miss Rate: " << missRate << "%" << endl;
    }
};

int main() {
    int N, B, I, associativity;
    string replacementPolicy, filename;

    cout << "Enter total address space (2^N bytes): ";
    cin >> N;
    cout << "Enter block size (in bytes): ";
    cin >> B;
    cout << "Enter number of blocks: ";
    cin >> I;
    cout << "Enter associativity (1 for direct-mapped): ";
    cin >> associativity;
    cout << "Enter replacement policy (LRU/MRU): ";
    cin >> replacementPolicy;
    cout << "Enter filename containing addresses: ";
    cin >> filename;

    CacheSimulator simulator(B, I, associativity, replacementPolicy);

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }

    string line;
    cout << "\nSimulating memory accesses:\n";
    while (getline(file, line)) {
        int address;
        stringstream ss(line);
        ss >> hex >> address;
        simulator.accessCache(address);
    }

    simulator.printStats();

    return 0;
}


