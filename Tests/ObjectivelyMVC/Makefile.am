
AM_TESTS_ENVIRONMENT = \
	AM_TESTS=1; export AM_TESTS;

DEFAULT_INCLUDES = \
	$(top_srcdir)/Sources

TESTS = \
	Constraint

CFLAGS += \
	-I$(top_srcdir)/Sources \
	@HOST_CFLAGS@ \
	@CHECK_CFLAGS@ \
	@FONTCONFIG_CFLAGS@ \
	@OBJECTIVELY_CFLAGS@ \
	@SDL2_CFLAGS@

LDADD = \
	$(top_srcdir)/Sources/ObjectivelyMVC/libObjectivelyMVC.la \
	@HOST_LIBS@ \
	@CHECK_LIBS@ \
	@FONTCONFIG_LIBS@ \
	@OBJECTIVELY_LIBS@ \
	@SDL2_LIBS@

check_PROGRAMS = \
	$(TESTS)
