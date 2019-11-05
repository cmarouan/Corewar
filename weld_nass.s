.name "weld nass"
.comment "we crashed everythings front of us"

        live %15
        fork %511
start:
        sti r1, %:l_live, %1
l_live:
        live %15
        ld %0 , r5
        zjmp %:start
