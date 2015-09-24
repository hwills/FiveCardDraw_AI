#AI Five Card Draw

Authors: Hunter Wills, Tung Tran (t.t.tran@wustl.edu)

This program was created with Visual Studio 2013 and C++11 to make a command line verion of Five Card Draw. This includes an AI to play the game. AI players are represented with a * after their name.

EXAMPLE TESTS:
<------------ AI LEAVING TABLE After Loss (No rank choice)------------------->

./FiveCardDraw FiveCardDraw alex* hunter



The round is about to begin! Prepare to play some Five Card Draw!



CURRENT PLAYER: hunter

YOUR HAND:

3S 9H JC QH KS

Which cards do you want to discard?

0



AI Player Taking Turn: alex

AI PLAYER'S HAND:

3C 6S 8C 9C QD



Here is what each player has after drawing their brand new CARDS!

hunter

9H JC QH QS KS

alex

9C 9D JH QD KD



The round has come to a close here are the post round stats:

hunter 8 8

9H JC QH QS KS

alex 7 40

9C 9D JH QD KD

alex is leaving the table.

<------------ AI STAYING AT TABLE After Win (pair choice)--------------->

./FiveCardDraw FiveCardDraw jack* sam



The round is about to begin! Prepare to play some Five Card Draw!



CURRENT PLAYER: sam

YOUR HAND:

2D 6H 9D 10D JC

Which cards do you want to discard?

0 1



AI Player Taking Turn: jack

AI PLAYER'S HAND:

4C 4H 5C 6S 9S



Here is what each player has after drawing their brand new CARDS!

sam

3C 5H 9D 10D JC

jack

4C 4H 7S JH QD



The round has come to a close here are the post round stats:

jack 1 1

4C 4H 7S JH QD

sam 0 1

3C 5H 9D 10D JC

Anybody wanna call it quits?

<------------ Many AI making a variety of choices--------------->


./FiveCardDraw FiveCardDraw jack* sam* frank* david* sarah* michael* paulie*



The round is about to begin! Prepare to play some Five Card Draw!



AI Player Taking Turn: sam

AI PLAYER'S HAND:

2C 4H 5S 10S KC



AI Player Taking Turn: frank

AI PLAYER'S HAND:

2D 3D 5D 8H 10C



AI Player Taking Turn: david

AI PLAYER'S HAND:

4S 6D 6H JD KD



AI Player Taking Turn: sarah

AI PLAYER'S HAND:

3H 5H 7S 8C 8S



AI Player Taking Turn: michael

AI PLAYER'S HAND:

2H 9D QH KH AC



AI Player Taking Turn: paulie

AI PLAYER'S HAND:

3S 6C 9S JH QS



AI Player Taking Turn: jack

AI PLAYER'S HAND:

3C 7C 7D 10H AH



Here is what each player has after drawing their brand new CARDS!

sam

6S 7H 10S QC KC

frank

2S 8D 8H 10C 10D

david

4C 6D 6H JC JS

sarah

8C 8S 9H QD KS

michael

4D 5C 9C AC AD

paulie

7S JD JH QS AS

jack

7C 7D KD KH AH



The round has come to a close here are the post round stats:

jack 1 2

7C 7D KD KH AH

david 0 1

4C 6D 6H JC JS

frank 0 1

2S 8D 8H 10C 10D

michael 0 1

4D 5C 9C AC AD

paulie 0 1

7S JD JH QS AS

sarah 0 1

8C 8S 9H QD KS

sam 0 1

6S 7H 10S QC KC

david is leaving the table.

paulie is leaving the table.

sam is leaving the table.

Anybody wanna call it quits?





#Trials: we have tested our program with a lot of trials, and we have no known bugs.



**test_1: normal game, 1 round:

./FiveCardDraw FiveCardDraw hunter alex nana batman



The round is about to begin! Prepare to play some Five Card Draw!



CURRENT PLAYER: alex

YOUR HAND:

4S 9D KH AD AS

Which cards do you want to discard?

0 1



CURRENT PLAYER: nana

YOUR HAND:

6S 10S JD QC QS

Which cards do you want to discard?

0 1 2



CURRENT PLAYER: batman

YOUR HAND:

2H 4D 6C JC KC

Which cards do you want to discard?

0 1



CURRENT PLAYER: hunter

YOUR HAND:

2C 4H 5D 7H KD

Which cards do you want to discard?

2 3 4



Here is what each player has after drawing their brand new CARDS!

alex

9S 10D KH AD AS

nana

3D 3S 5H QC QS

batman

6C 9H 10H JC KC

hunter

2C 3C 4H 8S AH



The round has come to a close here are the post round stats:

nana 1 0

3D 3S 5H QC QS

alex 0 1

9S 10D KH AD AS

hunter 0 1

2C 3C 4H 8S AH

batman 0 1

6C 9H 10H JC KC

Anybody wanna call it quits?

alex hunter nana

Anybody wanna call it quits?

no

Anybody wanna join?

no

------------------------------------------------------------

file output:

file alex:

alex

0

1

file hunter:

hunter

0

1

file nana:

nana

1

0

-------------------------------------------------------------



**test_2: normal game, 2 rounds
./FiveCardDraw FiveCardDraw hunter alex



The round is about to begin! Prepare to play some Five Card Draw!



CURRENT PLAYER: alex

YOUR HAND:

3S 6C 8H AC AH

Which cards do you want to discard?

0 1 2



CURRENT PLAYER: hunter

YOUR HAND:

4C 4H 8C 9H KS

Which cards do you want to discard?

2 3



Here is what each player has after drawing their brand new CARDS!

alex

2S 4D 8S AC AH

hunter

3C 4C 4H 5C KS



The round has come to a close here are the post round stats:

alex 1 1

2S 4D 8S AC AH

hunter 0 2

3C 4C 4H 5C KS

Anybody wanna call it quits?

no

Anybody wanna join?

no



The round is about to begin! Prepare to play some Five Card Draw!



CURRENT PLAYER: hunter

YOUR HAND:

4C 4H 5C 9C 9S

Which cards do you want to discard?

2



CURRENT PLAYER: alex

YOUR HAND:

4D 10S JC AC AD

Which cards do you want to discard?

0 1



Here is what each player has after drawing their brand new CARDS!

hunter

4C 4H 8S 9C 9S

alex

10C JC AC AD AS



The round has come to a close here are the post round stats:

alex 2 1

10C JC AC AD AS

hunter 0 3

4C 4H 8S 9C 9S

Anybody wanna call it quits?

alex hunter

Anybody wanna call it quits?

no

Anybody wanna join?

no

-------------------------------------------------------------

file alex:

alex

2

1

file hunter: 

hunter

0

3

file nana:

nana

1

0

---------------------------------------------------------------





**test_3: too many players

./FiveCardDraw FiveCardDraw 1 2 3 4 5 6 7 8 9 10 11



The round is about to begin! Prepare to play some Five Card Draw!

FiveCardDraw: Woah there buddy, we need more cards!



**test_4: not enough arguments

./FiveCardDraw 
FiveCardDraw: Not enough arguments! Please supply the game name and at least two players (different names)



**test_5: duplicate names

./FiveCardDraw FiveCardDraw alex alex

FiveCardDraw: There is a player already playing, dude!



**test_6: unknown game

./FiveCardDraw holdem alex hunter

FiveCardDraw: I have no idea what kind of game you are trying to play, but I know FiveCardDraw, so we should do that.
