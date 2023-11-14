#include <cxxopts.hpp>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <source_location>
#include <string>
#include <utility>
#include <vector>

auto is_palindrome(int i) -> bool
{
    auto str = std::to_string(i);

    return std::ranges::equal(str | std::views::take(str.size() / 2),
                              str | std::views::reverse | std::views::take(str.size() / 2));
}

auto longestCommonPrefix(const std::vector<std::string> &strs) -> std::string
{
    auto common = std::string{strs[0]};
    for (const auto &str : strs)
    {
        auto end = std::ranges::mismatch(common, str).in1;
        common.resize(static_cast<size_t>(std::ranges::distance(common.begin(), end)));
    }
    return common;
}

auto is_valid(std::string s) -> bool
{
    auto token_stack = std::stack<char>{};
    auto tokens = std::unordered_map<char, char>{{')', '('}, {'}', '{'}, {']', '['}};
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

auto main(int argc, char **argv) -> int
{
    auto options = cxxopts::Options{std::source_location::current().file_name()};
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

    auto v = std::vector<std::string>{"asdf", "astg", "as"};
    std::cout << "Common prefix is: " << longestCommonPrefix(v) << '\n';

    auto s = std::string{"(){}[]([{}{}])"};
    std::cout << s << " is " << (!is_valid(s) ? " not " : "") << " valid.\n";
    return 0;
}
