#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>

namespace std {
    struct hash<std::pair<size_t,size_t>> {
        size_t operator()(const std::pair<size_t,size_t> & pr) {
            return std::hash<size_t>()(pr.first)^std::hash<size_t>()(pr.second);
        }
    };
}

class solution {
  public:
    int maximalRectangle(const std::vector<std::vector<int>> & mat) {
        std::unordered_map<std::pair<size_t,size_t>, std::pair<size_t,size_t>> recs;
        for (size_t i = 0; i < mat.size(); ++i) {
            for (size_t j = 0; j < mat[i].size(); ++j) {
                if (mat[i][j] == 1) {
                    std::vector<std::pair<size_t,size_t>> cands = extend(mat, std::make_pair(i,j));
                    auto it = std::max_element(cands.begin(), cands.end());
                    recs.insert(std::make_pair(i,j), *it);
                }                    
            }
        }

        auto it = std::max_element(recs.begin(), recs.end(),
                                   [](const std::pair<std::pair<size_t,size_t>, std::pair<size_t,size_t>> & p1,const std::pair<std::pair<size_t,size_t>, std::pair<size_t,size_t>> & p2){
                                       return (p1.second.second-p1.first.second+1)*(p1.second.first-p1.first.first+1) < (p2.second.second-p2.first.second+1)*(p2.second.first-p2.first.first+1);
                                   });
        return (it->second.second-it->first.second+1)*(it->second.first-it->first.first+1);
    }

  private:
    std::vector<std::pair<size_t,size_t>> extend(const std::vector<std::vector<int>> & mat, const std::pair<size_t,size_t> & curr) {
        
    }

    std::vector<std::pair<size_t,size_t>> getNext(const std::vector<std::vector<int>> & mat, const std::pair<size_t,size_t> & curr) {
        
    }
};
