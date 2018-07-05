QTMQTT_VERSION = 5.10
QTMQTT_SITE = https://code.qt.io/qt/qtmqtt.git
QTMQTT_SITE_METHOD=git
QTMQTT_INSTALL_STAGING = YES
QTMQTT_DEPENDENCIES = qt5base

define QTMQTT_CONFIGURE_CMDS
	(cd $(@D); mkdir build)
	(cd $(@D); tar -zxf $(BR2_EXTERNAL_EMB22109_PATH)/package/qtmqtt/qtmqtt-fixgit.tgz)
	(cd $(@D)/build; $(TARGET_MAKE_ENV) $(HOST_DIR)/bin/qmake -r ..)
endef

define QTMQTT_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/build
endef

define QTMQTT_INSTALL_STAGING_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/build install
	$(QT5_LA_PRL_FILES_FIXUP)
endef

ifeq ($(BR2_STATIC_LIBS),)
define QTMQTT_INSTALL_TARGET_CMDS
	cp -dpf $(STAGING_DIR)/usr/lib/libQt5Mqtt.so.* $(TARGET_DIR)/usr/lib
	cp -dpfr $(STAGING_DIR)/usr/lib/qt/examples/mqtt $(TARGET_DIR)/usr/lib/qt/examples/ 
endef
endif

$(eval $(generic-package))
