// // C++ implementation to read
// // file word by word
// #include <bits/stdc++.h>
// using namespace std;
//
// // driver code
// int main()
// {
// 	// filestream variable file
// 	fstream file;
// 	string word, t, q, filename;
//
// 	// filename of the file
// 	filename = "and_xor.dot";
//
// 	// opening file
// 	file.open(filename.c_str());
//
// 	// extracting words from the file
// 	while (file >> word)
// 	{
// 		// displaying content
// 		cout << word << endl;
// 	}
//
// 	return 0;
// }



#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::string s = "This Is An Example";
    std::cout << "1) " << s << '\n';

    s.erase(7, 3); // erases " An" using overload (1)
    std::cout << "2) " << s << '\n';

    s.erase(std::find(s.begin(), s.end(), ' ')); // erases first ' '; overload (2)
    std::cout << "3) " << s << '\n';

    s.erase(s.find(' ')); // trims from ' ' to the end of the string; overload (1)
    std::cout << "4) " << s << '\n';
}
