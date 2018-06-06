#include <iostream>
#include <vector>
#include <algorithm>

int main() {

 std::vector<int> v;
 v.push_back(5);
 v.push_back(7);
 v.push_back(9);
 
 std::cout << v.size() << std::endl;

 //Print Method #1 Copy to output stream  
 std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

 //Print Method #2 Range based iterator
 for (const auto& value : v) {
   std::cout<< value;
 } 
 
 return 0;
}
