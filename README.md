# TOAST (SA:MP)
 _**T**extured **O**bjects **A**s **S**pri**T**es_
 
https://streamable.com/psabc

As of this moment, the code is very cluttered and hardcoded, therefore it is of no use to anyone outside of being a proof of concept.

I will turn this into a fully featured include whenever I have the time. Thank you for your patience.
Contributions/suggestions/issue reports are all welcome!

## About

I made this initially for Riddick and his The Last of Us SA-MP gamemode to demonstrate what I had in mind as a replacement for 3D Text Labels.
Figured I should expand on it and make it available to everyone.

## Idea

1. Create an area with the streamer. 
2. Once a player enters - display an object that has `SetObjectMaterialText` used on it to display a wingding/webding font symbol. 
3. Point the object towards the player's camera to make it look 2D. 
4. Once a player leaves the area - destroy the object. 

Bonuses: animation for popping up, making the sprite disappear, have the sprite track different things other than the player cam, different design. Support for this https://www.youtube.com/watch?v=zSzb6dCBZ-g and similar types prompts.

## Thanks to

Riddick - for having an issue that gave birth to this idea

RyDeR\` - For doing the calculations to rotate the object towards the player's camera, so that I don't have to.
