#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <set>

void analyze_document(const std::string & fname);

int main(int argc, char **argv)
{
    const std::string FNAME = argv[1];

    analyze_document(FNAME);

    return 0;
}

void analyze_document(const std::string & fname)
{
    std::ifstream file(fname);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fname << std::endl;
        return;
    }

    std::map<std::string, int> word_count;
    std::string word;

    while (file >> word) {
        size_t start = 0;
        while (start < word.size() && std::ispunct(word[start])) {
            start++;
        }

        size_t end = word.size();
        while (end > start && std::ispunct(word[end - 1])) {
            end--;
        }
        word = word.substr(start, end - start);
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty()) {
            word_count[word]++;
        }
    }

    std::vector<std::pair<std::string,int>> freq(word_count.begin(), word_count.end());
    std::sort(freq.begin(), freq.end(),
              [](auto &a, auto &b) {
                  return a.second > b.second;
              });
    for (int i = 0; i < 20; ++i) {
        std::cout << (i + 1) << ". " << freq[i].first << ": " << freq[i].second << " veces\n";
    }
}
