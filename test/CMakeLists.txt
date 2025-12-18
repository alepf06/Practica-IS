# GTest include code for fetch content over the internet 
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
  GIT_SHALLOW    TRUE
  GIT_PROGRESS   TRUE
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
# End GTest include code

add_executable(test_sistema test_sistema.cc)
target_link_libraries(test_sistema
	PRIVATE GTest::gtest_main sistema)
gtest_discover_tests(test_sistema)
