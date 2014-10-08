REM Call of letter black operation
CLS
PRINT "                          Call Of Letter  Black Operation"
SLEEP (2)
CLS
PRINT "Welcome::"
PRINT "1.Single Player"
PRINT "2.Exit"
DO
    in$ = INKEY$
LOOP UNTIL in$ = "1" OR in$ = "2"
IF in$ = "2" THEN
    CLS
    PRINT "Closed."
    SLEEP (1)
    END
END IF
IF in$ = "1" THEN
    CLS
    PRINT "Starting New Game....."
    SLEEP (2)
    PRINT "No SAVING ALLOWED"
    SLEEP (1)
    CLS
    PRINT "Your Name Is GRISS"
    SLEEP (1)
    CLS
    FOR i = 1 TO 20
        IF i = 1 THEN
            PRINT "Mike::Hey Griss."
            SLEEP (2)
            PRINT "Griss::Hi Mike"
            PRINT "Griss::How are you."
            SLEEP (2)
            PRINT "Mike::Good."
            SLEEP (2)
            PRINT "Mike::Did you remember Asman."
            SLEEP (2)
            PRINT "Griss::NO."
            SLEEP (1)
            PRINT "Mike::Shit!!Shit!!"
            SLEEP (5)
            PRINT "Mike::How did you forgot that bastard!"
            SLEEP (5)
            PRINT "Griss::Was he a bastard"
            SLEEP (1)
            PRINT "Mike::For god sake dont say this!"
            SLEEP (2)
            PRINT "BOOM BOOM!"
            SLEEP (1)
            PRINT "Mike::Shit!"
            SLEEP (2)
            PRINT "Griss::Who are they ? "
            SLEEP (1)
            PRINT "Commander::The PLA"
            PRINT "Commander::Common man get moving . They will burst your ASS."
            SLEEP 2
            PRINT "Griss::OK"
            SLEEP 3
            PRINT "Griss::Get me a weapon !"
            SLEEP (1)
            PRINT "Mike::Ok . See you at field"
            SLEEP (1)
            PRINT "Griss::OK"
            SLEEP (2)
            CLS
            ph = 100
            e1h = 100
            e2h = 100
            e3h = 100
            e4h = 100
            e5h = 100
            pc = 4
            pr = 8
            e1c = 13
            e1r = 15
            e2r = 5
            e2c = 5
            e3c = 13
            e3r = 16
            e4r = 17
            e4c = 17
            e1c = 13
            e1r = 20
            pbl = 145
            cv1c = 8
            cv1r = 8
            pb = 30
            DO
                CLS
                in$ = INKEY$
                IF e1h > 0 THEN
                    LOCATE e1r, e1c
                    PRINT "E"
                END IF
                IF e2h > 0 THEN
                    LOCATE e2r, e2c
                    PRINT "E"
                END IF
                IF e3h > 0 THEN
                    LOCATE e3r, e3c
                    PRINT "E"
                END IF
                IF e4h > 0 THEN
                    LOCATE e4r, e4c
                    PRINT "E"
                END IF
                IF e5h > 0 THEN
                    LOCATE e5r, e5c
                    PRINT "E"
                END IF
            LOOP
        END IF
    NEXT i
END IF
END




