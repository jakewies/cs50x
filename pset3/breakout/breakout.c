// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define WINDOW_H 600
#define WINDOW_W 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// height and width of bricks
#define BRICK_H 7.5
#define BRICK_W 35

// radius of ball in pixels
#define RADIUS 5

// height and width of game's paddle
#define PADDLE_H 5
#define PADDLE_W 50

// location of paddle
#define PADDLE_X 175
#define PADDLE_Y 502.5

// lives
#define LIVES 3

//prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window, string message);
void updateScoreboard(GWindow window, GLabel label, int points, int bricks, int lives);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WINDOW_W, WINDOW_H);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window, "0");

    // ball speed
    double x_velo = drand48() * 3;
    double y_velo = drand48() * 3;

    // keep playing until game is over
    while(lives > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = PADDLE_Y;
                setLocation(paddle, x, y);
            }
        }

        // ball mechanics
        move(ball, x_velo, y_velo);
        pause(7.5);

        // check if ball hits right wall and reverse if true
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_velo = -x_velo;
        }
        // check if ball hits left wall and reverse if true
        else if (getX(ball) <= 0)
        {
            x_velo = -x_velo;
        }
        // check if ball hits top wall and reverse if true
        else if (getY(ball) <= 0)
        {
            y_velo = -y_velo;
        }
        // check if ball hits bottom. start over/subtract life
        else if (getY(ball) + getHeight(ball)  >= getHeight(window))
        {
            lives--;
                
            if (lives == 0)
            {
                updateScoreboard(window, label, points, bricks, lives);
                waitForClick();
                
                // game over
                closeGWindow(window);
                return 0; 
            }            
            else
            {
                setLocation(ball, (WINDOW_W / 2) - RADIUS, (WINDOW_H / 2) - RADIUS);
                setLocation(paddle, PADDLE_X, PADDLE_Y);
                waitForClick();
            }
        }
 
        // check for ball collision
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            // if ball hits rectangle
            if (strcmp(getType(object), "GRect") == 0)
            {
                // check if paddle
                if (object == paddle)
                {
                    y_velo = -y_velo;
                }
                // if not paddle, remove brick/add point/reverse ball
                else
                {
                    removeGWindow(window, object);
                    
                    // if no more bricks, user wins
                    if (bricks == 0)
                    {
                        points++;
                        removeGWindow(window, ball);
                        updateScoreboard(window, label, points, bricks, lives);
                        waitForClick();
                        
                        // game over
                        closeGWindow(window);
                        return 0; 
                    }
                    else
                    {
                        y_velo = -y_velo;
                        points++;  
                        bricks--;
                        updateScoreboard(window, label, points, bricks, lives);
                    }
                }
            }
        }
    }    
    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // set initial brick y-coordinate
    int y_coord = 15;

    for (int i = 0; i < ROWS; i++)
    {
        // reset x coordinate and label row
        int x_coord = 2;
        int row = i;

        // Create 10 columns of bricks
        for (int j = 0; j < COLS; j++)
        {
            // create a brick
            GRect brick = newGRect(x_coord, y_coord, BRICK_W, BRICK_H);
            setFilled(brick, true);

            // hexadecimal color values for different rows
            switch(row)
            {
                case 0 :
                    setColor(brick, "#0099ff");
                    break;
                case 1 :
                    setColor(brick, "#58bcff");
                    break;
                case 2 :
                    setColor(brick, "#92d3ff");
                    break;
                case 3 :
                    setColor(brick, "#b0dfff");
                    break;
                case 4 :
                    setColor(brick, "#c5e8ff");
                    break;
                default :
                    setColor(brick, "BLACK");
                    break;
            }

            add(window, brick);

            // increment x coordinate for column spacing
            x_coord += 40;
        }
        // increment y coordinate for row spacing
        y_coord += 12;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x = (WINDOW_W / 2) - RADIUS;
    int y = (WINDOW_H / 2) - RADIUS;
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "#696969");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Create a paddle
    GRect paddle = newGRect(PADDLE_X, PADDLE_Y, PADDLE_W, PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle, "#323232");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window, string message)
{
    GLabel label = newGLabel(message);
    setFont(label, "Helvetica-24");
    setColor(label, "#c1c1c1");

    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points, int bricks, int lives)
{    
    if (bricks == 0)
    {
        setLabel(label, "You Win");
    }
    else if (lives == 0)
    {
        setLabel(label, "Game Over");
    }
    else 
    {
        // update label
        char s[12];
        sprintf(s, "%i", points);
        setLabel(label, s);
    }
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}


/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
       
    // no collision
    return NULL;
}
