QTMQTT_VERSION = 5.11
QTMQTT_SITE = $(call github,qt,qtmqtt,$(QTMQTT_VERSION))

define QTMQTT_CONFIGURE_CMDS 
	$(HOST_MAKE_ENV) qmake -makefile -o $(@D)/Makefile $(@D)/qtmqtt.pro
endef

define QTMQTT_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

$(eval $(generic-package))
