#include <cstddef>
#include <iostream>
#include <vector>
#include <map>

struct State {
  std::map<char, int> transitions;
  int link = -1;
  int length = 0;
  bool isClone = false;
};

class SuffixAutomaton {
 public:
  SuffixAutomaton() = default;

  explicit SuffixAutomaton(const std::string& s) {
    states_.emplace_back();
    for (char c : s) {
      Add(c);
    }
  }

  void Add(char c) {
    int current_state_index = static_cast<int>(states_.size());
    states_.emplace_back();
    states_[current_state_index].length = states_[last_idx_].length + 1;
    int prev_state_index = last_idx_;

    while (prev_state_index != -1 && !states_[prev_state_index].transitions.count(c)) {
      states_[prev_state_index].transitions[c] = current_state_index;
      prev_state_index = states_[prev_state_index].link;
    }

    if (prev_state_index == -1) {
      states_[current_state_index].link = 0;
    } else {
      int next_state_index = states_[prev_state_index].transitions[c];
      if (states_[prev_state_index].length + 1 == states_[next_state_index].length) {
        states_[current_state_index].link = next_state_index;
      } else {
        int clone_state_index = static_cast<int>(states_.size());
        states_.emplace_back(states_[next_state_index]);
        states_[clone_state_index].length = states_[prev_state_index].length + 1;
        states_[clone_state_index].isClone = true;

        while (prev_state_index != -1 && states_[prev_state_index].transitions[c] == next_state_index) {
          states_[prev_state_index].transitions[c] = clone_state_index;
          prev_state_index = states_[prev_state_index].link;
        }
        states_[current_state_index].link = clone_state_index;
        states_[next_state_index].link = clone_state_index;
      }
    }
    last_idx_ = current_state_index;
  }

  void PrintAutomaton() {
    std::cout << states_.size() << "\n";
    for (size_t i = 0; i < states_.size(); ++i) {
      for (const auto& transition : states_[i].transitions) {
        std::cout << i << " " << transition.first << " " << transition.second << "\n";
      }
    }
  }

 private:
  std::vector<State> states_;
  int last_idx_ = 0;
};

int main() {
  std::string s;
  std::cin >> s;
  SuffixAutomaton automaton(s);
  automaton.PrintAutomaton();
}
