#include <bits/stdc++.h>
#include <boost/process.hpp>

using namespace std;

namespace bp = boost::process;

int main(int argc, char *argv[]) {
  string mode = argv[1];
  string script_path = argv[2];
  string input_path = argv[3];
  string output_path = argv[4];
  cerr << mode << endl;
  cerr << script_path << endl;
  cerr << input_path << endl;
  cerr << output_path << endl;
  bp::system(script_path,
             bp::std_out > output_path,
             bp::std_err > stderr,
             bp::std_in < input_path);
}
