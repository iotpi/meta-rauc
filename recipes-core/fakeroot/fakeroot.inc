DESCRIPTION = "Gives a fake root environment"
HOMEPAGE = "http://fakeroot.alioth.debian.org"
SECTION = "base"
LICENSE = "GPLv3"
LIC_FILES_CHKSUM = "file://COPYING;md5=f27defe1e96c2e1ecd4e0c9be8967949"

inherit autotools

DEPENDS = "libcap"

SRC_URI = "\
    http://ftp.debian.org/debian/pool/main/f/fakeroot/fakeroot_${PV}.orig.tar.gz \
"

# fakeroot needs getopt which is provided by the util-linux package
RDEPENDS_${PN} = "util-linux bash"

FILES_${PN} = "${bindir}/fakeroot \
               ${bindir}/faked \
               ${libdir}/libfakeroot-0.so \
               ${libdir}/libfakeroot.so \
              "
PACKAGES = "${PN} ${PN}-dbg"

# https://stackoverflow.com/questions/34761974/qa-issue-in-yocto-build-while-trying-to-pack-symlink-in-my-image
INSANE_SKIP_${PN} = "dev-so"

do_configure_prepend() {
    (cd ${S} && [ -f Makefile ] && make distclean ; ./bootstrap)
}

do_install_append() {
    ln -sf libfakeroot-0.so ${D}${libdir}/libfakeroot.so
}
