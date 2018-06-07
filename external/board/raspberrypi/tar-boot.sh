#!/bin/sh
if [ ! -d ${BINARIES_DIR}/boot ] 
then
	mkdir ${BINARIES_DIR}/boot
fi

cp -r ${BINARIES_DIR}/rpi-firmware/* ${BINARIES_DIR}/boot/
cp ${BINARIES_DIR}/*.dtb ${BINARIES_DIR}/boot/
cp ${BINARIES_DIR}/zImage ${BINARIES_DIR}/boot/

(cd ${BINARIES_DIR}/boot && tar -zcvf ../boot.tar.gz *)

exit $?
