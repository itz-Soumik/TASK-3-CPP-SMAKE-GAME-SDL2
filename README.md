# TASK-3-CPP-SNAKE-GAME-SDL2

COMPANY: CODTECH IT SOLUTIONS

NAME: SOUMIK SAHA

INTERN ID: CTO4DN437

DOMAIN: C++ PROGRAMMING 

DURATION: 4 WEEKS

MENTOR: NEELA SANTOSH

DESCRIPTION OF THE TASK: 
This project is a modern recreation of the classic Snake Game, developed using the Simple DirectMedia Layer (SDL) library along with its extensions SDL_ttf (for font rendering) and SDL_mixer (for sound effects). Designed in C++, this interactive game runs in a graphical window and provides a responsive, real-time gameplay experience.

Technologies Used:
(i) C++: Core programming language used for logic and structure.

(ii) SDL2: Handles window creation, rendering, and event processing.

(iii) SDL_ttf: Renders game score using TrueType fonts.

(iv) SDL_mixer: Adds audio features including eating and game-over sounds.

Key Features:
(i) Interactive Gameplay:

The player controls a snake that moves around the screen, eating food to grow longer.

Arrow keys are used for movement in four directions (UP, DOWN, LEFT, RIGHT).

(ii) Food Mechanics:

Food appears at random locations.

When the snake eats the food, it grows in length, score increases, and speed accelerates—making the game progressively harder.

(iii) Collision Detection:

The game ends if the snake hits the wall or collides with itself.

This is handled through proper boundary and self-collision checks.

(iv) Audio Feedback:

Eating food triggers a sound (eat.wav).

Crashing plays a game-over sound (game_over.wav), enhancing the gameplay experience.

(v) Score Display:

Real-time score is displayed on screen using a TrueType font.

This is dynamically updated as the player collects food.

(vi) Graphics:

Smooth rendering using SDL with colored blocks representing the snake and food.

Consistent game visuals with a dark background and vibrant elements.

(vii) Speed Scaling:

The snake's speed increases each time it eats food, controlled via a timing mechanism using SDL_GetTicks() and SDL_Delay().



