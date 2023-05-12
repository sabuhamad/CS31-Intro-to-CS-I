// cyborgs.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order that you choose to tackle the rest of
// the functionality.  As you finish implementing each TODO: item, remove
// its TODO: comment; that makes it easier to find what you have left to do.
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;              // max number of rows in the arena
const int MAXCOLS = 20;              // max number of columns in the arena
const int MAXCYBORGS = 100;          // max number of cyborgs allowed
const int MAXCHANNELS = 3;           // max number of channels
const int INITIAL_CYBORG_HEALTH = 3; // initial cyborg health
const double WALL_DENSITY = 0.11;    // density of walls

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;
const int BADDIR = -1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Cyborg declaration.

class Cyborg
{
  public:
      // Constructor
    Cyborg(Arena* ap, int r, int c, int channel);

      // Accessors
    int  row() const;
    int  col() const;
    int  channel() const;
    bool isDead() const;

      // Mutators
    void forceMove(int dir);
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_channel;
    int    m_health;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string stand();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     cyborgCount() const;
    bool    hasWallAt(int r, int c) const;
    int     numberOfCyborgsAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void   placeWallAt(int r, int c);
    bool   addCyborg(int r, int c, int channel);
    bool   addPlayer(int r, int c);
    string moveCyborgs(int channel, int dir);

  private:
    bool    m_wallGrid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Cyborg* m_cyborgs[MAXCYBORGS];
    int     m_nCyborgs;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nCyborgs);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
    string takeCyborgsTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char ch);
int randInt(int lowest, int highest);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Cyborg implementation
///////////////////////////////////////////////////////////////////////////

Cyborg::Cyborg(Arena* ap, int r, int c, int channel)
{
    if (ap == nullptr)
    {
        cout << "***** A cyborg must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Cyborg created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    if (channel < 1  ||  channel > MAXCHANNELS)
    {
        cout << "***** Cyborg created with invalid channel " << channel << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_channel = channel;
    m_health = INITIAL_CYBORG_HEALTH;
}

int Cyborg::row() const
{
    // Return what row the cyborg is at.
     
    return m_row;
}

int Cyborg::col() const
{
      // Return what column the cyborg is at.
       
    return m_col;
}

int Cyborg::channel() const
{
      // Return what channel the cyborg is listening on.
       
    return m_channel;
}

bool Cyborg::isDead() const
{
      // Return whether the cyborg is dead.
       
    if(m_health > 0)
        return false;
    return true;  // This implementation compiles, but is incorrect
}

void Cyborg::forceMove(int dir)
{
      // Move the cyborg in the indicated direction, if possible.
      // Suffer one unit of damage if moving fails.
    if(!isDead())
    {
        if(attemptMove(*m_arena, dir, m_row, m_col))
        {

        }
        else
        {
            m_health--;
        }
    }
        
}

void Cyborg::move()
{
      // Attempt to move in a random direction; if cannot move, don't move
    if (!isDead())
        attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col);
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
      // Return what row the player is at.
       
    return m_row;
}

int Player::col() const
{
      // Return what column the player is at.
    return m_col;
}

string Player::stand()
{
    return "Player stands.";
}

string Player::move(int dir)
{
      //        Attempt to move the player one step in the indicated
      //        direction.  If this fails,
      //        return "Player couldn't move; player stands."
      //        A player who moves onto a cyborg dies, and this
      //        returns "Player walked into a cyborg and died."
      //        Otherwise, return one of "Player moved north.",
      //        "Player moved east.", "Player moved south.", or
      //        "Player moved west."
    if (attemptMove(*m_arena, dir, m_row, m_col))
    {
        if(m_arena->numberOfCyborgsAt(m_row, m_col) > 0)
        {
            setDead();
            return "Player walked into a cyborg and died.";
        }
        else
        {
            switch(dir)
            {
                case NORTH:
                    return "Player moved north.";
                    break;
                case EAST:
                    return "Player moved east.";
                    break;
                case WEST:
                    return "Player moved west.";
                    break;
                case SOUTH:
                    return "Player moved south.";
                    break;
            }
        }
    }
    else
    {
    return "Player couldn't move; player stands.";
    }
    return "";
}

bool Player::isDead() const
{
      // Return whether the player is dead.
    if(m_dead)
        return true;
    return false;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nCyborgs = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            m_wallGrid[r-1][c-1] = false;
}

Arena::~Arena()
{
    // Release the player and all remaining dynamically allocated cyborgs.
    for(int i = 0; i < m_nCyborgs; i++)
    {
        delete m_cyborgs[i];
    }
    delete m_player;
}

int Arena::rows() const
{
      // Return the number of rows in the arena.
    return m_rows;
}

int Arena::cols() const
{
      // return the number of columns in the arena
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::cyborgCount() const
{
      // return the number of cyborgs in the arena
    return m_nCyborgs;
}

bool Arena::hasWallAt(int r, int c) const
{
    checkPos(r, c, "Arena::hasWallAt");
    return m_wallGrid[r-1][c-1];
}

int Arena::numberOfCyborgsAt(int r, int c) const
{
      // Return the number of cyborgs at row r, column c.
    int number = 0;
    for(int i = 0; i < m_nCyborgs; i++)
    {
        if(!(m_cyborgs[i]->isDead()))
        {
           if( m_cyborgs[i]->row() == r && m_cyborgs[i]->col() == c)
           {
               number++;
           }
        }
    }
    return number;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (wall)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (hasWallAt(r, c) ? '*' : '.');

      // Indicate cyborg positions by their channels.  If more than one cyborg
      // occupies a cell, show just one (any one will do).

      //        For each cyborg, set the grid cell to the digit character
      //        representing its channel number.
    
    for(int i = 0; i < m_nCyborgs; i++)
    {
        char c = m_cyborgs[i]->channel() + 48 ;
        displayGrid[m_cyborgs[i]->row() - 1 ][m_cyborgs[i]->col() - 1] = (m_cyborgs[i]->isDead() ? '.' : c);
    }
   

      // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, cyborg, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << cyborgCount() << " cyborgs remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::placeWallAt(int r, int c)
{
    checkPos(r, c, "Arena::placeWallAt");
    m_wallGrid[r-1][c-1] = true;
}

bool Arena::addCyborg(int r, int c, int channel)
{
    if (! isPosInBounds(r, c)  ||  hasWallAt(r, c))
        return false;
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (channel < 1  ||  channel > MAXCHANNELS)
        return false;
    if (m_nCyborgs == MAXCYBORGS)
        return false;
    m_cyborgs[m_nCyborgs] = new Cyborg(this, r, c, channel);
    m_nCyborgs++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (m_player != nullptr  ||  ! isPosInBounds(r, c)  ||  hasWallAt(r, c))
        return false;
    if (numberOfCyborgsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

string Arena::moveCyborgs(int channel, int dir)
{
      // Cyborgs on the channel will respond with probability 1/2
    bool willRespond = (randInt(0, 1) == 0);

      // Move all cyborgs
    int nCyborgsOriginally = m_nCyborgs;

      //        Move each cyborg.  Force cyborgs listening on the channel to
      //        move in the indicated direction if willRespond is true.  If
      //        willRespond is false, or if the cyborg is listening on a
      //        different channel, it just moves.  Mark the player as dead
      //        if necessary.  Release any dead dynamically allocated cyborgs.
    for(int i = 0; i < m_nCyborgs; i++)
    {
        if(willRespond && m_cyborgs[i]->channel() == channel)
        {
                m_cyborgs[i]->forceMove(dir);
                if(m_cyborgs[i]->isDead())
                {
                    Cyborg* tempCyborg = m_cyborgs[i];
                    m_cyborgs[i] =  m_cyborgs[m_nCyborgs - 1];
                    m_cyborgs[m_nCyborgs - 1] = tempCyborg;
                    delete m_cyborgs[m_nCyborgs - 1];
                    m_nCyborgs--;
                    i--;
                }
                else if(m_player->row() == m_cyborgs[i]->row() && m_player->col() == m_cyborgs[i]->col())
                {
                    m_player->setDead();
                }
        }
        else
        {
            m_cyborgs[i]->move();
            if(m_player->row() == m_cyborgs[i]->row() && m_player->col() == m_cyborgs[i]->col())
            {
                m_player->setDead();            }
        }
    }
    

    if (m_nCyborgs < nCyborgsOriginally)
        return "Some cyborgs have been destroyed.";
    else
        return "No cyborgs were destroyed.";
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nCyborgs)
{
    if (nCyborgs < 0  ||  nCyborgs > MAXCYBORGS)
    {
        cout << "***** Game created with invalid number of cyborgs:  "
             << nCyborgs << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nCyborgs - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nCyborgs << " cyborgs!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add some walls in WALL_DENSITY of the empty spots
    assert(WALL_DENSITY >= 0  &&  WALL_DENSITY <= 1);
    int nWalls = static_cast<int>(WALL_DENSITY * nEmpty);
    while (nWalls > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c))
            continue;
        m_arena->placeWallAt(r, c);
        nWalls--;
    }

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->hasWallAt(rPlayer, cPlayer));
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with cyborgs
    while (nCyborgs > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c)  ||  (r == rPlayer && c == cPlayer))
            continue;
        m_arena->addCyborg(r, c, randInt(1, MAXCHANNELS));
        nCyborgs--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->stand();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->stand();
            else
            {
                dir = decodeDirection(tolower(playerMove[0]));
                if (dir != BADDIR)
                    return player->move(dir);
            }
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

string Game::takeCyborgsTurn()
{
    for (;;)
    {
        cout << "Broadcast (e.g., 2n): ";
        string broadcast;
        getline(cin, broadcast);
        if (broadcast.size() != 2)
        {
            cout << "You must specify a channel followed by a direction." << endl;
            continue;
        }
        else if (broadcast[0] < '1'  ||  broadcast[0] > '0'+MAXCHANNELS)
            cout << "Channel must be a digit in the range 1 through "
                 << MAXCHANNELS << "." << endl;
        else
        {
            int dir = decodeDirection(tolower(broadcast[1]));
            if (dir == BADDIR)
                cout << "Direction must be n, e, s, or w." << endl;
            else
                return m_arena->moveCyborgs(broadcast[0]-'0', dir);
        }
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->cyborgCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        msg = takeCyborgsTurn();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'n':  return NORTH;
      case 'e':  return EAST;
      case 's':  return SOUTH;
      case 'w':  return WEST;
    }
    return BADDIR;  // bad argument passed in!
}

  // Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would hit a wall or run off the edge of the
  // arena.  Otherwise, update r and c to the position resulting from the
  // move and return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
      // Implement this function.
       
    switch(dir)
    {
        case NORTH:
            if((r-1 < 1) || a.hasWallAt(r - 1,c))
                return false;
            r--;
            return true;
            break;
        case EAST:
            if((c+1 > a.cols()) || a.hasWallAt(r,c + 1))
                return false;
            c++;
            return true;
            break;
        case SOUTH:
            if((r + 1 > a.rows()) || a.hasWallAt(r + 1,c) )
                return false;
            r++;
            return true;
            break;
        case WEST:
            if((c-1 < 1) || a.hasWallAt(r,c - 1))
                return false;
            c--;
            return true;
            break;
    }
    return false;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should stand; otherwise, bestDir is
  // set to the recommended direction to move.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
      // TODO:  Replace this implementation:
      // Delete the following line and replace it with a better strategy than
      // to always recommend standing.
    int tempBest = -1;
    int leastCyborgs = a.numberOfCyborgsAt(r+1, c) + a.numberOfCyborgsAt(r-1, c) + a.numberOfCyborgsAt(r, c+1) + a.numberOfCyborgsAt(r, c-1);
    int cyborgsAround = 0;
    
    if(!((r-1 < 1) || (a.hasWallAt(r - 1,c)) || a.numberOfCyborgsAt(r-1, c) > 0))
    {
       if(r - 2 < 1)
       {
           cyborgsAround = a.numberOfCyborgsAt(r-1, c+1) + a.numberOfCyborgsAt(r-1, c-1);
           if(cyborgsAround < leastCyborgs)
           {
               leastCyborgs = cyborgsAround;
               tempBest = NORTH;
           }
       }
       else
       {
           cyborgsAround = a.numberOfCyborgsAt(r-1, c+1) + a.numberOfCyborgsAt(r-1, c-1) + a.numberOfCyborgsAt(r-2, c);
           if(cyborgsAround < leastCyborgs)
           {
               leastCyborgs = cyborgsAround;
               tempBest = NORTH;
           }
       }
    }
    if(!((c+1 > a.cols()) || a.hasWallAt(r,c + 1) || a.numberOfCyborgsAt(r, c+1) > 0))
    {
        if(c + 2 > a.cols())
        {
            cyborgsAround = a.numberOfCyborgsAt(r-1, c+1) + a.numberOfCyborgsAt(r+1, c+1);
            if(cyborgsAround < leastCyborgs)
            {
                leastCyborgs = cyborgsAround;
                tempBest = EAST;
            }
        }
        else
        {
            cyborgsAround = a.numberOfCyborgsAt(r-1, c+1) + a.numberOfCyborgsAt(r+1, c+1) + a.numberOfCyborgsAt(r, c + 2);
            if(cyborgsAround < leastCyborgs)
            {
                leastCyborgs = cyborgsAround;
                tempBest = EAST;
            }
        }
    }
    if(!((r + 1 > a.rows()) ||a.hasWallAt(r + 1,c) || a.numberOfCyborgsAt(r+1, c) > 0))
    {
        if(r+2 > a.rows())
        {
            cyborgsAround = a.numberOfCyborgsAt(r+1, c+1) + a.numberOfCyborgsAt(r+1, c-1);
            if(cyborgsAround < leastCyborgs)
            {
                leastCyborgs = cyborgsAround;
                tempBest = SOUTH;
            }
        }
        else
        {
            cyborgsAround = a.numberOfCyborgsAt(r+1, c+1) + a.numberOfCyborgsAt(r+1, c-1) + a.numberOfCyborgsAt(r + 2, c);
            if(cyborgsAround < leastCyborgs)
            {
                leastCyborgs = cyborgsAround;
                tempBest = SOUTH;
            }
        }
    }
    if(!((c-1 < 1) || a.hasWallAt(r,c - 1) || a.numberOfCyborgsAt(r, c-1) > 0))
    {
        if(c - 2 > 1)
        {
            cyborgsAround = a.numberOfCyborgsAt(r-1, c-1) + a.numberOfCyborgsAt(r+1, c-1);
            if(cyborgsAround < leastCyborgs)
            {
                leastCyborgs = cyborgsAround;
                tempBest = WEST;
            }
        }
        else
        {
            cyborgsAround = a.numberOfCyborgsAt(r-1, c-1) + a.numberOfCyborgsAt(r+1, c-1) + a.numberOfCyborgsAt(r, c - 2);
            if(cyborgsAround < leastCyborgs)
            {
                leastCyborgs = cyborgsAround;
                tempBest = WEST;
            }
        }
    }
    if(tempBest == -1)
    {
        return false;
    }
    bestDir = tempBest;
    return true;

      // Your replacement implementation should do something intelligent.
      // For example, if you're standing next to four cyborgs, and moving
      // north would put you next to two cyborgs, but moving east would put
      // you next to none, moving east is a safer choice than standing or
      // moving north.
}
///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////
int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    //Game g(12, 20, 20);

      // Play the game
    //g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
