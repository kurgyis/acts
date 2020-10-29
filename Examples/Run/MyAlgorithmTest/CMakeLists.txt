add_executable(
  ActsExampleMyAlgorithmTest
  MyAlgorithmTest.cpp
  MyAlgorithm.cpp)
target_link_libraries(
  ActsExampleMyAlgorithmTest
  PRIVATE
    ActsCore
    ActsExamplesFramework ActsExamplesCommon
    Boost::program_options)

install(
  TARGETS ActsExampleMyAlgorithmTest
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
