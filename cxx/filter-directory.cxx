#if 0
#include <iostream>
#include <vector>
#include <filesystem>
#endif

#include <bits/stdc++.h>

namespace fs = std::filesystem;
using namespace std;

int main(int argc, const char * argv[])
{
	fs::path current = fs::current_path();
	fs::path search;
	vector<fs::directory_entry> files;

	//cin >> search;
	search = "cxx";
	search = fs::canonical(current / search);
	cout << "search " << search << endl;

	error_code err;
	// follow_directory_symlink will allow directory traversal
	copy_if(fs::recursive_directory_iterator(search /*, fs::directory_options::follow_directory_symlink */),
			fs::recursive_directory_iterator(),
			back_inserter(files),
			[ &current, &files ] (auto &dent) -> bool
			{
				auto path = dent.path();
				auto relpath = fs::relative(path, current);
				cout << "relpath " << relpath << endl;
				// ends_with is c++20 only
				auto ret = path.string().ends_with(".cxx");
				//cout << "ends with .cxx " << ret << endl;
				auto ret_find = relpath.string().find("..");
				//warning: find_first_of find char only not substring

				//cout << "ret_find " << ret_find << endl;
				ret = ret && (ret_find == string::npos);
				cout << (ret ? "\e[32m" : "\e[0m") << "find " << path << "\e[0m" << endl;
				cout << endl;
				return ret;
			});

	for (auto &f : files) {
		cout << f << endl;
	}

	return 0;
}