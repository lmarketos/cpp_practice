#include <cxxopts.hpp>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <source_location>
#include <string>
#include <utility>
#include <vector>

bool is_palindrome(int i)
{
    auto str = std::to_string(i);

    return std::ranges::equal(str | std::views::take(str.size() / 2),
                              str | std::views::reverse | std::views::take(str.size() / 2));
}

std::string longestCommonPrefix(const std::vector<std::string> &strs)
{
    std::string common{strs[0]};
    for (const auto &str : strs)
    {
        auto end = std::ranges::mismatch(common, str).in1;
        common.resize(static_cast<size_t>(std::ranges::distance(common.begin(), end)));
    }
    return common;
}

bool is_valid(std::string s)
{
    std::stack<char> token_stack{};
    std::unordered_map<char, char> tokens{{')', '('}, {'}', '{'}, {']', '['}};
    for (auto c : s)
    {
        auto closing = tokens[c];

        if (token_stack.size() > 0 && closing == token_stack.top())
        {
            token_stack.pop();
        }
        else
        {
            token_stack.push(c);
        }
    }

    return token_stack.empty();
}

int main(int argc, char **argv)
{
    cxxopts::Options options(std::source_location::current().file_name());
    options.add_options()("i", "Int to check for palindrome", cxxopts::value<int>())("h,help", "Print usage");
    options.parse_positional({"i"});
    auto result = options.parse(argc, argv);
    if (result.count("help") || !result.count("i"))
    {
        std::cout << options.help() << '\n';
        return 0;
    }

    auto i = result["i"].as<int>();
    std::cout << i << " is " << (!is_palindrome(i) ? " not " : "") << "a palindrome!\n";

    std::vector<std::string> v{"asdf", "astg", "as"};
    std::cout << "Common prefix is: " << longestCommonPrefix(v) << '\n';

    std::string s = "(){}[]([{}{}])";
    std::cout << s << " is " << (!is_valid(s) ? " not " : "") << " valid.\n";
    return 0;
}
