# used programs
RE2C = re2c
SED = sed

# additional flags
FLAGS = -Wall -Wextra -pedantic -Weffc++ -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wfloat-equal

all: json_unit

# clean up
clean:
	rm -f json_unit json_benchmarks

# build unit tests
json_unit: test/unit.cpp src/json.hpp test/catch.hpp
	$(CXX) -std=c++11 $(CXXFLAGS) $(FLAGS) $(CPPFLAGS) -I src -I test $< $(LDFLAGS) -o $@

check: json_unit
	./json_unit "*"
	make check -C docs/examples

docset:
	cp Doxyfile Doxyfile_docset
	gsed -i 's/DISABLE_INDEX          = NO/DISABLE_INDEX          = YES/' Doxyfile_docset
	gsed -i 's/SEARCHENGINE           = YES/SEARCHENGINE           = NO/' Doxyfile_docset
	gsed -i 's/GENERATE_TREEVIEW      = YES/GENERATE_TREEVIEW      = NO/' Doxyfile_docset
	gsed -i 's/SEPARATE_MEMBER_PAGES  = NO/SEPARATE_MEMBER_PAGES  = YES/' Doxyfile_docset
	gsed -i 's/BINARY_TOC             = YES/BINARY_TOC             = NO/' Doxyfile_docset
	rm -fr html *.docset
	doxygen Doxyfile_docset
	make -C html
	mv html/*.docset .
	gsed -i 's@<string>doxygen</string>@<string>json</string>@' me.nlohmann.json.docset/Contents/Info.plist
	rm -fr Doxyfile_docset html

# create scanner with re2c
re2c: src/json.hpp.re2c
	$(RE2C) -b -s -i --no-generation-date $< | $(SED) '1d' > src/json.hpp

# static analyser
cppcheck:
	cppcheck --enable=all --inconclusive --std=c++11 src/json.hpp

# pretty printer
pretty:
	astyle --style=allman --indent=spaces=4 --indent-modifiers \
	   --indent-switches --indent-preproc-block --indent-preproc-define \
	   --indent-col1-comments --pad-oper --pad-header --align-pointer=type \
	   --align-reference=type --add-brackets --convert-tabs --close-templates \
	   --lineend=linux --preserve-date --suffix=none \
	   src/json.hpp src/json.hpp.re2c test/unit.cpp benchmarks/benchmarks.cpp docs/examples/*.cpp

# update docs
update_docs:
	make create -C docs/examples

# benchmarks
json_benchmarks: benchmarks/benchmarks.cpp benchmarks/benchpress.hpp benchmarks/cxxopts.hpp src/json.hpp
	$(CXX) -std=c++11 $(CXXFLAGS) -O3 -flto -I src -I benchmarks $< $(LDFLAGS) -o $@
	./json_benchmarks
