set(SRC
  mol-compare.cpp
)

FILE(GLOB HEADERS "*.h")
list(APPEND SRC ${HEADERS})

add_executable(mol-compare ${SRC})
include_directories(..)
