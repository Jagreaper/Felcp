## CLEAN ##
.clean-debug-pre:

.clean-debug-post:

.clean-release-pre:

.clean-release-post:

## BUILD ##
.compile-debug-pre: .clean_dependencies_debug

.compile-debug-post: .copy_dependencies_debug
	
.compile-release-pre: .clean_dependencies_release

.compile-release-post: .copy_dependencies_release

## DIST ##
.distr-pre:

.distr-post: