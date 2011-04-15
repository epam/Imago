set(SRC
  src/static_object.cpp
  src/filter.cpp
  src/wedge_bond_extractor.cpp
  src/graph_extractor.cpp
  src/exception.cpp
  src/output.cpp
  src/scanner.cpp
  src/bitarray.cpp
  src/molecule.cpp
  src/png_loader.cpp
  src/jpg_loader.cpp
  src/font.cpp
  src/label_logic.cpp
  src/log.cpp
  src/image_utils.cpp
  src/molfile_saver.cpp
  src/segmentator.cpp
  #src/vec2d.cpp
  src/approximator.cpp
  src/label_combiner.cpp
  src/graphics_detector.cpp
  src/session_manager.cpp
  src/recognition_settings.cpp
  src/png_saver.cpp
  src/thin_filter2.cpp
  src/binarizer.cpp
  src/chemical_structure_recognizer.cpp
  src/convolver.cpp
  src/segment.cpp
  src/image.cpp
  src/fourier_descriptors.cpp
  src/separator.cpp
  src/image_draw_utils.cpp
  src/algebra.cpp
  src/double_bond_maker.cpp
  src/triple_bond_maker.cpp
  src/multiple_bond_checker.cpp
  src/segments_graph.cpp
  src/skeleton.cpp
  src/rectangle.cpp
  src/character_recognizer.cpp
  src/character_recognizer_font.cpp
  src/prefilter.cpp
  src/contour_extractor.cpp
  src/orientation_finder.cpp
  src/features_compare_method.cpp
  src/fourier_features.cpp
  src/shape_context.cpp
  src/munkres.cpp
)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

if(WIN32)
  list(APPEND SRC
    src/thread_local_win.cpp
    src/lock_win.cpp
    )
else(WIN32)
  list(APPEND SRC
    src/thread_local_posix.cpp
    src/lock_posix.cpp
    )
endif(WIN32)

include_directories(..)
include_directories(${PNG_INCLUDE_DIR})
include_directories(${JPEG_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

if(EMBED_FONT)
  add_definitions("-DIMAGO_FONT_BUILT_IN")
endif(EMBED_FONT)

add_library(imago_static STATIC ${SRC})
target_link_libraries(imago_static ${PNG_LIBRARIES} ${JPEG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(imago_static ${OpenCV_LIBS}) 
