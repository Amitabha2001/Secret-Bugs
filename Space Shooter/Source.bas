SCREEN _NEWIMAGE(1100, 600, 256)
RANDOMIZE TIMER
REM =============================================
DIM SHARED shot.x(100, 2) 'x=20,y=10
DIM SHARED shot.y(100, 2)
DIM SHARED shot.exist(100, 2)
DIM SHARED timeleft
DIM SHARED ran
DIM SHARED shipexist(15) AS INTEGER
REM DIM SHARED shot.exist(2)
DIM SHARED x AS INTEGER
DIM SHARED oldt
DIM SHARED tmInit2
DIM SHARED no.attacker
DIM SHARED attacker.x(15) '=100
DIM SHARED attacker.y(15) '=70
DIM SHARED shooter.y 'x=70,y=70
DIM SHARED shotfired
DIM SHARED shooter.x
DIM SHARED ammo AS DOUBLE
DIM SHARED score AS DOUBLE
DIM SHARED health AS DOUBLE
DIM pscore(6)
DIM pname(6) AS STRING
DIM I AS INTEGER
DIM SHARED shotimage AS LONG
DIM SHARED image1 AS LONG
DIM SHARED shooterimage AS LONG
REM =============================================
shotimage = _LOADIMAGE("shot.png")
image1 = _LOADIMAGE("spaceattacker2.png")
shooterimage = _LOADIMAGE("attacker.png")
REM =============================================
MAX_TIME% = 100
REM =============================================
rootpath$ = ENVIRON$("SYSTEMROOT")
fontfile$ = rootpath$ + "\Fonts\cour.ttf"
style$ = "monospace, italic, bold"
f& = _LOADFONT(fontfile$, 30, style$)
REM =============================================
100
COLOR 45
CLS
_FONT f&
LOCATE 4, 27
PRINT "highscore"
LOCATE 10, 27
PRINT "play game"
LOCATE 16, 27
PRINT "about game"
ch = 0
REM _FONT 16
DO
    DO
        IF _MOUSEX > 440 AND _MOUSEX < 670 THEN
            IF _MOUSEY > 80 AND _MOUSEY < 120 THEN
                IF _MOUSEBUTTON(1) THEN
                    ch = 1
                END IF
            ELSEIF _MOUSEY > 260 AND _MOUSEY < 300 THEN
                IF _MOUSEBUTTON(1) THEN
                    ch = 2
                END IF
            ELSEIF _MOUSEY > 440 AND _MOUSEY < 480 THEN
                IF _MOUSEBUTTON(1) THEN
                    ch = 3
                END IF
            END IF
        END IF
    LOOP WHILE _MOUSEINPUT
LOOP UNTIL ch <> 0
COLOR 42
SELECT CASE ch
    CASE 1
        CLS
        OPEN "hscores.txt" FOR INPUT AS #2
        INPUT #2, pscore(1)
        INPUT #2, pscore(2)
        INPUT #2, pscore(3)
        INPUT #2, pscore(4)
        INPUT #2, pscore(5)
        CLOSE #2
        OPEN "hnames.txt" FOR INPUT AS #1
        FOR I = 1 TO 5
            INPUT #1, pname(I)
        NEXT
        CLOSE #1
        FOR I = 1 TO 5
            PRINT pname(I); "  :"; pscore(I)
        NEXT I
        PRINT
        PRINT
        PRINT
        SLEEP
        GOTO 100
    CASE 2
        _FONT 16
        CLS
        shooter.x = 1
        timeleft = MAX_TIME%
        health = 100
        ammo = 100
        shooter.y = 240 - 45
        shotfired = 0
        oldt = TIMER
        score = 0
        tmInit2 = TIMER
        _SNDPLAY _SNDOPEN("introsound.wav", "sync,vol")
        DO
            _LIMIT 100
            PCOPY _DISPLAY, 1
            LINE (0, 35)-(1200, 35)
            LINE (0, 575)-(1200, 575)
            LOCATE 2
            IF timeleft <= 10 THEN
                IF timeleft MOD 2 = 0 THEN
                    COLOR 4
                    PRINT "Time Left :"; fnTimeLeft; " seconds"
                ELSE
                    COLOR 7
                    PRINT "Time Left :"; fnTimeLeft; " seconds"
                END IF
            ELSE
                PRINT "Time Left :"; fnTimeLeft; " seconds"
            END IF
            COLOR 7
            LOCATE 37
            PRINT "health  :"; health; "  "; "score  :"; score; "  "; "ammo  :"; ammo
            shooter
            fireshot
            attacker
            _PUTIMAGE (5, shooter.y), shooterimage
            IF INKEY$ = "e" THEN EXIT DO
            a = 0
            DO
                IF _MOUSEX < 1200 AND _MOUSEY < 600 AND _MOUSEX > 0 AND _MOUSEY > 0 THEN
                    IF _MOUSEBUTTON(2) THEN
                        DO
                            DO
                                IF _MOUSEBUTTON(1) THEN a = 1
                            LOOP WHILE _MOUSEINPUT
                        LOOP UNTIL a = 1
                    END IF
                END IF
            LOOP WHILE _MOUSEINPUT
            a = 0
            _DISPLAY
            PCOPY 1, _DISPLAY
            asd = 0
            FOR j = 1 TO 100
                FOR I = 1 TO 2
                    IF shot.exist(j, I) > 10 THEN asd = 1
                NEXT I
            NEXT j

        LOOP UNTIL health <= 1 OR (ammo = 0 AND asd = 0) OR fnTimeLeft < 0
        SLEEP 2
        CLS
        LOCATE 18, 60
        PRINT "score"; score
        LOCATE 19, 60
        PRINT "health= "; health
        LOCATE 20, 60
        PRINT "Ammo= "; ammo
        REM INPUT "", x
        OPEN "hscores.txt" FOR INPUT AS #2
        INPUT #2, pscore(1)
        INPUT #2, pscore(2)
        INPUT #2, pscore(3)
        INPUT #2, pscore(4)
        INPUT #2, pscore(5)
        CLOSE #2
        OPEN "hnames.txt" FOR INPUT AS #1
        FOR I = 1 TO 5
            INPUT #1, pname(I)
        NEXT
        CLOSE #1
        REM COMPARING AND REPLACING
        FOR I = 5 TO 1 STEP -1
            IF score >= pscore(I) AND score < pscore(I - 1) THEN
                LOCATE 23, 60
                INPUT "ENTER NAME   :", Name$
                FOR j = 5 TO I STEP -1
                    pscore(j + 1) = pscore(j)
                    pscore(j) = score
                    pname(j + 1) = pname(j)
                    pname(j) = Name$
                NEXT
                flag = 1
            END IF
            IF score >= pscore(I) AND I = 1 AND flag = 0 THEN
                LOCATE 23, 60
                INPUT "ENTER NAME   :", Name$
                FOR j = 5 TO I STEP -1
                    pscore(j + 1) = pscore(j)
                    pscore(j) = score
                    pname(j + 1) = pname(j)
                    pname(j) = Name$
                NEXT
            END IF
        NEXT
        flag = 0
        REM REWRITING IN THE FILE
        OPEN "hscores.txt" FOR OUTPUT AS #1
        FOR I = 1 TO 5
            WRITE #1, pscore(I)
        NEXT
        CLOSE #1
        OPEN "hnames.txt" FOR OUTPUT AS #1
        FOR I = 1 TO 5
            WRITE #1, pname(I)
        NEXT
        CLOSE #1
        INPUT "", c

        END
    CASE 3
        COLOR 70
        CLS
        PRINT "CREATED BY     : RAJARSHI BASU    !! RAJNIKANT OF CALCUTTA !! "
        PRINT "CODE WRITTEN IN QBASIC 64"
        PRINT
        PRINT
        PRINT
        PRINT "THERE CAN BE A MAXIMUM OF 10 ENEMY SHIPS ON THE SCREEN AT ONE TIME "
        PRINT "UP ARROW AND DOWN ARROW KEYS TO MOVE THE SHOOTER"
        PRINT "MAX AMMO          : 100"
        PRINT "MAX HEALTH        : 100"
        PRINT "MAX TIME          : 100 SECONDS"
        SLEEP
        GOTO 100
END SELECT
FUNCTION fnTimeLeft
IF (TIMER - tmInit2) >= 1 THEN
    tmInit2 = TIMER
    timeleft = timeleft - 1
END IF
fnTimeLeft = timeleft
END FUNCTION
SUB shooter
f.shooter.y = shooter.y
IF _KEYDOWN(CVI(CHR$(0) + CHR$(72))) AND shooter.y > 40 THEN
    shooter.y = shooter.y - 1
ELSEIF _KEYDOWN(CVI(CHR$(0) + CHR$(80))) AND shooter.y + 70 < 560 THEN
    shooter.y = shooter.y + 1
ELSE
    shooter.y = f.shooter.y
END IF
END SUB
SUB fireshot
IF INKEY$ = " " THEN
    FOR j = 1 TO 100
        IF shot.exist(j, 1) = 0 AND shot.exist(j, 2) = 0 THEN
            shot.y(j, 1) = shooter.y + 14
            shot.y(j, 2) = shooter.y + 54
            FOR i = 1 TO 2
                shot.exist(j, i) = 1
                shot.x(j, i) = 71
            NEXT
            ammo = ammo - 2
            oldt2 = TIMER
            a = 1
            _SNDPLAY _SNDOPEN("firesound.wav", "sync,vol")
            GOTO 100
        END IF
    NEXT
END IF
100
FOR j = 1 TO 100
    IF shot.exist(j, 1) = 1 OR shot.exist(j, 2) = 1 THEN
        FOR i = 1 TO 2
            IF shot.exist(j, i) = 0 THEN GOTO 30
            _PUTIMAGE (shot.x(j, i), shot.y(j, i)), shotimage
            shot.x(j, i) = shot.x(j, i) + 2
        30 NEXT
    END IF
NEXT
FOR j = 1 TO 100
    FOR i = 1 TO 2
        IF shot.x(j, i) >= 900 THEN
            shot.exist(j, i) = 0
        END IF
    NEXT
NEXT
END SUB
SUB attacker
FOR i = 1 TO 10
    ran = ((RND * 100) MOD 4) + 1
    IF oldt + ran < TIMER THEN
        IF attacker.x(i) = 0 AND attacker.y(i) = 0 AND shipexist(i) = 0 THEN
            90 attacker.y(i) = ((RND * 100 MOD 5) * 100) + ((RND * 100 MOD 5) * 10) + (RND * 100 MOD 5)
            IF attacker.y(i) < 50 THEN GOTO 90
            attacker.x(i) = 1099
            shipexist(i) = 1
            oldt = TIMER
            EXIT FOR
        END IF
    END IF
NEXT
FOR i = 1 TO 10
    IF shipexist(i) = 1 THEN
        attacker.x(i) = attacker.x(i) - 3
        _PUTIMAGE (attacker.x(i), attacker.y(i)), image1
    END IF
NEXT
FOR i = 1 TO 10
    IF attacker.x(i) < -90 THEN
        attacker.x(i) = 0
        attacker.y(i) = 0
        shipexist(i) = 0
    END IF
    FOR j = 1 TO 100
        IF shot.exist(j, 2) = 1 AND (shot.x(j, 2) + 20 >= attacker.x(i) AND (shot.y(j, 2) + 10 >= attacker.y(i) AND shot.y(j, 2) < attacker.y(i) + 100)) THEN
            score = score + 10
            attacker.x(i) = 0
            attacker.y(i) = 0
            shipexist(i) = 0
            shot.exist(j, 2) = 0
            _SNDPLAY _SNDOPEN("hit2sound.wav", "sync,vol")
        END IF
        IF shot.exist(j, 1) = 1 AND (shot.x(j, 1) + 20 >= attacker.x(i) AND (shot.y(j, 1) + 10 >= attacker.y(i) AND shot.y(j, 1) < attacker.y(i) + 100)) THEN
            score = score + 10
            attacker.x(i) = 0
            attacker.y(i) = 0
            shipexist(i) = 0
            shot.exist(j, 1) = 0
            _SNDPLAY _SNDOPEN("hit2sound.wav", "sync,vol")
        END IF
    NEXT
    IF (70 >= attacker.x(i)) AND ((shooter.y + 70 >= attacker.y(i) AND shooter.y <= attacker.y(i) + 100)) AND shipexist(i) = 1 THEN
        attacker.x(i) = 0
        attacker.y(i) = 0
        shipexist(i) = 0
        health = health - 10
        score = score + 5
        _SNDPLAY _SNDOPEN("hit2sound.wav", "sync,vol")
    END IF
NEXT
END SUB

