#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>
#include <iterator>

using coord = std::pair<size_t,size_t>;

namespace std {
  template<>
  struct hash<coord> {
    size_t operator()(const coord & pr) const {
      return std::hash<size_t>()(pr.first)^std::hash<size_t>()(pr.second);
    }
  };
}

namespace std {
  std::ostream & operator<<(std::ostream & os, const coord & pos) {
    os << "(" << pos.first << "," << pos.second << ")";
    return os;
  }
}

class solution {
public:
  int maximalRectangle(const std::vector<std::vector<int>> & mat) {
    std::unordered_map<coord, coord> recs;
    for (size_t i = 0; i < mat.size(); ++i) {
      for (size_t j = 0; j < mat[i].size(); ++j) {
	if (mat[i][j] == 1) {
	  auto curr = std::make_pair(i,j);
	  std::vector<coord> cands = extend(mat, std::make_pair(curr,curr));
	  std::cout << "topleft = (" << i << "," << j << "):\n";
	  std::copy(cands.begin(), cands.end(), std::ostream_iterator<coord>(std::cout, " "));
	  std::cout << std::endl;
	  auto it = std::max_element(cands.begin(), cands.end());
	  recs.insert(std::make_pair(curr, *it));
	}                    
      }
    }

    auto it = std::max_element(recs.begin(), recs.end(),
			       [](const std::pair<coord, coord> & p1, const std::pair<coord, coord> & p2){
				 return (p1.second.second-p1.first.second+1)*(p1.second.first-p1.first.first+1) < (p2.second.second-p2.first.second+1)*(p2.second.first-p2.first.first+1);
			       });
    std::cout << "(" << it->first.first << "," << it->first.second << ") - (" << it->second.first << "," << it->second.second << ")" << std::endl;
    return (it->second.second-it->first.second+1)*(it->second.first-it->first.first+1);
  }

private:
  std::vector<coord> extend(const std::vector<std::vector<int>> & mat,const std::pair<coord, coord> & curr) {
    std::vector<coord> result;
    auto next = getNext(mat, curr);
    if (next.empty())
      result.push_back(curr.second);
    else {
      for (auto nx : next) {
	auto temp = extend(mat, std::make_pair(curr.first, nx));
	for (auto tmp :temp)
	  result.push_back(tmp);
      }
    }
    return result;
  }

  std::vector<coord> getNext(const std::vector<std::vector<int>> & mat,const std::pair<coord,coord> & curr) {
    std::vector<coord> next;
    auto topleft = curr.first, botright = curr.second;
    if (botright.first < mat.size()-1) {
      std::vector<int> temp;
      for (size_t j = topleft.second; j <= botright.second; j++)
	temp.push_back(mat[botright.first+1][j]);
      if (std::all_of(temp.begin(), temp.end(), [](int i){return i == 1;}))
	next.push_back(std::make_pair(botright.first+1, botright.second));
    }
    if (botright.second < mat[0].size()-1) {
      std::vector<int> temp;
      for (size_t i = topleft.first; i <= botright.first; i++)
	temp.push_back(mat[i][botright.second+1]);
      if (std::all_of(temp.begin(), temp.end(), [](int i){return i == 1;}))
	next.push_back(std::make_pair(botright.first, botright.second+1));
    }
    return next;
  }
};

int main() {
  std::vector<std::vector<int>> matrix{
    {1,0,1,0,0},
      {1,0,1,1,1},
	{1,1,1,1,1},
	  {1,0,0,1,0}
  };

  solution soln;
  int maxRec = soln.maximalRectangle(matrix);
  std::cout << "The largest rectangle containing 1's has an area of " << maxRec << std::endl;
}
