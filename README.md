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
