# MiniYellowBot
Small yellow robotic arm controlled by arduino &amp; motor drivers. solo project made in club at school.


The MiniYellowBot project was a solo project I worked on during my time as member of the [Redacted] at [Redacted].
Essentially, I took a prebuilt robotic arm (initially controlled by a wired remote) and rewired it so that it was controlled by a gyroscopic Wii "Nunchuk" remote controller.
To accomplish this, arduino development board was used in order to read in signals generated from the new remote as it accelerates along various axies, and re-transmit that signal (using PWM) an H-Bridge, which drove the motors in specific directions, thus controlling the robotic arm.
The coding part was very simple due to the existance of various libraries that already existed for the Nunchuk remote.
Also included, are the resources that I referenced when reconfiguring the wires on the remotes, and utilizing the L298N H-bridge motor driver.

-Gary Smith
