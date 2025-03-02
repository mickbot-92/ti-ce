### KhiCAS -*- mode:text -*-
Install https://github.com/CE-Programming/toolchain/releases/tag/nightly
* both OS version and clibs *
Doc: https://ce-programming.github.io/toolchain/

Modification of the toolchain: so that malloc uses upper part of LCD ram for heap and aborts instead of returning a null pointer that is not handled correctly, copy allocator_standard.c to
toolchain/src/libc/allocator_standard.c


Compilation:
./mkappen or ./mkappfr  
will create in bin a lot of 8xv variables and an installer (8xp) 
(make V=1 app install_prog) and copy to shared/ti/app
(cp bin/App**x* shared/ti/app, mkdir -p shared/ti/app, cp bin/App**x* shared/ti/app)

bundle83 or bundle84 will bundle these 8xv files and the installer

Installation on a hardware calculator: see install_en or install_fr

Customization: some compile flags control inclusion of parts of the code
Without any flag: total size about 2260Ko
maths:
-DWITH_LAPLACE  Laplace/inverse Laplace transform about 20K
-DWITH_DESOLVE  desolve command about 60K (including Laplace)
sciences:
-DWITH_PERIODIC periodic table about 10K
-DWITH_UNITS physical units about 40K 
Note that 2 apps do never share a flash page, as a consequence you can
add space up to a multiple of 65.536, e.g. 2260Ko and 2280Ko will
leave free the same amount of flash.

