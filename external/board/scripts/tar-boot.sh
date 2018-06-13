#!/bin/sh
if [ ! -d ${BINARIES_DIR}/boot ] 
then
	mkdir ${BINARIES_DIR}/boot
fi

mcopy -si ${BINARIES_DIR}/boot.vfat ::* ${BINARIES_DIR}/boot/ 

(cd ${BINARIES_DIR}/boot && tar -zcvf ../boot.tar.gz *)

if [ -f ${BINARIES_DIR}/rootfs.tar.gz ]
then
	rm ${BINARIES_DIR}/rootfs.tar
fi

rm -rf ${BINARIES_DIR}/boot

exit $?
