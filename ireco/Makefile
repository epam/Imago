all:
	ls ../iSMILES/src/Image/*.cpp ../imago/src/*.cpp | sed '/lock_win.cpp/d' | sed '/thread_local_win.cpp/d' | sed '/test_main.cpp/d' | xargs g++ -o recognize main.cpp -I../imago/src/ -I../ -I../iSMILES/src/Image/ -O2 -Wall -lpng -lpthread -ljpeg -v
