#include <bits/stdc++.h>
#include <boost/process.hpp>

namespace bp = boost::process;

int RemoveFiles(const std::vector<std::string>& file_names) {
  for (const auto& file_name : file_names) {
    int ret_code = bp::system("rm " + file_name);
    if (ret_code != 0) {
      std::cerr << "can't remove file " + file_name << std::endl;
      return ret_code;
    }
  }
  return 0;
}

std::string GetFileName(const std::string& type, int name) {
  return "tmp_file_" + type + "_" + std::to_string(name) + ".txt";
}

int main(int argc, char* argv[]) {
  std::string mode = argv[1];
  std::string script_path = argv[2];
  std::string input_path = argv[3];
  std::string output_path = argv[4];
//  std::cerr << mode << std::endl;
//  std::cerr << script_path << std::endl;
//  std::cerr << input_path << std::endl;
//  std::cerr << output_path << std::endl;
  if (mode == "map") {
    bp::system(script_path, bp::std_out > output_path, bp::std_err > stderr, bp::std_in < input_path);
  } else if (mode == "reduce") {
    std::vector<std::pair<std::string, int>> words;
    { // input data
      std::string word;
      int cnt;
      std::ifstream stream(input_path);
      while (stream >> word >> cnt) {
        // std::cerr << word << " " << cnt << std::endl;
        words.emplace_back(word, cnt);
      }
    }
    // std::cerr << std::endl;

    std::sort(words.begin(), words.end());


    std::vector<std::string> input_files;
    std::vector<std::string> output_files;
    for (int i = 0; i < words.size();) {
      std::string input_file = GetFileName("input", i);
      std::string output_file = GetFileName("output", i);

      input_files.push_back(input_file);
      output_files.push_back(output_file);

      std::ofstream os(input_file);
      int first_index = i;
      while (i < words.size() && words[i].first == words[first_index].first) {
        os << words[i].first << ' ' << words[i].second << std::endl;
        // std::cerr << words[i].first << ' ' << words[i].second << std::endl;
        ++i;
      }
      auto ret_code = bp::system(script_path, bp::std_out > output_file, bp::std_err > stderr, bp::std_in < input_file);
      if (ret_code != 0) {
        std::cerr << "something went wrong..." << std::endl;
        return ret_code;
      }
    }

    if (RemoveFiles(input_files) != 0) {
      return 1;
    }

    { // output data
      std::ofstream stream(output_path);
      for (auto& name : output_files) {
        std::ifstream in(name);
        std::string word;
        int count;
        while (in >> word >> count) {
          stream << word << ' ' << count << std::endl;
        }
      }
      if (RemoveFiles(output_files) != 0) {
        return 1;
      }
    }
  } else {
    std::cerr << R"(mode can be only "map" or "reduce")" << std::endl;
  }
}
