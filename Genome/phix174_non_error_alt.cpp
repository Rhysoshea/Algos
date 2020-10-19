#include <iostream>
#include <cstring>
#include <vector>

int calculate_overlap(const std::string & a, const std::string & b, const int mer) noexcept
{
    for (int i = 0, n = 1 + a.size()-mer; i < n; ++i)
        if(strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0)
            return a.size() - i;
    return 0;
}

std::string assemble_genome(std::vector<std::string> input, const int mer) noexcept
{
    std::string genome;
    genome.reserve(1000);
    genome += input.front(); // genome begins with first read

    std::string first_read = input.front(), cur_read = "";
    int cur_index = 0;

    while(input.size() > 1)
    {
        cur_read = std::move(input[cur_index]); //allocates the value to cur_read
        input.erase(input.begin() + cur_index); //erases first read

        int max_overlap = -1;

        for(int j = 0; j < input.size(); ++j)
        {
            int overlap = calculate_overlap(cur_read, input[j], mer);
            if(overlap > max_overlap) max_overlap = overlap, cur_index = j;
        }

        genome += input[cur_index].substr(max_overlap);
    }

    genome.erase(0, calculate_overlap(input[0], first_read, mer));
    return genome;
}

int main ()
{
    std::ios::sync_with_stdio(false); // disables C and C++ synchronization
    std::cin.tie(NULL); // unties cin and cout

    std::vector<std::string> input;
    input.reserve(5); //sets the minimum capacity for the vector
    std::string s;

    // constructs the vector of input with multiple inputs s
    while(std::cin >> s)
        if(input.back() != s) input.emplace_back(std::move(s));

    std::cout << assemble_genome(std::move(input), 0) << std::endl;

    return 0;
}
