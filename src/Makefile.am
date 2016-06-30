AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = zerg
zerg_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc

zerg_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(SPY_CPPFLAGS) \
		$(ZEBRA_CPPFLAGS) \
		$(RAPIDJSON_CPPFLAGS) \
		$(JSON_CPPFLAGS) \
		$(ZOD_CPPFLAGS)


zerg_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(AIR_LIBADD) \
	$(ZEBRA_LIBADD) \
	$(JSON_LIBADD) \
	$(ZOD_LIBADD)


zerg_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh \
	Log.hh \
	Server.hh

EXTRA_DIST = env.sh zerg.cfg log.cfg

zergdir = $(bindir)
zerg_DATA = $(EXTRA_DIST)

