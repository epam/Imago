include_directories(../../imago/src)

set(SRC
  calc_prob_matr.cpp
  )

add_executable(calc_probability_matrices ${SRC})

add_dependencies(calc_probability_matrices imago)
target_link_libraries(calc_probability_matrices imago)