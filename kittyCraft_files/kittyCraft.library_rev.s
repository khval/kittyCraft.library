VERSION = 53
REVISION = 1

.macro DATE
.ascii "21.3.2020"
.endm

.macro VERS
.ascii "kittyCraft.library 53.1"
.endm

.macro VSTRING
.ascii "kittyCraft.library 53.1 (21.3.2020)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: kittyCraft.library 53.1 (21.3.2020)"
.byte 0
.endm
