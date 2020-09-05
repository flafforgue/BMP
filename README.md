# BMP
Sample Arduino rythm machine 
a little more than simple metronome

sounds are stored on sd card in the mp3 DFPlayer Mini module.
actualy there are only 4 sound possible :
1 Kick
2 HiHat
3 Snare
4 Ride
extention is possible by repeating transistors module and connect to ADKey2,
for this step 4 is enougth for me.

new sample playing is not possible until current is not finished. so when rythm is too quick some notes may be ommited.

each patern may have up to 48 notes.
number of note of patern is defined by constant NTxx where xx is patern number

by using space divider constant ( DVxx) you can define number of beats in a measure for example all this notations have same tempo :
1 0 0 0 ... with DVxx = 4
1 0 1 0 ... with DVxx = 2
1 1 1 1 ... with DVxx = 1

