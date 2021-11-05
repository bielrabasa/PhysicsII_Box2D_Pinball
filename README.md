# PhysicsII_Box2D_Pinball

## A pinball group project created with Box2D


Pinball created by Roger Salas, Gerard Ramón & Biel Rabasa


# CONTROLS

## Game Controls

* *Left arrow key* - Left flipper
* *Right arrow key* - Right flipper
* *Down arrow key* - Plunger
* *R key* - Start game

## DEBUG 

* *F1* - Debug view
* *Left mouse button* - Mouse Joint (ball grab)
* *Number 1 key* - Spawn new ball

# SPECIAL STUFF

* Canon (17 points) - Shots the ball down
* Right sprinter - Speeds the ball
* Middle - Left bumper (8 points)
* Down - Left bumper (5 points)
* Down - Right bumper (5 points)
* Middle - Right bumper (7 points)
* Top - Right bumper (11 points)
* 3 bumper balls - Bounces the ball
* 10 balls (1 point) - Normal obstacles

## Combo 
* Touching the 3 bumper balls combo (69 points + extra live)


# DEVELOPMENT (solution to the problems we had)

### Tunneling:
The ball did not collide with the flippers sometimes, we fixed it by setting the ball in bullet.

### Bumper balls:
Bumpers did not make the ball bounce correctly, we fixed it by realising the coordinates of the ball object were not set in the center, but in the top-left corner.

### Sensor malfunction:
This bug is still happening in the release of the game, sensors only detect objects by one of the sides, we FUYM the result by separating all the sensors in the right part of the map by a bit.

### Mouse joint:
The mouse joint was very difficult to make as we figured out we had to update the target of the ball in each frame very late.


# Development

During the development of the game we have made sensors that make you bounce in a way that emulates bumpers. There are 5 of them distributed around the entire map.
Besides that, there is a cannon that propels the ball after a second. In the right zone we decided to make a tunnel to accelerate the ball when it passes through.
To fill the map and make it more reality look-like, we placed 3 large balls on top that make you bounce. If you touch the 3 active balls you activate a combo to give you an additional life.
Just below the large balls we decided to place a large number of small balls with a much lower bounce in order to reduce the speed of the ball as it passed through the middle of the map.
At the bottom there are the 2 flippers that we managed to make work extremely well without any type of bug or problem. Under the levers we place a sensor which destroys the ball and spawns another in the starting area.
To finish, we have the exit zone which gives a push to the ball according to the time you keep the key pressed. If you are lucky you can re-enter this area to help you make the combo easier.

# GitHub Link
https://github.com/bielrabasa/PhysicsII_Box2D_Pinball


# Members

[Biel Rabasa Galan](https://github.com/bielrabasa)

[Roger Salas Bernadó](https://github.com/Draquian)

[Gerard Josep Ramon Catasus](https://github.com/kramtron)


# License

This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. 
Check [LICENSE](LICENSE) for further details.
