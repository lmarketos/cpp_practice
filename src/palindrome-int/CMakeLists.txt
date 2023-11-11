add_executable(palindrome-int main.cpp)
target_include_directories(palindrome-int PUBLIC ${cxxopts_INCLUDE_DIRS})
install(TARGETS palindrome-int DESTINATION bin)
target_compile_features(palindrome-int PUBLIC cxx_std_23)

