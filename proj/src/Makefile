# Project Name
PROG=proj

# Source directories
.PATH: ${.CURDIR}/controller/
.PATH: ${.CURDIR}/controller/keyboard
.PATH: ${.CURDIR}/controller/mouse
.PATH: ${.CURDIR}/controller/timer
.PATH: ${.CURDIR}/controller/video
.PATH: ${.CURDIR}/controller/rtc
.PATH: ${.CURDIR}/model/
.PATH: ${.CURDIR}/view/

# Source files to be compiled
SRCS = main.c utils.c timer.c KBC.c keyboard.c mouse.c graphic.c rtc.c model.c sprite.c view.c

# Compilation flags
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_ -O2

# Dependências
DPADD += ${LIBLCF}
LDADD += -Wall -llcf -lxpm -llm
.include <minix.lcom.mk>
