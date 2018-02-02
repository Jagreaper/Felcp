include $(_MAKE_INCLUDE_PATH)Rules-Compiler.make
include $(_MAKE_INCLUDE_PATH)Rules-Clean.make
include $(_MAKE_INCLUDE_PATH)Rules-Dist.make
include $(_MAKE_INCLUDE_PATH)Rules-Dependencies.make

clean-debug: .clean-debug-pre .clean-debug .clean-debug-post

clean-release: .clean-release-pre .clean-release .clean-release-post

clean: clean-debug clean-release

build-debug: .compile-debug-pre .compile-debug .compile-debug-post

build-release: .compile-release-pre .compile-release .compile-release-post

build: build_debug build_release

rebuild-debug: clean-debug build-debug

rebuild-release: clean-release build-release

rebuild: rebuild-debug rebuild-release

distr: .distr-pre .distr-clean rebuild .distr-copy .distr-post